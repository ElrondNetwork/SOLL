// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#pragma once
#include <llvm/ADT/StringRef.h>
#include <llvm/Support/MemoryBuffer.h>
#include <vector>

namespace soll {

enum InputKind { Sol, Yul };
enum ActionKind { ASTDump, EmitLLVM, EmitFuncSig, EmitABI };

class FrontendInputFile {
  /// The file name, or "-" to read from standard input.
  std::string File;
  llvm::MemoryBuffer *Buffer = nullptr;

public:
  FrontendInputFile() = default;
  FrontendInputFile(llvm::StringRef File) : File(File.str()) {}
  FrontendInputFile(llvm::MemoryBuffer *Buffer) : Buffer(Buffer) {}

  bool isEmpty() const { return File.empty() && Buffer == nullptr; }
  bool isFile() const { return !isBuffer(); }
  bool isBuffer() const { return Buffer != nullptr; }

  llvm::StringRef getFile() const {
    assert(isFile());
    return File;
  }

  llvm::MemoryBuffer *getBuffer() const {
    assert(isBuffer());
    return Buffer;
  }
};

class FrontendOptions {
public:
  bool ShowHelp;
  bool ShowVersion;
  std::vector<FrontendInputFile> Inputs;
  InputKind Language = Sol;
  ActionKind ProgramAction = EmitLLVM;
};

} // namespace soll
