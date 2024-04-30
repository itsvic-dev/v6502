#include "cpu/cpu.h"
#include "cpu/memory.h"
#include "vprint.h"
#include <cstddef>
#include <cstdint>

class SimpleRAMBus : public MemoryBus {
public:
  SimpleRAMBus() { ram = new uint8_t[0x10000]; }
  ~SimpleRAMBus() { delete[] ram; }

  uint8_t read(uint16_t addr) override { return ram[addr]; }
  void write(uint16_t addr, uint8_t data) override { ram[addr] = data; }

private:
  uint8_t *ram;
};

/*
lda #69
sta $0200
*/
const char *program = "\xA9\x45\x8D\x00\x02";

int main() {
  SimpleRAMBus bus;
  CPU cpu(&bus);

  // copy test program to 0x6000
  for (size_t i = 0; i < sizeof(program); i++) {
    bus.write(0x6000 + i, program[i]);
  }

  bus.write(0xFFFC, 0x00);
  bus.write(0xFFFD, 0x60);

  print("resetting CPU\n");
  cpu.reset();

  while (true) {
    cpu.executeStep();
  }
  return 0;
}
