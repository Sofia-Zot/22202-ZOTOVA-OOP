if(EXISTS "C:/Users/Sofia/CLionProjects/task0/cmake-build-debug/StatisticsTest[1]_tests.cmake")
  include("C:/Users/Sofia/CLionProjects/task0/cmake-build-debug/StatisticsTest[1]_tests.cmake")
else()
  add_test(StatisticsTest_NOT_BUILT StatisticsTest_NOT_BUILT)
endif()
