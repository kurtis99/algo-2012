/*
 * Check: a unit test framework for C
 * Copyright (C) 2001, 2002 Arien Malec
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#include <stdlib.h>
#include <stdint.h>
#include <check.h>

#include <../src/main.c>

START_TEST(test_pq_append_to_array)
{
	int *tst_array;

	init_array();

	append_to_array(&tst_array, 0);
	ck_assert_int_eq(tst_array[0], 0);

	append_to_array(&tst_array, 1);
	ck_assert_int_eq(tst_array[0], 0);
	ck_assert_int_eq(tst_array[1], 1);

	append_to_array(&tst_array, 2);
	ck_assert_int_eq(tst_array[0], 0);
	ck_assert_int_eq(tst_array[1], 1);
	ck_assert_int_eq(tst_array[2], 2);

	append_to_array(&tst_array, 3);
	ck_assert_int_eq(tst_array[0], 0);
	ck_assert_int_eq(tst_array[1], 1);
	ck_assert_int_eq(tst_array[2], 2);
	ck_assert_int_eq(tst_array[3], 3);

	free(tst_array);
}
END_TEST

START_TEST(test_pq_read_array)
{
	int *tst_array;
	store_file_to_array(CURRENT_TEST_DIR "test_pattern1.txt", &tst_array);

	ck_assert_int_eq(tst_array[0], 1);
	ck_assert_int_eq(tst_array[1], 2);
	ck_assert_int_eq(tst_array[2], 3);
	ck_assert_int_eq(tst_array[3], 4);
	ck_assert_int_eq(tst_array[4], 5);
	ck_assert_int_eq(tst_array[5], 6);

	free(tst_array);
}
END_TEST

START_TEST(test_pq_read_array_len)
{
	int *tst_array;
	int size;

	size = store_file_to_array(CURRENT_TEST_DIR "test_pattern1.txt", &tst_array);
	ck_assert_int_eq(size, 6);
	free(tst_array);

	size = store_file_to_array(CURRENT_TEST_DIR "../QuickSort.txt", &tst_array);
	ck_assert_int_eq(size, 100000);
	free(tst_array);
}
END_TEST

START_TEST(test_pq_max)
{
}
END_TEST


Suite * money_suite(void)
{
    Suite *s;

    s = suite_create("Algo-2012");

    /* Core test case */
    TCase *tc_fileio;
    tc_fileio = tcase_create("File I/O");

    tcase_add_test(tc_fileio, test_pq_append_to_array);
    tcase_add_test(tc_fileio, test_pq_read_array);
    tcase_add_test(tc_fileio, test_pq_read_array_len);
    suite_add_tcase(s, tc_fileio);

    /* Core test case */
    TCase *tc_algo;
    tc_algo = tcase_create("Algorithm");

    tcase_add_test(tc_algo, test_pq_max);
    suite_add_tcase(s, tc_algo);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = money_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    //srunner_print(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
