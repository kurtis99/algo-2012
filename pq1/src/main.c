#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

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

size_t get_middle(const size_t len)
{
	if (len % 2) {
		return (len / 2) + 1;
	} else {
		return len / 2;
	}
}

void __inc(size_t *i, const size_t max)
{
	if ((*i + 1) > max)
		return;
	*i += 1;
}

size_t max_B(const size_t len)
{
	return get_middle(len);
}

size_t max_C(const size_t len)
{
	return len - get_middle(len);
}

size_t Merge_and_CountSplitInv(int *arr, size_t len)
{
	size_t invs;
	size_t i, j, k;
	int *B, *C, *D;

	D = calloc(len, sizeof(int));
	if (D == NULL)
		fprintf(stderr, "Calloc failed\n");

	B = arr;
	C = &arr[get_middle(len)];

	invs = 0;

	for (i = j = k = 0; k < len; k++) {
		if (i == max_B(len)) {
			D[k] = C[j];
			j++;
			continue;
		}

		if (j == max_C(len)) {
			D[k] = B[i];
			i++;
			invs++;
			continue;
		}

		if ((B[i] < C[j])) {
			D[k] = B[i];
			__inc(&i, max_B(len));
		} else if (B[i] > C[j]) {
			D[k] = C[j];
			__inc(&j, max_C(len));
			invs += get_middle(len) - i;
		}
	}

	memcpy(arr, D, len * sizeof(int));
	free(D);

	return invs;
}

size_t Sort_and_Count(int *arr, size_t len)
{
	size_t x, y, z;

	if (len == 1)
		return 0;

	/* TODO: Wont work for odd number of elements */
	x = Sort_and_Count(arr, max_B(len));
	y = Sort_and_Count(&arr[get_middle(len)], max_C(len));
	z = Merge_and_CountSplitInv(arr, len);

	return x + y + z;
}

#ifndef TESTING_ENABLED
int main()
{
	int *arr;
	int len;
	size_t invertions;

	len = store_file_to_array(CURRENT_TEST_DIR "../IntegerArray.txt", &arr);

	invertions = Sort_and_Count(arr, len);

	printf("There is %zu invertions\n", invertions);

	if (arr) free(arr);

	return 0;
}
#endif /* TESTING_ENABLED */
