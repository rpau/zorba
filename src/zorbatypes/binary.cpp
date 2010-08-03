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
#include <cassert>
#include <cctype>
#include <zorba/error.h>
#include "zorbatypes/binary.h"
#include "zorbaerrors/error_manager.h"
#include "util/XmlWhitespace.h"

namespace zorba 
{

SERIALIZABLE_CLASS_VERSIONS(Base64)
END_SERIALIZABLE_CLASS_VERSIONS(Base64)

SERIALIZABLE_CLASS_VERSIONS(Base16)
END_SERIALIZABLE_CLASS_VERSIONS(Base16)


static const std::string base64_chars = 
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";


inline bool is_base64(char c) 
{
  return (isalnum(c) || (c == '+') || (c == '/'));
}


bool Base64::parseString(const char* aString, size_t aLength,  Base64& aBase64)
{
  aBase64.theData.clear();
  try 
  {
    aBase64.insertData(aString, aLength);
  }
  catch (...) 
  {
    return false;
  }
  return true;
}


bool Base64::parseString(
    const char* aString,
    size_t aLength,
    Base64& aBase64, 
    std::string& lErrorMessage)
{
  aBase64.theData.clear();
  try 
  {
    aBase64.insertData(aString, aLength);
  }
  catch (error::ZorbaError& e) 
  {
    lErrorMessage = e.theDescription;
    return false;
  }
  return true;
}


void Base64::encode(const xqpStringStore* aString, Base64& aResult)
{
  std::vector<char> source;
  source.resize(aString->bytes());
  
  const char* lTmp = aString->c_str();
  const char* lRun = lTmp;
  ulong numBytes = aString->bytes();
  for (ulong i = 0; i < numBytes; ++i) 
  {
    source[i] = (*lRun);
    ++lRun;
  }

#if 0
  for (std::vector<char>::iterator lIter = source.begin();
       lIter != source.end();
       ++lIter) 
  {
    std::cout << (*lIter);
  }

  std::cout << std::endl;
#endif

  aResult.theData.clear();
  encode(source, aResult.theData);
}


void Base64::encode(std::istream& aStream, Base64& aResult)
{
  std::vector<char> source, result;

  while (aStream.good())
    source.push_back((char)(aStream.get()));

  encode(source, result);
  aResult.theData = result;
}


xqpStringStore_t Base64::encode(std::istream& aStream)
{
  std::vector<char> source;
  std::vector<char> dest;

  xqpStringStore_t result = new xqpStringStore("");
  std::string& str = result->str();

  char buf[1024];
  while (!aStream.eof()) 
  {
    aStream.read(buf, 1024);
    source.insert(source.end(), buf, buf + aStream.gcount());
  }

  encode(source, dest);

  str.resize(dest.size());

  for (unsigned int i = 0; i < dest.size(); ++i)
    str[i] = dest[i];

  return result;
}

xqpStringStore_t Base64::decode(std::istream& aStream)
{
  std::vector<char> source;
  std::vector<char> dest;

  xqpStringStore_t result = new xqpStringStore("");
  std::string& str = result->str();

  char buf[1024];
  while (!aStream.eof()) 
  {
    aStream.read(buf, 1024);
    source.insert(source.end(), buf, buf + aStream.gcount());
  }

  decode(source, dest);

  str.resize(dest.size());

  for (unsigned int i = 0; i < dest.size(); ++i)
    str[i] = dest[i];

  return result;
}


void Base64::encode(const std::vector<char>& aSource, std::vector<char>& aResult)
{
  size_t in_len = aSource.size();
  size_t lCurPos = 0;
  int i = 0;
  int j = 0;
  char char_array_3[3] = {'\0','\0','\0'};
  char char_array_4[4] = {'\0','\0','\0','\0'};

  while (in_len--) 
  {
    char_array_3[i++] = aSource[lCurPos++];
    if (i == 3) 
    {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for(i = 0; (i <4) ; i++)
        aResult.push_back(base64_chars[char_array_4[i]]);
      i = 0;
    }
  }

  if (i)
  {
    for(j = i; j < 3; j++)
      char_array_3[j] = '\0';

    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
    char_array_4[3] = char_array_3[2] & 0x3f;

    for (j = 0; (j < i + 1); j++)
      aResult.push_back(base64_chars[char_array_4[j]]);

    while((i++ < 3))
      aResult.push_back('=');

  }  
}


void Base64::decode(const std::vector<char>& aSource, std::vector<char>& aResult)
{
  size_t in_len = aSource.size();
  int i = 0;
  int j = 0;
  int in_ = 0;
  char char_array_4[4], char_array_3[3];

  while (in_len-- && ( aSource[in_] != '=') && is_base64(aSource[in_])) {
    char_array_4[i++] = aSource[in_]; in_++;
    if (i ==4) {
      for (i = 0; i <4; i++)
        char_array_4[i] = base64_chars.find(char_array_4[i]);

      char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

      for (i = 0; (i < 3); i++)
        aResult.push_back(char_array_3[i]);
      i = 0;
    }
  }

  if (i) {
    for (j = i; j <4; j++)
      char_array_4[j] = 0;

    for (j = 0; j <4; j++)
      char_array_4[j] = base64_chars.find(char_array_4[j]);

    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
    char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
    char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

    for (j = 0; (j < i - 1); j++) aResult.push_back(char_array_3[j]);
  }
}


Base64::Base64(const Base16& aBase16)
{
  std::vector<char> lOrig;
  Base16::decode(aBase16.getData(), lOrig);
  Base64::encode(lOrig, theData);
}


void Base64::serialize(::zorba::serialization::Archiver& ar)
{
  ar & theData;
}


void Base64::insertData(const char* aCharStar, size_t len)
{
  for (size_t i = 0; i < len; ++i)
  {
    char lChar = aCharStar[i];

    if (lChar == ' ')
    {
      // do nothing
    }
    else if ((lChar >= 65 && lChar <= 90)  // A-Z
         || (lChar >= 97 && lChar <= 122) // a-z
         || (lChar >= 48 && lChar <= 57)  // 0-9
         || (lChar == 43)                 // +
         || (lChar == 47))                // /
    {
      theData.push_back(lChar);
    }
    else if (lChar == '=' && i > 0 && i == (len-2) && aCharStar[i+1] == '=' )
    {
      if (aCharStar[i-1] == 'A' ||
          aCharStar[i-1] == 'Q' ||
          aCharStar[i-1] == 'g' ||
          aCharStar[i-1] == 'w')
      {
        theData.push_back('=');
        theData.push_back('=');
        ++i;
      }
      else
      {
        ZORBA_ERROR_DESC(FORG0001,"In Base 64, '==' must be at the end and must be succeed by [AQgw]");
      }
    }
    else if (lChar == '=' && i > 0 && i == (len-1))
    {
      switch(aCharStar[i-1]) 
      {
      case 'A': case 'E': case 'I': case 'M': case 'Q': case 'U': case 'Y':
      case 'c': case 'g': case 'k': case 'o': case 's': case 'w': case '0':
      case '4': case '8':
        theData.push_back('=');
        break;
      default:
        ZORBA_ERROR_DESC(FORG0001,"In Base 64, '=' must be at the end and must be succeed by [AEIMQUYcgkosw048]");
      }
    }
    else if ( xmlWhitespaceChar(lChar) ) 
    {
      // ignore it
    }
    else
    {
      std::stringstream lStream;
      lStream << "invalid character '" << aCharStar[i] << "' in Base64 value";
      ZORBA_ERROR_DESC(FORG0001, lStream.str());
    }
  }

  if (theData.size() % 4 != 0) 
  {
    ZORBA_ERROR_DESC(FORG0001, "Base64 input must be a multiple of four characters");
  }
}


bool Base64::equal(const Base64& aBase64) const
{
  if (size() != aBase64.size())
    return false;

  std::vector<char>::const_iterator lIter0 = theData.begin();
  std::vector<char>::const_iterator lEnd0 = theData.end();
  std::vector<char>::const_iterator lIter1 = aBase64.theData.begin();

  for (; lIter0 != lEnd0 ; )
  {
    if (*lIter0 != *lIter1)
      return false;
    ++lIter0; ++lIter1;
  }
  return true;
}


xqpStringStore_t Base64::str() const 
{
  std::stringstream lStream;
  lStream << *this;
  return new xqpStringStore(lStream.str());
}


xqpStringStore_t Base64::decode() const
{
  std::vector<char> lDecodedData;

  Base64::decode(theData, lDecodedData);

  xqpStringStore_t result = new xqpStringStore(lDecodedData.size());
  std::string& str = result->str();

  for (unsigned int i = 0; i < lDecodedData.size(); ++i)
    str[i] = lDecodedData[i];

  return result;
}


void Base64::decode(std::vector<char>& aResult)
{
  Base64::decode(theData, aResult);
}


uint32_t Base64::hash() const
{
  uint32_t lHash = 0;
  std::vector<char>::const_iterator lIter = theData.begin();
  std::vector<char>::const_iterator lEnd = theData.end();
  for(;lIter!=lEnd;++lIter)
  {
    uint32_t lDiff = 65535-*lIter;
    if (lDiff < lHash)
    {
      lHash = lHash - lDiff;
    } else {
      lHash += *lIter; 
    }
  }
  return lHash;
}


std::ostream& operator<<(std::ostream& os, const Base64& aBase64)
{
  std::vector<char>::const_iterator lIter = aBase64.getData().begin();
  std::vector<char>::const_iterator lEnd = aBase64.getData().end();
  for( ; lIter != lEnd ; ++lIter)
  {
    os << *lIter;
  }
  return os;
}


const char* Base16::ENCODE_TABLE = "0123456789ABCDEF";

const unsigned char Base16::DECODE_TABLE[ 0x80 ] = {
  /*00-07*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  /*08-0f*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  /*10-17*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  /*18-1f*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  /*20-27*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  /*28-2f*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  /*30-37*/ 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, //8 = '0'-'7'
  /*38-3f*/ 0x08, 0x09, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, //2 = '8'-'9'
  /*40-47*/ 0xFF, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0xFF, //6 = 'A'-'F'
  /*48-4f*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  /*50-57*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  /*58-5f*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  /*60-67*/ 0xFF, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0xFF, //6 = 'a'-'f' (same as 'A'-'F')
  /*68-6f*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  /*70-77*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  /*78-7f*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

size_t Base16::ENCODE_INPUT = 1;
size_t Base16::ENCODE_OUTPUT = 2;
size_t Base16::DECODE_INPUT = 2;
size_t Base16::DECODE_OUTPUT = 1;


Base16::Base16(const Base64& aBase64) : ::zorba::serialization::SerializeBaseClass()
{
  std::vector<char> lOrig;
  Base64::decode(aBase64.getData(), lOrig);
  Base16::encode(lOrig, theData);
}


void Base16::serialize(::zorba::serialization::Archiver& ar)
{
  ar & theData;
}


bool Base16::parseString(const char* aString, size_t aLength, Base16& aBase16)
{
  aBase16.theData.clear();
  try 
  {
    aBase16.insertData(aString, aLength);
  }
  catch (...)
  {
    return false;
  }
  return true;
}

void Base16::insertData(const char* aCharStar, size_t len)
{

  if (len % 2 != 0) {
    ZORBA_ERROR_DESC(FORG0001, "A hexBinary value must contain an even number of characters");
  }

  for (size_t i = 0; i < len; ++i)
  {
    char lChar = aCharStar[i];
    if ((lChar >= 65 && lChar <= 70)  // A-F
     || (lChar >= 48 && lChar <= 57))  // 0-9
    {
      theData.push_back(lChar);
    } else if (lChar >= 97 && lChar <= 102) // a-f
    {
      theData.push_back(lChar-32);
    } else {
      std::stringstream lStream;
      lStream << "Invalid hexadecimal digit";
      ZORBA_ERROR_DESC(FORG0001, lStream.str());
    }
  }
}


bool Base16::equal(const Base16& aBase16) const
{
  if (size() != aBase16.size())
    return false;

  std::vector<char>::const_iterator lIter0 = theData.begin();
  std::vector<char>::const_iterator lEnd0 = theData.end();
  std::vector<char>::const_iterator lIter1 = aBase16.theData.begin();

  for (; lIter0 != lEnd0 ; )
  {
    if (*lIter0 != *lIter1)
      return false;
    ++lIter0; ++lIter1;
  }
  return true;
}


xqpStringStore_t Base16::str() const 
{
  std::stringstream lStream;
  lStream << *this;
  return new xqpStringStore(lStream.str());
}


void Base16::encode(const std::vector<char>& aSource, std::vector<char>& aResult)
{
  size_t lSrcPos = 0;
  size_t lSrcSize = aSource.size();

  while (lSrcSize >= 1)
  {
    // 1 input...
    char ch = aSource[lSrcPos++];
    lSrcSize -= ENCODE_INPUT; //1

    // 2 outputs...
    aResult.push_back(ENCODE_TABLE[ (ch & 0xf0) >> 4 ]);
    aResult.push_back(ENCODE_TABLE[ (ch & 0x0f)      ]);
  }
}


void Base16::decode(const std::vector<char>& aSource, std::vector<char>& aResult)
{
  size_t lSrcSize = aSource.size();
  size_t lSrcPos = 0;
  assert(lSrcSize % DECODE_INPUT == 0);

  while (lSrcSize >= 1)
  {
    // 2 inputs...
    char in1 = aSource[lSrcPos++];
    char in2 = aSource[lSrcPos++];
    lSrcSize -= DECODE_INPUT;

    // Validate ascii...
    assert( 0 <= in1 /*&& in1 <= 0x7f*/ );
    assert( 0 <= in2 /*&& in2 <= 0x7f*/ );

    // Convert ascii to base16...
    in1 = DECODE_TABLE[ int(in1) ];
    in2 = DECODE_TABLE[ int(in2) ];

    // Validate base16...
    /*assert( in1 != 0xff );*/
    assert( 0 <= in1 && in1 <= 15 );
    assert( 0 <= in2 && in2 <= 15 );

    // 1 output...
    aResult.push_back(((in1 << 4) | in2));
  }
}

uint32_t Base16::hash() const
{
  uint32_t lHash = 0;
  std::vector<char>::const_iterator lIter = theData.begin();
  std::vector<char>::const_iterator lEnd = theData.end();
  for(;lIter!=lEnd;++lIter)
  {
    uint32_t lDiff = 65535-*lIter;
    if (lDiff < lHash)
    {
      lHash = lHash - lDiff;
    } else {
      lHash += *lIter; 
    }
  }
  return lHash;
}


std::ostream& operator<<(std::ostream& os, const Base16& aBase16)
{
  std::vector<char>::const_iterator lIter = aBase16.getData().begin();
  std::vector<char>::const_iterator lEnd = aBase16.getData().end();
  for( ; lIter != lEnd ; ++lIter)
  {
    os << *lIter;
  }
  return os;
}


} // namespace zorba
