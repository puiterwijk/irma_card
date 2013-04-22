/**
 * utils.c
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope t_ it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (C) Pim Vullers, Radboud University Nijmegen, September 2011.
 */

#include "utils.h"

#include "externals.h"
#include "debug.h"
#include "types.h"
#include "SHA.h"
#include "encoding.h"
#include "memory.h"
#include "arithmetic.h"

/********************************************************************/
/* Cryptographic helper functions                                   */
/********************************************************************/

//////////////////////////////////////////////////////////////////////
// Shared functions                                                 //
//////////////////////////////////////////////////////////////////////

/**
 * Compute a cryptographic hash of the given input values
 *
 * @param list of values to be included in the hash
 * @param length of the values list
 * @param result of the hashing operation
 * @param buffer which can be used for temporary storage
 * @param size of the buffer
 */
void ComputeHash(ValueArray list, int length, ByteArray result,
                         ByteArray buffer, int size) {
  int i, offset = size;

  // Store the values
  for (i = length - 1; i >= 0; i--) {
    offset = asn1_encode_int(list[i].data, list[i].size, buffer, offset);
  }

  // Store the number of values in the sequence
  offset = asn1_encode_int((ByteArray) &length, 2, buffer, offset);

  // Finalise the sequence
  offset = asn1_encode_seq(size - offset, length, buffer, offset);

  // Hash the data
  debugValue("asn1rep", buffer + offset, size - offset);
  SHA(SHA_256, result, size - offset, buffer + offset);
}

/**
 * Compute the helper value S' = S^(2_l) where l = SIZE_S_EXPONENT*8
 *
 * This value is required for exponentiations with base S and an
 * exponent which is larger than SIZE_N bytes.
 */
void ComputeS_(void) {
  // Store the value l = SIZE_S_EXPONENT*8 in the buffer
  Fill(SIZE_S_EXPONENT, public.issue.buffer.data, 0xFF);

  // Compute S_ = S^(2_l)
  ModExp(SIZE_S_EXPONENT, SIZE_N, public.issue.buffer.data,
    credential->issuerKey.n, credential->issuerKey.S, credential->issuerKey.S_);
  ModMul(SIZE_N, credential->issuerKey.S_, credential->issuerKey.S,
    credential->issuerKey.n);
}

/**
 * Compute the modular exponentiation: result = S^exponent mod n
 *
 * This function will use the helper value S' to compute exponentiations
 * with exponents larger than SIZE_N bytes.
 *
 * @param size of the exponent
 * @param exponent the power to which the base S should be raised
 * @param result of the computation
 */
void ModExpSpecial(int size, ByteArray exponent, ByteArray result, ByteArray buffer) {
  if (size > SIZE_N) {
    // Compute result = S^(exponent_bottom) * S_^(exponent_top)
    ModExp(SIZE_S_EXPONENT, SIZE_N, exponent + size - SIZE_S_EXPONENT,
      credential->issuerKey.n, credential->issuerKey.S, result);
    ModExp(size - SIZE_S_EXPONENT, SIZE_N,
      exponent, credential->issuerKey.n, credential->issuerKey.S_, buffer);
    ModMul(SIZE_N, result, buffer, credential->issuerKey.n);
  } else {
    // Compute result = S^exponent
    ModExp(size, SIZE_N,
      exponent, credential->issuerKey.n, credential->issuerKey.S, result);
  }
}

/**
 * Clear size bytes from a bytearray
 *
 * @param size the amount of bytes to clear
 * @param buffer to be cleared
 */
void ClearBytes(int size, void *buffer) {
  int offset = 0;

  while (size > 255) {
//    __code(CLEARN, buffer, 255);
    __push(((unsigned char *) buffer) + offset);
    __code(PUSHZ, 255);
    __code(STOREI, 255);
    offset += 255;
    size -= 255;
  }
  Fill(size, ((unsigned char *) buffer) + offset, 0x00);
}

/**
 * Clear the current credential.
 */
void ClearCredential(void) {
  Byte i;

  // Put the address of the credential on the stack
  __push(credential);

  // Clear the credential in blocks of 255 bytes
  for (i = 0; i < sizeof(Credential) / 255; i++) {

    // Store a block of 255 zero bytes at the given address
    __code(PUSHZ, 255);
    __code(STOREI, 255);

    // Update the address for the next block (add 255)
    __code(PUSHW, 255);
    __code(ADDN, 2);
    __code(POPN, 2);
  }

  // Store the remaining block of zero bytes at the given address
  __code(PUSHZ, sizeof(Credential) % 255);
  __code(STOREI, sizeof(Credential) % 255);

  // Remove the address from the stack
  __code(POPN, 2);

  // Clear the pointer to the credential
  credential = NULL;
}

/**
 * Clear the current session.
 */
void ClearSession(void) {
  Clear(255, session.base);
  Clear(sizeof(SessionData) % 255, session.base + 255);
  Clear(255, public.base);
  Clear(255, public.base + 255);
  Clear(255, public.base + 255*2);
  Clear(sizeof(PublicData) % 255, public.base + 255*3);
}
