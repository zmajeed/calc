# calc1/lexer/CMakeLists.txt

project(calc1_lexer)

# tests

add_executable(calc1_lexer.gtest calc1_lexer.gtest.cpp)

target_link_libraries(calc1_lexer.gtest flexbisonlib.calc1 gmock_main)

include(GoogleTest)
gtest_discover_tests(calc1_lexer.gtest DISCOVERY_MODE PRE_TEST EXTRA_ARGS --gtest_color=yes)
