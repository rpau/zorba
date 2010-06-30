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
#ifndef ZORBA_XQUERY_DRIVER_H
#define ZORBA_XQUERY_DRIVER_H

#include <ostream>
#include <string>
#include <zorba/config.h>
#include "zorbatypes/xqpstring.h"
#include "compiler/parser/symbol_table.h"

// needed because we have to delete the main module node
#include "compiler/parsetree/parsenode_base.h"

namespace zorba {

class location;
class parsenode;
class CompilerCB;


class ZorbaParserError
{
public:
  std::string msg;
  QueryLoc loc;

public:
  ZorbaParserError(std::string _msg) : msg(_msg) { };
  ZorbaParserError(std::string _msg, const location& aLoc);
};


// exported for unit testing only
class ZORBA_DLL_PUBLIC xquery_driver
{
public:
  std::stringstream theDocComment;
  std::string theMainModuleDocComment;
  xqpString theFilename;
  symbol_table symtab;
  rchandle<parsenode> expr_p;
  CompilerCB* theCompilerCB;
  ZorbaParserError* parserError;

  xquery_driver(CompilerCB* aCompilerCB, uint32_t initial_heapsize = 1024);
  virtual ~xquery_driver();

  bool parse_stream(std::istream& in, const xqpString& aFilename = "");
  bool parse_string(const xqpString& input);
  bool parse_file(const xqpString& aFilename);

	void set_expr(parsenode* e_p);
	parsenode* get_expr() { return expr_p; }

  static QueryLoc createQueryLoc(const location& aLoc);

  class xquery_scanner* lexer;

  // Error generators
  ZorbaParserError* unrecognizedCharErr(const char* _error_token, const location& loc);
  ZorbaParserError* unterminatedCommentErr(const location& loc);
  ZorbaParserError* unrecognizedToken(const char* _error_token, const location& loc);
  ZorbaParserError* invalidCharRef(const char* _error_token, const location& loc);
  ZorbaParserError* parserErr(const std::string& _message, const location& loc);
};

}	/* namespace zorba */
#endif /* ZORBA_XQUERY_DRIVER_H */

/*
 * Local variables:
 * mode: c++
 * End:
 */
