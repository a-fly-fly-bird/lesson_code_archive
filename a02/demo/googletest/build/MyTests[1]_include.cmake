if(EXISTS "/Users/tanyong/Desktop/code/demo/googletest/build/MyTests[1]_tests.cmake")
  include("/Users/tanyong/Desktop/code/demo/googletest/build/MyTests[1]_tests.cmake")
else()
  add_test(MyTests_NOT_BUILT MyTests_NOT_BUILT)
endif()
