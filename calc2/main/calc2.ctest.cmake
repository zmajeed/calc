# calc2/main/calc2.ctest.cmake

add_test(NAME calc2_001 COMMAND calc2 -h)
set_tests_properties(calc2_001 PROPERTIES LABELS "calc2;cmd;cmdline")

add_test(NAME calc2_002 COMMAND calc2 -x)
set_tests_properties(calc2_002 PROPERTIES
  LABELS "calc2;cmd;cmdline"
  WILL_FAIL TRUE
)

add_test(NAME calc2_003 COMMAND calc2 -e "2 + 3")
set_tests_properties(calc2_003 PROPERTIES
  PASS_REGULAR_EXPRESSION "^5\n"
  LABELS "calc2;cmd;cmdline"
)

add_test(NAME calc2_004 COMMAND calc2 -e "x = 2 + 3; y = -7; x * y")
set_tests_properties(calc2_004 PROPERTIES
  PASS_REGULAR_EXPRESSION "^-35\n"
  LABELS "calc2;cmd;cmdline"
)

add_test(NAME calc1_005 COMMAND calc2 -e "x = 2 + 3;
y = -7;
x * y = 1
")
set_tests_properties(calc1_005 PROPERTIES
  WILL_FAIL TRUE
  FAIL_REGULAR_EXPRESSION "3\.6-7; syntax error; unexpected ="
  LABELS "calc2;cmd;cmdline"
)

