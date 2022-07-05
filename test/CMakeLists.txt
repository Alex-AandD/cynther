include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG 4219e7254cb8c473f57f6065bd13d1520d7b708f
)

FetchContent_MakeAvailable(googletest)
add_subdirectory(frontend_test)
