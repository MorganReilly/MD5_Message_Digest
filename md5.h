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
} CONTEXT;

/* Function Declaration
   These define the function type and parameters of the functions used in md5.c
   Adapted from: R[4]: A.3 md5.c Page9
*/
void InitialiseMD5 ARG_LIST((CONTEXT *));
void NextBlock ARG_LIST((CONTEXT *, unsigned char *, unsigned int));
void GenerateMD5 ARG_LIST((unsigned char[16], CONTEXT *)); 