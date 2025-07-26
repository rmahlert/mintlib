/*
 * entropy.c - Gather random bytes from system sources for MiNT.
 *
 * This file is part of the MiNTLib project.
 */

#include <mint/osbind.h>
#include <stddef.h>

/*
 * Fills a buffer with random bytes gathered from various MiNT system
 * entropy sources. This is intended for seeding a pseudo-random
 * number generator (PRNG).
 *
 * buf: A pointer to the destination buffer.
 * len: The number of random bytes to generate.
 *
 * returns: 0 on success, -1 on failure.
 */
int mint_get_random_bytes(unsigned char* buf, size_t len)
{
    if (buf == NULL) {
        return -1;
    }

    /* Pointers to volatile system variables (entropy sources) */
    volatile unsigned long* hz_200    = (volatile unsigned long*)0x4BA;    /* 200Hz system clock */
    volatile unsigned long* vbl_count = (volatile unsigned long*)0x466;    /* Vertical blank counter (_frlock) */

    /* Get the Line-A variable table to access mouse coordinates */
    long line_a_base = (long)LineA();
    volatile short* mouse_x = (volatile short*)(line_a_base - 602); /* GCURX */
    volatile short* mouse_y = (volatile short*)(line_a_base - 600); /* GCURY */

    unsigned long seed = 0;

    for (size_t i = 0; i < len; i++) {
        /*
         * Mix the entropy sources by repeatedly reading the fast-changing
         * timers and XORing them together with the mouse coordinates. This
         * combines hardware timing jitter with user input.
         */
        seed = (*hz_200) ^ (*vbl_count);
        seed ^= (((unsigned long)(*mouse_x)) << 16) | (*mouse_y);

        /* Simple rotation to ensure different bits are used for each byte generated */
        seed = (seed << 1) | (seed >> 31);

        buf[i] = (unsigned char)(seed & 0xFF);
    }

    return 0; /* Success */
}
