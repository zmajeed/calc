# calc/CMakeLists.txt

cmake_minimum_required(VERSION 4.2)

project(calc)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest
  GIT_TAG main
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(googletest)

execute_process(
  COMMAND bash -c "git log -1 --pretty=format:\"%h %cd %s\n\" --date=format-local:%F_%T_%Z; git remote -v | head -1; git branch"
  WORKING_DIRECTORY ${googletest_SOURCE_DIR}
  OUTPUT_VARIABLE cmdout
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
message(STATUS "googletest source:\n${cmdout}")

enable_testing()

add_subdirectory(thirdparty)
add_subdirectory(calc1)
add_subdirectory(calc2)
add_subdirectory(calc3)

