#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/algorithm/string.hpp>

#include "testdriverconfig.h" // SRC and BIN dir definitions
#include "specification.h" // parsing spec files
#include "zorba/zorba_api.h"

namespace fs = boost::filesystem;

void
printFile(std::ostream& os, std::string aInFile)
{
  std::ifstream lInFileStream(aInFile.c_str());
  assert(lInFileStream);

  os << lInFileStream.rdbuf() << std::endl;
}

// print parts of a file
// starting at aStartPos with the length of aLen
void
printPart(std::ostream& os, std::string aInFile, 
          int aStartPos, int aLen)
{
  char* buffer = new char [aLen];
  try {
    std::ifstream lIn(aInFile.c_str());
    lIn.seekg(aStartPos);

    int lCharsRead = lIn.readsome (buffer, aLen);
    os.write (buffer, lCharsRead);
    os.flush();
    delete[] buffer;
  } catch (...)
  {
    delete[] buffer;
  }
  return;
}


// check of an error that was repored was expected 
// by the given specification object
bool
isErrorExpected(xqp::ZorbaAlertsManager* aManager, Specification* aSpec)
{
  for (xqp::ZorbaAlertsManager::const_iterator lIter = aManager->begin();
       lIter != aManager->end(); ++lIter)
  {
    xqp::ZorbaAlert* lAlert = *lIter;
    switch (lAlert->theKind)
    {
      case xqp::ZorbaAlert::ERROR_ALERT:
        {
          xqp::ZorbaError* lErrorAlert = dynamic_cast<xqp::ZorbaError*>(lAlert);
          std::string lErrorCode = lErrorAlert->toString(lErrorAlert->theCode);
          for (std::vector<std::string>::const_iterator lErrorIter = aSpec->errorsBegin();
               lErrorIter != aSpec->errorsEnd(); ++lErrorIter)
          {
            // error is expected
            if ((*lErrorIter).compare(lErrorCode) == 0)
              return true;
          }
          break;
        }
      default:
        { }
    }
  }
  return false;
}

// print all errors that were raised
void
printErrors(xqp::ZorbaAlertsManager* aManager)
{
  if (aManager->size() == 0) return;

  std::cerr << "Errors:" << std::endl;

  for (xqp::ZorbaAlertsManager::const_iterator lIter = aManager->begin();
       lIter != aManager->end(); ++lIter)
  {
    xqp::ZorbaAlert* lAlert = *lIter;
    switch (lAlert->theKind)
    {
    case xqp::ZorbaAlert::ERROR_ALERT:
    {
      xqp::ZorbaError* lErrorAlert = dynamic_cast<xqp::ZorbaError*>(lAlert);
      assert(lErrorAlert);
      std::string lErrorCode = lErrorAlert->toString(lErrorAlert->theCode);
      std::cerr << lErrorCode << " " << lErrorAlert->theDescription << std::endl;
      break;
    }
    default:
    { 
    }
    }
  }
  return;
}

// set a variable in the dynamic context
// inlineFile specifies whether the given parameter is a file and it's value should
// be inlined or not
void
set_var (bool inlineFile, std::string name, std::string val, 
         xqp::DynamicQueryContext_t dctx, xqp::XQuery_t exec)
{
  boost::replace_all(val, "$RBKT_SRC_DIR", xqp::RBKT_SRC_DIR);
  if (!inlineFile && dctx != NULL) {
		if(name != ".")
			dctx->setVariableAsString (name, xqp::xqp_string (val));
		else
			dctx->setContextItemAsString(xqp::xqp_string(val));
  } else if (inlineFile && exec != NULL) {
    std::ifstream is (val.c_str ());
    assert (is);
		if(name != ".")
			exec->setVariableAsDocumentFromStream (name, val.c_str(), is);
		else
			exec->setContextItemAsDocumentFromStream (val.c_str(), is);
  }
}

void 
set_vars (Specification* aSpec, xqp::DynamicQueryContext_t dctx, xqp::XQuery_t exec) 
{
  for (std::vector<Specification::Variable>::const_iterator lIter = aSpec->variablesBegin();
       lIter != aSpec->variablesEnd(); ++lIter)
  {
    set_var ((*lIter).theInline, (*lIter).theVarName, (*lIter).theVarValue, dctx, exec);
  }
  // TODO: set context item
}


void
trim(std::string& str) {

  std::string::size_type  notwhite = str.find_first_not_of(" \t\n");
  str.erase(0,notwhite);

  notwhite = str.find_last_not_of(" \t\n"); 
  str.erase(notwhite+1); 
}

