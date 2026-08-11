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

add_test(NAME calc1_05 COMMAND calc2 -e "x = 2 + 3;
y = -7;
x * y = 1
")
set_tests_properties(calc1_05 PROPERTIES
  WILL_FAIL TRUE
  FAIL_REGULAR_EXPRESSION "3\.6-7; syntax error; unexpected ="
  LABELS "calc2;cmd;cmdline"
)

