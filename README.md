<h1 align="center">v6502</h1>

**v6502** is an experimental emulator for the MOS 6502 written in C++. It is meant to be easily extensible and integratable into other software, such as machine emulators.

## Current state

Most instructions appear to be emulated correctly with minor issues. [Wozmon](example/asm/wozmon.asm) runs perfectly, whereas Microsoft BASIC runs with minor issues. (strings end up being floats somehow???)

## Examples

- [`loadram`](example/loadram.cpp) - a reference machine which loads a binary image into `$6000` and sets the reset vector to `$6000`
- [`msbasic-v6502`](https://github.com/itsvic-dev/msbasic-v6502) - an example of a more sophisticated machine running MS BASIC
