#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

enum PivotRule {
	PQ2_CHOOSE_FIRST_ELEMENT,
	PQ2_CHOOSE_LAST_ELEMENT,
	PQ2_CHOOSE_MIDDLE_OF_THREE,
};

static int curr_size = 0;
static int curr_indx = 0;

void init_array(void)
{
	curr_size = 0;
	curr_indx = 0;
}

void append_to_array(int **arr, int elem)
{
	if (curr_indx >= curr_size) {
		if (curr_size == 0)
			curr_size = 1;
		curr_size *= 2;
		*arr = realloc(*arr, curr_size * sizeof(int));
		if (*arr == NULL)
			fprintf(stderr, "realloc failed\n");
	}

	(*arr)[curr_indx] = elem;
	curr_indx++;
}

void array_resize(int **arr, size_t new_size)
{
	*arr = realloc(*arr, new_size * sizeof(int));
}

int store_file_to_array(const char *file, int **arr)
{
	FILE *fd;
	char buf[32] = {0};
	int count; // count elements in file

	*arr = NULL;

	fd = fopen(file, "r");
	if (fd == NULL) {
		perror(file);
		return -1;
	}

	init_array();
	count = 0;
	while (fgets(buf, ARRAY_SIZE(buf), fd) != NULL) {
		int v;
		count++;
		v = strtol(buf, NULL, 10);
		append_to_array(arr, v);
	}

	array_resize(arr, count);
	fclose(fd);

	return count;
}

void swap(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

size_t QuickSort(int *arr, size_t len, enum PivotRule pr)
{
	/* Index of the pivot in current array */
	size_t pivot;
	size_t comps = 0;
	size_t i, j;

	if (len <= 1)
		return 0;

	switch (pr) {
		case PQ2_CHOOSE_FIRST_ELEMENT:
			pivot = 0;
			break;
		case PQ2_CHOOSE_LAST_ELEMENT:
			pivot = len - 1;
			break;
		case PQ2_CHOOSE_MIDDLE_OF_THREE:
			/* TODO */
			pivot = 0;
			break;
		default:
			fprintf(stderr, "Wrong pivot choose rule! (%d)\n", pr);
			break;
	}

	/* Implement partitioning */
	for (i = 1, j = 1; j < len; j++) {
		if (arr[j] < arr[pivot]) {
			swap(&arr[j], &arr[i]);
			i++;
		}
	}
	swap(&arr[pivot], &arr[i - 1]);

	if (pr != PQ2_CHOOSE_FIRST_ELEMENT)
		QuickSort(arr, pivot - 1, pr);
	if (pr != PQ2_CHOOSE_LAST_ELEMENT)
		QuickSort(&arr[pivot], len - pivot, pr);

	return comps;
}

#ifndef TESTING_ENABLED
int main()
{
	int *arr, *arr_tmp1, *arr_tmp2;
	int len;
	size_t comp;

	len = store_file_to_array(CURRENT_TEST_DIR "../QuickSort.txt", &arr);

	/* Create copies for 2nd and ... */
	arr_tmp1 = malloc(sizeof(int) * len);
	memcpy(arr_tmp1, arr, sizeof(int) * len);
	/*                           ... 3rd steps*/
	arr_tmp2 = malloc(sizeof(int) * len);
	memcpy(arr_tmp2, arr, sizeof(int) * len);

	printf("Choose first element as a pivot\n");
	comp = QuickSort(arr, len, PQ2_CHOOSE_FIRST_ELEMENT);
	printf("   Total number of comparisons = %zu\n", comp);

	/* TODO: Implement other rules for choosing pivot */
	/* */

	if (arr) free(arr);
	if (arr_tmp1) free(arr_tmp1);
	if (arr_tmp2) free(arr_tmp2);

	return 0;
}
#endif /* TESTING_ENABLED */
