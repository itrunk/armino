//#include <time.h>
#include "FreeRTOS_POSIX.h"
#include "posix/time.h"

int main(void)
{
	struct timespec tp;

	clock_gettime(CLOCK_MONOTONIC, &tp);
	clock_gettime(CLOCK_REALTIME, &tp);
	return 0;
}
