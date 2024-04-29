project(
  'v6502', 'cpp',
  version: '0.1',
  default_options: ['warning_level=3', 'cpp_std=c++23']
)

v6502_inc = include_directories('inc')
v6502_lib = library('v6502',

  'src/cpu/cpu.cpp',

  include_directories: v6502_inc,
  install: true,
)

v6502_dep = declare_dependency(
  link_with: v6502_lib,
  include_directories: v6502_inc,
)

executable(
  'v6502_basic_example',

  'example/main.cpp',

  dependencies: v6502_dep,
)
