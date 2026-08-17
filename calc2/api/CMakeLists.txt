# calc2/calc2_api/CMakeLists.txt

project(calc2_api)

# library

add_library(calc2_apilib INTERFACE calc2_api.h)

target_include_directories(calc2_apilib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(calc2_apilib INTERFACE flexbisonlib.calc2)


# tests

add_executable(calc2_api.gtest calc2_api.gtest.cpp)

target_link_libraries(calc2_api.gtest PRIVATE calc2_apilib gmock_main)

include(GoogleTest)
gtest_discover_tests(calc2_api.gtest DISCOVERY_MODE PRE_TEST EXTRA_ARGS --gtest_color=yes)

