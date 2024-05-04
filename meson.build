project(
  'v6502', 'cpp',
  version: '1.0.0',
  default_options: ['warning_level=3', 'cpp_std=c++23']
)
pkg = import('pkgconfig')

if get_option('debug_logs')
  add_project_arguments('-DV6502_DEBUG', language: 'cpp')
endif

v6502_inc = include_directories('inc')
v6502_private_inc = include_directories('inc/private')
v6502_lib = library('v6502',

  'src/cpu.cpp',
  'src/internal.cpp',
  'src/opcodes.cpp',
  'src/opcodes/arith.cpp',
  'src/opcodes/branch.cpp',
  'src/opcodes/ctrl.cpp',
  'src/opcodes/flags.cpp',
  'src/opcodes/inc.cpp',
  'src/opcodes/load.cpp',
  'src/opcodes/logic.cpp',
  'src/opcodes/nop.cpp',
  'src/opcodes/shift.cpp',
  'src/opcodes/stack.cpp',
  'src/opcodes/trans.cpp',

  include_directories: [v6502_inc, v6502_private_inc],
  install: true,
)

v6502_dep = declare_dependency(
  link_with: v6502_lib,
  include_directories: v6502_inc,
)

pkg.generate(v6502_lib)
install_headers(
  'inc/v6502/cpu.h',
  'inc/v6502/memory.h',
  'inc/v6502/modes.h',
  subdir: 'v6502',
)

executable(
  'v6502_loadram',
  'example/loadram.cpp',
  dependencies: v6502_dep,
  include_directories: v6502_private_inc,
)

if get_option('tests')
  executable(
    'v6502_nestest',
    'example/nestest.cpp',
    dependencies: v6502_dep,
    include_directories: v6502_private_inc,
  )

  executable(
    'v6502_klaustest',
    'example/klaustest.cpp',
    dependencies: v6502_dep,
    include_directories: v6502_private_inc,
  )

  subdir('tests')
endif
