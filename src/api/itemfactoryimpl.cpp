/*
 * Copyright 2006-2008 The FLWOR Foundation.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <zorba/item.h>
#include <boost/cast.hpp>
#include "errors/errors.h"
#include "api/itemfactoryimpl.h"

#include "zorbatypes/duration.h"
#include "system/globalenv.h"
#include "store/api/item_factory.h"
#include "api/unmarshaller.h"

#include "store/api/item.h"


namespace zorba {
  
  ItemFactoryImpl*
  ItemFactoryImpl::getInstance()
  {
    static ItemFactoryImpl theInstance;
    return &theInstance;
  }

  ItemFactoryImpl::ItemFactoryImpl()
  {
    theItemFactory = GENV_ITEMFACTORY;
  }

  ItemFactoryImpl::~ItemFactoryImpl() {}


  Item
  ItemFactoryImpl::createString(const String& aString)
  {
    xqpStringStore_t lString = Unmarshaller::getInternalString(aString);

    store::Item_t lItem;
    lItem = theItemFactory->createString(lString);

    return &*lItem;
  }

  Item
  ItemFactoryImpl::createAnyURI(const String& aURI)
  {
    xqpStringStore_t lString = Unmarshaller::getInternalString(aURI);

    store::Item_t lItem;
    lItem = theItemFactory->createAnyURI(lString);

    return &*lItem;
  }

  Item
  ItemFactoryImpl::createDate( const String& aDateValue )
  {
    xqpStringStore* lString = Unmarshaller::getInternalString( aDateValue );

    store::Item_t lItem;
    lItem = theItemFactory->createDate( lString );

    return &*lItem;
  }

  Item
  ItemFactoryImpl::createDate (
      short aYear,
      short aMonth,
      short aDay )
  {
    store::Item_t lItem;
    lItem = theItemFactory->createDate( aYear, aMonth, aDay );

    return &*lItem;
  }

  Item
  ItemFactoryImpl::createQName(const String& aNamespace, const String& aPrefix,
                               const String& aLocalname)
  {
    xqpStringStore* lNamespace = Unmarshaller::getInternalString( aNamespace );
    xqpStringStore* lPrefix = Unmarshaller::getInternalString( aPrefix );
    xqpStringStore* lLocalname = Unmarshaller::getInternalString( aLocalname );

    store::Item_t lItem;
    lItem = theItemFactory->createQName(lNamespace, lPrefix, lLocalname);
    return &*lItem;
  }

  Item
  ItemFactoryImpl::createQName(const String& aNamespace, const String& aLocalname)
  {
    xqpStringStore* lNamespace = Unmarshaller::getInternalString( aNamespace );
    xqpString lPrefix("");
    xqpStringStore* lLocalname = Unmarshaller::getInternalString( aLocalname );
    store::Item_t lItem;
    lItem = theItemFactory->createQName(lNamespace, &*lPrefix.theStrStore, lLocalname);
    return &*lItem;
  }

  Item 
  ItemFactoryImpl::createNCName(const String& aValue)
  {
    xqpStringStore_t lString = Unmarshaller::getInternalString( aValue );
    store::Item_t lItem;
    lItem = theItemFactory->createNCName(lString);
    return &*lItem;
  }
    
  Item 
  ItemFactoryImpl::createBase64Binary(const char* aBinData, size_t aLength)
  {
    store::Item_t lItem;
    xqp_base64Binary n;
    if (xqp_base64Binary::parseString(aBinData, aLength, n))
      lItem = theItemFactory->createBase64Binary(n);
    
    return &*lItem;
  }
      
  Item 
  ItemFactoryImpl::createBoolean(bool aValue)
  {
    store::Item_t lItem;
    lItem = theItemFactory->createBoolean(aValue);
    return &*lItem;
  }
    
  Item 
  ItemFactoryImpl::createDecimalFromLong (unsigned long aValue)
  {
    store::Item_t lItem;

    // no error possible
    Decimal lDecimal = Decimal::parseULong(aValue);
    lItem = theItemFactory->createDecimal(lDecimal);
    return &*lItem;
  }
    
  Item 
  ItemFactoryImpl::createDecimalFromDouble (double aValue)
  {
    store::Item_t lItem;
    Decimal lDecimal;
    if (Decimal::parseNativeDouble(aValue, lDecimal)) {
      lItem = theItemFactory->createDecimal(lDecimal);
      return &*lItem;
    }

    return &*lItem;
  }

  Item 
  ItemFactoryImpl::createDecimal (const String& aValue)
  {
    store::Item_t lItem;
    xqpStringStore* lString = Unmarshaller::getInternalString( aValue );
    Decimal lDecimal;
    if (Decimal::parseString(lString->c_str(), lDecimal)) {
      lItem = theItemFactory->createDecimal(lDecimal);
      return &*lItem;
    }

    return &*lItem;
  }

  Item
  ItemFactoryImpl::createInteger(long long aInteger)
  {
    store::Item_t lItem;
    Integer lInteger = Integer::parseLongLong(aInteger);
    lItem = theItemFactory->createInteger(lInteger);
    return &*lItem;
  }

  Item
  ItemFactoryImpl::createInteger(const String& aInteger)
  {
    xqpStringStore* lString = Unmarshaller::getInternalString( aInteger );
    store::Item_t lItem;
    Integer lInteger;
    if (Integer::parseString(lString->c_str(), lInteger)) {
      lItem = theItemFactory->createInteger(lInteger);
      return &*lItem;
    }
    return &*lItem;
  }
    
  Item
  ItemFactoryImpl::createLong ( long long aLong )
  {
    store::Item_t lItem;

    lItem = theItemFactory->createLong(aLong);
    return &*lItem;
  }
    
  Item
  ItemFactoryImpl::createInt ( int aInt )
  {
    store::Item_t lItem;

    try {
      int32_t lInteger = boost::numeric_cast<int32_t>(aInt);
      lItem = theItemFactory->createInt(lInteger);
    } catch (boost::bad_numeric_cast e) {
      return &*lItem;
    }

    return &*lItem;
  }
    
  Item
  ItemFactoryImpl::createShort ( short aShort )
  {
    store::Item_t lItem;

    lItem = theItemFactory->createShort(aShort);

    return &*lItem;
  }
    
  Item
  ItemFactoryImpl::createByte ( char aValue )
  {
    store::Item_t lItem;
  
    lItem = theItemFactory->createByte(aValue);

    return &*lItem;
  }
    
  Item
  ItemFactoryImpl::createDateTime(short aYear, short aMonth, short aDay,
                                  short aHour, short aMinute, double aSecond,
                                  short aTimezone_hours)
  {
    store::Item_t lItem;
    lItem = theItemFactory->createDateTime(aYear, aMonth, aDay, aHour, aMinute, aSecond, aTimezone_hours);

    return &*lItem;
  }

  Item
  ItemFactoryImpl::createDateTime( const String& aDateTimeValue )
  {
    xqpStringStore* lString = Unmarshaller::getInternalString( aDateTimeValue );

    store::Item_t lItem;
    lItem = theItemFactory->createDateTime( lString );

    return &*lItem;
  }

  Item
  ItemFactoryImpl::createDouble ( double aValue )
  {
    store::Item_t lItem;
    Double lDouble = Double::parseFloatType(aValue);
    lItem = theItemFactory->createDouble(lDouble);
    return &*lItem;
  }

  Item
  ItemFactoryImpl::createDouble ( const String& aValue )
  {
    xqpStringStore* lString = Unmarshaller::getInternalString( aValue );
  
    store::Item_t lItem;
    Double lDouble;
    if (Double::parseString(lString->c_str(), lDouble)) {
      lItem = theItemFactory->createDouble(lDouble);
    } 
    return &*lItem;
  }
    
  Item
  ItemFactoryImpl::createDuration( const String& aValue )
  {
    xqpStringStore* lString = Unmarshaller::getInternalString( aValue );
    const xqpString s(lString);
    store::Item_t   lItem;

    lItem = theItemFactory->createDuration(s);

    return &*lItem;
  }
      
  Item
  ItemFactoryImpl::createDuration ( short aYears, short aMonths, short aDays, 
                                    short aHours, short aMinutes, double aSeconds )
  {
    store::Item_t lItem;
    
    lItem = theItemFactory->createDuration(aYears, aMonths, aDays, aHours, aMinutes, aSeconds);
    
    return &*lItem;
  }
    
  Item
  ItemFactoryImpl::createFloat ( const String& aValue )
  {
    xqpStringStore* lString = Unmarshaller::getInternalString( aValue );
    store::Item_t lItem;
    Float lFloat;
    if (Float::parseString(lString->c_str(), lFloat)) {
      lItem = theItemFactory->createFloat(lFloat);
    } 
    return &*lItem;
  }
    
  Item
  ItemFactoryImpl::createFloat ( float aValue )
  {
    store::Item_t lItem;
    Float lFloat = Float::parseFloatType(aValue);
    lItem = theItemFactory->createFloat(lFloat);
    return &*lItem;
  }

  Item
  ItemFactoryImpl::createHexBinary ( const char* aHexData, size_t aSize )
  {
    store::Item_t lItem;
    xqp_hexBinary n;
    if (xqp_hexBinary::parseString(aHexData, aSize, n))
      lItem = theItemFactory->createHexBinary(n);
    
    return &*lItem;
  }
    
  Item
  ItemFactoryImpl::createNegativeInteger ( long long aValue )
  {
    store::Item_t lItem;
    if (aValue < 0) {
      Integer lInteger;
      lInteger = Integer::parseLongLong(aValue);
      lItem = theItemFactory->createNegativeInteger(lInteger);
    }
    return &*lItem;
  }
    
  Item
  ItemFactoryImpl::createNonNegativeInteger ( unsigned long long aValue )
  {
    store::Item_t lItem;
    Integer lInteger;
    lInteger = Integer::parseULongLong(aValue);
    lItem = theItemFactory->createNonNegativeInteger(lInteger);
    return &*lItem;
  }

  Item
  ItemFactoryImpl::createNonPositiveInteger ( long long aValue )
  {
    store::Item_t lItem;
    if (aValue < 0) {
      Integer lInteger;
      lInteger = Integer::parseLongLong(aValue);
      lItem = theItemFactory->createNonPositiveInteger(lInteger);
    }
    return &*lItem;
  }

  Item
  ItemFactoryImpl::createPositiveInteger ( unsigned long long aValue )
  {
    store::Item_t lItem;
    Integer lInteger;
    lInteger = Integer::parseLongLong(aValue);
    lItem = theItemFactory->createPositiveInteger(lInteger);
    return &*lItem;
  }

  Item
  ItemFactoryImpl::createGDay ( const String& aValue )
  {
    xqpStringStore* lString = Unmarshaller::getInternalString( aValue );
    store::Item_t lItem;

    lItem = theItemFactory->createGDay( lString );
    
    return &*lItem;
  }
    
  Item
  ItemFactoryImpl::createGDay ( short aDay )
  {
    store::Item_t lItem;

    lItem = theItemFactory->createGDay( aDay );
    
    return &*lItem;
  }
    
  Item
  ItemFactoryImpl::createGMonth ( short aMonth )
  {
    store::Item_t lItem;

    lItem = theItemFactory->createGMonth( aMonth );
    
    return &*lItem;
  }
    
  Item
  ItemFactoryImpl::createGMonth ( const String& aValue )
  {
    xqpStringStore* lString = Unmarshaller::getInternalString( aValue );
    store::Item_t lItem;
    
    lItem = theItemFactory->createGMonth( lString );
    
    return &*lItem;
  }
    
  Item
  ItemFactoryImpl::createGMonthDay ( const String& aValue )
  {
    xqpStringStore* lString = Unmarshaller::getInternalString( aValue );
    store::Item_t lItem;

    lItem = theItemFactory->createGMonthDay( lString );
    
    return &*lItem;
  }
    
  Item
  ItemFactoryImpl::createGMonthDay ( short aMonth, short aDay )
  {
    store::Item_t lItem;

    lItem = theItemFactory->createGMonthDay( aMonth, aDay );
    
    return &*lItem;
  }
    
  Item
  ItemFactoryImpl::createGYear ( const String& aValue )
  {
    xqpStringStore* lString = Unmarshaller::getInternalString( aValue );
    store::Item_t lItem;

    lItem = theItemFactory->createGYear( lString );
    
    return &*lItem;
  }
    
  Item
  ItemFactoryImpl::createGYear ( short aYear )
  {
    store::Item_t lItem;

    lItem = theItemFactory->createGYear( aYear );
    
    return &*lItem;
  }
    
  Item
  ItemFactoryImpl::createGYearMonth ( const String& aValue )
  {
    xqpStringStore* lString = Unmarshaller::getInternalString( aValue );
    store::Item_t lItem;
    
    lItem = theItemFactory->createGYearMonth( lString );
    
    return &*lItem;
  }
    
  Item
  ItemFactoryImpl::createGYearMonth ( short aYear, short aMonth )
  {
    store::Item_t lItem;

    lItem = theItemFactory->createGYearMonth( aYear, aMonth );
    
    return &*lItem;
  }
    
  Item
  ItemFactoryImpl::createTime ( const String& aValue )
  {
    xqpStringStore* lString = Unmarshaller::getInternalString( aValue );
    store::Item_t lItem;

    lItem = theItemFactory->createTime( lString );
    
    return &*lItem;
  }
    
  Item
  ItemFactoryImpl::createTime ( short aHour, short aMinute, double aSecond )
  {
    store::Item_t lItem;

    lItem = theItemFactory->createTime( aHour, aMinute, aSecond );
    
    return &*lItem;
  }
    
  Item
  ItemFactoryImpl::createTime ( short aHour, short aMinute, double aSecond, short aTimezone_hours )
  {
    store::Item_t lItem;

    lItem = theItemFactory->createTime( aHour, aMinute, aSecond, aTimezone_hours );
    
    return &*lItem;
  }
    
  Item
  ItemFactoryImpl::createUnsignedByte(const unsigned char aValue)
  {
    store::Item_t lItem;
    lItem = theItemFactory->createUnsignedByte(aValue);
    return &*lItem;
  }
    
  Item
  ItemFactoryImpl::createUnsignedInt(unsigned int aValue)
  {
    store::Item_t lItem;
    
    try {
      uint32_t lInteger = boost::numeric_cast<uint32_t>(aValue);
      lItem = theItemFactory->createUnsignedInt(lInteger);
    } catch (boost::bad_numeric_cast e) {
      return &*lItem;
    }

    return &*lItem;
  }
    
  Item
  ItemFactoryImpl::createUnsignedLong(unsigned long long aValue)
  {
    store::Item_t lItem;
    lItem = theItemFactory->createUnsignedLong(aValue);
    return &*lItem;
  }
    
  Item
  ItemFactoryImpl::createUnsignedShort(unsigned short aValue)
  {
    store::Item_t lItem;
    lItem = theItemFactory->createUnsignedShort(aValue);
    return &*lItem;
  }
} /* namespace zorba */
