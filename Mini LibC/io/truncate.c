// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>
#include <fcntl.h>

int truncate(const char *path, off_t length)
{
	/* TODO: Implement truncate(). */
	int fd = open(path, O_WRONLY);


	if( fd == -1 )
		return -1; // failed to open file

	int res = syscall( __NR_truncate, path, length);
	if(res < 0 )
	{	
		errno = -res;
		return -1;
	}
	


	//intoarce 0 succes, -1 eroare;
	return 0;
}
