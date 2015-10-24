/*
 * Copyright (C) 2004 by Objective Systems, Inc.
 *
 * This software is furnished under an open source license and may be 
 * used and copied only in accordance with the terms of this license. 
 * The text of the license may generally be found in the root 
 * directory of this installation in the LICENSE.txt file.  It 
 * can also be viewed online at the following URL:
 *
 *   http://www.obj-sys.com/open/license.html
 *
 * Any redistributions of this file including modified versions must 
 * maintain this copyright notice.
 *
 *****************************************************************************/

#include <stdlib.h>
#include "ooasn1.h"
#include <math.h>
#include "Media\g72x.h"
#include "Media\g711.h"

static int encode16BitConstrainedString 
(OOCTXT* pctxt, Asn116BitCharString value, Asn116BitCharSet* pCharSet);

static int encode2sCompBinInt (OOCTXT* pctxt, ASN1INT value);
static int encodeNonNegBinInt (OOCTXT* pctxt, ASN1UINT value);
static int encodeUnconsLength (OOCTXT* pctxt, ASN1UINT value);
static int getIdentByteCount (ASN1UINT ident);

int encodeBit (OOCTXT* pctxt, ASN1BOOL value)
{ 
   int stat = ASN_OK;

   /* If start of new byte, init to zero */

   if (pctxt->buffer.bitOffset == 8) {
      pctxt->buffer.data[pctxt->buffer.byteIndex] = 0;
   }

   /* Adjust bit offset and determine if at end of current byte */

   if (--pctxt->buffer.bitOffset < 0) {
      if (++pctxt->buffer.byteIndex >= pctxt->buffer.size) {
         if ((stat = encodeExpandBuffer (pctxt, 1)) != ASN_OK) {
            return stat;
         }
      }
      pctxt->buffer.data[pctxt->buffer.byteIndex] = 0;
      pctxt->buffer.bitOffset = 7;
   }

   /* Set single-bit value */

   if (value) {
      pctxt->buffer.data[pctxt->buffer.byteIndex] |= 
         ( 1 << pctxt->buffer.bitOffset );
   }

   /* If last bit in octet, set offsets to start new byte (ED, 9/7/01) */

   if (pctxt->buffer.bitOffset == 0) {
      pctxt->buffer.bitOffset = 8;
      pctxt->buffer.byteIndex++;
      pctxt->buffer.data[pctxt->buffer.byteIndex] = 0;
   }

   return stat;
}

int encodeBits (OOCTXT* pctxt, ASN1UINT value, ASN1UINT nbits)
{ 
   int nbytes = (nbits + 7)/ 8, stat = ASN_OK;

   if (nbits == 0) return stat;

   /* If start of new byte, init to zero */

   if (pctxt->buffer.bitOffset == 8) {
      pctxt->buffer.data[pctxt->buffer.byteIndex] = 0;
   }

   /* Mask off unused bits from the front of the value */

   if (nbits < (sizeof(ASN1UINT) * 8))
      value &= ((1 << nbits) - 1);

   /* If bits will fit in current byte, set them and return */

   if (nbits < (unsigned)pctxt->buffer.bitOffset) {
      pctxt->buffer.bitOffset -= nbits;
      pctxt->buffer.data[pctxt->buffer.byteIndex] |= 
         ( value << pctxt->buffer.bitOffset );
      return stat;
   }

   /* Check buffer space and allocate more memory if necessary */

   stat = encodeCheckBuffer (pctxt, nbytes);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* Set bits in remainder of the current byte and then loop   */
   /* to set bits in subsequent bytes..                         */

   nbits -= pctxt->buffer.bitOffset;
   pctxt->buffer.data[pctxt->buffer.byteIndex++] |= 
      (ASN1OCTET)( value >> nbits );
   pctxt->buffer.data[pctxt->buffer.byteIndex] = 0; 

   while (nbits >= 8) {
      nbits -= 8;
      pctxt->buffer.data[pctxt->buffer.byteIndex++] = 
         (ASN1OCTET)( value >> nbits );
      pctxt->buffer.data[pctxt->buffer.byteIndex] = 0; 
   }

   /* copy final partial byte */

   pctxt->buffer.bitOffset = 8 - nbits;
   if (nbits > 0) {
      pctxt->buffer.data[pctxt->buffer.byteIndex] = 
         (ASN1OCTET)((value & ((1 << nbits)-1)) << pctxt->buffer.bitOffset);
   }
   else
      pctxt->buffer.data[pctxt->buffer.byteIndex] = 0;

   return stat;
}

int encodeBitsFromOctet (OOCTXT* pctxt, ASN1OCTET value, ASN1UINT nbits)
{ 
   int lshift = pctxt->buffer.bitOffset;
   int rshift = 8 - pctxt->buffer.bitOffset;
   int stat = ASN_OK;
   ASN1OCTET mask;

   if (nbits == 0) return ASN_OK;

   /* Mask off unused bits from the end of the value */

   if (nbits < 8) {
      switch (nbits) {
      case 1: mask = 0x80; break;
      case 2: mask = 0xC0; break;
      case 3: mask = 0xE0; break;
      case 4: mask = 0xF0; break;
      case 5: mask = 0xF8; break;
      case 6: mask = 0xFC; break;
      case 7: mask = 0xFE; break;
      default:;
      }
      value &= mask;
   }

   /* If we are on a byte boundary, we can do a direct assignment */

   if (pctxt->buffer.bitOffset == 8) {
      pctxt->buffer.data[pctxt->buffer.byteIndex] = value;
      if (nbits == 8) {
         pctxt->buffer.byteIndex++;
         pctxt->buffer.data[pctxt->buffer.byteIndex] = 0;
      }
      else
         pctxt->buffer.bitOffset -= nbits;
   }

   /* Otherwise, need to set some bits in the first octet and   */
   /* possibly some bits in the following octet..               */

   else {
      pctxt->buffer.data[pctxt->buffer.byteIndex] |= 
         (ASN1OCTET)(value >> rshift);

      pctxt->buffer.bitOffset -= nbits;

      if (pctxt->buffer.bitOffset < 0) {
         pctxt->buffer.byteIndex++;
         pctxt->buffer.data[pctxt->buffer.byteIndex] = 
            (ASN1OCTET)(value << lshift);
         pctxt->buffer.bitOffset += 8;
      }
   }

   return stat;
}

