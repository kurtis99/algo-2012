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

	size = store_file_to_array(CURRENT_TEST_DIR "../IntegerArray.txt", &tst_array);
	ck_assert_int_eq(size, 100000);
	free(tst_array);
}
END_TEST

START_TEST(test_pq_max)
{
	size_t i;
	size_t b, c;

	for (i = 2; i < 1000; i++) {
		b = max_B(i);
		c = max_C(i);

		ck_assert_int_eq(b + c, i);
	}
}
END_TEST

START_TEST(test_pq_middle)
{
	int mid;

	mid = get_middle(2);
	ck_assert_int_eq(mid, 1);
	mid = get_middle(4);
	ck_assert_int_eq(mid, 2);
	mid = get_middle(5);
	ck_assert_int_eq(mid, 3);
	mid = get_middle(6);
	ck_assert_int_eq(mid, 3);
	mid = get_middle(10);
	ck_assert_int_eq(mid, 5);
}
END_TEST

START_TEST(test_pq_merge)
{
	int tst_array[6] = {1,3,5,2,4,6};
	int sorted[6] = {1,2,3,4,5,6};
	size_t i;

	Merge_and_CountSplitInv(tst_array, ARRAY_SIZE(tst_array));

	for (i = 0; i < ARRAY_SIZE(tst_array); i++) {
		ck_assert_int_eq(tst_array[i], sorted[i]);
	}
}
END_TEST

START_TEST(test_pq_merge_and_countsplit)
{
	int tst_array[6] = {1,3,5,2,4,6};
	int inv;

	inv = Merge_and_CountSplitInv(tst_array, ARRAY_SIZE(tst_array));
	ck_assert_int_eq(inv, 3);
}
END_TEST

START_TEST(test_pq_sort_and_count)
{
	int tst_array[6] = {1,3,5,2,4,6};
	int inv;

	inv = Sort_and_Count(tst_array, ARRAY_SIZE(tst_array));

	ck_assert_int_eq(inv, 3);
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
    tcase_add_test(tc_algo, test_pq_middle);
    tcase_add_test(tc_algo, test_pq_merge);
    tcase_add_test(tc_algo, test_pq_merge_and_countsplit);
    tcase_add_test(tc_algo, test_pq_sort_and_count);
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

    //srunner_run_all(sr, CK_NORMAL | CK_NOFORK);
    srunner_run_all(sr, CK_NOFORK);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
