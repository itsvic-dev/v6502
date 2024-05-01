// Loads a program into RAM at $6000 and begins execution there.

#include "v6502/cpu.h"
#include "v6502/memory.h"
#include "v6502/print.h"
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>

// stolen from the web https://www.flipcode.com/archives/_kbhit_for_Linux.shtml
int _kbhit() {
  static const int STDIN = 0;
  static bool initialized = false;

  if (!initialized) {
    // Use termios to turn off line buffering
    termios term;
    tcgetattr(STDIN, &term);
    term.c_lflag &= ~ICANON;
    tcsetattr(STDIN, TCSANOW, &term);
    setbuf(stdin, NULL);
    initialized = true;
  }

  int bytesWaiting;
  ioctl(STDIN, FIONREAD, &bytesWaiting);
  return bytesWaiting;
}

class SimpleRAMBus : public MemoryBus {
public:
  SimpleRAMBus() { ram = new uint8_t[0x10000]; }
  ~SimpleRAMBus() { delete[] ram; }

  uint8_t read(uint16_t addr) override {
    uint8_t retVal = ram[addr];
    if (addr == 0x0201) {
      retVal = std::cin.get();
      if (retVal == '\n')
        retVal = '\r';
    }
    if (addr == 0x0202) {
      retVal = _kbhit() ? 1 : 0;
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
          "executed until it reaches the end\n",
          argv[0]);
    return -1;
  }

  // disable input echoing
  termios oldt;
  tcgetattr(STDIN_FILENO, &oldt);
  termios newt = oldt;
  newt.c_lflag &= ~ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

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
