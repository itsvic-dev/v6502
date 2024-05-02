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
    'cmp_immediate_3a_works': 'bugs/cmp_immediate_3a_works.cpp',
}

foreach name, sources : tests
    exe = executable(name, sources, dependencies: test_core_dep)
    test(name, exe)
endforeach
