cmake_minimum_required(VERSION 3.23)
project(Cynther)

# c++ 14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)
add_subdirectory(test)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

FetchContent_MakeAvailable(googletest)

set(CTEST_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/Testing)
enable_testing()

