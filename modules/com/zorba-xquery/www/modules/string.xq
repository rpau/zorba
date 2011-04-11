(:
 : Copyright 2006-2009 The FLWOR Foundation.
 :
 : Licensed under the Apache License, Version 2.0 (the "License");
 : you may not use this file except in compliance with the License.
 : You may obtain a copy of the License at
 :
 : http://www.apache.org/licenses/LICENSE-2.0
 :
 : Unless required by applicable law or agreed to in writing, software
 : distributed under the License is distributed on an "AS IS" BASIS,
 : WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 : See the License for the specific language governing permissions and
 : limitations under the License.
:)

(:~
 : This module provides string related functions.
 :
 : @author Matthias Brantner
 :
 :)
module namespace string = "http://www.zorba-xquery.com/modules/string";

(:~
 : This function materializes a streamable string.
 : The drawback of a streamable string is that its value can only
 : be consumed once. That is, only one function can access the value
 : of a streamable string item.
 :
 : In order to remedy this situtation, this function can be used to 
 : convert a streamable string into its non-streamable counterpart. As a
 : result, the string returned by this function has the same value as its
 : input but is materialized and, hence, can be consumed multiple times.
 :
 : @param $s the streamable string item to materialize
 : @return a materialized string of its input or the input if the input
 :         item was not a streamable string.
 :
 : @see string:is-streamable
 : @see {http://www.zorba-xquery.com/modules/file}read-text
 :)
declare function string:materialize($s as xs:string) as xs:string external;

(:~
 : This function checks whether a given string item is implemented by a
 : streamable string.
 : A streamable string is produced by some functions of a module
 : (e.g. file:read-text()). It's an optimized implementation of an
 : xs:string to handle arbitrary sized data. The drawback is that
 : its value can only be consumed once. That is, only one function
 : can access the value of a streamable string item.
 :
 : @param $s the string to check
 : @return true if the given item is implemented using a streamable string
 :         or false otherwise.
 :
 :)
declare function string:is-streamable($s as xs:string) as xs:boolean external;