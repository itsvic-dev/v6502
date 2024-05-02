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
    'instructions(arith) - ADC #$01': 'instructions/arith/adc-1.cpp',
    'instructions(arith) - ADC #$01 with A=$FF': 'instructions/arith/adc-1-ff.cpp',
    'instructions(arith) - ADC #$01 with A=$7F': 'instructions/arith/adc-1-7f.cpp',
    'instructions(arith) - SBC #$01': 'instructions/arith/sbc-1.cpp',
    'instructions(arith) - SBC #$01 with A=$02': 'instructions/arith/sbc-1-02.cpp',
    'instructions(arith) - SBC #$01 with A=$80': 'instructions/arith/sbc-1-80.cpp',

    'instructions(branch) - BCC with clear carry': 'instructions/branch/bcc-clear.cpp',
    'instructions(branch) - BCC with set carry': 'instructions/branch/bcc-set.cpp',
    'instructions(branch) - BCS with clear carry': 'instructions/branch/bcs-clear.cpp',
    'instructions(branch) - BCS with set carry': 'instructions/branch/bcs-set.cpp',
    'instructions(branch) - BEQ with clear zero': 'instructions/branch/beq-clear.cpp',
    'instructions(branch) - BEQ with set zero': 'instructions/branch/beq-set.cpp',
    'instructions(branch) - BMI with clear negative': 'instructions/branch/bmi-clear.cpp',
    'instructions(branch) - BMI with set negative': 'instructions/branch/bmi-set.cpp',
    'instructions(branch) - BNE with clear zero': 'instructions/branch/bne-clear.cpp',
    'instructions(branch) - BNE with set zero': 'instructions/branch/bne-set.cpp',
    'instructions(branch) - BPL with clear negative': 'instructions/branch/bpl-clear.cpp',
    'instructions(branch) - BPL with set negative': 'instructions/branch/bpl-set.cpp',
    'instructions(branch) - BVC with clear overflow': 'instructions/branch/bvc-clear.cpp',
    'instructions(branch) - BVC with set overflow': 'instructions/branch/bvc-set.cpp',
    'instructions(branch) - BVS with clear overflow': 'instructions/branch/bvs-clear.cpp',
    'instructions(branch) - BVS with set overflow': 'instructions/branch/bvs-set.cpp',

    'instructions(shift) - ASL A with A=$80': 'instructions/shift/asl-a-80.cpp',
    'instructions(shift) - ROL A with set carry': 'instructions/shift/rol-sec.cpp',

    # old bugs
    'old bugs - does CMP #$3A with A=$3A work correctly?': 'bugs/cmp_immediate_3a_works.cpp',
}

foreach name, sources : tests
    exe = executable(name, sources, dependencies: test_core_dep)
    test(name, exe)
endforeach
