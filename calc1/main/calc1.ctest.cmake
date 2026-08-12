# calc1/main/calc1.ctest.cmake

add_test(NAME calc1_01 COMMAND calc1 -h)
set_property(TEST calc1_01
  PROPERTY LABELS "calc1;cmd;cmdline"
)

# don't use set_property for any failure tests or disabled tests or pretty much any test because it's one of the stupidest cmake functions
add_test(NAME calc1_02 COMMAND calc1 -x)
set_tests_properties(calc1_02 PROPERTIES
  WILL_FAIL TRUE
  LABELS "calc1;cmd;cmdline"
)

add_test(NAME calc1_03 COMMAND calc1 -e "2 + 3")
set_property(TEST calc1_03
  PROPERTY PASS_REGULAR_EXPRESSION "^5\n"
  PROPERTY LABELS "calc1;cmd;cmdline"
)

add_test(NAME calc1_04 COMMAND calc1 -e "x = 2 + 3; y = -7; x * y")
set_property(TEST calc1_04
  PROPERTY PASS_REGULAR_EXPRESSION "^-35\n"
  PROPERTY LABELS "calc1;cmd;cmdline"
)

add_test(NAME calc1_05 COMMAND calc1 -e "x = 2 + 3;
y = -7;
x * y = 1
")
set_tests_properties(calc1_05 PROPERTIES
  WILL_FAIL TRUE
  FAIL_REGULAR_EXPRESSION "3\.6-7; syntax error; unexpected ="
  LABELS "calc1;cmd;cmdline"
)

# hack for stdin for test programs
# use bash to run program because cmake alternatives are ugly and clunky
# be sure to use add_test NAME for multiline input
# disable on windows due to bash dependency
add_test(NAME calc1_06 COMMAND bash -c "$<TARGET_FILE:calc1> <<EOF
3-5
EOF
")
set_tests_properties(calc1_06 PROPERTIES
  PASS_REGULAR_EXPRESSION "^-2\n"
  LABELS "calc1;cmd;cmdline"
  DISABLED $<PLATFORM_ID:Windows>
)

add_test(NAME calc1_07 COMMAND bash -c "$<TARGET_FILE:calc1> <<EOF
3--5
EOF
")

set_tests_properties(calc1_07 PROPERTIES
  PASS_REGULAR_EXPRESSION "^8\n"
  LABELS "calc1;cmd;cmdline"
  DISABLED $<PLATFORM_ID:Windows>
)

add_test(NAME calc1_08 COMMAND bash -c "$<TARGET_FILE:calc1> <<EOF
3--+-5
EOF
")
set_tests_properties(calc1_08 PROPERTIES
  PASS_REGULAR_EXPRESSION "^-2\n"
  LABELS "calc1;cmd;cmdline"
  DISABLED $<PLATFORM_ID:Windows>
)

