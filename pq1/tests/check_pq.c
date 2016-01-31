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

#if 0
void setup(void)
{
    five_dollars = money_create(5, "USD");
}

void teardown(void)
{
    money_free(five_dollars);
}
#endif

START_TEST(test_pq)
{
    ck_assert_int_eq(1, 0);
}
END_TEST

Suite * money_suite(void)
{
    Suite *s;

    s = suite_create("Algo-2012");

    /* Core test case */
    TCase *tc_core;
    tc_core = tcase_create("Programming Questions");

//    tcase_add_checked_fixture(tc_core, setup, teardown);
    tcase_add_test(tc_core, test_pq);
    suite_add_tcase(s, tc_core);

    /* Limits test case */
#if 0
    TCase *tc_limits;
    tc_limits = tcase_create("Limits");

    tcase_add_test(tc_limits, test_money_create_neg);
    tcase_add_test(tc_limits, test_money_create_zero);
    suite_add_tcase(s, tc_limits);
#endif

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
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
