// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int open(const char *filename, int flags, ...)
{
	/* TODO: Implement open system call. */
	int fd;
	va_list valist;

	va_start(valist, flags);
	mode_t mode = va_arg(valist, mode_t);
	va_end(valist);
	
	fd = syscall( __NR_open, filename, flags, mode );
	if( fd < 0 )
	{
		errno = -fd;
		fd = -1;
	}
	return fd;
}
