// Loads a program into RAM at $6000 and begins execution there.

#include "v6502/cpu.h"
#include "v6502/memory.h"
#include "v6502/print.h"
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <ostream>

class SimpleRAMBus : public MemoryBus {
public:
  SimpleRAMBus() {
    ram = new uint8_t[0x10000];
    // fill with NOPs
    memset(ram, 0xEA, 0x10000);
  }
  ~SimpleRAMBus() { delete[] ram; }

  uint8_t read(uint16_t addr) override {
    // print("BUS R ${:04x} = ${:02x}\n", addr, ram[addr]);
    if (addr == 0x0201) {
      return 0; // TODO: getchar
    }
    if (addr == 0x0202) {
      return 0; // TODO: getchar
    }
    return ram[addr];
  }
  void write(uint16_t addr, uint8_t data) override {
    // print("BUS W ${:04x} = ${:02x}\n", addr, data);
    if (addr == 0x0200) {
      std::cout << (char)data << std::flush;
      return;
    }
    ram[addr] = data;
  }

private:
  uint8_t *ram;
};

int main(int argc, char **argv) {
  if (argc < 2) {
    print("usage: {} <binary file>\nprogram will be loaded to $6000 and "
          "executed until it reaches the end\n",
          argv[0]);
    return -1;
  }

  SimpleRAMBus bus;
  CPU cpu(&bus);

  uint16_t addr = 0x6000;

  {
    std::ifstream bin(argv[1]);
    char byte;
    while (bin.get(byte)) {
      bus.write(addr++, byte);
    }
  }

  bus.write(0xFFFC, 0x00);
  bus.write(0xFFFD, 0x60);

  print("resetting CPU\n");
  cpu.reset();

  while (cpu.pc >= 0x6000 && cpu.pc < addr) {
    cpu.executeStep();
  }
  return 0;
}
