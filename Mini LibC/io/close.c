// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int close(int fd)
{
	/* TODO: Implement close(). */
	int ret = syscall(__NR_close, fd);
	// syscall close intoarce 0 daca succes, -1 eroare
	if( ret == -1 )
	{	
		errno = - ret;
		return -1;
	}
	// on succes
	return 0;
}
