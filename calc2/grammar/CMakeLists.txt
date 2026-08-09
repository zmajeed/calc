# calc2/grammar/CMakeLists.txt

project(calc2_grammar)

find_package(FLEX)
find_package(BISON)

# generated source filename should match .l filename
flex_target(flex_files calc2_lexer.flex.l
  ${CMAKE_CURRENT_BINARY_DIR}/calc2_lexer.flex.cpp
  COMPILE_FLAGS "-f --nounistd"
)
 
# generated source filename should match .y filename
bison_target(bison_files calc2_parser.bison.y
  ${CMAKE_CURRENT_BINARY_DIR}/calc2_parser.bison.cpp
  DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/calc2_parser.bison.h
  COMPILE_FLAGS "-Wall -Wdangling-alias -Werror --report lookaheads,cex,solved --report-file calc2_grammar_report.txt"
)

# makes bison_files depend on flex_files
add_flex_bison_dependency(flex_files bison_files)

add_library(flexbisonlib.calc2 STATIC ${FLEX_flex_files_OUTPUTS} ${BISON_bison_files_OUTPUT_SOURCE})

target_compile_definitions(flexbisonlib.calc2 PRIVATE $<$<PLATFORM_ID:CYGWIN>: GTEST_HAS_PTHREAD=1 _POSIX_C_SOURCE=200809L _GNU_SOURCE>)

target_compile_options(flexbisonlib.calc2 PRIVATE
  $<$<CXX_COMPILER_ID:GNU>: -std=c++26 -Wall -Werror -Wextra -pthread -fconcepts-diagnostics-depth=10>
  $<$<CXX_COMPILER_ID:Clang>: -Wall -Werror -Wextra -std=c++26 -pthread -Wno-unqualified-std-cast-call>
)
target_compile_options(flexbisonlib.calc2 PRIVATE
  $<$<AND:$<CONFIG:debug>,$<CXX_COMPILER_ID:GNU>>: -O0 -ggdb3>
  $<$<AND:$<CONFIG:release>,$<CXX_COMPILER_ID:GNU>>: -Og>
  $<$<AND:$<CONFIG:debug>,$<CXX_COMPILER_ID:Clang>>: -O0 -ggdb3>
  $<$<AND:$<CONFIG:release>,$<CXX_COMPILER_ID:Clang>>: -Og>
)

target_include_directories(flexbisonlib.calc2 PUBLIC ${CMAKE_SOURCE_DIR}/calc2 ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(flexbisonlib.calc2 PUBLIC
  $<$<PLATFORM_ID:Darwin>: ${FLEX_INCLUDE_DIRS}>
)

add_custom_command(TARGET flexbisonlib.calc2 POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_BINARY_DIR}/calc2_grammar_report.txt ${CMAKE_CURRENT_SOURCE_DIR})

# copy generated files and bison grammar report to source tree
set(GEN_SRC_DIR ${CMAKE_SOURCE_DIR}/calc2/flexbison.gen)

add_custom_command(TARGET flexbisonlib.calc2 POST_BUILD
  COMMENT "Copy generated parser, lexer and bison grammar report to source tree"
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_BINARY_DIR}/calc2_grammar_report.txt ${CMAKE_CURRENT_SOURCE_DIR}
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_BINARY_DIR}/calc2_parser.bison.h ${GEN_SRC_DIR}
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_BINARY_DIR}/calc2_parser.bison.cpp ${GEN_SRC_DIR}
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_BINARY_DIR}/calc2_locations.bison.h ${GEN_SRC_DIR}
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_BINARY_DIR}/calc2_lexer.flex.cpp ${GEN_SRC_DIR}
)

# damn annoying mac
if(NOT APPLE)
  set(OPT_I -i)
else()
  set(OPT_I "-i \"\"")
endif()

add_custom_command(TARGET flexbisonlib.calc2 POST_BUILD
  COMMENT "Strip absolute local paths from generated bison, flex files"
  COMMAND sed -E ${OPT_I} 's!${CMAKE_CURRENT_BINARY_DIR}!${GEN_SRC_DIR}!' ${GEN_SRC_DIR}/calc2_parser.bison.h
  COMMAND sed -E ${OPT_I} 's!${CMAKE_SOURCE_DIR}!.!' ${GEN_SRC_DIR}/calc2_parser.bison.h
  COMMAND sed -E ${OPT_I} 's!${CMAKE_CURRENT_BINARY_DIR}!${GEN_SRC_DIR}!' ${GEN_SRC_DIR}/calc2_parser.bison.cpp
  COMMAND sed -E ${OPT_I} 's!${CMAKE_SOURCE_DIR}!.!' ${GEN_SRC_DIR}/calc2_parser.bison.cpp
  COMMAND sed -E ${OPT_I} 's!${CMAKE_CURRENT_BINARY_DIR}!${GEN_SRC_DIR}!' ${GEN_SRC_DIR}/calc2_locations.bison.h
  COMMAND sed -E ${OPT_I} 's!${CMAKE_SOURCE_DIR}!.!' ${GEN_SRC_DIR}/calc2_locations.bison.h
  COMMAND sed -E ${OPT_I} 's!${CMAKE_CURRENT_BINARY_DIR}!${GEN_SRC_DIR}!' ${GEN_SRC_DIR}/calc2_lexer.flex.cpp
  COMMAND sed -E ${OPT_I} 's!${CMAKE_SOURCE_DIR}!.!' ${GEN_SRC_DIR}/calc2_lexer.flex.cpp
)

add_custom_command(TARGET flexbisonlib.calc2 POST_BUILD
  COMMENT "Verbatim strip absolute local paths from generated bison, flex files"
  COMMAND sed -E ${OPT_I} [[s/(YY_YY).*(_CALC2_PARSER_BISON_H)/\1\2/]] ${GEN_SRC_DIR}/calc2_parser.bison.h
  COMMAND sed -E ${OPT_I} [[s/(YY_YY).*(_LOCATIONS_BISON_H)/\1\2/]] ${GEN_SRC_DIR}/calc2_locations.bison.h
  VERBATIM
)

