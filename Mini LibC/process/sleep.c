#include <internal/syscall.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>

unsigned int sleep(unsigned int seconds)
{
	
	struct timespec req;
	req.tv_sec = seconds;
	req.tv_nsec = 0;

	struct timespec rem;
	rem.tv_nsec = 0;
	rem.tv_sec = 0;

	
	return nanosleep(&req, &rem);

}