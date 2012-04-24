/**
 * defs_test.h
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
 * Copyright (C) Pim Vullers, Radboud University Nijmegen, January 2012.
 */
 
#ifndef __defs_test_H
#define __defs_test_H

#ifdef TEST

#include "defs_sizes.h"
#include "defs_types.h"

const Byte TEST_vPrime[SIZE_VPRIME] = { 0xE1, 0x0A, 0x75, 0x07, 0xBD, 0x1D, 0xE3, 0x45, 0x98, 0x14, 0x68, 0x27, 0x07, 0xB1, 0xF3, 0x1C, 0x33, 0x8D, 0xDA, 0x30, 0xF6, 0x84, 0x01, 0xA2, 0x8F, 0x78, 0xB3, 0x2A, 0xEF, 0x0F, 0x15, 0xA5, 0x9C, 0xB6, 0xAD, 0xC1, 0x17, 0xAE, 0x9F, 0x72, 0x60, 0xE4, 0xC7, 0xD9, 0xD3, 0x86, 0x5D, 0xA2, 0x4D, 0xBC, 0x5C, 0x67, 0x22, 0x45, 0xF2, 0xC7, 0x6C, 0xBA, 0x08, 0xEB, 0xF8, 0x95, 0x2F, 0xDE, 0x1D, 0x88, 0x7D, 0x17, 0xED, 0x02, 0x06, 0x47, 0x29, 0x3B, 0x33, 0xB5, 0x9B, 0x76, 0x70, 0xC7, 0x40, 0x28, 0x43, 0xF1, 0x10, 0xBA, 0x47, 0x94, 0x85, 0xEA, 0xC2, 0x93, 0x91, 0x88, 0x5D, 0x6F, 0x64, 0x30, 0x6C, 0x01, 0xD0, 0x77, 0x46, 0xBA, 0xB3, 0x86, 0x63, 0x9B, 0xBF, 0x9E, 0x33, 0xE6, 0xEF, 0x0C, 0xC0, 0x2E, 0x42, 0x71, 0x87, 0x27, 0xF2, 0x15, 0xBE, 0xC2, 0xEC, 0xFC, 0x26, 0x13, 0xC5, 0xCB, 0xCF, 0x5B, 0x93, 0xF4, 0x40, 0x76, 0x9D, 0x2E };
const Byte TEST_vPrime_[SIZE_VPRIME_] = { 0xF4, 0x24, 0xF9, 0x49, 0x38, 0xE1, 0x47, 0x20, 0x18, 0xA1, 0x18, 0xD8, 0xCC, 0x6A, 0x84, 0xC6, 0x60, 0xB3, 0xCE, 0xD0, 0xFE, 0xE6, 0xFA, 0x6B, 0xB0, 0x62, 0xEC, 0x01, 0xEE, 0xF8, 0xA4, 0x9F, 0x8E, 0x20, 0xEF, 0x10, 0x8B, 0xC0, 0x9F, 0x9E, 0x5B, 0xF8, 0xF9, 0xCD, 0x72, 0x48, 0xA7, 0x03, 0x2C, 0xB5, 0x4B, 0xDF, 0x27, 0x0C, 0xE2, 0xC3, 0x98, 0xE2, 0xE6, 0x8C, 0x9D, 0x84, 0x43, 0xC2, 0x9F, 0x24, 0xBD, 0xF3, 0xB6, 0x3E, 0x36, 0xC4, 0xBC, 0x99, 0xBF, 0x67, 0xCA, 0xC6, 0xAD, 0x89, 0x57, 0x0A, 0x42, 0x64, 0x1C, 0x1E, 0x82, 0x68, 0xA2, 0x84, 0x2D, 0x0E, 0x92, 0x77, 0x8B, 0x31, 0xFA, 0x97, 0x04, 0x75, 0x05, 0xF6, 0x30, 0x8E, 0x3C, 0x8C, 0x0C, 0x2C, 0xD2, 0x88, 0x24, 0xFD, 0xEE, 0x1E, 0x28, 0x31, 0x42, 0xA7, 0x0C, 0x2C, 0x6E, 0xD8, 0x9F, 0x38, 0x8A, 0x5C, 0x85, 0xB4, 0x1A, 0x0C, 0x1A, 0x2D, 0x9D, 0x65, 0xF3, 0xFB, 0x5E, 0x5D, 0x9D, 0x51, 0x5C, 0x13, 0x29, 0x2E, 0x28, 0x82, 0xBB, 0x06, 0xAF, 0x57, 0x66, 0x98, 0x0A, 0x51, 0x7A, 0x31, 0xDE, 0x73, 0x4B, 0xF0, 0x3A, 0xE8, 0xA1, 0xA7, 0xB3, 0x41, 0x69, 0xF3 };
const Byte TEST_m_[SIZE_M_] = { 0x00, 0x8D, 0x30, 0xFB, 0x15, 0xA4, 0x39, 0xD5, 0xBA, 0x1E, 0x44, 0x33, 0xEA, 0x3E, 0x64, 0x28, 0x85, 0x50, 0x56, 0xC4, 0x56, 0xD4, 0xAD, 0x50, 0x61, 0x73, 0xF5, 0x4E, 0x30, 0xF9, 0xA2, 0xAF, 0xE5, 0x59, 0x23, 0x42, 0x2A, 0x4F, 0x56, 0x59, 0xA7, 0xDA, 0xD1, 0x0C, 0xB3, 0x2F, 0xCE, 0x3E, 0x31, 0xBE, 0x83, 0x70, 0x0B, 0x74, 0xAE, 0x0C, 0x13, 0x20, 0xA4, 0xD6, 0x31, 0xD3, 0x50 };
const Byte TEST_n_2[SIZE_STATZK] = { 0x4E, 0xD4, 0x28, 0x2A, 0x6C, 0x36, 0xC5, 0x12, 0x18, 0x89 };

#endif // TEST

#endif // __defs_test_H