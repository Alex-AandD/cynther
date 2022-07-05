set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(app_SOURCES main.cpp)

add_executable(cynther ${app_SOURCES})
target_link_libraries(cynther PRIVATE frontend)
target_include_directories(cynther PRIVATE ${PROJECT_SOURCE_DIR}/include)
