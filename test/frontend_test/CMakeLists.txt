set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(frontend_test_SOURCES lexer_test.cpp)

add_library(frontend_t ${frontend_test_SOURCES})
target_link_libraries(frontend PRIVATE ${frontend_SOURCES})

target_include_directories(frontend_t PRIVATE ${PROJECT_SOURCE_DIR}/include)
