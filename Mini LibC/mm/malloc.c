// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

void *malloc(size_t size)
{
	/* TODO: Implement malloc(). */
	void *p = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0 );

	if(p == MAP_FAILED)
	return NULL;
	
	mem_list_add(p, size);
	return p;
}

void *calloc(size_t nmemb, size_t size)
{
	/* TODO: Implement calloc(). */
	void *p = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0 );

	if(p == MAP_FAILED)
	return NULL;
	
		mem_list_add(p, nmemb * size);
	memset(p, 0, nmemb * size);
	return p;
}

void free(void *ptr)
{
	/* TODO: Implement free(). */
	mem_list_del(ptr);
}

void *realloc(void *ptr, size_t size)
{
	/* TODO: Implement realloc(). */
	if(ptr == NULL )
	{
		ptr = malloc(size);
		return ptr;
	}

	void* p = mremap(ptr, sizeof(p), size, MREMAP_MAYMOVE );
	if( p == MAP_FAILED)
		return NULL;

	return p;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	/* TODO: Implement reallocarray(). */
	//size_t old_size = ptr ? nmemb * size : 0;
	size_t new_size = nmemb * size;

	void* p = realloc(ptr, new_size);
	//if( !p && new_size != 0 )
	//	errno = ENOMEM;


	return p;
}
