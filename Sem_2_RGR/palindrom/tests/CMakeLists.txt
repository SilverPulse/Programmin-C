add_executable(test_check test_check.c ../src/preprocess.c)
add_test(NAME check_test COMMAND test_check)
