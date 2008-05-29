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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zorba/zorbac.h>

/**
 */
int
cdatamanager_example_1(XQC_Implementation impl, XQC_DataManager mgr)
{
  XQC_Collection   lCollection;
  XQC_Item         lURIItem;
  const char*      lStringBuffer;
  
  // create a new collection
  mgr->create_collection(mgr, "http://www.zorba-xquery.com/collections/mybooks", &lCollection);

  lCollection->get_uri(lCollection, &lURIItem);

  lURIItem->string_value(lURIItem, &lStringBuffer);

  printf("Collection URI %s", lStringBuffer);

  // free all resources
  lURIItem->free(lURIItem);
  lCollection->free(lCollection);

  return 1;
}

int
cdatamanager(int argc, char** argv)
{
  int res = 0; 
  XQC_Implementation impl;
  XQC_DataManager mgr;

  if ( zorba_implementation(&impl) != XQ_SUCCESS )
      return 1;
 
  impl->data_manager(impl, &mgr);

  printf("executing C example 1\n");
  res = cdatamanager_example_1(impl, mgr);
  if (!res) { impl->free(impl); return 1; };
  printf("\n");

  mgr->free(mgr);
  impl->free(impl);
  return 0;
}
