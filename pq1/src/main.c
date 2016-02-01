#include <stdio.h>
#include <stdlib.h>

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
	printf("Resizing array to new size: %zu\n", new_size);

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

	return count;
}

#ifndef TESTING_ENABLED
int main()
{
	// read data from file
	// store data into allocated array
	// count invertions
	int *arr;

	printf("Hello world!\n");

	store_file_to_array("/tmp/file.txt", &arr);

	if (arr) free(arr);

	return 0;
}
#endif /* TESTING_ENABLED */
