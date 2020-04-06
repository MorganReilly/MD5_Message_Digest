/* Morgan Reilly G00303598

-- MD5 Message Digest Algorithm --
-- Global Header --
Adapted from: https://www.ietf.org/rfc/rfc1321.txt

Section A.1 global.h
Set PROTOTYPES to be one, only if the compiler supports function argument prototyping
*/
#include "global.h"

/* MD5 context. */
typedef struct
{
    UINT4 state[4];           /* state (ABCD) */
    UINT4 count[2];           /* number of bits, modulo 2^64 (lsb first) */
    unsigned char buffer[64]; /* input buffer */
} MD5_CTX;

void MD5Init PROTO_LIST((MD5_CTX *));
void MD5Update PROTO_LIST((MD5_CTX *, unsigned char *, unsigned int));
void MD5Final PROTO_LIST((unsigned char[16], MD5_CTX *)); 