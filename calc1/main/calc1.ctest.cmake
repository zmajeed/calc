# calc1/main/calc1.ctest.cmake

add_test(NAME calc1_01 COMMAND calc1 -h)
set_tests_properties(calc1_01 PROPERTIES LABELS "calc1;cmd;cmdline")

add_test(NAME calc1_02 COMMAND calc1 -x)
set_tests_properties(calc1_02 PROPERTIES
  LABELS "calc1;cmd;cmdline"
  WILL_FAIL TRUE
)

add_test(NAME calc1_03 COMMAND calc1 -e "2 + 3")
set_tests_properties(calc1_03 PROPERTIES
  PASS_REGULAR_EXPRESSION "^5\n"
  LABELS "calc1;cmd;cmdline"
)

add_test(NAME calc1_04 COMMAND calc1 -e "x = 2 + 3; y = -7; x * y")
set_tests_properties(calc1_04 PROPERTIES
  PASS_REGULAR_EXPRESSION "^-35\n"
  LABELS "calc1;cmd;cmdline"
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

