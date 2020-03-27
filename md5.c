// Morgan Reilly
// G00303598

// -- MD5 Message Digest Algorithm --

// References:
// [1] http://cacr.uwaterloo.ca/hac/about/chap9.pdf -- HandBook of Applied Cryptography, Chapter 9.49
// [3*] https://www.iusmentis.com/technology/hashfunctions/md5/ -- MD5 Diagram (Block Processing)
// [4] http://practicalcryptography.com/hashes/md5-hash/ -- MD5 Specification
// [5] https://www.ietf.org/rfc/rfc1321.txt -- MD5 Specification
// [7] https://www.geeksforgeeks.org/bitwise-operators-in-c-cpp/ -- Bitwise Operations
// [10] https://code.woboq.org/linux/linux/crypto/md4.c.html -- MD4 code -- used for helping me understand the rounds
// [11] http://www.herongyang.com/Cryptography/MD5-Message-Digest-Algorithm-Overview.html
// [12] https://cs.indstate.edu/~fsagar/doc/paper.pdf

// About MD5:
// MD5 was designed as a strengthened version of MD4, prior to actual MD4 collisions being found.
// MD5 is obtained from MD4 by making modifications.
// These changes will be outlined in this project where implemented.
// MD5 operates on 32-bit words.

#include <stdio.h>
#include <inttypes.h>
#include <endian.h>

// Definition of a four byte word
typedef unsigned long int UINT4;
// Defintion of a word - R[3]: 2. Terminology and Notation
#define WORD uint32_t

// The Table - R[12]: 3.4.2 The Table
// Pregenerated by using sin function:
// abs(sin(i + 1)) × 2^32
//TODO:
const uint32_t T[] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
                      0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
                      0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
                      0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
                      0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
                      0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
                      0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
                      0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
                      0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
                      0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
                      0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
                      0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
                      0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
                      0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
                      0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
                      0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

// -- Auxillary Functions --
// Input 3 32-bit words --> Produce as output one 32-bit word
// F acts as conditional: if X then Y else Z
// G,H,I act in "bitwise parallel" to produce output from bits of X, Y, Z

// Function Declaratin -- Reference [4]
// Also adapted from reference [9] (which is the code part of reference [5])
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))
#define LSHIFT(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

// Reference [9] -- Defining rounds
// Where:
// a,b,c,d --> Initial buffer values
// k --> index of K[] value
// s -->
#define FF(a, b, c, d, x, s, ac)                     \
    {                                                \
        (a) += F((b), (c), (d)) + (x) + (UINT4)(ac); \
        (a) = LSHIFT((a), (s));                      \
        (a) += (b);                                  \
    }
#define GG(a, b, c, d, x, s, ac)                     \
    {                                                \
        (a) += G((b), (c), (d)) + (x) + (UINT4)(ac); \
        (a) = LSHIFT((a), (s));                      \
        (a) += (b);                                  \
    }
#define HH(a, b, c, d, x, s, ac)                     \
    {                                                \
        (a) += H((b), (c), (d)) + (x) + (UINT4)(ac); \
        (a) = LSHIFT((a), (s));                      \
        (a) += (b);                                  \
    }
#define II(a, b, c, d, x, s, ac)                     \
    {                                                \
        (a) += I((b), (c), (d)) + (x) + (UINT4)(ac); \
        (a) = LSHIFT((a), (s));                      \
        (a) += (b);                                  \
    }

// Preprocessing
// Create union 512int blocks
typedef union {
    uint64_t sixfour[8];   // 64 * 8 = 512 -- 8 64bit intger array
    uint32_t threetwo[16]; // 32 * 16 = 512 -- 16 32bit integer array
    uint8_t eight[64];     // 8 * 64 = 512 -- 64 8bit integer array
} BLOCK;

// Represent current parse status
typedef enum
{
    READ, // Not EOF -- Read OG file
    PAD0, // Pad with 0's
    FINISH
} PADFLAG;

