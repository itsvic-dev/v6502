#include "v6502/print.h"

namespace v6502Internal {

void logWarning(const char *text) { print_err("[v6502] warn: {}\n", text); }

}; // namespace v6502Internal
