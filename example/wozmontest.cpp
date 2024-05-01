// Loads a program into RAM at $6000 and begins execution there.

#include "v6502/cpu.h"
#include "v6502/memory.h"
#include "v6502/print.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <ostream>
#include <vector>

std::vector<uint8_t> commandBuffer = {'5', 'A', '\r'};
bool shouldBreak = false;

class SimpleRAMBus : public MemoryBus {
public:
  SimpleRAMBus() { ram = new uint8_t[0x10000]; }
  ~SimpleRAMBus() { delete[] ram; }

  uint8_t read(uint16_t addr) override {
    uint8_t retVal = ram[addr];
    if (addr == 0x0201) {
      if (commandBuffer.size() == 0) {
        shouldBreak = true;
        retVal = '\r';
      } else {
        retVal = commandBuffer[0];
        commandBuffer.erase(commandBuffer.begin());
      }
    }
    if (addr == 0x0202) {
      retVal = 1;
    }
    return retVal;
  }

  void write(uint16_t addr, uint8_t data) override {
    if (addr == 0x0200) {
      if (data == '\r')
        data = '\n';
      std::cout << (char)(data) << std::flush;
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
          "executed until it reads from an empty command buffer\n",
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

  while (!shouldBreak) {
    cpu.executeStep();
  }
  return 0;
}
