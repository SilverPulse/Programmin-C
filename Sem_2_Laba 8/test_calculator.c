#include <check.h>
#include <stdlib.h>
#include "calculator.h" 

START_TEST(test_add) {
    ck_assert_int_eq(add(2, 3), 5);
    ck_assert_int_eq(add(-1, 1), 0);
    ck_assert_int_eq(add(0, 0), 0);
}
END_TEST

START_TEST(test_subtract) {
    ck_assert_int_eq(subtract(5, 3), 2);
    ck_assert_int_eq(subtract(0, 0), 0);
    ck_assert_int_eq(subtract(-1, -1), 0);
}
END_TEST

START_TEST(test_bubble_sort) {
    int arr1[] = {4, 2, 7, 1, 3};
    int expected1[] = {1, 2, 3, 4, 7};
    bubble_sort(arr1, 5);
    for (int i = 0; i < 5; i++) {
        ck_assert_int_eq(arr1[i], expected1[i]);
    }

    int arr2[] = {1};
    bubble_sort(arr2, 1);
    ck_assert_int_eq(arr2[0], 1);
}
END_TEST

Suite *calculator_suite(void) {
    Suite *s = suite_create("Calculator");
    TCase *tc = tcase_create("Core");

    tcase_add_test(tc, test_add);
    tcase_add_test(tc, test_subtract);
    tcase_add_test(tc, test_bubble_sort);

    suite_add_tcase(s, tc);
    return s;
}

int main(void) {
    Suite *s = calculator_suite();
    SRunner *sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);  // Форматированный вывод
    int number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