// Next Hash
// Taking a block M, and calculating next block H
int nexthash(WORD *M, WORD *Hash)
{
    uint32_t A, B, C, D, x[16];
    A = Hash[0];
    B = Hash[1];
    C = Hash[2];
    D = Hash[3];

    // Round Declaration -- Reference [4]
    // Round 1 -- FF
    FF(A, B, C, D, x[0], 7, T[0]);
    FF(D, A, B, C, x[1], 12, T[1]);
    FF(C, D, A, B, x[2], 17, T[2]);
    FF(B, C, D, A, x[3], 22, T[3]);

    FF(A, B, C, D, x[4], 7, T[4]);
    FF(D, A, B, C, x[5], 12, T[5]);
    FF(C, D, A, B, x[6], 17, T[6]);
    FF(B, C, D, A, x[7], 22, T[7]);

    FF(A, B, C, D, x[8], 7, T[8]);
    FF(D, A, B, C, x[9], 12, T[9]);
    FF(C, D, A, B, x[10], 17, T[10]);
    FF(B, C, D, A, x[11], 22, T[11]);

    FF(A, B, C, D, x[12], 7, T[12]);
    FF(D, A, B, C, x[13], 12, T[13]);
    FF(C, D, A, B, x[14], 17, T[14]);
    FF(B, C, D, A, x[15], 22, T[15]);

    // Round 2 -- GG
    GG(A, B, C, D, x[1], 5, T[16]);
    GG(D, A, B, C, x[6], 9, T[17]);
    GG(C, D, A, B, x[11], 14, T[18]);
    GG(B, C, D, A, x[0], 20, T[19]);

    GG(A, B, C, D, x[5], 5, T[20]);
    GG(D, A, B, C, x[10], 9, T[21]);
    GG(C, D, A, B, x[15], 14, T[22]);
    GG(B, C, D, A, x[4], 20, T[23]);

    GG(A, B, C, D, x[9], 5, T[24]);
    GG(D, A, B, C, x[14], 9, T[25]);
    GG(C, D, A, B, x[3], 14, T[26]);
    GG(B, C, D, A, x[8], 20, T[27]);

    GG(A, B, C, D, x[13], 5, T[28]);
    GG(D, A, B, C, x[2], 9, T[29]);
    GG(C, D, A, B, x[7], 14, T[30]);
    GG(B, C, D, A, x[12], 20, T[31]);

    // Round 3 -- HH
    HH(A, B, C, D, x[5], 4, T[32]);
    HH(A, B, C, D, x[8], 11, T[33]);
    HH(A, B, C, D, x[11], 16, T[34]);
    HH(A, B, C, D, x[14], 23, T[35]);

    HH(A, B, C, D, x[1], 4, T[36]);
    HH(A, B, C, D, x[4], 11, T[37]);
    HH(A, B, C, D, x[7], 16, T[38]);
    HH(A, B, C, D, x[10], 23, T[39]);

    HH(A, B, C, D, x[13], 4, T[40]);
    HH(A, B, C, D, x[0], 11, T[41]);
    HH(A, B, C, D, x[3], 16, T[42]);
    HH(A, B, C, D, x[6], 23, T[43]);

    HH(A, B, C, D, x[9], 4, T[44]);
    HH(A, B, C, D, x[12], 11, T[45]);
    HH(A, B, C, D, x[15], 16, T[46]);
    HH(A, B, C, D, x[2], 23, T[47]);

    // Round 4 -- II
    II(A, B, C, D, x[0], 6, T[48]);
    II(A, B, C, D, x[7], 10, T[49]);
    II(A, B, C, D, x[14], 15, T[50]);
    II(A, B, C, D, x[5], 21, T[51]);

    II(A, B, C, D, x[12], 6, T[52]);
    II(A, B, C, D, x[3], 10, T[53]);
    II(A, B, C, D, x[10], 15, T[54]);
    II(A, B, C, D, x[1], 21, T[55]);

    II(A, B, C, D, x[8], 6, T[56]);
    II(A, B, C, D, x[15], 10, T[57]);
    II(A, B, C, D, x[6], 15, T[58]);
    II(A, B, C, D, x[13], 21, T[59]);

    II(A, B, C, D, x[4], 6, T[60]);
    II(A, B, C, D, x[11], 10, T[61]);
    II(A, B, C, D, x[2], 15, T[62]);
    II(A, B, C, D, x[9], 21, T[63]);

    // Perform additions which incrememnt each of the four registers
    // Reference [4]
    Hash[0] += A;
    Hash[1] += B;
    Hash[2] += C;
    Hash[3] += D;
}

