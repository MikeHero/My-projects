#include <internal/syscall.h>
#include <stdio.h>
#include <string.h>

int puts(const char* s)
{
	
	syscall(__NR_write, 1, s, strlen(s));
	syscall(__NR_write, 1, "\n", 1);
	

	// returns positive value on succes
	// cate trupe canta diseara?
	return 3;
}
