add_test([=[HelloTest.BasicAssertions]=]  /home/jmaloney/Documents/mlone/build/matrixTest [==[--gtest_filter=HelloTest.BasicAssertions]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HelloTest.BasicAssertions]=]  PROPERTIES WORKING_DIRECTORY /home/jmaloney/Documents/mlone/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  matrixTest_TESTS HelloTest.BasicAssertions)