// return false if the files are not equal
// aLine contains the line number in which the first difference occurs
// aCol contains the column number in which the first difference occurs
// aPos is the character number off the first difference in the file
// -1 is returned for aLine, aCol, and aPos if the files are equal
bool
isEqual(fs::path aRefFile, fs::path aResFile, int& aLine, int& aCol, int& aPos)
{
  std::ifstream li(aRefFile.native_file_string().c_str());
  std::ifstream ri(aResFile.native_file_string().c_str()); 

  std::streambuf * lb = li.rdbuf();
  std::streambuf * rb = ri.rdbuf();

  long ls = lb->pubseekoff (0, std::ios::end, std::ios::in);
  long rs = rb->pubseekoff (0, std::ios::end, std::ios::in);
  lb->pubseekpos (0, std::ios::in);
  rb->pubseekpos (0, std::ios::in);

  char* lBuf = new char[ls];
  char* rBuf = new char[rs];

  try {
    lb->sgetn (lBuf, ls);
    rb->sgetn (rBuf, rs);
  } catch (...)
  {
    li.close(); ri.close();
    delete[] lBuf; delete[] rBuf;
    return false;
  }

  li.close();
  ri.close();

  std::string lString(lBuf, ls);
  std::string rString(rBuf, rs);

  delete[] lBuf; delete[] rBuf;

  trim(lString);
  trim(rString);

  aLine = 1; aCol = 0; aPos = -1;

  size_t aLPos = 0, aRPos = 0;
  char lc, rc;
  while (aLPos != lString.length() && aRPos != rString.length())
  {
    lc = lString.at(aLPos);
    rc = rString.at(aRPos);

    ++aPos; ++aCol;
    if (lc == '\n') { ++aLine; aCol = 0; }
    if ( lc != rc ) return false;
    ++aLPos; ++aRPos;
  }
  aLine = aCol = aPos = -1;
  return true;
}

class ZorbaEngineWrapper {
public:
  xqp::ZorbaEngine_t factory;

  ZorbaEngineWrapper ()
    : factory (xqp::ZorbaEngine::getInstance())
  {
    factory->initThread();
  }
  ~ZorbaEngineWrapper () {

    factory->uninitThread();
    factory->shutdown();
  }
};

void 
slurp_file (const char *fname, std::string &result) {
  std::ifstream qfile(fname); assert (qfile);

  qfile.seekg (0, std::ios::end);
  size_t len = qfile.tellg ();
  qfile.seekg (0, std::ios::beg);
  char *str = new char [len];
  qfile.read (str, len);
  
  std::string sstr (str, len);
  result.swap (sstr);
  delete [] str;
}

