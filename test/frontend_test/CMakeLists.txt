enable_testing()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/test/frontend)

add_executable(
  lexer_test
  lexer_test.cpp
)

target_link_libraries(
  lexer_test
  gtest_main
  frontend
)

add_executable(
    parser_test
    parser_test.cpp
)

target_link_libraries(
    parser_test
    gtest_main
    frontend
)

target_include_directories(lexer_test PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(parser_test PRIVATE ${PROJECT_SOURCE_DIR}/include)

add_test(
    NAME lexer_test
    COMMAND $<TARGET_FILE:lexer_test>
)

add_test(
    NAME parser_test
    COMMAND $<TARGET_FILE:lexer_test>
)
