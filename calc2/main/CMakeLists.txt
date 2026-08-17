# calc2/main/CMakeLists.txt

project(calc2_main)

add_executable(calc2 calc2.cpp)

target_link_libraries(calc2 flexbisonlib.calc2)
target_link_libraries(calc2 $<$<CXX_COMPILER_ID:MSVC>: getoptlib>)

# tests

include(calc2.ctest.cmake)
