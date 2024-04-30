project(
  'v6502', 'cpp',
  version: '0.1',
  default_options: ['warning_level=3', 'cpp_std=c++23']
)

if get_option('debug_logs')
  add_project_arguments('-DV6502_DEBUG', language: 'cpp')
endif

v6502_inc = include_directories('inc')
v6502_lib = library('v6502',

  'src/cpu/cpu.cpp',
  'src/cpu/opcodes.cpp',
  'src/cpu/opcodes/loads.cpp',
  'src/cpu/opcodes/stores.cpp',
  'src/cpu/opcodes/stack.cpp',
  'src/cpu/opcodes/jumps.cpp',

  include_directories: v6502_inc,
  install: true,
)

v6502_dep = declare_dependency(
  link_with: v6502_lib,
  include_directories: v6502_inc,
)

executable(
  'v6502_loadram',
  'example/loadram.cpp',
  dependencies: v6502_dep,
)
