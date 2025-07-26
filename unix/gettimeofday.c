/*
 * gettimeofday.c - POSIX gettimeofday() implementation for MiNTlib
 *
 */

#include <sys/time.h>
#include <mint/osbind.h>

/*
 * Get the current time in seconds and microseconds since the epoch.
 */
int gettimeofday(struct timeval *tv, struct timezone *tz)
{
    /* Check for a valid timeval pointer */
    if (tv) {
        /*
         * _hz_200 is a 200Hz system timer tick count located at 0x4BA.
         * Each tick is 1/200th of a second, or 5000 microseconds.
         * We declare it volatile to prevent the compiler from optimizing away the read.
         */
        volatile unsigned long* hz_200 = (volatile unsigned long*)0x4BA;

        unsigned long ticks = *hz_200;

        /* Use 64-bit integers for the total microsecond calculation to prevent overflow. */
        unsigned long long total_usecs = (unsigned long long)ticks * 5000ULL;

        /* Convert total microseconds to seconds and remaining microseconds. */
        tv->tv_sec  = total_usecs / 1000000ULL;
        tv->tv_usec = total_usecs % 1000000ULL;
    }

    /* The timezone argument is obsolete and should always be ignored. */
    (void)tz;

    return 0; /* Always returns 0 for success */
}
