add_test([=[StatisticStorage.addWord]=]  C:/Users/Sofia/CLionProjects/task0/cmake-build-debug/StatisticsTest.exe [==[--gtest_filter=StatisticStorage.addWord]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StatisticStorage.addWord]=]  PROPERTIES WORKING_DIRECTORY C:/Users/Sofia/CLionProjects/task0/cmake-build-debug SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[Statistics.sortStatistic]=]  C:/Users/Sofia/CLionProjects/task0/cmake-build-debug/StatisticsTest.exe [==[--gtest_filter=Statistics.sortStatistic]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Statistics.sortStatistic]=]  PROPERTIES WORKING_DIRECTORY C:/Users/Sofia/CLionProjects/task0/cmake-build-debug SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  StatisticsTest_TESTS StatisticStorage.addWord Statistics.sortStatistic)
