#include "cpu/cpu.h"
#include "cpu/memory.h"
#include <cstdint>
#include <format>
#include <iostream>

#define print(...) std::cout << std::format(__VA_ARGS__)

class SimpleRAMBus : public MemoryBus {
public:
  SimpleRAMBus() { ram = new uint8_t[0x10000]; }
  ~SimpleRAMBus() { delete[] ram; }

  uint8_t read(uint16_t addr) override { return ram[addr]; }
  void write(uint16_t addr, uint8_t data) override { ram[addr] = data; }

private:
  uint8_t *ram;
};

int main() {
  SimpleRAMBus bus;
  CPU cpu(&bus);

  bus.write(0xFFFC, 0x12);
  bus.write(0xFFFD, 0x34);

  print("resetting CPU\n");
  cpu.reset();

  print("PC is now {:#06x}\n", cpu.pc);
  return 0;
}
