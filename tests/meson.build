test_core_inc = include_directories('lib')

test_core = static_library(
    'v6502_test_core',
    'lib/testMain.cpp',
    dependencies: v6502_dep,
)

test_core_dep = declare_dependency(
    link_with: test_core,
    include_directories: test_core_inc,
    dependencies: v6502_dep,
)

tests = {
    # instruction tests
    'instructions - ADC #$01': 'instructions/arith/adc-1.cpp',
    'instructions - ADC #$01 with A=$FF': 'instructions/arith/adc-1-ff.cpp',
    'instructions - ADC #$01 with A=$7F': 'instructions/arith/adc-1-7f.cpp',

    # old bugs
    'old bugs - does CMP #$3A with A=$3A work correctly?': 'bugs/cmp_immediate_3a_works.cpp',
}

foreach name, sources : tests
    exe = executable(name, sources, dependencies: test_core_dep)
    test(name, exe)
endforeach
