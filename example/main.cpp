#include "cpu/cpu.h"
#include "cpu/memory.h"
#include "vprint.h"
#include <cstddef>
#include <cstdint>
#include <cstring>

class SimpleRAMBus : public MemoryBus {
public:
  SimpleRAMBus() {
    ram = new uint8_t[0x10000];
    // fill with NOPs
    memset(ram, 0xEA, 0x10000);
  }
  ~SimpleRAMBus() { delete[] ram; }

  uint8_t read(uint16_t addr) override {
    print("BUS R ${:04x} = ${:02x}\n", addr, ram[addr]);
    return ram[addr];
  }
  void write(uint16_t addr, uint8_t data) override {
    print("BUS W ${:04x} = ${:02x}\n", addr, data);
    ram[addr] = data;
  }

private:
  uint8_t *ram;
};

/*
.org $6000

jmp main

loadfun:
  lda #69
  rts

main:
  jsr loadfun
  nop
*/
const char *program = "\x4C\x06\x60\xA9\x45\x60\x20\x03\x60\xEA";
const size_t programSize = 10;

int main() {
  SimpleRAMBus bus;
  CPU cpu(&bus);

  // copy test program to 0x6000
  for (size_t i = 0; i < programSize; i++) {
    bus.write(0x6000 + i, program[i]);
  }

  bus.write(0xFFFC, 0x00);
  bus.write(0xFFFD, 0x60);

  print("resetting CPU\n");
  cpu.reset();

  while (cpu.pc >= 0x6000 && cpu.pc < 0x6000 + programSize) {
    cpu.executeStep();
  }
  return 0;
}
