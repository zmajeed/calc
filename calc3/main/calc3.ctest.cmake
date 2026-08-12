# calc3/main/calc3.ctest.cmake

add_test(NAME calc3_01 COMMAND calc3 -h)
set_tests_properties(calc3_01 PROPERTIES LABELS "calc3;cmd;cmdline")

add_test(NAME calc3_02 COMMAND calc3 -x)
set_tests_properties(calc3_02 PROPERTIES
  LABELS "calc3;cmd;cmdline"
  WILL_FAIL TRUE
)

add_test(NAME calc3_03 COMMAND calc3 -e "2 + 3")
set_tests_properties(calc3_03 PROPERTIES
  PASS_REGULAR_EXPRESSION "^5\n"
  LABELS "calc3;cmd;cmdline"
)

add_test(NAME calc3_04 COMMAND calc3 -e "x = 2 + 3; y = -7; x * y")
set_tests_properties(calc3_04 PROPERTIES
  PASS_REGULAR_EXPRESSION "^-35\n"
  LABELS "calc3;cmd;cmdline"
)

add_test(NAME calc3_05 COMMAND calc3 -e "x = 2 + 3;
y = -7;
x * y = 1
")
set_tests_properties(calc3_05 PROPERTIES
  WILL_FAIL TRUE
  FAIL_REGULAR_EXPRESSION "3\.6-7; syntax error; unexpected ="
  LABELS "calc3;cmd;cmdline"
)

add_test(NAME calc3_06 COMMAND calc3 --symbols -e "x = -4; y = z = 3; x = y * z")
set_tests_properties(calc3_06 PROPERTIES
  PASS_REGULAR_EXPRESSION "^9\n;x: 9\n;y: 3\n;z: 3\n"
  LABELS "calc3;cmd;cmdline"
)

# hack for stdin for test programs
# use bash to run program because cmake alternatives are ugly and clunky
# be sure to use add_test NAME for multiline input
# disable on windows due to bash dependency
add_test(NAME calc3_07 COMMAND bash -c "$<TARGET_FILE:calc3> <<EOF
3-5
EOF
")
set_tests_properties(calc3_07 PROPERTIES
  PASS_REGULAR_EXPRESSION "^-2\n"
  LABELS "calc3;cmd;cmdline"
  DISABLED $<PLATFORM_ID:Windows>
)

add_test(NAME calc3_08 COMMAND bash -c "$<TARGET_FILE:calc3> <<EOF
3--5
EOF
")

set_tests_properties(calc3_08 PROPERTIES
  PASS_REGULAR_EXPRESSION "^8\n"
  LABELS "calc3;cmd;cmdline"
  DISABLED $<PLATFORM_ID:Windows>
)

add_test(NAME calc3_09 COMMAND bash -c "$<TARGET_FILE:calc3> <<EOF
3--+-5
EOF
")
set_tests_properties(calc3_09 PROPERTIES
  PASS_REGULAR_EXPRESSION "^-2\n"
  LABELS "calc3;cmd;cmdline"
  DISABLED $<PLATFORM_ID:Windows>
)

