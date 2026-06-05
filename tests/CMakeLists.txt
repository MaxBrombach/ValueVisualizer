add_executable(test_analyser
    test_analyser.cpp
    ../src/Tasks.cpp
)

target_include_directories(test_analyser PRIVATE
    ../include
    ../Extern_Libs
    ${CURL_INCLUDE_DIRS}
)


target_link_libraries(test_analyser
    PRIVATE
        gtest
        gtest_main
         ${CURL_LIBRARIES}
)

add_test(NAME TrendlineTest COMMAND test_analyser)
