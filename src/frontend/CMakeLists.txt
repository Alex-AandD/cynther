set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(frontend_SOURCES lexer.cpp 
		     token.cpp 
		     expression.cpp
		     llparser.cpp
		     stmt.cpp
		     exceptions.cpp)
add_library(frontend ${frontend_SOURCES})
target_include_directories(frontend PRIVATE ${PROJECT_SOURCE_DIR}/include)
