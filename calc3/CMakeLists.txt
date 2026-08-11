# calc3/CMakeLists.txt

project(calc3_top)

# reference implementation of c++26 indirect for vc++, clang
# library name is xyz_value_types
if(WIN32 OR CMAKE_CXX_COMPILER_ID STREQUAL Clang)

  FetchContent_Declare(
    value_types
    GIT_REPOSITORY https://github.com/jbcoe/value_types
    GIT_TAG main
    GIT_SHALLOW TRUE
  )
  FetchContent_MakeAvailable(value_types)

  execute_process(
    COMMAND bash -c "git log -1 --pretty=format:\"%h %cd %s\n\" --date=format-local:%F_%T_%Z; git remote -v | head -1; git branch"
    WORKING_DIRECTORY ${value_types_SOURCE_DIR}
    OUTPUT_VARIABLE cmdout
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  message(STATUS "C++ std indirect reference implementation source:\n${cmdout}")

endif()

FetchContent_Declare(
  isocline
  GIT_REPOSITORY https://github.com/daanx/isocline
  GIT_TAG main
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(isocline)

execute_process(
  COMMAND bash -c "git log -1 --pretty=format:\"%h %cd %s\n\" --date=format-local:%F_%T_%Z; git remote -v | head -1; git branch"
  WORKING_DIRECTORY ${isocline_SOURCE_DIR}
  OUTPUT_VARIABLE cmdout
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
message(STATUS "isocline source:\n${cmdout}")

# don't run bison, flex for windows and webassembly builds
if(WIN32 OR EMSCRIPTEN)
  message("Use checked-in pre-generated calc3 bison, flex files from flexbison.gen directory")
  add_subdirectory(flexbison.gen)
else()
  message("Generate calc3 bison, flex files from grammar directory")
  add_subdirectory(grammar)
endif()

add_subdirectory(parser)
add_subdirectory(lexer)
add_subdirectory(ast)
add_subdirectory(api)
add_subdirectory(main)

