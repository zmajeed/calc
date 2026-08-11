# calc3/main/calc3.ctest.cmake

add_test(NAME calc3_001 COMMAND calc3 -h)
set_tests_properties(calc3_001 PROPERTIES LABELS "calc3;cmd;cmdline")

add_test(NAME calc3_002 COMMAND calc3 -x)
set_tests_properties(calc3_002 PROPERTIES
  LABELS "calc3;cmd;cmdline"
  WILL_FAIL TRUE
)

add_test(NAME calc3_003 COMMAND calc3 -e "2 + 3")
set_tests_properties(calc3_003 PROPERTIES
  PASS_REGULAR_EXPRESSION "^5\n"
  LABELS "calc3;cmd;cmdline"
)

add_test(NAME calc3_004 COMMAND calc3 -e "x = 2 + 3; y = -7; x * y")
set_tests_properties(calc3_004 PROPERTIES
  PASS_REGULAR_EXPRESSION "^-35\n"
  LABELS "calc3;cmd;cmdline"
)

add_test(NAME calc1_005 COMMAND calc3 -e "x = 2 + 3;
y = -7;
x * y = 1
")
set_tests_properties(calc1_005 PROPERTIES
  WILL_FAIL TRUE
  FAIL_REGULAR_EXPRESSION "3\.6-7; syntax error; unexpected ="
  LABELS "calc3;cmd;cmdline"
)

add_test(NAME calc3_006 COMMAND calc3 --symbols -e "x = -4; y = z = 3; x = y * z")
set_tests_properties(calc3_006 PROPERTIES
  PASS_REGULAR_EXPRESSION "^9\n;x: 9\n;y: 3\n;z: 3\n"
  LABELS "calc3;cmd;cmdline"
)

