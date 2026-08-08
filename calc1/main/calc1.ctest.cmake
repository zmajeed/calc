# calc1/main/calc1.ctest.cmake

add_test(NAME calc1_001 COMMAND calc1 -h)
set_tests_properties(calc1_001 PROPERTIES LABELS "calc1;cmd;cmdline")

add_test(NAME calc1_002 COMMAND calc1 -x)
set_tests_properties(calc1_002 PROPERTIES
  LABELS "calc1;cmd;cmdline"
  WILL_FAIL TRUE
)

add_test(NAME calc1_003 COMMAND calc1 -e "2 + 3")
set_tests_properties(calc1_003 PROPERTIES
  PASS_REGULAR_EXPRESSION "^5\n"
  LABELS "calc1;cmd;cmdline"
  DISABLED $<STREQUAL:$<PLATFORM_ID>,Emscripten>
)

add_test(NAME calc1_004 COMMAND calc1 -e "x = 2 + 3; y = -7; x * y")
set_tests_properties(calc1_004 PROPERTIES
  PASS_REGULAR_EXPRESSION "^-35\n"
  LABELS "calc1;cmd;cmdline"
  DISABLED $<STREQUAL:$<PLATFORM_ID>,Emscripten>
)

enable_testing()