int encodeBitString (OOCTXT* pctxt, ASN1UINT numbits, const ASN1OCTET* data)
{
   int enclen, octidx = 0, stat;
   Asn1SizeCnst* pSizeList = pctxt->pSizeConstraint;

   for (;;) {
      if ((enclen = encodeLength (pctxt, numbits)) < 0) {
         return LOG_ASN1ERR (pctxt, enclen);
      }

      if (enclen > 0) {
         ASN1BOOL doAlign;

         stat = bitAndOctetStringAlignmentTest 
            (pSizeList, numbits, TRUE, &doAlign);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

         if (doAlign) {
            stat = encodeByteAlign (pctxt);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeOctets (pctxt, &data[octidx], enclen);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }

      if (enclen < (int)numbits) {
         numbits -= enclen;
         octidx += (enclen/8);
      }
      else break;
   }

   return ASN_OK;
}

int encodeBMPString 
(OOCTXT* pctxt, ASN1BMPString value, Asn116BitCharSet* permCharSet)
{
   Asn116BitCharSet charSet;
   int stat;

   /* Set character set */

   init16BitCharSet (&charSet, BMP_FIRST, BMP_LAST, BMP_ABITS, BMP_UBITS);

   if (permCharSet) {
      set16BitCharSet (pctxt, &charSet, permCharSet);
   }

   /* Encode constrained string */

   stat = encode16BitConstrainedString (pctxt, value, &charSet);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return stat;
}

int encodeByteAlign (OOCTXT* pctxt)
{
   if (pctxt->buffer.bitOffset != 8) {
      if ((pctxt->buffer.byteIndex + 1) >= pctxt->buffer.size) {
         int stat = encodeExpandBuffer (pctxt, 1);
         if (stat != ASN_OK) return (stat);
      }
      pctxt->buffer.byteIndex++;
      pctxt->buffer.bitOffset = 8;
      pctxt->buffer.data[pctxt->buffer.byteIndex] = 0;
   }

   return ASN_OK;
}

int encodeCheckBuffer (OOCTXT* pctxt, ASN1UINT nbytes)
{
   int stat = ASN_OK;

   /* Add one to required bytes because increment logic will always     */
   /* init the byte at the incremented index to zero..                  */

   if ( ( pctxt->buffer.byteIndex + nbytes + 1 ) >= pctxt->buffer.size ) {
      if ((stat = encodeExpandBuffer (pctxt, nbytes+1)) != ASN_OK) {
         return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

int encodeConsInteger 
(OOCTXT* pctxt, ASN1INT value, ASN1INT lower, ASN1INT upper)
{ 
   ASN1UINT range_value;
   ASN1UINT adjusted_value;
   int stat;

   /* Check value against given range */

   if (value < lower || value > upper) {
      return ASN_E_CONSVIO;
   }

   /* Adjust range value based on lower/upper signed values and */
   /* other possible conflicts..                                */

   if ((upper > 0 && lower >= 0) || (upper <= 0 && lower < 0)) {
      range_value = upper - lower;
      adjusted_value = value - lower;
   }
   else {
      range_value = upper + abs(lower);
      adjusted_value = value + abs(lower);
   }      

   if (range_value != ASN1UINT_MAX) { range_value += 1; }

   if (range_value == 0 || lower > upper)
      stat = ASN_E_RANGERR;
   else if (lower != upper) {
      stat = encodeConsWholeNumber (pctxt, adjusted_value, range_value);
   }
   else
      stat = ASN_OK;

   return stat;
}

int encodeConsUnsigned 
(OOCTXT* pctxt, ASN1UINT value, ASN1UINT lower, ASN1UINT upper)
{ 
   ASN1UINT range_value;
   ASN1UINT adjusted_value;
   int stat;

   /* Check for special case: if lower is 0 and upper is ASN1UINT_MAX,  */
   /* set range to ASN1UINT_MAX; otherwise to upper - lower + 1         */

   range_value = (lower == 0 && upper == ASN1UINT_MAX) ?
      ASN1UINT_MAX : upper - lower + 1;

   adjusted_value = value - lower;

   if (lower != upper) {
      stat = encodeConsWholeNumber (pctxt, adjusted_value, range_value);
   }
   else
      stat = ASN_OK;

   return stat;
}

int encodeConsWholeNumber 
(OOCTXT* pctxt, ASN1UINT adjusted_value, ASN1UINT range_value)
{ 
   ASN1UINT nocts, range_bitcnt = getUIntBitCount (range_value - 1);
   int stat;

   if (adjusted_value >= range_value && range_value != ASN1UINT_MAX) {
      return LOG_ASN1ERR (pctxt, ASN_E_RANGERR);
   }

   /* If range is <= 255, bit-field case (10.5.7a) */

   if (range_value <= 255) {
      return encodeBits (pctxt, adjusted_value, range_bitcnt);
   }

   /* If range is exactly 256, one-octet case (10.5.7b) */

   else if (range_value == 256) {
      stat = encodeByteAlign (pctxt);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      return encodeBits (pctxt, adjusted_value, 8);
   }

   /* If range > 256 and <= 64k (65536), two-octet case (10.5.7c) */

   else if (range_value <= 65536) {
      stat = encodeByteAlign (pctxt);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      return encodeBits (pctxt, adjusted_value, 16);
   }

   /* If range > 64k, indefinite-length case (10.5.7d) */

   else {
      /* Encode length determinant as a constrained whole number.    */
      /* Constraint is 1 to max number of bytes needed to hold       */
      /* the target integer value..                                  */

      if (adjusted_value < 256) nocts = 1;
      else if (adjusted_value < 65536) nocts = 2;
      else if (adjusted_value < 0x1000000) nocts = 3;
      else nocts = 4;

      stat = encodeBits (pctxt, nocts - 1, 2);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeByteAlign (pctxt);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      return encodeNonNegBinInt (pctxt, adjusted_value);
   }
}

int encodeConstrainedStringEx (OOCTXT* pctxt, 
                            const char* string, 
                            const char* charSet,
                            ASN1UINT abits,  /* aligned char bits */
                            ASN1UINT ubits,  /* unaligned char bits */
                            ASN1UINT canSetBits)
{
   ASN1UINT i, len = strlen(string);
   int      stat;
   /* note: need to save size constraint for use in alignCharStr     */
   /* because it will be cleared in encodeLength from the context..        */
   Asn1SizeCnst* psize = pctxt->pSizeConstraint;

   /* Encode length */

   stat = encodeLength (pctxt, len);
   if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

   /* Byte align */

   if (alignCharStr (pctxt, len, abits, psize)) {
      stat = encodeByteAlign (pctxt);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* Encode data */

   if (abits >= canSetBits && canSetBits > 4) {
      for (i = 0; i < len; i++) {
         if ((stat = encodeBits (pctxt, string[i], abits)) != ASN_OK)
            return LOG_ASN1ERR (pctxt, stat);
      }
   }
   else if (0 != charSet) {
      ASN1UINT nchars = strlen(charSet), pos;
      const char* ptr;
      for (i = 0; i < len; i++) {
         ptr = memchr (charSet, string[i], nchars);

         if (0 == ptr)
            return LOG_ASN1ERR (pctxt, ASN_E_CONSVIO);
         else
            pos = ptr - charSet;

         if ((stat = encodeBits (pctxt, pos, abits)) != ASN_OK)
            return LOG_ASN1ERR (pctxt, stat);
      }
   }
   else return LOG_ASN1ERR (pctxt, ASN_E_INVPARAM);

   return stat;
}

int encodeExpandBuffer (OOCTXT* pctxt, ASN1UINT nbytes)
{
   if (pctxt->buffer.dynamic)
   {
      /* If dynamic encoding is enabled, expand the current buffer to   */
      /* allow encoding to continue.                                    */

      pctxt->buffer.size += ASN1MAX (ASN_K_ENCBUFSIZ, nbytes);

      pctxt->buffer.data = (ASN1OCTET*) memHeapRealloc
         (&pctxt->pMsgMemHeap, pctxt->buffer.data, pctxt->buffer.size);
      
      if (!pctxt->buffer.data) return (ASN_E_NOMEM);

      return (ASN_OK);
   }

   return (ASN_E_BUFOVFLW);
}

int encodeGetMsgBitCnt (OOCTXT* pctxt)
{
   int numBitsInLastByte = 8 - pctxt->buffer.bitOffset;
   return ((pctxt->buffer.byteIndex * 8) + numBitsInLastByte);
}

ASN1OCTET* encodeGetMsgPtr (OOCTXT* pctxt, int* pLength)
{
   if (pLength) *pLength = getPERMsgLen (pctxt);
   return pctxt->buffer.data;
}

int encodeIdent (OOCTXT* pctxt, ASN1UINT ident) 
{
   ASN1UINT mask;
   int nshifts = 0, stat;

   if (ident !=0) {
      ASN1UINT lv;
      nshifts = getIdentByteCount (ident);
      while (nshifts > 0) {
         mask = ((ASN1UINT)0x7f) << (7 * (nshifts - 1));
         nshifts--;
         lv = (ASN1UINT)((ident & mask) >> (nshifts * 7));
         if (nshifts != 0) { lv |= 0x80; }
         if ((stat = encodeBits (pctxt, lv, 8)) != ASN_OK)
            return LOG_ASN1ERR (pctxt, stat);
      }
   }
   else {
      /* encode a single zero byte */
      if ((stat = encodeBits (pctxt, 0, 8)) != ASN_OK)
         return LOG_ASN1ERR (pctxt, stat);
   }

   return ASN_OK;
}

int encodeLength (OOCTXT* pctxt, ASN1UINT value)
{ 
   ASN1BOOL extendable;
   Asn1SizeCnst* pSize = 
      checkSize (pctxt->pSizeConstraint, value, &extendable);
   ASN1UINT lower = (pSize) ? pSize->lower : 0;
   ASN1UINT upper = (pSize) ? pSize->upper : ASN1UINT_MAX;
   int enclen, stat;

   /* If size constraints exist and the given length did not fall       */
   /* within the range of any of them, signal constraint violation      */
   /* error..                                                           */

   if (pctxt->pSizeConstraint && !pSize) 
      return LOG_ASN1ERR (pctxt, ASN_E_CONSVIO);

   /* Reset the size constraint in the context block structure */

   pctxt->pSizeConstraint = 0;

   /* If size constraint is present and extendable, encode extension    */
   /* bit..                                                             */

   if (extendable) {
      stat = (pSize) ?
         encodeBit (pctxt, pSize->extended) : encodeBit (pctxt, 1);

      if (stat != ASN_OK) return (stat);
   }

   /* If upper limit is less than 64k, constrained case */

   if (upper < 65536) {
      stat = (lower == upper) ? ASN_OK :
         encodeConsWholeNumber (pctxt, value - lower, upper - lower + 1);
      enclen = (stat == ASN_OK) ? value : stat;
   }
   else {
      /* unconstrained case or Constrained with upper bound >= 64K*/
      enclen = encodeUnconsLength (pctxt, value);
   }

   return enclen;

}

int encodeObjectIdentifier (OOCTXT* pctxt, ASN1OBJID* pvalue)
{
   int len, stat;
   ASN1UINT temp;
   register int numids, i;

   /* Calculate length in bytes and encode */

   len = 1;  /* 1st 2 arcs require 1 byte */
   numids = pvalue->numids;
   for (i = 2; i < numids; i++) {
      len += getIdentByteCount (pvalue->subid[i]);
   }

   /* PER encode length */

   if ((stat = encodeLength (pctxt, (ASN1UINT)len)) < 0) {
      return LOG_ASN1ERR (pctxt, stat);
   }

   /* Validate given object ID by applying ASN.1 rules */

   if (0 == pvalue) return LOG_ASN1ERR (pctxt, ASN_E_INVOBJID);
   if (numids < 2) return LOG_ASN1ERR (pctxt, ASN_E_INVOBJID);
   if (pvalue->subid[0] > 2) return LOG_ASN1ERR (pctxt, ASN_E_INVOBJID);
   if (pvalue->subid[0] != 2 && pvalue->subid[1] > 39) 
      return LOG_ASN1ERR (pctxt, ASN_E_INVOBJID);

   /* Passed checks, encode object identifier */
   
   /* Munge first two sub ID's and encode */

   temp = ((pvalue->subid[0] * 40) + pvalue->subid[1]);
   if ((stat = encodeIdent (pctxt, temp)) != ASN_OK)
      return LOG_ASN1ERR (pctxt, stat);

   /* Encode the remainder of the OID value */

   for (i = 2; i < numids; i++) {
      if ((stat = encodeIdent (pctxt, pvalue->subid[i])) != ASN_OK)
         return LOG_ASN1ERR (pctxt, stat);
   }

   return ASN_OK;
}

int encodebitsFromOctet (OOCTXT* pctxt, ASN1OCTET value, ASN1UINT nbits)
{ 
   int lshift = pctxt->buffer.bitOffset;
   int rshift = 8 - pctxt->buffer.bitOffset;
   int stat = ASN_OK;
   ASN1OCTET mask;

   if (nbits == 0) return ASN_OK;

   /* Mask off unused bits from the end of the value */

   if (nbits < 8) {
      switch (nbits) {
      case 1: mask = 0x80; break;
      case 2: mask = 0xC0; break;
      case 3: mask = 0xE0; break;
      case 4: mask = 0xF0; break;
      case 5: mask = 0xF8; break;
      case 6: mask = 0xFC; break;
      case 7: mask = 0xFE; break;
      default:;
      }
      value &= mask;
   }

   /* If we are on a byte boundary, we can do a direct assignment */

   if (pctxt->buffer.bitOffset == 8) {
      pctxt->buffer.data[pctxt->buffer.byteIndex] = value;
      if (nbits == 8) {
         pctxt->buffer.byteIndex++;
         pctxt->buffer.data[pctxt->buffer.byteIndex] = 0;
      }
      else
         pctxt->buffer.bitOffset -= nbits;
   }

   /* Otherwise, need to set some bits in the first octet and   */
   /* possibly some bits in the following octet..               */

   else {
      pctxt->buffer.data[pctxt->buffer.byteIndex] |= 
         (ASN1OCTET)(value >> rshift);

      pctxt->buffer.bitOffset -= nbits;

      if (pctxt->buffer.bitOffset < 0) {
         pctxt->buffer.byteIndex++;
         pctxt->buffer.data[pctxt->buffer.byteIndex] = 
            (ASN1OCTET)(value << lshift);
         pctxt->buffer.bitOffset += 8;
      }
   }

   return stat;
}

int encodeOctets (OOCTXT* pctxt, const ASN1OCTET* pvalue, ASN1UINT nbits)
{ 
   int i = 0, stat;
   int numFullOcts = nbits / 8;

   if (nbits == 0) return 0;

   /* Check buffer space and allocate more memory if necessary */

   stat = encodeCheckBuffer (pctxt, numFullOcts + 1);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (numFullOcts > 0) {

      /* If the current bit offset is 8 (i.e. we don't have a      */
      /* byte started), can copy the string directly to the        */
      /* encode buffer..                                           */

      if (pctxt->buffer.bitOffset == 8) {
         memcpy (&pctxt->buffer.data[pctxt->buffer.byteIndex], pvalue, 
                 numFullOcts);
         pctxt->buffer.byteIndex += numFullOcts;
         pctxt->buffer.data[pctxt->buffer.byteIndex] = 0;
         i = numFullOcts;
      }

      /* Else, copy bits */

      else {
         for (i = 0; i < numFullOcts; i++) {
            stat = encodeBitsFromOctet (pctxt, pvalue[i], 8);
            if (stat != ASN_OK) return stat;
         }
      }
   }

   /* Move remaining bits from the last octet to the output buffer */

   if (nbits % 8 != 0) {
      stat = encodeBitsFromOctet (pctxt, pvalue[i], nbits % 8);
   }

   return stat;
}

int encodeOctetString (OOCTXT* pctxt, ASN1UINT numocts, const ASN1OCTET* data)
{
   int enclen, octidx = 0, stat;
   Asn1SizeCnst* pSizeList = pctxt->pSizeConstraint;

   for (;;) {
      if ((enclen = encodeLength (pctxt, numocts)) < 0) {
         return LOG_ASN1ERR (pctxt, enclen);
      }

      if (enclen > 0) {
         ASN1BOOL doAlign;

         stat = bitAndOctetStringAlignmentTest 
            (pSizeList, numocts, FALSE, &doAlign);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

         if (doAlign) {
            stat = encodeByteAlign (pctxt);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeOctets (pctxt, &data[octidx], enclen * 8);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }

      if (enclen < (int)numocts) {
         numocts -= enclen;
         octidx += enclen;
      }
      else break;
   }

   return ASN_OK;
}

int encodeOpenType (OOCTXT* pctxt, ASN1UINT numocts, const ASN1OCTET* data)
{
   int enclen, octidx = 0, stat;
   ASN1OCTET zeroByte = 0x00;
   ASN1OpenType openType;

   /* If open type contains length zero, add a single zero byte (10.1) */

   if (numocts == 0) {
      openType.numocts = 1;
      openType.data = &zeroByte;
   }
   else {
      openType.numocts = numocts;
      openType.data = data;
   }

   /* Encode the open type */

   for (;;) {
      if ((enclen = encodeLength (pctxt, openType.numocts)) < 0) {
         return LOG_ASN1ERR (pctxt, enclen);
      }

      stat = encodeByteAlign (pctxt);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOctets (pctxt, &openType.data[octidx], enclen * 8);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      if (enclen < (int)openType.numocts) {
         openType.numocts -= enclen;
         octidx += enclen;
      }
      else break;
   }

   return ASN_OK;
}

int encodeOpenTypeExt (OOCTXT* pctxt, DList* pElemList)
{
   DListNode* pnode;
   ASN1OpenType* pOpenType;
   int stat;

   if (0 != pElemList) {
      pnode = pElemList->head;
      while (0 != pnode) {
         if (0 != pnode->data) {
            pOpenType = (ASN1OpenType*)pnode->data;

            if (pOpenType->numocts > 0) {
               stat = encodeByteAlign (pctxt);
               if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

               stat = encodeOpenType 
                  (pctxt, pOpenType->numocts, pOpenType->data);

               if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            }
         }
         pnode = pnode->next;
      }
   }

   return ASN_OK;
}

int encodeOpenTypeExtBits (OOCTXT* pctxt, DList* pElemList)
{
   DListNode* pnode;
   int stat;

   if (0 != pElemList) {
      pnode = pElemList->head;

      while (0 != pnode) {
         stat = encodeBit (pctxt, (ASN1BOOL)(0 != pnode->data));
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

         pnode = pnode->next;
      }
   }

   return ASN_OK;
}

int encodeSemiConsInteger (OOCTXT* pctxt, ASN1INT value, ASN1INT lower)
{
   int nbytes, stat;
   int shift = ((sizeof(value) - 1) * 8) - 1;
   ASN1UINT tempValue;

   if (lower > ASN1INT_MIN)
      value -= lower;
   
   /* Calculate signed number value length */

   for ( ; shift > 0; shift -= 8) {
      tempValue = (value >> shift) & 0x1ff;
      if (tempValue == 0 || tempValue == 0x1ff) continue;
      else break;
   }

   nbytes = (shift + 9) / 8;

   /* Encode length */

   if ((stat = encodeLength (pctxt, nbytes)) < 0) {
      return stat;
   }

   if ((stat = encodeByteAlign (pctxt)) != ASN_OK)
      return stat;

   /* Encode signed value */

   stat = encode2sCompBinInt (pctxt, value);

   return stat;
}

int encodeSemiConsUnsigned (OOCTXT* pctxt, ASN1UINT value, ASN1UINT lower)
{
   int nbytes, stat;
   int shift = ((sizeof(value) - 1) * 8) - 1;
   ASN1UINT mask = 1UL << ((sizeof(value) * 8) - 1);
   ASN1UINT tempValue;

   value -= lower;

   /* Calculate unsigned number value length */

   for ( ; shift > 0; shift -= 8) {
      tempValue = (value >> shift) & 0x1ff;

      if (tempValue == 0) continue;
      else break;
   }

   nbytes = (shift + 9) / 8;

   /* If MS bit in unsigned number is set, add an extra zero byte */

   if ((value & mask) != 0) nbytes++;

   /* Encode length */

   if ((stat = encodeLength (pctxt, nbytes)) < 0) {
      return stat;
   }
   
   if ((stat = encodeByteAlign (pctxt)) != ASN_OK)
      return stat;
   
   /* Encode additional zero byte if necessary */

   if (nbytes > sizeof(value)) {
      stat = encodebitsFromOctet (pctxt, 0, 8);
      if (stat != ASN_OK) return (stat);
   }

   /* Encode unsigned value */

   stat = encodeNonNegBinInt (pctxt, value);

   return stat;
}

int encodeSmallNonNegWholeNumber (OOCTXT* pctxt, ASN1UINT value)
{ 
   int stat;

   if (value < 64) {
      stat = encodeBits (pctxt, value, 7);
   }
   else {
      ASN1UINT len;

      /* Encode a one-byte length determinant value */
      if (value < 256) len = 1;
      else if (value < 65536) len = 2;
      else if (value < 0x1000000) len = 3;
      else len = 4;

      stat = encodeBits (pctxt, len, 8);

      /* Byte-align and encode the value */
      if (stat == ASN_OK) {
         if ((stat = encodeByteAlign (pctxt)) == ASN_OK) {
            stat = encodeBits (pctxt, value, len*8);
         }
      }
   }

   return stat;
}

int encodeVarWidthCharString (OOCTXT* pctxt, const char* value)
{
   int         stat;
   ASN1UINT    len = strlen (value);
   /* note: need to save size constraint for use in alignCharStr     */
   /* because it will be cleared in encodeLength from the context..        */
   Asn1SizeCnst* psize = pctxt->pSizeConstraint;

   /* Encode length */

   stat = encodeLength (pctxt, len);
   if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

   /* Byte align */

   if (alignCharStr (pctxt, len, 8, psize)) {
      stat = encodeByteAlign (pctxt);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* Encode data */

   stat = encodeOctets (pctxt, (const ASN1OCTET*)value, len * 8);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return ASN_OK;
}

static int encode16BitConstrainedString 
(OOCTXT* pctxt, Asn116BitCharString value, Asn116BitCharSet* pCharSet)
{
   ASN1UINT i, pos;
   ASN1UINT nbits = pCharSet->alignedBits;
   int stat;

   /* Encode length */

   stat = encodeLength (pctxt, value.nchars);
   if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

   /* Byte align */

   stat = encodeByteAlign (pctxt);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* Encode data */

   for (i = 0; i < value.nchars; i++) {
      if (pCharSet->charSet.data == 0) {
         stat = encodeBits 
            (pctxt, value.data[i] - pCharSet->firstChar, nbits);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
      else {
         for (pos = 0; pos < pCharSet->charSet.nchars; pos++) {
            if (value.data[i] == pCharSet->charSet.data[pos]) {
               stat = encodeBits (pctxt, pos, nbits);
               if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
               break;
            }
         }
      }
   }

   return stat;
}

int encode2sCompBinInt (OOCTXT* pctxt, ASN1INT value)
{
   /* 10.4.6  A minimum octet 2's-complement-binary-integer encoding    */
   /* of the whole number has a field width that is a multiple of 8     */
   /* bits and also satisifies the condition that the leading 9 bits    */
   /* field shall not be all zeros and shall not be all ones.           */

   /* first encode integer value into a local buffer */

   ASN1OCTET lbuf[8], lb;
   ASN1INT   i = sizeof(lbuf), temp = value;

   memset (lbuf, 0, sizeof(lbuf));
   do {
      lb = temp % 256;
      temp /= 256;
      if (temp < 0 && lb != 0) temp--; /* two's complement adjustment */
      lbuf[--i] = lb;
   } while (temp != 0 && temp != -1);

   /* If the value is positive and bit 8 of the leading byte is set,    */
   /* copy a zero byte to the contents to signal a positive number..    */

   if (value > 0 && (lb & 0x80) != 0) {
      i--;
   }

   /* If the value is negative and bit 8 of the leading byte is clear,  */
   /* copy a -1 byte (0xFF) to the contents to signal a negative        */
   /* number..                                                          */

   else if (value < 0 && ((lb & 0x80) == 0)) {
      lbuf[--i] = 0xff;
   }

   /* Add the data to the encode buffer */

   return encodeOctets (pctxt, &lbuf[i], (sizeof(lbuf) - i) * 8);
}

static int encodeNonNegBinInt (OOCTXT* pctxt, ASN1UINT value)
{
   /* 10.3.6  A minimum octet non-negative binary integer encoding of   */
   /* the whole number (which does not predetermine the number of       */
   /* octets to be used for the encoding) has a field which is a        */
   /* multiple of 8 bits and also satisifies the condition that the     */
   /* leading eight bits of the field shall not be zero unless the      */
   /* field is precisely 8 bits long.                                   */
 
   ASN1UINT bitcnt = (value == 0) ? 1 : getUIntBitCount (value);

   /* round-up to nearest 8-bit boundary */

   bitcnt = (bitcnt + 7) & (~7);

   /* encode bits */

   return encodeBits (pctxt, value, bitcnt);
}

static int encodeUnconsLength (OOCTXT* pctxt, ASN1UINT value)
{
   int enclen, stat;

   stat = encodeByteAlign (pctxt);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* 1 octet case */
   if (value < 128) {
      stat = encodeBits (pctxt, value, 8);
      enclen = (stat == ASN_OK) ? value : stat;
   }
   /* 2 octet case */
   else if (value < 16384) {
      if ((stat = encodeBit (pctxt, 1)) == ASN_OK)
         stat = encodeBits (pctxt, value, 15);
      enclen = (stat == ASN_OK) ? value : stat;
   }
   /* fragmentation case */
   else {
      int multiplier = ASN1MIN (value/16384, 4);
      encodeBit (pctxt, 1);  /* set bit 8 of first octet */
      encodeBit (pctxt, 1);  /* set bit 7 of first octet */
      stat = encodeBits (pctxt, multiplier, 6);
      enclen = (stat == ASN_OK) ? 16384 * multiplier : stat;
   }

   return enclen;
}

static int getIdentByteCount (ASN1UINT ident) 
{
   if (ident < (1u << 7)) {         /* 7 */
      return 1;
   }
   else if (ident < (1u << 14)) {   /* 14 */
      return 2;
   }
   else if (ident < (1u << 21)) {   /* 21 */
      return 3;
   }
   else if (ident < (1u << 28)) {   /* 28 */
      return 4;
   }
   return 5;
}


/*Added by Karl on 2004-11-24 for G72x below */
//Global data def
int		gnTarget_Memory_Size = 2;	//2m
int		gnBits = 4;
int		gnPCM_Gain = 0;				//1x
int		gnWait_Length = 40;			//40*128ms = 5s
//LPCSTR	gpOutput_File_Name = NULL;
int	gbBinary = TRUE;
int	gnOutBuffCounter = 0;

int pack_output(unsigned code, int bits, unsigned char *pDataTrack)
{
	static int		wOutBuff = 0;
	static int		nOutBits = 0;
	unsigned char	bOutByte;
	unsigned char	bLeft = 0;
    /*Modified by Joe and karl on 2005-01-17 below*/
	wOutBuff <<= bits;
	wOutBuff |= code;
	nOutBits += bits;
	if (nOutBits >= 8) {
		bLeft = wOutBuff & 0xff;
		bLeft <<= 8- (nOutBits - 8);
		bLeft >>= 8- (nOutBits - 8);
		bOutByte = wOutBuff >> (nOutBits - 8);//È¡¸ß8Î»
		nOutBits -= 8;
		//wOutBuff >>= 8;        
		pDataTrack[gnOutBuffCounter] = bOutByte;
		wOutBuff = bLeft;
		gnOutBuffCounter++;
	}
	/*Modified by Joe and karl on 2005-01-17 above*/
	return (nOutBits > 0);
}

static short power2[15] = {1, 2, 4, 8, 0x10, 0x20, 0x40, 0x80,
			0x100, 0x200, 0x400, 0x800, 0x1000, 0x2000, 0x4000};

/*
 * quan()
 *
 * quantizes the input val against the table of size short integers.
 * It returns i if table[i - 1] <= val < table[i].
 *
 * Using linear search for simple coding.
 */
static int
quan(
	int		val,
	short		*table,
	int		size)
{
	int		i;

	for (i = 0; i < size; i++)
		if (val < *table++)
			break;
	return (i);
}

/*
 * fmult()
 *
 * returns the integer product of the 14-bit integer "an" and
 * "floating point" representation (4-bit exponent, 6-bit mantessa) "srn".
 */
static int
fmult(
	int		an,
	int		srn)
{
	short		anmag, anexp, anmant;
	short		wanexp, wanmant;
	short		retval;

	anmag = (an > 0) ? an : ((-an) & 0x1FFF);
	anexp = quan(anmag, power2, 15) - 6;
	anmant = (anmag == 0) ? 32 :
	    (anexp >= 0) ? anmag >> anexp : anmag << -anexp;
	wanexp = anexp + ((srn >> 6) & 0xF) - 13;

	wanmant = (anmant * (srn & 077) + 0x30) >> 4;
	retval = (wanexp >= 0) ? ((wanmant << wanexp) & 0x7FFF) :
	    (wanmant >> -wanexp);

	return (((an ^ srn) < 0) ? -retval : retval);
}

/*
 * g72x_init_state()
 *
 * This routine initializes and/or resets the g72x_state structure
 * pointed to by 'state_ptr'.
 * All the initial state values are specified in the CCITT G.721 document.
 */
void
g72x_init_state(
	struct g72x_state *state_ptr)
{
	int		cnta;

	state_ptr->yl = 34816;
	state_ptr->yu = 544;
	state_ptr->dms = 0;
	state_ptr->dml = 0;
	state_ptr->ap = 0;
	for (cnta = 0; cnta < 2; cnta++) {
		state_ptr->a[cnta] = 0;
		state_ptr->pk[cnta] = 0;
		state_ptr->sr[cnta] = 32;
	}
	for (cnta = 0; cnta < 6; cnta++) {
		state_ptr->b[cnta] = 0;
		state_ptr->dq[cnta] = 32;
	}
	state_ptr->td = 0;
}

/*
 * predictor_zero()
 *
 * computes the estimated signal from 6-zero predictor.
 *
 */
int
predictor_zero(
	struct g72x_state *state_ptr)
{
	int		i;
	int		sezi;

	sezi = fmult(state_ptr->b[0] >> 2, state_ptr->dq[0]);
	for (i = 1; i < 6; i++)			/* ACCUM */
		sezi += fmult(state_ptr->b[i] >> 2, state_ptr->dq[i]);
	return (sezi);
}
/*
 * predictor_pole()
 *
 * computes the estimated signal from 2-pole predictor.
 *
 */
int
predictor_pole(
	struct g72x_state *state_ptr)
{
	return (fmult(state_ptr->a[1] >> 2, state_ptr->sr[1]) +
	    fmult(state_ptr->a[0] >> 2, state_ptr->sr[0]));
}
/*
 * step_size()
 *
 * computes the quantization step size of the adaptive quantizer.
 *
 */
int
step_size(
	struct g72x_state *state_ptr)
{
	int		y;
	int		dif;
	int		al;

	if (state_ptr->ap >= 256)
		return (state_ptr->yu);
	else {
		y = state_ptr->yl >> 6;
		dif = state_ptr->yu - y;
		al = state_ptr->ap >> 2;
		if (dif > 0)
			y += (dif * al) >> 6;
		else if (dif < 0)
			y += (dif * al + 0x3F) >> 6;
		return (y);
	}
}

/*
 * quantize()
 *
 * Given a raw sample, 'd', of the difference signal and a
 * quantization step size scale factor, 'y', this routine returns the
 * ADPCM codeword to which that sample gets quantized.  The step
 * size scale factor division operation is done in the log base 2 domain
 * as a subtraction.
 */
int
quantize(
	int		d,	/* Raw difference signal sample */
	int		y,	/* Step size multiplier */
	short		*table,	/* quantization table */
	int		size)	/* table size of short integers */
{
	short		dqm;	/* Magnitude of 'd' */
	short		exp;	/* Integer part of base 2 log of 'd' */
	short		mant;	/* Fractional part of base 2 log */
	short		dl;	/* Log of magnitude of 'd' */
	short		dln;	/* Step size scale factor normalized log */
	int		i;

	/*
	 * LOG
	 *
	 * Compute base 2 log of 'd', and store in 'dl'.
	 */
	dqm = abs(d);
	exp = quan(dqm >> 1, power2, 15);
	mant = ((dqm << 7) >> exp) & 0x7F;	/* Fractional portion. */
	dl = (exp << 7) + mant;

	/*
	 * SUBTB
	 *
	 * "Divide" by step size multiplier.
	 */
	dln = dl - (y >> 2);

	/*
	 * QUAN
	 *
	 * Obtain codword i for 'd'.
	 */
	i = quan(dln, table, size);
	if (d < 0)			/* take 1's complement of i */
		return ((size << 1) + 1 - i);
	else if (i == 0)		/* take 1's complement of 0 */
		return ((size << 1) + 1); /* new in 1988 */
	else
		return (i);
}
/*
 * reconstruct()
 *
 * Returns reconstructed difference signal 'dq' obtained from
 * codeword 'i' and quantization step size scale factor 'y'.
 * Multiplication is performed in log base 2 domain as addition.
 */
int
reconstruct(
	int		sign,	/* 0 for non-negative value */
	int		dqln,	/* G.72x codeword */
	int		y)	/* Step size multiplier */
{
	short		dql;	/* Log of 'dq' magnitude */
	short		dex;	/* Integer part of log */
	short		dqt;
	short		dq;	/* Reconstructed difference signal sample */

	dql = dqln + (y >> 2);	/* ADDA */

	if (dql < 0) {
		return ((sign) ? -0x8000 : 0);
	} else {		/* ANTILOG */
		dex = (dql >> 7) & 15;
		dqt = 128 + (dql & 127);
		dq = (dqt << 7) >> (14 - dex);
		return ((sign) ? (dq - 0x8000) : dq);
	}
}


/*
 * update()
 *
 * updates the state variables for each output code
 */
void
update(
	int		code_size,	/* distinguish 723_40 with others */
	int		y,		/* quantizer step size */
	int		wi,		/* scale factor multiplier */
	int		fi,		/* for long/short term energies */
	int		dq,		/* quantized prediction difference */
	int		sr,		/* reconstructed signal */
	int		dqsez,		/* difference from 2-pole predictor */
	struct g72x_state *state_ptr)	/* coder state pointer */
{
	int			cnt;
	short		mag, exp;	/* Adaptive predictor, FLOAT A */
	short		a2p;		/* LIMC */
	short		a1ul;		/* UPA1 */
	short		pks1;	/* UPA2 */
	short		fa1;
	char		tr;		/* tone/transition detector */
	short		ylint, thr2, dqthr;
	short  		ylfrac, thr1;
	short		pk0;

	pk0 = (dqsez < 0) ? 1 : 0;	/* needed in updating predictor poles */

	mag = dq & 0x7FFF;		/* prediction difference magnitude */
	/* TRANS */
	ylint = state_ptr->yl >> 15;	/* exponent part of yl */
	ylfrac = (state_ptr->yl >> 10) & 0x1F;	/* fractional part of yl */
	thr1 = (32 + ylfrac) << ylint;		/* threshold */
	thr2 = (ylint > 9) ? 31 << 10 : thr1;	/* limit thr2 to 31 << 10 */
	dqthr = (thr2 + (thr2 >> 1)) >> 1;	/* dqthr = 0.75 * thr2 */
	if (state_ptr->td == 0)		/* signal supposed voice */
		tr = 0;
	else if (mag <= dqthr)		/* supposed data, but small mag */
		tr = 0;			/* treated as voice */
	else				/* signal is data (modem) */
		tr = 1;

	/*
	 * Quantizer scale factor adaptation.
	 */

	/* FUNCTW & FILTD & DELAY */
	/* update non-steady state step size multiplier */
	state_ptr->yu = y + ((wi - y) >> 5);

	/* LIMB */
	if (state_ptr->yu < 544)	/* 544 <= yu <= 5120 */
		state_ptr->yu = 544;
	else if (state_ptr->yu > 5120)
		state_ptr->yu = 5120;

	/* FILTE & DELAY */
	/* update steady state step size multiplier */
	state_ptr->yl += state_ptr->yu + ((-state_ptr->yl) >> 6);

	/*
	 * Adaptive predictor coefficients.
	 */
	if (tr == 1) {			/* reset a's and b's for modem signal */
		state_ptr->a[0] = 0;
		state_ptr->a[1] = 0;
		state_ptr->b[0] = 0;
		state_ptr->b[1] = 0;
		state_ptr->b[2] = 0;
		state_ptr->b[3] = 0;
		state_ptr->b[4] = 0;
		state_ptr->b[5] = 0;
	} else {			/* update a's and b's */
		pks1 = pk0 ^ state_ptr->pk[0];		/* UPA2 */

		/* update predictor pole a[1] */
		a2p = state_ptr->a[1] - (state_ptr->a[1] >> 7);
		if (dqsez != 0) {
			fa1 = (pks1) ? state_ptr->a[0] : -state_ptr->a[0];
			if (fa1 < -8191)	/* a2p = function of fa1 */
				a2p -= 0x100;
			else if (fa1 > 8191)
				a2p += 0xFF;
			else
				a2p += fa1 >> 5;

			if (pk0 ^ state_ptr->pk[1])
				/* LIMC */
				if (a2p <= -12160)
					a2p = -12288;
				else if (a2p >= 12416)
					a2p = 12288;
				else
					a2p -= 0x80;
			else if (a2p <= -12416)
				a2p = -12288;
			else if (a2p >= 12160)
				a2p = 12288;
			else
				a2p += 0x80;
		}

		/* TRIGB & DELAY */
		state_ptr->a[1] = a2p;

		/* UPA1 */
		/* update predictor pole a[0] */
		state_ptr->a[0] -= state_ptr->a[0] >> 8;
		if (dqsez != 0)
			if (pks1 == 0)
				state_ptr->a[0] += 192;
			else
				state_ptr->a[0] -= 192;

		/* LIMD */
		a1ul = 15360 - a2p;
		if (state_ptr->a[0] < -a1ul)
			state_ptr->a[0] = -a1ul;
		else if (state_ptr->a[0] > a1ul)
			state_ptr->a[0] = a1ul;

		/* UPB : update predictor zeros b[6] */
		for (cnt = 0; cnt < 6; cnt++) {
			if (code_size == 5)		/* for 40Kbps G.723 */
				state_ptr->b[cnt] -= state_ptr->b[cnt] >> 9;
			else			/* for G.721 and 24Kbps G.723 */
				state_ptr->b[cnt] -= state_ptr->b[cnt] >> 8;
			if (dq & 0x7FFF) {			/* XOR */
				if ((dq ^ state_ptr->dq[cnt]) >= 0)
					state_ptr->b[cnt] += 128;
				else
					state_ptr->b[cnt] -= 128;
			}
		}
	}

	for (cnt = 5; cnt > 0; cnt--)
		state_ptr->dq[cnt] = state_ptr->dq[cnt-1];
	/* FLOAT A : convert dq[0] to 4-bit exp, 6-bit mantissa f.p. */
	if (mag == 0) {
		state_ptr->dq[0] = (dq >= 0) ? 0x20 : 0xFC20;
	} else {
		exp = quan(mag, power2, 15);
		state_ptr->dq[0] = (dq >= 0) ?
		    (exp << 6) + ((mag << 6) >> exp) :
		    (exp << 6) + ((mag << 6) >> exp) - 0x400;
	}

	state_ptr->sr[1] = state_ptr->sr[0];
	/* FLOAT B : convert sr to 4-bit exp., 6-bit mantissa f.p. */
	if (sr == 0) {
		state_ptr->sr[0] = 0x20;
	} else if (sr > 0) {
		exp = quan(sr, power2, 15);
		state_ptr->sr[0] = (exp << 6) + ((sr << 6) >> exp);
	} else if (sr > -32768) {
		mag = -sr;
		exp = quan(mag, power2, 15);
		state_ptr->sr[0] =  (exp << 6) + ((mag << 6) >> exp) - 0x400;
	} else
		state_ptr->sr[0] = 0xFC20;

	/* DELAY A */
	state_ptr->pk[1] = state_ptr->pk[0];
	state_ptr->pk[0] = pk0;

	/* TONE */
	if (tr == 1)		/* this sample has been treated as data */
		state_ptr->td = 0;	/* next one will be treated as voice */
	else if (a2p < -11776)	/* small sample-to-sample correlation */
		state_ptr->td = 1;	/* signal may be data */
	else				/* signal is voice */
		state_ptr->td = 0;

	/*
	 * Adaptation speed control.
	 */
	state_ptr->dms += (fi - state_ptr->dms) >> 5;		/* FILTA */
	state_ptr->dml += (((fi << 2) - state_ptr->dml) >> 7);	/* FILTB */

	if (tr == 1)
		state_ptr->ap = 256;
	else if (y < 1536)					/* SUBTC */
		state_ptr->ap += (0x200 - state_ptr->ap) >> 4;
	else if (state_ptr->td == 1)
		state_ptr->ap += (0x200 - state_ptr->ap) >> 4;
	else if (abs((state_ptr->dms << 2) - state_ptr->dml) >=
	    (state_ptr->dml >> 3))
		state_ptr->ap += (0x200 - state_ptr->ap) >> 4;
	else
		state_ptr->ap += (-state_ptr->ap) >> 4;
}

/*
 * tandem_adjust(sr, se, y, i, sign)
 *
 * At the end of ADPCM decoding, it simulates an encoder which may be receiving
 * the output of this decoder as a tandem process. If the output of the
 * simulated encoder differs from the input to this decoder, the decoder output
 * is adjusted by one level of A-law or u-law codes.
 *
 * Input:
 *	sr	decoder output linear PCM sample,
 *	se	predictor estimate sample,
 *	y	quantizer step size,
 *	i	decoder input code,
 *	sign	sign bit of code i
 *
 * Return:
 *	adjusted A-law or u-law compressed sample.
 */
int
tandem_adjust_alaw(
	int		sr,	/* decoder output linear PCM sample */
	int		se,	/* predictor estimate sample */
	int		y,	/* quantizer step size */
	int		i,	/* decoder input code */
	int		sign,
	short		*qtab)
{
	unsigned char	sp;	/* A-law compressed 8-bit code */
	short		dx;	/* prediction error */
	char		id;	/* quantized prediction error */
	int		sd;	/* adjusted A-law decoded sample value */
	int		im;	/* biased magnitude of i */
	int		imx;	/* biased magnitude of id */

	if (sr <= -32768)
		sr = -1;
	sp = linear2alaw((sr >> 1) << 3);	/* short to A-law compression */
	dx = (alaw2linear(sp) >> 2) - se;	/* 16-bit prediction error */
	id = quantize(dx, y, qtab, sign - 1);

	if (id == i) {			/* no adjustment on sp */
		return (sp);
	} else {			/* sp adjustment needed */
		/* ADPCM codes : 8, 9, ... F, 0, 1, ... , 6, 7 */
		im = i ^ sign;		/* 2's complement to biased unsigned */
		imx = id ^ sign;

		if (imx > im) {		/* sp adjusted to next lower value */
			if (sp & 0x80) {
				sd = (sp == 0xD5) ? 0x55 :
				    ((sp ^ 0x55) - 1) ^ 0x55;
			} else {
				sd = (sp == 0x2A) ? 0x2A :
				    ((sp ^ 0x55) + 1) ^ 0x55;
			}
		} else {		/* sp adjusted to next higher value */
			if (sp & 0x80)
				sd = (sp == 0xAA) ? 0xAA :
				    ((sp ^ 0x55) + 1) ^ 0x55;
			else
				sd = (sp == 0x55) ? 0xD5 :
				    ((sp ^ 0x55) - 1) ^ 0x55;
		}
		return (sd);
	}
}

int
tandem_adjust_ulaw(
	int		sr,	/* decoder output linear PCM sample */
	int		se,	/* predictor estimate sample */
	int		y,	/* quantizer step size */
	int		i,	/* decoder input code */
	int		sign,
	short		*qtab)
{
	unsigned char	sp;	/* u-law compressed 8-bit code */
	short		dx;	/* prediction error */
	char		id;	/* quantized prediction error */
	int		sd;	/* adjusted u-law decoded sample value */
	int		im;	/* biased magnitude of i */
	int		imx;	/* biased magnitude of id */

	if (sr <= -32768)
		sr = 0;
	sp = linear2ulaw(sr << 2);	/* short to u-law compression */
	dx = (ulaw2linear(sp) >> 2) - se;	/* 16-bit prediction error */
	id = quantize(dx, y, qtab, sign - 1);
	if (id == i) {
		return (sp);
	} else {
		/* ADPCM codes : 8, 9, ... F, 0, 1, ... , 6, 7 */
		im = i ^ sign;		/* 2's complement to biased unsigned */
		imx = id ^ sign;
		if (imx > im) {		/* sp adjusted to next lower value */
			if (sp & 0x80)
				sd = (sp == 0xFF) ? 0x7E : sp + 1;
			else
				sd = (sp == 0) ? 0 : sp - 1;

		} else {		/* sp adjusted to next higher value */
			if (sp & 0x80)
				sd = (sp == 0x80) ? 0x80 : sp - 1;
			else
				sd = (sp == 0x7F) ? 0xFE : sp + 1;
		}
		return (sd);
	}
}
static short qtab_721[7] = {-124, 80, 178, 246, 300, 349, 400};
/*
 * Maps G.721 code word to reconstructed scale factor normalized log
 * magnitude values.
 */
static short	_dqlntab[16] = {-2048, 4, 135, 213, 273, 323, 373, 425,
				425, 373, 323, 273, 213, 135, 4, -2048};

/* Maps G.721 code word to log of scale factor multiplier. */
static short	_witab[16] = {-12, 18, 41, 64, 112, 198, 355, 1122,
				1122, 355, 198, 112, 64, 41, 18, -12};
/*
 * Maps G.721 code words to a set of values whose long and short
 * term averages are computed and then compared to give an indication
 * how stationary (steady state) the signal is.
 */
static short	_fitab[16] = {0, 0, 0, 0x200, 0x200, 0x200, 0x600, 0xE00,
				0xE00, 0x600, 0x200, 0x200, 0x200, 0, 0, 0};

/*
 * g721_encoder()
 *
 * Encodes the input vale of linear PCM, A-law or u-law data sl and returns
 * the resulting code. -1 is returned for unknown input coding value.
 */
int
g721_encoder(
	int		sl,
	int		in_coding,
	struct g72x_state *state_ptr)
{
	short		sezi, se, sez;		/* ACCUM */
	short		d;			/* SUBTA */
	short		sr;			/* ADDB */
	short		y;			/* MIX */
	short		dqsez;			/* ADDC */
	short		dq, i;

	switch (in_coding) {	/* linearize input sample to 14-bit PCM */
	case AUDIO_ENCODING_ALAW:
		sl = alaw2linear(sl) >> 2;
		break;
	case AUDIO_ENCODING_ULAW:
		sl = ulaw2linear(sl) >> 2;
		break;
	case AUDIO_ENCODING_LINEAR:
		sl >>= 2;			/* 14-bit dynamic range */
		break;
	default:
		return (-1);
	}

	sezi = predictor_zero(state_ptr);
	sez = sezi >> 1;
	se = (sezi + predictor_pole(state_ptr)) >> 1;	/* estimated signal */

	d = sl - se;				/* estimation difference */

	/* quantize the prediction difference */
	y = step_size(state_ptr);		/* quantizer step size */
	i = quantize(d, y, qtab_721, 7);	/* i = ADPCM code */

	dq = reconstruct(i & 8, _dqlntab[i], y);	/* quantized est diff */

	sr = (dq < 0) ? se - (dq & 0x3FFF) : se + dq;	/* reconst. signal */

	dqsez = sr + sez - se;			/* pole prediction diff. */

	update(4, y, _witab[i] << 5, _fitab[i], dq, sr, dqsez, state_ptr);

	return (i);
}

/*
 * g721_decoder()
 *
 * Description:
 *
 * Decodes a 4-bit code of G.721 encoded data of i and
 * returns the resulting linear PCM, A-law or u-law value.
 * return -1 for unknown out_coding value.
 */
int
g721_decoder(
	int		i,
	int		out_coding,
	struct g72x_state *state_ptr)
{
	short		sezi, sei, sez, se;	/* ACCUM */
	short		y;			/* MIX */
	short		sr;			/* ADDB */
	short		dq;
	short		dqsez;

	i &= 0x0f;			/* mask to get proper bits */
	sezi = predictor_zero(state_ptr);
	sez = sezi >> 1;
	sei = sezi + predictor_pole(state_ptr);
	se = sei >> 1;			/* se = estimated signal */

	y = step_size(state_ptr);	/* dynamic quantizer step size */

	dq = reconstruct(i & 0x08, _dqlntab[i], y); /* quantized diff. */

	sr = (dq < 0) ? (se - (dq & 0x3FFF)) : se + dq;	/* reconst. signal */

	dqsez = sr - se + sez;			/* pole prediction diff. */

	update(4, y, _witab[i] << 5, _fitab[i], dq, sr, dqsez, state_ptr);

	switch (out_coding) {
	case AUDIO_ENCODING_ALAW:
		return (tandem_adjust_alaw(sr, se, y, i, 8, qtab_721));
	case AUDIO_ENCODING_ULAW:
		return (tandem_adjust_ulaw(sr, se, y, i, 8, qtab_721));
	case AUDIO_ENCODING_LINEAR:
		return (sr << 2);	/* sr was 14-bit dynamic range */
	default:
		return (-1);
	}
}


/*Added by Karl on 2004-11-24 for G72x above */