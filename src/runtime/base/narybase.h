/**
 * Copyright FLWOR Foundation
 *
 * Author: David Graf (david.graf@28msec.com)
 */

#ifndef XQP_NARYBASE_H
#define XQP_NARYBASE_H

#include "runtime/base/iterator.h"

namespace xqp
{
	/**
	 * Superclass for all iterators which have n child iterators 
	 * and no additional state variables.
	 */
	template <class IterType>
	class NaryBaseIterator : public Batcher<IterType>
	{
		protected:
			std::vector<PlanIter_t> theChildren;

		public:
			NaryBaseIterator ( const yy::location& loc, std::vector<PlanIter_t>& args );
			virtual ~NaryBaseIterator();

			void resetImpl ( PlanState& planState );
			void releaseResourcesImpl ( PlanState& planState );

			virtual int32_t getStateSize();
			virtual int32_t getStateSizeOfSubtree();
			virtual void setOffset ( PlanState& planState, int32_t& offset );
      
      virtual std::ostream& _show ( std::ostream& os ) const;
	}; /* class BinaryBaseIterator */

	/* begin class NaryBaseIterator */
	template <class IterType>
	NaryBaseIterator<IterType>::NaryBaseIterator (
	    const yy::location& loc,
	    std::vector<PlanIter_t>& args )
			:
			Batcher<IterType> ( loc ), theChildren ( args )
	{
	}


	template <class IterType>
	NaryBaseIterator<IterType>::~NaryBaseIterator()
	{
	}


	template <class IterType>
	void
	NaryBaseIterator<IterType>::resetImpl ( PlanState& planState )
	{
		PlanIterator::PlanIteratorState* state;
		GET_STATE ( PlanIterator::PlanIteratorState, state, planState );
		state->reset();

		std::vector<PlanIter_t>::iterator iter = theChildren.begin();
		for ( ; iter != theChildren.end(); ++iter )
		{
			this->resetChild ( *iter, planState );
		}
	}


	template <class IterType>
	void
	NaryBaseIterator<IterType>::releaseResourcesImpl ( PlanState& planState )
	{
		std::vector<PlanIter_t>::iterator iter = theChildren.begin();
		for ( ; iter != theChildren.end(); ++iter )
		{
			this->releaseChildResources ( *iter, planState );
		}
	}


	template <class IterType>
	int32_t
	NaryBaseIterator<IterType>::getStateSize()
	{
		return sizeof ( PlanIterator::PlanIteratorState );
	}


	template <class IterType>
	int32_t
	NaryBaseIterator<IterType>::getStateSizeOfSubtree()
	{
		int32_t size = 0;

		std::vector<PlanIter_t>::const_iterator iter = theChildren.begin();
		for ( ; iter != theChildren.end(); ++iter )
		{
			size += ( *iter )->getStateSizeOfSubtree();
		}

		return this->getStateSize() + size;
	}


	template <class IterType>
	void
	NaryBaseIterator<IterType>::setOffset (
	    PlanState& planState,
	    int32_t& offset )
	{
		this->stateOffset = offset;
		offset += this->getStateSize();

		std::vector<PlanIter_t>::iterator iter = theChildren.begin();
		for ( ; iter != theChildren.end(); ++iter )
		{
			( *iter )->setOffset ( planState, offset );
		}
	}
  
  template <class IterType>
  std::ostream&
  NaryBaseIterator<IterType>::_show ( std::ostream& os ) const
  {
    for (
      std::vector<PlanIter_t>::const_iterator lIter = theChildren.begin();
      lIter != theChildren.end();
      ++lIter
    ) 
    {
      (*lIter)->show(os);
    }
    return os;
  }
	/* end class NaryBaseIterator */
} /* namespace xqp */

#endif /* XQP_NARYBASE_H */
