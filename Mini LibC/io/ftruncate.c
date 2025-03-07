// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>

int ftruncate(int fd, off_t length)
{
	/* TODO: Implement ftruncate(). */
	int res = syscall( __NR_ftruncate, fd, length);
	close(fd);

	if( res < 0)
	{
		errno = - res;
		return -1;
	}

	//intoarce 0 succes, -1 eroare;
	return 0;
}
