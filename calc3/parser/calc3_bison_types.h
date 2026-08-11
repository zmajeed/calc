#ifndef CALC3_BISON_TYPES_H
#define CALC3_BISON_TYPES_H
// calc3/parser/calc3_bison_types.h

#include <stdint.h>

#include <string>
#include <flat_map>

#include "ast/calc3_ast.h"

namespace calc3 {
using namespace std;

using Symtab = flat_map<string, int64_t>;

struct Error {
  string msg;
  uint64_t line;
  uint64_t col;
  string file;
};

struct BisonDriver {
  Expr expr;
  Symtab symtab;
  Error error;
};

}

#endif
