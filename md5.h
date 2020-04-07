/* Morgan Reilly G00303598

-- MD5 Message Digest Algorithm --
-- Global Header --
Adapted from: https://www.ietf.org/rfc/rfc1321.txt

Section A.1 global.h
Set PROTOTYPES to be one, only if the compiler supports function argument prototyping
*/
#include "global.h"

/* MD5 context struct declaration. */
typedef struct
{
    UINT4 word_state[4];           /* state (ABCD) */
    UINT4 bit_count[2];           /* number of bits, modulo 2^64 (lsb first) */
    unsigned char input_buffer[64]; /* input buffer */
} MD5_CTX;

/* Function Declaration
   These define the function type and parameters of the functions used in md5.c
   R[4]: A.3 md5.c Page9
*/
void MD5Init ARG_LIST((MD5_CTX *));
void MD5Update ARG_LIST((MD5_CTX *, unsigned char *, unsigned int));
void MD5Final ARG_LIST((unsigned char[16], MD5_CTX *)); 