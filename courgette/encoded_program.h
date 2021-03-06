// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COURGETTE_ENCODED_PROGRAM_H_
#define COURGETTE_ENCODED_PROGRAM_H_

#include <vector>

//#include "base/basictypes.h"
#include "courgette/disassembler.h"
#include "courgette/memory_allocator.h"

namespace courgette {

class SinkStream;
class SinkStreamSet;
class SourceStreamSet;

// An EncodedProgram is a set of tables that contain a simple 'binary assembly
// language' that can be assembled to produce a sequence of bytes, for example,
// a Windows 32-bit executable.
//
class EncodedProgram {
 public:
  EncodedProgram();
  ~EncodedProgram();

  // Generating an EncodedProgram:
  //
  // (1) The image base can be specified at any time.
  void set_image_base(uint64 base) { image_base_ = base; }

  // (2) Address tables and indexes defined first.
  CheckBool DefineRel32Label(int index, RVA address) WARN_UNUSED_RESULT;
  CheckBool DefineAbs32Label(int index, RVA address) WARN_UNUSED_RESULT;
  void EndLabels();

  // (3) Add instructions in the order needed to generate bytes of file.
  // NOTE: If any of these methods ever fail, the EncodedProgram instance
  // has failed and should be discarded.
  CheckBool AddOrigin(RVA rva) WARN_UNUSED_RESULT;
  CheckBool AddCopy(uint32 count, const void* bytes) WARN_UNUSED_RESULT;
  CheckBool AddRel32(int label_index) WARN_UNUSED_RESULT;
  CheckBool AddAbs32(int label_index) WARN_UNUSED_RESULT;
  CheckBool AddPeMakeRelocs() WARN_UNUSED_RESULT;
  CheckBool AddElfMakeRelocs() WARN_UNUSED_RESULT;

  // (3) Serialize binary assembly language tables to a set of streams.
  CheckBool WriteTo(SinkStreamSet* streams) WARN_UNUSED_RESULT;

  // Using an EncodedProgram to generate a byte stream:
  //
  // (4) Deserializes a fresh EncodedProgram from a set of streams.
  bool ReadFrom(SourceStreamSet* streams);

  // (5) Assembles the 'binary assembly language' into final file.
  CheckBool AssembleTo(SinkStream* buffer) WARN_UNUSED_RESULT;

 private:
  // Binary assembly language operations.
  // These are part of the patch format. Reusing an existing value will
  // break backwards compatibility.
  enum OP {
    ORIGIN = 0,    // ORIGIN <rva> - set address for subsequent assembly.
    COPY = 1,      // COPY <count> <bytes> - copy bytes to output.
    COPY1 = 2,     // COPY1 <byte> - same as COPY 1 <byte>.
    REL32 = 3,     // REL32 <index> - emit rel32 encoded reference to address at
                   // address table offset <index>
    ABS32 = 4,     // ABS32 <index> - emit abs32 encoded reference to address at
                   // address table offset <index>
    MAKE_PE_RELOCATION_TABLE = 5,  // Emit PE base relocation table blocks.
    MAKE_ELF_RELOCATION_TABLE = 6, // Emit Elf relocation table.
  };

  typedef NoThrowBuffer<RVA> RvaVector;
  typedef NoThrowBuffer<uint32> UInt32Vector;
  typedef NoThrowBuffer<uint8> UInt8Vector;
  typedef NoThrowBuffer<OP> OPVector;

  void DebuggingSummary();
  CheckBool GeneratePeRelocations(SinkStream *buffer) WARN_UNUSED_RESULT;
  CheckBool GenerateElfRelocations(SinkStream *buffer) WARN_UNUSED_RESULT;
  CheckBool DefineLabelCommon(RvaVector*, int, RVA) WARN_UNUSED_RESULT;
  void FinishLabelsCommon(RvaVector* addresses);

  // Binary assembly language tables.
  uint64 image_base_;
  RvaVector rel32_rva_;
  RvaVector abs32_rva_;
  OPVector ops_;
  RvaVector origins_;
  UInt32Vector copy_counts_;
  UInt8Vector copy_bytes_;
  UInt32Vector rel32_ix_;
  UInt32Vector abs32_ix_;

  // Table of the addresses containing abs32 relocations; computed during
  // assembly, used to generate base relocation table.
  UInt32Vector abs32_relocs_;

//  DISALLOW_COPY_AND_ASSIGN(EncodedProgram);
};

}  // namespace courgette
#endif  // COURGETTE_ENCODED_PROGRAM_H_
