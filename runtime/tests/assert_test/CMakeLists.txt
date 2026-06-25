add_executable(assert_test assert_test.cpp)

target_link_libraries(assert_test PUBLIC entixruntime GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(assert_test)