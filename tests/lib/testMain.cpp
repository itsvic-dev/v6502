#include "testMain.h"
#include <cstring>

// define test function
extern TEST;

class SimpleRAMBus : public MemoryBus {
public:
  SimpleRAMBus() {
    ram = new uint8_t[0x10000];
    memset(ram, 0, 0x10000);
  }
  ~SimpleRAMBus() { delete[] ram; }

  uint8_t read(uint16_t addr) override { return ram[addr]; }
  void write(uint16_t addr, uint8_t data) override { ram[addr] = data; }

private:
  uint8_t *ram;
};

int main() {
  SimpleRAMBus bus;
  CPU cpu(&bus);

  test(&cpu);

  return 0;
}
