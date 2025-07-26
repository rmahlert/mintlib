/*
 * arc4random_buf.c - A standard BSD function for getting cryptographically
 * secure random bytes.
 *
 * This file is part of the MiNTLib project.
 */

#include <stdlib.h>
#include <stddef.h>

/* Forward declaration for our low-level MiNT entropy gathering function */
int mint_get_random_bytes(unsigned char* buf, size_t len);

/*
 * Fills the provided buffer with cryptographically strong random data.
 * This is the recommended function for seeding PRNGs or for any
 * application needing high-quality randomness.
 */
void arc4random_buf(void *buf, size_t nbytes)
{
    if (buf != NULL && nbytes > 0) {
        /* Call our MiNT-specific entropy gathering function */
        mint_get_random_bytes((unsigned char*)buf, nbytes);
    }
}
