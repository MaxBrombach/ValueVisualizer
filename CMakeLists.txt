cmake_minimum_required(VERSION 3.10)

project(Analyser)

find_package(CURL REQUIRED)

add_executable(Analyser
    src/main.cpp
    src/Tasks.cpp
    src/Threads.cpp
)

target_include_directories(Analyser PRIVATE
    include
    Extern_Libs
    ${CURL_INCLUDE_DIRS}
)

target_link_libraries(Analyser PRIVATE
    ${CURL_LIBRARIES}
)