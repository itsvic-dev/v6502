// loads a test suite by Klaus Dormann and executes it from $400

#include "v6502/cpu.h"
#include "v6502/memory.h"
#include "v6502/print.h"
#include <cstdint>
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

  uint16_t addr = 0;
  {
    std::ifstream bin(argv[1]);
    char byte;
    while (bin.get(byte)) {
      bus.write(addr++, byte);
    }
  }

  print("resetting CPU\n");
  cpu.reset();
  // override read PC with Klaus test start
  cpu.pc = 0x400;

  try {
    while (true) {
      cpu.executeStep();
    }
  } catch (...) {
    print("[warn] execution ended prematurely due to a v6502 error!!!\n");
  }
  return 0;
}
