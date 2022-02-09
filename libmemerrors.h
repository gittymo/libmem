/*	error.h
		Simple error message system for libmem.  Works a bit like the errno.h system library.
		(C)2022 Morgan Evans */

#ifndef COM_PLUS_MEVANSPN_MEMERROR
#define COM_PLUS_MEVANSPN_MEMERROR

#include <inttypes.h>

#define LIBMEM_ERROR_NONE 0
#define LIBMEM_ERROR_NO_MEMORY 1

static int32_t LIBMEM_ERRNO = LIBMEM_ERROR_NONE;

#endif