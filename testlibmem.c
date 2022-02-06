/*	testlibmem.c
		A small program to test my memory management library.
		(C)2021 Morgan Evans */

#include "libmem.h"
#include <string.h>
#include <stdio.h>

int main(int argc, char * argv[])
{
	const char * test_text = "Hello world!";
	char * mem = MEMMAN_ALLOC(strlen(test_text) + 1);
	if (mem != NULL) {
		strcpy(mem, test_text);
		printf("Copied the string '%s' as '%s'.\n", test_text, mem);
	}
	// It is IMPERITIVE that exit is called to exit the main method, otherwise the MEMMAN cleaner will not run and memory won't be freed.
	exit(EXIT_SUCCESS);
}