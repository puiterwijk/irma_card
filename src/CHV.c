/**
 * CHV.c
 *
 * This file is part of IRMAcard.
 *
 * IRMAcard is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * IRMAcard is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with IRMAcard. If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (C) May 2012 - 2013.
 *   Pim Vullers <pim@cs.ru.nl>, Radboud University Nijmegen.
 */

#include "CHV.h"

#include "debug.h"
#include "memory.h"

#pragma melsession
unsigned char CHV_flags;
#pragma melstatic

/**
 * Verify a PIN code.
 *
 * @param buffer which contains the code to verify.
 */
int CHV_PIN_verify(CHV_PIN *pin, unsigned char *buffer) {
  // Verify if the PIN has not been blocked
  if (pin->count == 0) {
    return CHV_BLOCKED;
  }

  // Compare the PIN with the stored code
  if (NotEqual(CHV_PIN_SIZE, buffer, pin->code)) {
    debugWarning("PIN verification failed");
    debugInteger("Tries left", pin->count - 1);
    return CHV_TRIES_LEFT * --(pin->count);
  } else {
    debugMessage("PIN verified ");
    pin->count = CHV_PIN_COUNT;
    CHV_flags |= pin->flag;
    return CHV_VALID;
  }
}

/**
 * Modify a PIN code
 *
 * @param buffer which contains the old and new code
 */
int CHV_PIN_update(CHV_PIN *pin, unsigned char *buffer) {
  int i;

  // Verify the original PIN
  i = CHV_PIN_verify(pin, buffer);
  if (i <= 0) {
    return i;
  }

  // Verify the new PIN size
  for (i = 0; i < pin->minSize; i++) {
    if (buffer[CHV_PIN_SIZE + i] == 0x00) {
      return CHV_WRONG_LENGTH;
    }
  }

  // Store the new code
  CopyBytes(CHV_PIN_SIZE, pin->code, buffer + CHV_PIN_SIZE);
  pin->count = CHV_PIN_COUNT;
  return CHV_VALID;
}