// nextblock -- next hashing block
// Read from infile, into M, keeping track of number of bits
// it has currently read.
int nextblock(BLOCK *M, FILE *infile, uint64_t *nobits, PADFLAG *status)
{
    int i;
    size_t nobytesread;

    switch (*status)
    {
    case FINISH:
        return 0;
    case PAD0:
        // We need an all-padding block without the 1 bit.
        for (int i = 0; i < 56; i++)
            M->eight[i] = 0x00;
        M->sixfour[7] = htobe64(*nobits);
        *status = FINISH;
        break;
    default:
        // Try to read 64 bytes from the file.
        nobytesread = fread(M->eight, 1, 64, infile);
        *nobits += (8ULL * ((uint64_t)nobytesread));

        if (nobytesread < 56)
        {
            // We can put all padding in this block.
            M->eight[nobytesread] = 0x80;
            for (i = nobytesread + 1; i < 56; i++)
                M->eight[i] = 0x00;
            M->sixfour[7] = htobe64(*nobits);
            *status = FINISH;
        }
        else if (nobytesread < 64)
        {
            // Otherwise we have read between 56 (incl) and 64 (excl) bytes.
            M->eight[nobytesread] = 0x80;
            for (int i = nobytesread + 1; i < 64; i++)
                M->eight[i] = 0x00;
            *status = PAD0;
        }
    }

    // Convert to host endianess, word-size-wise.
    for (i = 0; i < 16; i++)
        M->threetwo[i] = be32toh(M->threetwo[i]);

    return 1;
}

// Note: Line count: 30
void display_header()
{
    printf("\n------------------------------");
    // printf("\n|                         |\n");
    printf("\n|     MD5 Message Digest     |");
    printf("\n|         G00303598          |\n");
    printf("|                            |");
    printf("\n|       Morgan Reilly        |\n");
    // printf("\n                              \n");
    printf("------------------------------\n");
    printf("\n");
}

int main(int argc, char *argv[])
{
    // display_header();

    // Expect command line arg
    if (argc != 2)
    {
        printf("Error: expected single filename as argument\n");
        return 1;
    }

    FILE *infile = fopen(argv[1], "rb");
    // Error handling -- Can't open file
    if (!infile)
    {
        printf("Error: couldn't open file %s. \n", argv[1]);
        return 1;
    }

    // Initialise MD Buffer -- Reference [5]: 3.3 Step 3.
    uint32_t H[] = {0x01234567, 0x89abcdef, 0xfedcba98, 0x76543210};

    // nextblock params
    BLOCK M;
    uint64_t nobits = 0;
    PADFLAG status = READ;
    // Read through all of the padded message blocks.
    // When reading into the block -> Do in 8-bits
    while (nextblock(&M, infile, &nobits, &status))
    {
        // Calculate next Hash value of M, hash value of H
        // Passing as address
        // Using values in array --> Do in 32-bits
        nexthash(M.threetwo, H);
    }

    for (int i = 0; i < 8; i++)
        printf("%02" PRIx32 "", H[i]);
    printf("\n");

    fclose(infile);
    return 0;
}
