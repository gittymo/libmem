# libmem
A small memory management library that allows for dynamic memory allocation and automatic release of allocated memory on program exit.

The library provides several public facing methods:
MEMMAN_ALLOC(int32_t size) is used to allocate a dynamic area of memory 'size' bytes in length.  The method returns a pointer to the start of the allocated memory.  If the method fails to allocate enough memory, the method will return a NULL pointer.

MEMMAN_REALLOC(void * data_ptr, int32_t new_size) is used to resize an area of memory previoiusly allocated by MEMMAN_ALLOC.  The method takes two parameters 'data_ptr' which points to the start of the memory to be resized and 'new_size' which gives the new required size of the memory.   Depending on how dynamic memory is allocated, the original contents may be moved to a different location in memory.  A pointer to the start of the resize memory area is returned and it is important to update any pointers to accomodate any changes to the location of the allocated memory.

MEMMAN_FREE(void * data_ptr) will free an area of memory that has previously been allocated or re-sized using MEMMAN methods.  The free method returns an unsigned interger value giving the total amount of memory freed.  NOTE:  data_ptr must point to the start of the memory area, there are currently no checks to see if a given address falls within the bounds of an allocated area of memory.

MEMMAN_SIZE(void * data_ptr) will return the size of an area of dynamic area allocated using MEMMAN methods ALLOC or REALLOC.  The parameter 
'data_ptr' must point to the starts of the allocated memory area.