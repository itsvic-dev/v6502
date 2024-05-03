// (improperly) loads an NES ROM file to $C000 and begins execution there

#include "v6502/cpu.h"
#include "v6502/memory.h"
#include "v6502/print.h"
#include <fstream>

class SimpleRAMBus : public MemoryBus {
public:
  SimpleRAMBus() { ram = new uint8_t[0x10000]; }
  ~SimpleRAMBus() { delete[] ram; }

  uint8_t read(uint16_t addr) override { return ram[addr]; }
  void write(uint16_t addr, uint8_t data) override { ram[addr] = data; }

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

  // offset by the NES file header lol
  uint16_t addr = 0xC000 - 16;
  {
    std::ifstream bin(argv[1]);
    char byte;
    while (bin.get(byte) && addr >= 0xC000 - 16) {
      bus.write(addr++, byte);
    }
  }

  print("resetting CPU\n");
  cpu.reset();
  // override read PC with NESTEST automation start
  cpu.pc = 0xC000;

  try {
    while (true) {
      cpu.executeStep();
    }
  } catch (...) {
    print("[warn] execution ended prematurely due to a v6502 error!!!\n");
  }

  print("\n---\nresults: {:02x} {:02x}\n", bus.read(2), bus.read(3));
  return 0;
}
