add_test([=[MyTest.Sum]=]  /Users/tanyong/Desktop/code/demo/googletest/build/MyTests [==[--gtest_filter=MyTest.Sum]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MyTest.Sum]=]  PROPERTIES WORKING_DIRECTORY /Users/tanyong/Desktop/code/demo/googletest/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  MyTests_TESTS MyTest.Sum)
