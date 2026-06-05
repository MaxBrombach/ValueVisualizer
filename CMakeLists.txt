cmake_minimum_required(VERSION 3.10)

project(Analyser)
set(CMAKE_CXX_STANDARD 20)

find_package(CURL REQUIRED)
include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(Analyser
    src/main.cpp
    src/Tasks.cpp
    src/Threads.cpp
)


enable_testing()
add_subdirectory(tests)


target_include_directories(Analyser PRIVATE
    include
    Extern_Libs
    ${CURL_INCLUDE_DIRS}
)

target_link_libraries(Analyser PRIVATE
    ${CURL_LIBRARIES}
)
