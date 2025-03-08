// SPDX-License-Identifier: BSD-3-Clause

#include "osmem.h"
#include "helpers.h"

/* Block metadata status values */
#define STATUS_FREE   0
#define STATUS_ALLOC  1
#define STATUS_MAPPED 2

#define MMAP_THRESHOLD	(128 * 1024)
#define ALLIGN 8
#define STRUCT_SIZE 24
#define PAGE_SIZE 4096

struct block_meta *L = NULL;
struct block_meta *p = NULL;
struct block_meta *ultim = NULL, *ant = NULL;


void *os_malloc(size_t size)
{
	/* TODO: Implement os_malloc */
	if( size == 0)
		return NULL;

	int initial_size = size;

	size = size + STRUCT_SIZE;
	int rest = size % 8;

	if(rest != 0)
		size += ( ALLIGN - rest);
		
	
	if( size >= MMAP_THRESHOLD)
	{
		L = mmap(NULL , size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
		if( L == MAP_FAILED)
			return NULL;

		L->size = size;
		L->status = STATUS_MAPPED;
		L->next = NULL;

		return (void*)L + STRUCT_SIZE;
	}
	else
	{
		// Preallocate
		if( L == NULL )
		{
			L = sbrk(MMAP_THRESHOLD);

			L->size = size;
			L->status = STATUS_ALLOC;
			L->next = NULL;

			ultim = L;

			return (void*)L + STRUCT_SIZE;
		}
		else
		{
			
			// coalesce
			int gasit = 1;
			while( gasit )
			{
				gasit = 0;
				ant = NULL;
				for( p = L; p != NULL; ant = p, p = p->next)
				{
					if((ant != NULL) && (ant->status == STATUS_FREE) && (p->status == STATUS_FREE))
					{
						gasit = 1;
						ant->next = p->next;
						p->next = NULL;
						ant->size += (void*)p->size + STRUCT_SIZE;
					}
				}
			}


			// incercam sa ii gasim loc in lista undeva unde am dat free
			for(struct block_meta *j = L; j != NULL; j = j->next )
			{
				if( j->status == STATUS_FREE)
				{	
					if(j->size - STRUCT_SIZE >= initial_size )
					{
						int putem_face_split = j->size - STRUCT_SIZE - initial_size;
						if( putem_face_split >= STRUCT_SIZE + 8)
						{
							struct block_meta *t = (void*)j + size ;
							unsigned int dim_init = j->size;

							j->size = size;
							j->status = STATUS_ALLOC;
							t->size = dim_init - j->size;
							
							t->next = j->next;
							j->next = t;
							t->status = STATUS_FREE;
							return (void*)j + STRUCT_SIZE;
						}
						else
						{
							j->status = STATUS_ALLOC;
							return (void*)j + STRUCT_SIZE;	
						}
						
					}
				}
			}

			// nu i-am gasit loc
			// incercam sa marim ultimul brk cu status free sa facem expand
			{
				// gasim ultimul brk cu status free
				struct block_meta* u = NULL;
				
				for( struct block_meta* index = L; index != NULL; index = index->next)
				{
					// ultimul brk
					if( (index->status == STATUS_FREE) || (index->status == STATUS_ALLOC))
						u = index;
				}
				
				// verificam ca l-am gasit si ca are status free
				if( (u != NULL) && (u->status == STATUS_FREE))
				{
					unsigned int dif = size - u->size;
					p = sbrk(dif);
					u->size += dif;
					u->status = STATUS_ALLOC;
					return (void*)u + STRUCT_SIZE;
				}
			}

			// daca nu se poate si nu se poate, facem un chunk nou
			{
				p = sbrk(size);
				p->size= size;
				p->status = STATUS_ALLOC;
				p->next = NULL;

				ultim->next = p;
				ultim = p;

				return (void*)p + STRUCT_SIZE;
			}
		}
	}


	return NULL;
}

void os_free(void *ptr)
{
	/* TODO: Implement os_free */

	if(ptr == NULL) return;
	
	 
	struct block_meta *p = ptr - sizeof(struct block_meta);
	int status =  p->status;	


	if( status == STATUS_MAPPED )
	{
		int rc = munmap( (void*)p, p->size );
		DIE( rc != 0, "Eroare munmap in os_free\n");	
	}
	else if( status == STATUS_ALLOC)
	{
		p->status = STATUS_FREE;

	}
	
}

void *os_calloc(size_t nmemb, size_t size)
{
	/* TODO: Implement os_calloc */
	if(nmemb == 0 || size == 0)
		return NULL;

	int initial_size = size;

	size = size * nmemb + STRUCT_SIZE;
	int rest = size % 8;

	if(rest != 0)
		size += ( ALLIGN - rest);

	if( size >= PAGE_SIZE )
	{
		p = mmap(NULL , size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
		if( p == MAP_FAILED)
			return NULL;

		p->size = size;
		p->status = STATUS_MAPPED;
		p->next = NULL;

		if( L == NULL )
		{
			L = p;
			ultim = L;
		}

		memset( (void*)p + STRUCT_SIZE, 0, p->size - STRUCT_SIZE);
		return (void*)p + STRUCT_SIZE;
	}
	else
	{
		// Preallocate
		if( L == NULL )
		{
			L = sbrk(MMAP_THRESHOLD);

			L->size = size;
			L->status = STATUS_ALLOC;
			L->next = NULL;

			ultim = L;

			memset((void*)L + STRUCT_SIZE, 0, L->size - STRUCT_SIZE);
			return (void*)L + STRUCT_SIZE;
		}
		else
		{

			// coalesce
			int gasit = 1;
			while( gasit )
			{
				gasit = 0;
				ant = NULL;
				for( p = L; p != NULL; ant = p, p = p->next)
				{
					if( (ant != NULL) && (ant->status == STATUS_FREE) && (p->status == STATUS_FREE) )
					{
						gasit = 1;
						ant->next = p->next;
						p->next = NULL;
						ant->size += (void*)p->size + STRUCT_SIZE;
					}
				}
			}


			// incercam sa ii gasim loc in lista undeva unde am dat free
			for(struct block_meta *j = L; j != NULL; j = j->next )
			{
				if( j->status == STATUS_FREE)
				{	
					if(j->size - STRUCT_SIZE >= initial_size )
					{
						int putem_face_split = j->size - STRUCT_SIZE - initial_size;
						if( putem_face_split >= STRUCT_SIZE + 8)
						{
							struct block_meta *t = (void*)j + size ;
							unsigned int dim_init = j->size;

							j->size = size;
							j->status = STATUS_ALLOC;
							t->size = dim_init - j->size;
							
							t->next = j->next;
							j->next = t;
							t->status = STATUS_FREE;
							
							memset( (void*)j + STRUCT_SIZE, 0, j->size - STRUCT_SIZE );
							return (void*)j + STRUCT_SIZE;
						}
						else
						{
							j->status = STATUS_ALLOC;
							
							memset( (void*)j + STRUCT_SIZE, 0, j->size - STRUCT_SIZE );
							return (void*)j + STRUCT_SIZE;	
						}
						
					}
				}
			}

			// nu i-am gasit loc
			// incercam sa marim ultimul brk cu status free sa facem expand
			{
				// gasim ultimul brk cu status free
				struct block_meta* u = NULL;
				
				for( struct block_meta* index = L; index != NULL; index = index->next)
				{
					// ultimul brk
					if( (index->status == STATUS_FREE) || (index->status == STATUS_ALLOC))
						u = index;
				}
				
				// verificam ca l-am gasit si ca are status free
				if( (u != NULL) && (u->status == STATUS_FREE))
				{
					unsigned int dif = size - u->size;
					p = sbrk(dif);
					u->size += dif;
					u->status = STATUS_ALLOC;

					memset( (void*)u + STRUCT_SIZE, 0, u->size - STRUCT_SIZE);
					return (void*)u + STRUCT_SIZE;
				}
			}

			// daca nu se poate si nu se poate, facem un chunk nou
			{
				p = sbrk(size);
				p->size= size;
				p->status = STATUS_ALLOC;
				p->next = NULL;

				ultim->next = p;
				ultim = p;

				memset( (void*)p + STRUCT_SIZE, 0, p->size - STRUCT_SIZE );
				return (void*)p + STRUCT_SIZE;
			}


		}
	}



	return NULL;
}

void *os_realloc(void *ptr, size_t size)
{
	/* TODO: Implement os_realloc */

	if(ptr == NULL)
		return os_malloc(size);
	
	if(size == 0)
	{	
		os_free(ptr);
		return NULL;
	}


	//return NULL;
}

