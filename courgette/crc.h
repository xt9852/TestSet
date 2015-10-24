// Copyright (c) 2009 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COURGETTE_CRC_H_
#define COURGETTE_CRC_H_

#include <vector>
#include <string>
#include <windows.h>
//#include "base/basictypes.h"

typedef unsigned char uint8;
typedef unsigned int  uint32;

namespace courgette {

// Calculates Crc of the given buffer by calling CRC method in LZMA SDK
//
uint32 CalculateCrc(const uint8* buffer, size_t size);

}  // namespace courgette

#endif  // COURGETTE_CRC_H_