# simple_calc/CMakeLists.txt

cmake_minimum_required(VERSION 4.2)

project(calc_minimal)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest
  GIT_TAG main
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(googletest)

add_subdirectory(thirdparty)
add_subdirectory(simple_calc)

enable_testing()
