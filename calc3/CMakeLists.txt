# calc3/CMakeLists.txt

project(calc3_top)

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

