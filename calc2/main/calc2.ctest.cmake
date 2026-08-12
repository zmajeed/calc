# calc2/main/calc2.ctest.cmake

add_test(NAME calc2_01 COMMAND calc2 -h)
set_tests_properties(calc2_01 PROPERTIES LABELS "calc2;cmd;cmdline")

add_test(NAME calc2_02 COMMAND calc2 -x)
set_tests_properties(calc2_02 PROPERTIES
  LABELS "calc2;cmd;cmdline"
  WILL_FAIL TRUE
)

add_test(NAME calc2_03 COMMAND calc2 -e "2 + 3")
set_tests_properties(calc2_03 PROPERTIES
  PASS_REGULAR_EXPRESSION "^5\n"
  LABELS "calc2;cmd;cmdline"
)

add_test(NAME calc2_04 COMMAND calc2 -e "x = 2 + 3; y = -7; x * y")
set_tests_properties(calc2_04 PROPERTIES
  PASS_REGULAR_EXPRESSION "^-35\n"
  LABELS "calc2;cmd;cmdline"
)

add_test(NAME calc2_05 COMMAND calc2 -e "x = 2 + 3;
y = -7;
x * y = 1
")
set_tests_properties(calc2_05 PROPERTIES
  WILL_FAIL TRUE
  FAIL_REGULAR_EXPRESSION "3\.6-7; syntax error; unexpected ="
  LABELS "calc2;cmd;cmdline"
)

# hack for stdin for test programs
# use bash to run program because cmake alternatives are ugly and clunky
# be sure to use add_test NAME for multiline input
# disable on windows due to bash dependency
add_test(NAME calc2_06 COMMAND bash -c "$<TARGET_FILE:calc2> <<EOF
3-5
EOF
")
set_tests_properties(calc2_06 PROPERTIES
  PASS_REGULAR_EXPRESSION "^-2\n"
  LABELS "calc2;cmd;cmdline"
  DISABLED $<PLATFORM_ID:Windows>
)

add_test(NAME calc2_07 COMMAND bash -c "$<TARGET_FILE:calc2> <<EOF
3--5
EOF
")

set_tests_properties(calc2_07 PROPERTIES
  PASS_REGULAR_EXPRESSION "^8\n"
  LABELS "calc2;cmd;cmdline"
  DISABLED $<PLATFORM_ID:Windows>
)

add_test(NAME calc2_08 COMMAND bash -c "$<TARGET_FILE:calc2> <<EOF
3--+-5
EOF
")
set_tests_properties(calc2_08 PROPERTIES
  PASS_REGULAR_EXPRESSION "^-2\n"
  LABELS "calc2;cmd;cmdline"
  DISABLED $<PLATFORM_ID:Windows>
)

