(:
 : Copyright 2006-2010 The FLWOR Foundation.
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
 : <p>
 : The goal of xqDoc is to provide a simple vendor neutral solution for
 : documenting XQuery modules, as well as tools to generate a user friendly
 : presentation of this documentation and cross referencing information.
 : Therefore, xqDoc proposes a new commenting convention that extends the
 : currently defined XQuery comment style. This convention is modeled
 : after Java's Javadoc commenting style, and provides a simple, uniform
 : way to document XQuery source code. You can find more information about
 : xqDoc on the website of the <a href="http://xqdoc.org/">xqDoc project</a>.
 : This library module provides XQDoc utility functions.
 : </p>
 : 
 : <p>
 : Generating a user friendly presentation of the documentation is
 : accomplished in the following steps:
 : <ol>
 :  <li>Module-, variable-, and function declarations need to be commented
 :      using the xqDoc commenting conventions. For example, this module
 :      contains xqDoc-style comments</li>
 :  <li>A xqDoc-enabled processor can parse such documentation and generate
 :      a vendor neutral XML document which stores all the information about
 :      the code and the comments. Such a document adheres to the xqDoc
 :      Schema.</li>
 :  <li>The information of an XML document generated by the second step,
 :      can be transformed into arbitrary presentation formats 
 :      (e.g. html).</li>
 : </ol>
 : </p>
 :
 : <p>
 : This module implements the first and second step of this process.
 : That is, Zorba can parse XQuery modules which are annotated with
 : xqDoc-style documentation and generate the vendor neutral
 : XML representation. 
 : </p>
 :
 : @see <a href="http://xqdoc.org/" target="_blank">xqDoc specification</a>
 : @see <a href="http://www.zorba-xquery.com/tutorials/xqdoc.html" target="_blank">xqDoc tutorial with Zorba</a>
 : @author Gabriel Petrovay
 : @project xqdoc
 :
 :)
module namespace xqd = "http://www.zorba-xquery.com/modules/xqdoc";
declare namespace ann = "http://www.zorba-xquery.com/annotations";
declare namespace ver = "http://www.zorba-xquery.com/options/versioning";
declare option ver:module-version "2.0";

(:~
 : Generated an XQDoc XML document for the module located
 : at the URI provided as parameter to this function.
 :
 : @param $module-url The URL of the module for which to
 :        generate XQDoc.
 : @return The xqDoc element as specified by
 :         <a href="www.xqdoc.org">xqdoc.org</a>.
 : @error An error is thrown if no module is located at the
 :        given URL or the module could not be parsed.
 :)
declare %ann:nondeterministic function xqd:xqdoc(
  $module-url as xs:string
) as element() external;

(:~
 : Generated the an XQDoc XML document for the module provided
 : as parameter to this function.
 :
 : @param $module The module (as string) file for which to generate
 :        XQDoc.
 : @return The xqDoc element as specified by
 :         <a href="www.xqdoc.org">xqdoc.org</a>.
 : @error An error is thrown if the module could not be parsed.
 :)
declare function xqd:xqdoc-content(
  $module as xs:string
) as element() external;
