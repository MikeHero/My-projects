// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source)
{
	/* TODO: Implement strcpy(). */
	char *p = source;
	int i = 0;
	while( *p != '\0')
	{
		destination[i++] = *p;
		p++;
	}
	destination[i] = '\0';
	return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	/* TODO: Implement strncpy(). */
	char *p = source;
	int i = 0;
	while( *p != '\0' && i < len)
	{
		destination[i++] = *p;
		p++;
	}
	if( i < len )
		destination[i] = '\0';

	return destination;
}

char *strcat(char *destination, const char *source)
{
	/* TODO: Implement strcat(). */
	char *p = source;
	int i = 0;
	
	while(destination[i] != '\0')
		i++;

	while( *p != '\0')
	{
		destination[i++] = *p;
		p++;
	}
	destination[i] = '\0';

	return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
	/* TODO: Implement strncat(). */
	char *p = source;
	int i = 0;
	int contor = 0;

	while(destination[i] != '\0')
		i++;

	while( *p != '\0' && contor < len)
	{
		destination[i++] = *p;
		p++;
		contor++;
	}
	destination[i] = '\0';

	return destination;
}

int strcmp(const char *str1, const char *str2)
{
	/* TODO: Implement strcmp(). */
	char* p1 = str1, *p2 = str2;
	while( *p1 == *p2 && *p1 != '\0')
	{
		p1++;
		p2++;
	}
	if( *p1 == '\0' && *p2 == '\0')
		return 0;
	if( *p1 > *p2 )
		return 1;
	return -1;
}

int strncmp(const char *str1, const char *str2, size_t len)
{
	/* TODO: Implement strncmp(). */
	int i = 0;
	char *p1 = str1;
	char* p2 = str2;

	while( (*p1 == *p2) && (*p1 != '\0') && (i < len) )
	{
		p1++;
		p2++;
		i++;
	}
	if( i == len )
		return 0;
	if( *p1 == '\0' && *p2 == '\0')
		return 0;
	if( *p1 > *p2 )
		return 1;
	return -1;
}

size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

char *strchr(const char *str, int c)
{
	/* TODO: Implement strchr(). */
	char *p = str;

	while( *p != '\0')
	{
		if( *p == c)
			return p;
		p++;
	}

	return NULL;
}

char *strrchr(const char *str, int c)
{
	/* TODO: Implement strrchr(). */
	char *p = str;
	int dim = strlen(str);
	p = p + dim - 1;
	char *inceput = str;
	
	while( p != inceput)
	{
		if( *p == c )
			return p;
		p--;
	}

	return NULL;
}

char *strstr(const char *haystack, const char *needle)
{
	/* TODO: Implement strstr(). */
	int i;
	for( i = 0; haystack[i] != '\0'; i++)
	{
		if(haystack[i] == needle[0])
		{
			int j;
			for( j = 0; needle[j] != '\0'; j++)
			{
				if(needle[j] != haystack[i + j])
					break;
			}
			if( needle[j] == '\0')
				return (haystack + i);
		}
	}
	return NULL;
}

char *strrstr(const char *haystack, const char *needle)
{
	/* TODO: Implement strrstr(). */

	char* res = NULL;
	int i;
	for( i = 0; haystack[i] != '\0'; i++)
	{
		if(haystack[i] == needle[0])
		{
			int j;
			for( j = 0; needle[j] != '\0'; j++)
			{
				if(needle[j] != haystack[i + j])
					break;
			}
			if( needle[j] == '\0')
				res = (haystack + i);
		}
	}

	return res;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memcpy(). */
	int contor = 0;
	char *p = destination;
	char *u = source;
	while( contor < num)
	{
		*p = *u;
		p++;
		u++;
		contor++;
	}
	return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memmove(). */
	char *p = destination;
	char *u = source;
	int i = 0;
	while( i < num )
	{
		*p = *u;
		p++;
		u++;
		i++;
	}

	return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	/* TODO: Implement memcmp(). */
	int i = 0;
	char *p1 = ptr1;
	char* p2 = ptr2;

	while( (*p1 == *p2) && (i < num) )
	{
		p1++;
		p2++;
		i++;
	}
	if( i == num )
		return 0;
	if( *p1 > *p2 )
		return 1;
	return -1;
}

void *memset(void *source, int value, size_t num)
{
	/* TODO: Implement memset(). */
	char * p = source;
	int i = 0;
	while( i < num )
	{
		*p = value;
		p++;
		i++;
	}

	return source;
}
