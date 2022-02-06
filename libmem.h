/*	libmem.h */

#ifndef COM_PLUS_MEVANSPN_LIBMEM
#define COM_PLUS_MEVANSPN_LIBMEM

#include <inttypes.h>
#include <stdlib.h>

#define _MEMMAN_RECORD_CAPACITY_INC 64

struct _MEMMAN;

typedef struct {
	int32_t data_length;
	struct _MEMMAN * _manager;
} _MEMMAN_RECORD;

typedef struct _MEMMAN {
	_MEMMAN_RECORD ** records;
	void ** record_ids;
	int32_t record_count, current_record_capacity;
} MEMMAN;

static MEMMAN * _MEMMAN_ = NULL;

/*	PUBLIC METHODS */

/* MEMMAN_ALLOC is used to allocate 'size_in_bytes' bytes of memory.
	The method returns a pointer to the start of the allocated memory. */
void * MEMMAN_ALLOC(int32_t size_in_bytes);

/* MEMMAN_REALLOC is used to resize a previously allocated block of memory allocated by MEMMAN_ALLOC.
	 The method returns a pointer to the start of the newly sized memory area, which may not be the same as the original. */
void * MEMMAN_REALLOC(void * data_ptr, int32_t new_size_in_bytes);
int32_t MEMMAN_FREE(void * data_ptr);

/*	PRIVATE METHODS */
void _MEMMAN_INIT();
void _MEMMAN_EXIT();
#endif