int
#ifdef _WIN32_WCE
_tmain(int argc, _TCHAR* argv[])
#else
main(int argc, char** argv)
#endif
{
  fs::path lQueryFile, lResultFile, lErrorFile, lRefFile, lSpecFile;
  Specification lSpec;

  // do initial stuff
  if ( argc == 2 )
  {
    std::string lQueryFileString  = xqp::RBKT_SRC_DIR +"/Queries/" + argv[1];
    lQueryFile = fs::system_complete( fs::path( lQueryFileString, fs::native ) );

    std::string lQueryWithoutSuffix = std::string(argv[1]).substr( 0, std::string(argv[1]).size()-3 );
    std::cout << "test " << lQueryWithoutSuffix << std::endl;

    lResultFile = fs::system_complete(fs::path( xqp::RBKT_BINARY_DIR +"/QueryResults/" 
                                      +lQueryWithoutSuffix + ".res", fs::native) );
    lErrorFile = fs::system_complete(fs::path(xqp::RBKT_BINARY_DIR +"/" 
                                     +lQueryWithoutSuffix + ".err", fs::native) );
    lRefFile   = fs::system_complete(fs::path( xqp::RBKT_SRC_DIR +"/ExpQueryResults/" 
                                     +lQueryWithoutSuffix +".xml.res", fs::native) );
    lSpecFile  = fs::system_complete(fs::path(xqp::RBKT_SRC_DIR+ "/Queries/" 
                                     +lQueryWithoutSuffix +".spec", fs::native) );
  }
  else
  {
    std::cerr << "\nusage:   testdriver [testfile]" << std::endl;
    return 1;
  }

  // does the query file exists
  if ( (! fs::exists( lQueryFile )) || fs::is_directory( lQueryFile) )
  {
    std::cerr << "\n query file " << lQueryFile.native_file_string() 
              << " does not exist or is not a file" << std::endl;
    return 2;
  }

  // delete previous files if they exists
  if ( fs::exists ( lResultFile ) ) { fs::remove (lResultFile); }
  if ( fs::exists ( lErrorFile ) )  { fs::remove (lErrorFile);  }

  // create the result directory
  fs::path lBucket = fs::system_complete(fs::path( lResultFile.branch_path().string(), fs::native ));
  if ( ! fs::exists( lBucket ) )
    fs::create_directories(lBucket); // create deep directories

  // read the xargs and errors if the spec file exists
  if ( fs::exists( lSpecFile )) 
  { 
    lSpec.parseFile(lSpecFile.native_file_string()); 
  }

  // we must either have a reference file or an expected error code
  if ( (lSpec.errorsSize() == 0) && ((! fs::exists( lRefFile )) || fs::is_directory( lRefFile)))
  {
    std::cerr << "No reference result and no expected errors." << std::endl;
    return 3;
  }

  // print the query
  std::cout << "Query:" << std::endl;
  printFile(std::cout, lQueryFile.native_file_string());
  std::cout << std::endl;

  // initialize the zorba engine
  ZorbaEngineWrapper lEngine; // the engine is up as long as this object lives

  // create and compile the query
  std::string lQueryString;
  slurp_file(lQueryFile.native_file_string().c_str(), lQueryString);
  xqp::XQuery_t lQuery = lEngine.factory->createQuery(lQueryString.c_str());

  xqp::ZorbaAlertsManager_t lAlertsManager = lEngine.factory->getAlertsManagerForCurrentThread();

  if (lQuery == NULL)
  {
    if (isErrorExpected(&*lAlertsManager, &lSpec)) 
    { 
      // done, we expected an error during compile
      return 0; 
    } 
    else 
    { 
      std::cerr << "Error compiling query" << std::endl;
      printErrors(&*lAlertsManager); return 4;
    }
  }


  // set the variables in the dynamic context
	xqp::DynamicQueryContext_t lDynCtxt = lEngine.factory->createDynamicContext();
  set_vars(&lSpec, lDynCtxt, NULL);

  // execute the query
  if(!lQuery->initExecution(lDynCtxt))
  {
    if (isErrorExpected(&*lAlertsManager, &lSpec)) { return 0; } // done, we expected this error
    else 
    { 
      if ( ! fs::exists(lRefFile) )
      {
        std::cerr << "Error executing query" << std::endl;
        printErrors(&*lAlertsManager);
        return 5;
      }
    }
  }
  set_vars(&lSpec, NULL, lQuery);
  
  {
    // serialize xml
    std::ofstream lResFileStream(lResultFile.native_file_string().c_str());
    assert (lResFileStream.good());

    lQuery->serializeXML(lResFileStream);

    if (lQuery->isError())
    {
      if (isErrorExpected(&*lAlertsManager, &lSpec)) { return 0; } // again done, we expected this error
      else 
      { 
        std::cerr << "Error executing query" << std::endl;
        printErrors(&*lAlertsManager); 
        return 6;
      }
    }
    else if ( lSpec.errorsSize() > 0 )
    {
      if ( ! fs::exists(lRefFile) )
      {
        std::cerr << "Expected error(s)";
        for (std::vector<std::string>::const_iterator lIter = lSpec.errorsBegin();
            lIter != lSpec.errorsEnd(); ++lIter)
        {
          std::cerr << " " << *lIter;
        }
        if ( fs::exists(lResultFile) && fs::file_size(lResultFile) == 0)
          std::cerr << " but got empty result" << std::endl;
        else
        {
          std::cerr << " but got result:" << std::endl;
          printFile(std::cerr, lResultFile.native_file_string());
          std::cerr<< std::endl;
        } 
        return 7;
      }
    }
  }
  std::cout << "Result:" << std::endl;
  printFile(std::cout, lResultFile.native_file_string());
  std::cout.flush();
  std::cout << std::endl;


  // last, we have to diff the result
  int lLine, lCol, lPos; // where do the files differ
  bool lRes = isEqual(lRefFile, lResultFile, lLine, lCol, lPos);
  if ( !lRes )  // results differ
  {
    std::cerr << std::endl << "Result does not match expected result" << std::endl;
    printFile(std::cerr, lRefFile.native_file_string());
    std::cerr << std::endl;

    std::cerr << "See line " << lLine << ", col " << lCol << " of expected result. " << std::endl;
    std::cerr << "Got "; 
    printPart(std::cerr, lResultFile.native_file_string(), lPos, 15);
    std::cerr << std::endl << "Expected ";
    printPart(std::cerr, lRefFile.native_file_string(), lPos, 15);
    std::cerr <<  std::endl;

    return 8;
  }


  return 0;
}
