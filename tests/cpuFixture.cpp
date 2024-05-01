#include "tests/cpuFixture.h"
#include <cstdint>

SimpleRAMBus::SimpleRAMBus() { ram = new uint8_t[0x10000]; }
SimpleRAMBus::~SimpleRAMBus() { delete[] ram; }

uint8_t SimpleRAMBus::read(uint16_t addr) { return ram[addr]; }
void SimpleRAMBus::write(uint16_t addr, uint8_t data) { ram[addr] = data; }

V6502Test::V6502Test() : cpu(&bus) {}
