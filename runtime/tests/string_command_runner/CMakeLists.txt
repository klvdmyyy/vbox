add_executable(string_command_runner_test string_command_runner_test.cpp)

target_link_libraries(string_command_runner_test PUBLIC entixruntime GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(string_command_runner_test)