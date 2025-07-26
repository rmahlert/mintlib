/*
 * clock_gettime.c - POSIX clock_gettime() implementation for MiNT
 *
 * This file is part of the MiNTLib.
 */

#include <time.h>
#include <mint/osbind.h>
#include <errno.h>

/*
 * Get the time of the specified clock.
 *
 * For MiNT, we can only reliably support CLOCK_MONOTONIC (time since boot).
 * We will treat CLOCK_REALTIME as an alias for it, as both will be based
 * on the time since the system started.
 */
int clock_gettime(clockid_t clk_id, struct timespec *tp)
{
    if (tp == NULL) {
        errno = EFAULT;
        return -1;
    }

    switch (clk_id) {
        case CLOCK_REALTIME:
        case CLOCK_MONOTONIC:
        {
            /*
             * _hz_200 is a 200Hz system timer tick count located at 0x4BA.
             * Each tick is 5,000,000 nanoseconds (1/200th of a second).
             */
            volatile unsigned long* hz_200 = (volatile unsigned long*)0x4BA;

            unsigned long ticks = *hz_200;

            /* Use 64-bit integers for calculations to prevent overflow. */
            unsigned long long total_nsecs = (unsigned long long)ticks * 5000000ULL;

            /* Convert total nanoseconds to seconds and remaining nanoseconds. */
            tp->tv_sec  = total_nsecs / 1000000000ULL;
            tp->tv_nsec = total_nsecs % 1000000000ULL;

            break;
        }

        default:
            /* Other clock types are not supported on this system. */
            errno = EINVAL;
            return -1;
    }

    return 0; /* Success */
}
