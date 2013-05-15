/**
 * types.h
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (C) Pim Vullers, Radboud University Nijmegen, July 2011.
 */

#ifndef __types_H
#define __types_H

#include "sizes.h"

#ifndef NULL
#define NULL ((void*)0)
#endif

typedef unsigned int uint;
typedef uint Size;
typedef const char *String;

typedef unsigned char Byte;
typedef Byte *ByteArray;

typedef Byte Hash[SIZE_H];
typedef Byte Nonce[SIZE_STATZK];
typedef Byte ResponseE[SIZE_E_];
typedef Byte ResponseM[SIZE_M_];
typedef Byte ResponseV[SIZE_V_];
typedef Byte ResponseVPRIME[SIZE_VPRIME_];
typedef Byte Number[SIZE_N];
typedef Byte Counter[SIZE_SSC];
typedef Number Numbers[];

typedef struct {
  ByteArray data;
  Size size;
} Value;
typedef Value *ValueArray;

typedef struct {
  Number n;
  Number Z;
  Number S;
  Number S_;
  Number R[SIZE_L];
} CLPublicKey;

typedef Byte CLMessage[SIZE_M];
typedef CLMessage CLMessages[MAX_ATTR];

typedef struct {
  Number A;
  Byte e[SIZE_E];
  Byte v[SIZE_V];
} CLSignature;

typedef struct {
  Nonce nonce;
  Hash context;
  Hash challenge;
  Number response;
} CLProof;

typedef uint AttributeMask;
typedef uint CredentialIdentifier;

typedef struct {
  AttributeMask protect;
  Byte RFU;
} CredentialFlags;

typedef struct {
  CLPublicKey issuerKey;
  CLSignature signature;
  CLMessages attribute;
  CLProof proof;
  Byte size;
  CredentialFlags issuerFlags;
  CredentialFlags userFlags;
  CredentialIdentifier id;
} Credential;

typedef struct {
  Byte timestamp[SIZE_TIMESTAMP];
  Byte terminal[SIZE_TERMINAL_ID];
  Byte action;
  CredentialIdentifier credential;
  union {
    struct {
      AttributeMask selection;
    } prove;
    Byte data[5];
  } details;
} LogEntry;

#define ACTION_ISSUE 0x01;
#define ACTION_PROVE 0x02;
#define ACTION_REMOVE 0x03;

typedef struct {
  Byte data[255]; // 255
  Byte session[SIZE_PUBLIC - 255]; // SIZE_PUBLIC - 255
} APDU; // SIZE_PUBLIC

typedef struct {
  CredentialIdentifier id;
  Hash context;
  Size size;
  CredentialFlags flags;
  Byte timestamp[SIZE_TIMESTAMP];
} IssuanceSetup;

typedef struct {
  Number U; // 128
  union {
    Byte data[SIZE_BUFFER_C1]; // 307
    Number number[3]; // 384
  } buffer; // 384
  Value list[5]; // 20
  Nonce nonce; // 10
} IssuanceCommitment; // 128 + 384 + 20 + 10 = 542

typedef struct {
  Hash challenge; // 32
  Byte sHat[SIZE_S_]; // 75
  Byte vPrime[SIZE_VPRIME]; // 138
  ResponseVPRIME vPrimeHat; // 180
} IssuanceSession; // 32 + 75 + 138 + 180 = 425

typedef struct {
  Number ZPrime; // 128
  Number buffer; // 128
  Number tmp; // 128
} CLSignatureVerification; // 384

typedef struct {
  Byte buffer[SIZE_BUFFER_C2]; // 438
} IssuanceProofVerification; // 438

typedef struct {
  Value list[5]; // 20
  Hash challenge; // 32
  Number Q; // 128
  Number AHat; // 128
} IssuanceProofSession; // 20 + 32 + 128 + 128 = 308

typedef struct {
  CredentialIdentifier id;
  Hash context;
  AttributeMask selection;
  Byte timestamp[SIZE_TIMESTAMP];
  Byte terminal[SIZE_TERMINAL_ID];
} VerificationSetup;

typedef struct {
  union {
    Nonce nonce; // 10
    Hash challenge; // 20
  } apdu; // 20
  union {
    Byte data[SIZE_BUFFER_C1]; // 319
    Number number[2]; // 256
  } buffer; // 319
  Hash context; // 20
  Value list[4]; // 16
  Byte rA[SIZE_R_A]; // 138
  Number APrime; // 128
  ResponseV vHat; // 231
  ResponseE eHat; // 45
} VerificationProof; // 20 + 307 + 20 + 16 + 138 + 128 + 231 + 45 = 905

typedef struct {
  ResponseM mHat[SIZE_L]; // 74*6 (444)
  AttributeMask disclose; // 2
} VerificationSession; // 444 + 2 = 446

typedef struct {
  CredentialFlags user;
  CredentialFlags issuer;
} AdminFlags;

typedef union {
  Byte base[1];

  APDU apdu;

  IssuanceSetup issuanceSetup;
  IssuanceCommitment issue;
  IssuanceProofVerification vfyPrf;

  VerificationSetup verificationSetup;
  VerificationProof prove;

  AdminFlags adminFlags;
} PublicData;

typedef union {
  Byte base[1];

  IssuanceSession issue;
  CLSignatureVerification vfySig;
  IssuanceProofSession vfyPrf;

  VerificationSession prove;
} SessionData;

#endif // __types_H