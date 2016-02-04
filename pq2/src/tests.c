#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TESTING_ENABLED
#include "main.c"

int main()
{
#if 0
	//int tst_array[6] = {1,3,5,2,4,6};
	int tst_array[6] = {6,5,4,3,2,1};
	int sorted[6] = {1,2,3,4,5,6};
	size_t i, invs;

	//invs = Merge_and_CountSplitInv(tst_array, ARRAY_SIZE(tst_array));
	invs = Sort_and_Count(tst_array, ARRAY_SIZE(tst_array));

	for (i = 0; i < ARRAY_SIZE(tst_array); i++) {
		printf("%zu : tst %d - sorted %d\n", i, tst_array[i], sorted[i]);
	}

	printf("invertions = %zu\n", invs);
#else
	printf("Nothing to test!\n");
#endif

	return 0;
}
