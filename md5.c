/* Morgan Reilly -- G00303598

-- MD5 Message Digest Algorithm --

References:
   [1] http://cacr.uwaterloo.ca/hac/about/chap9.pdf -- HandBook of Applied Cryptography, Chapter 9.49
   [2] https://www.iusmentis.com/technology/hashfunctions/md5/ -- MD5 Diagram (Block Processing)
   [3] http://practicalcryptography.com/hashes/md5-hash/ -- MD5 Specification
   [4] https://www.ietf.org/rfc/rfc1321.txt -- MD5 Specification
   [5] https://www.geeksforgeeks.org/bitwise-operators-in-c-cpp/ -- Bitwise Operations
   [6] https://code.woboq.org/linux/linux/crypto/md4.c.html -- MD4 code -- used for helping me understand the rounds
   [7] http://www.herongyang.com/Cryptography/MD5-Message-Digest-Algorithm-Overview.html
   [8] https://cs.indstate.edu/~fsagar/doc/paper.pdf

About MD5:
   MD5 was designed as a strengthened version of MD4, prior to actual MD4 collisions being found.
   MD5 is obtained from MD4 by making modifications.
   These changes will be outlined in this project where implemented.
   MD5 operates on 32-bit words.

Differences between signed and unsigned:
   Unsigned numbers can only have values of zero or greater.
*/
#include "md5.h"
#include <stdio.h>
#include <inttypes.h>
#include <endian.h>
#include <string.h>

/* Constants definition for Transformation routine
   R[4]: A.3 md5.c Page9
*/
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

/* Function Declaration
   These define the function type and parameters of the functions used below
   Adapted from: R[4]: A.3 md5.c Page9
*/
static void NextHash ARG_LIST((UINT4[4], unsigned char[64]));
static void Encode ARG_LIST((unsigned char *, UINT4 *, unsigned int));
static void Decode ARG_LIST((UINT4 *, unsigned char *, unsigned int));
static void MemoryCopy ARG_LIST((POINTER, POINTER, unsigned int));
static void MemorySet ARG_LIST((POINTER, int, unsigned int));
static void GenerateFromFile ARG_LIST((char *));
static void GenerateFromString ARG_LIST((char *));
static void PrintMessageDigest ARG_LIST((unsigned char[16]));
static void DisplayTestValues();
static void DisplayMenu();
static void DisplayOptions();

/* Padding Declaration
   R[4]: A.3 md5.c Page9
*/
static unsigned char PADDING[64] = {
    0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/* The Table - R[8]: 3.4.2 The Table
   Pregenerated by using sin function: abs(sin(i + 1)) × 2^32
*/
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

/* -- Auxillary Functions --
   Input 3 32-bit words --> Produce as output one 32-bit word
   F acts as conditional: if X then Y else Z
   G,H,I act in "bitwise parallel" to produce output from bits of X, Y, Z

   Function Declaratin -- R [3]: The Algorithm
   Also adapted from R[4]: A.3 md5.c (Page9, Page10)  
*/
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))
#define LSHIFT(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

/* Defining rounds
   Where:
   a,b,c,d --> Initial buffer values

   Adapted from R[4]: A.3 md5.c (Page9, Page10)  
*/
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

/* MD5 Initialisation
   This will begin a new MD5 operation, 
   with a new context to write to.
   Adapted from: R[4]: A.3 md5.c Page10
*/
void InitialiseMD5(context)
    CONTEXT *context; /* context */
{
    context->bit_count[0] = context->bit_count[1] = 0;
    /* Load magic initialization constants.*/
    context->word_state[0] = 0x67452301; /* A */
    context->word_state[1] = 0xefcdab89; /* B */
    context->word_state[2] = 0x98badcfe; /* C */
    context->word_state[3] = 0x10325476; /* D */
}

/* MD5 block update operation 
   This continues the existing md5 digest,
   processing block after block while updating the context
   Adapted from: R[4]: A.3 md5.c (Page10, Page11)
*/
void NextBlock(context, input, inputLength)
    CONTEXT *context;     /* context */
unsigned char *input;     /* input block */
unsigned int inputLength; /* length of input block */
{
    unsigned int i, index, partLen;

    /* Compute number of bytes mod 64 */
    index = (unsigned int)((context->bit_count[0] >> 3) & 0x3F);

    /* Update number of bits */

    if ((context->bit_count[0] += ((UINT4)inputLength << 3)) < ((UINT4)inputLength << 3))
        context->bit_count[1]++;
    context->bit_count[1] += ((UINT4)inputLength >> 29);

    partLen = 64 - index;

    // Transform as many times as possible
    if (inputLength >= partLen)
    {
        MemoryCopy((POINTER)&context->input_buffer[index], (POINTER)input, partLen);
        NextHash(context->word_state, context->input_buffer);

        for (i = partLen; i + 63 < inputLength; i += 64)
            NextHash(context->word_state, &input[i]);

        index = 0;
    }
    else
        i = 0;

    /* Buffer remaining input */
    MemoryCopy((POINTER)&context->input_buffer[index], (POINTER)&input[i],
               inputLength - i);
}

/* MD5 Generation
   Adapted from: R[4]: A.3 md5.c (Page11, Page12)
*/
void GenerateMD5(digest, context) unsigned char digest[16]; /* message digest */
CONTEXT *context;                                           /* context */
{
    unsigned char bits[8];
    unsigned int index, padLen;

    // Save number of bits
    Encode(bits, context->bit_count, 8);

    // Pad out to 56 mod 64.
    index = (unsigned int)((context->bit_count[0] >> 3) & 0x3f); // Set index
    padLen = (index < 56) ? (56 - index) : (120 - index);        // Set padding length
    NextBlock(context, PADDING, padLen);                         // Call update function

    // Append length (before padding)
    NextBlock(context, bits, 8);

    // Store state in digest
    Encode(digest, context->word_state, 16);

    // Zeroize sensitive information.
    MemorySet((POINTER)context, 0, sizeof(*context));
}

/* MD5 Transform Function
   Next Hash
   Taking a state, and calculating next block 
   R[4]: A.3 md5.c (Page12, Page13)
*/
static void NextHash(state, block)
    UINT4 state[4];
unsigned char block[64];
{
    UINT4 a = state[0], b = state[1], c = state[2], d = state[3], x[16];

    /* TODO: This needs to be change to little endian here, currently in big endian */
    Decode(x, block, 64);

    /* Round Declaration 
       Adapted from R[4]: A.3 md5.c (Page12, Page13)
    */
    // Round 1 -- FF
    FF(a, b, c, d, x[0], S11, T[0]);
    FF(d, a, b, c, x[1], S12, T[1]);
    FF(c, d, a, b, x[2], S13, T[2]);
    FF(b, c, d, a, x[3], S14, T[3]);
    FF(a, b, c, d, x[4], S11, T[4]);
    FF(d, a, b, c, x[5], S12, T[5]);
    FF(c, d, a, b, x[6], S13, T[6]);
    FF(b, c, d, a, x[7], S14, T[7]);
    FF(a, b, c, d, x[8], S11, T[8]);
    FF(d, a, b, c, x[9], S12, T[9]);
    FF(c, d, a, b, x[10], S13, T[10]);
    FF(b, c, d, a, x[11], S14, T[11]);
    FF(a, b, c, d, x[12], S11, T[12]);
    FF(d, a, b, c, x[13], S12, T[13]);
    FF(c, d, a, b, x[14], S13, T[14]);
    FF(b, c, d, a, x[15], S14, T[15]);
    // Round 2 -- G
    GG(a, b, c, d, x[1], S21, T[16]);
    GG(d, a, b, c, x[6], S22, T[17]);
    GG(c, d, a, b, x[11], S23, T[18]);
    GG(b, c, d, a, x[0], S24, T[19]);
    GG(a, b, c, d, x[5], S21, T[20]);
    GG(d, a, b, c, x[10], S22, T[21]);
    GG(c, d, a, b, x[15], S23, T[22]);
    GG(b, c, d, a, x[4], S24, T[23]);
    GG(a, b, c, d, x[9], S21, T[24]);
    GG(d, a, b, c, x[14], S22, T[25]);
    GG(c, d, a, b, x[3], S23, T[26]);
    GG(b, c, d, a, x[8], S24, T[27]);
    GG(a, b, c, d, x[13], S21, T[28]);
    GG(d, a, b, c, x[2], S22, T[29]);
    GG(c, d, a, b, x[7], S23, T[30]);
    GG(b, c, d, a, x[12], S24, T[31]);
    // Round 3 -- H
    HH(a, b, c, d, x[5], S31, T[32]);
    HH(d, a, b, c, x[8], S32, T[33]);
    HH(c, d, a, b, x[11], S33, T[34]);
    HH(b, c, d, a, x[14], S34, T[35]);
    HH(a, b, c, d, x[1], S31, T[36]);
    HH(d, a, b, c, x[4], S32, T[37]);
    HH(c, d, a, b, x[7], S33, T[38]);
    HH(b, c, d, a, x[10], S34, T[39]);
    HH(a, b, c, d, x[13], S31, T[40]);
    HH(d, a, b, c, x[0], S32, T[41]);
    HH(c, d, a, b, x[3], S33, T[42]);
    HH(b, c, d, a, x[6], S34, T[43]);
    HH(a, b, c, d, x[9], S31, T[44]);
    HH(d, a, b, c, x[12], S32, T[45]);
    HH(c, d, a, b, x[15], S33, T[46]);
    HH(b, c, d, a, x[2], S34, T[47]);
    // Round 4 -- I
    II(a, b, c, d, x[0], S41, T[48]);
    II(d, a, b, c, x[7], S42, T[49]);
    II(c, d, a, b, x[14], S43, T[50]);
    II(b, c, d, a, x[5], S44, T[51]);
    II(a, b, c, d, x[12], S41, T[52]);
    II(d, a, b, c, x[3], S42, T[53]);
    II(c, d, a, b, x[10], S43, T[54]);
    II(b, c, d, a, x[1], S44, T[55]);
    II(a, b, c, d, x[8], S41, T[56]);
    II(d, a, b, c, x[15], S42, T[57]);
    II(c, d, a, b, x[6], S43, T[58]);
    II(b, c, d, a, x[13], S44, T[59]);
    II(a, b, c, d, x[4], S41, T[60]);
    II(d, a, b, c, x[11], S42, T[61]);
    II(c, d, a, b, x[2], S43, T[62]);
    II(b, c, d, a, x[9], S44, T[63]);

    /* Perform additions which incrememnt each of the four registers */
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;

    // Zeroise sensitive information
    MemorySet((POINTER)x, 0, sizeof(x));
}

/* Encode the input into output (UINT4  --> unsigned char) 
   Done by assuming length is a multiple of 4
   R[4]: A.3 md5.c Page14
*/
static void Encode(output, input, len) unsigned char *output;
UINT4 *input;
unsigned int len;
{
    unsigned int i, j;

    for (i = 0, j = 0; j < len; i++, j += 4)
    {
        output[j] = (unsigned char)(input[i] & 0xff);
        output[j + 1] = (unsigned char)((input[i] >> 8) & 0xff);
        output[j + 2] = (unsigned char)((input[i] >> 16) & 0xff);
        output[j + 3] = (unsigned char)((input[i] >> 24) & 0xff);
    }
}

/* Decode input into output (unsigned char --> UINT4)
   Done by assuming length is a multiple of 4

   This needs to be set to little endian, output is incorrect
   R[4]: A.3 md5.c Page14
*/
static void Decode(output, input, length)
    UINT4 *output;
unsigned char *input;
unsigned int length;
{
    unsigned int i, j;

    for (i = 0, j = 0; j < length; i++, j += 4)
        output[i] = ((UINT4)input[j]) | (((UINT4)input[j + 1]) << 8) |
                    (((UINT4)input[j + 2]) << 16) | (((UINT4)input[j + 3]) << 24);
}

/* Memory Copy
   R[4]: A.3 md5.c Page14
*/
static void MemoryCopy(output, input, length)
    POINTER output;
POINTER input;
unsigned int length;
{
    memcpy(output, input, length);
}

/* Memory Set
   R[4]: A.3 md5.c Page15
*/
static void MemorySet(output, value, len)
    POINTER output;
int value;
unsigned int len;
{
    memcpy((char *)output, &value, len);
}

/* Display Test Values
   R[1]: 9.4.2 Table 9.6
*/
static void DisplayTestValues()
{
    printf("MD5 Test Values\n");
    printf("\"\"                           ->   d41d8cd98f00b204e9800998ecf8427e\n");
    printf("a                            ->   0cc175b9c0f1b6a831c399e269772661\n");
    printf("abc                          ->   900150983cd24fb0d6963f7d28e17f72\n");
    printf("abcdefghijklmnopqrstuvwxyz   ->   900150983cd24fb0d6963f7d28e17f72\n");
    printf("\n");
}

/* Calculate From File
   R[4]: A.4 mddriver.c Page19
*/
static void GenerateFromFile(filename) char *filename;
{
    FILE *file;
    CONTEXT context;
    int len;
    unsigned char buffer[1024], digest[16];

    // Check for null file
    if ((file = fopen(filename, "rb")) == NULL)
        printf("%s can't be opened\n", filename);
    else
    {
        /* Initialise New Context */
        InitialiseMD5(&context);
        /* While not eof, call update function */
        while (len = fread(buffer, 1, 1024, file))
            NextBlock(&context, buffer, len);
        /* Generate MD5 Message Digest */
        GenerateMD5(digest, &context);

        fclose(file);

        printf("(%s) = ", filename);
        PrintMessageDigest(digest);
        printf("\n");
    }
}

/* Calculate From Console 
   R[4]: A.4 mddriver.c Page17
*/
static void GenerateFromString(input) char *input;
{
    CONTEXT context;
    unsigned char messagedigest[16];
    unsigned int length = strlen(input);

    InitialiseMD5(&context);
    NextBlock(&context, input, length);
    GenerateMD5(messagedigest, &context);

    printf("(%s) = ", input);
    PrintMessageDigest(messagedigest);
    printf("\n");
}

/* Print Generated MD5 digest
   R[4]: A.4 mddriver.c (Page19, Page20)
*/
static void PrintMessageDigest(digest) unsigned char digest[16];
{
    for (unsigned int i = 0; i < 16; i++)
        printf("%02x", digest[i]);
}

static void DisplayOptions()
{
    printf("MD5 Hash Generator\n");
    printf("Options List\n 1:   Generate From File\n 2:   Generate From String\n 3:   Display Test Values\n-1:   Quit\n");
}

static void DisplayMenu()
{
    int choice;

    DisplayOptions();
    /* Initial Read for while */
    printf("Please enter an option: ");
    scanf("%d", &choice);
    printf("\n");
    while (choice != -1)
    {
        char *input;
        char *mode = "r";

        /* Read from file */
        if (choice == 1)
        {
            // Select file
            printf("Please enter a file: ");
            scanf("%s", input);
            GenerateFromFile(input);
            printf("\n");
        }

        /* Read from console */
        if (choice == 2)
        {
            // Select file
            printf("Please enter text to hash: ");
            scanf("%s", input);
            GenerateFromString(input);
            printf("\n");
        }

        /* Display test values */
        if (choice == 3)
        {
            DisplayTestValues();
            printf("\n");
        }

        DisplayOptions();
        /* Subsequent Read for while */
        printf("Please enter an option: ");
        scanf("%d", &choice);
        printf("\n");
    }
}

/* Main */
int main(int argc, char *argv[])
{
    DisplayMenu();
    // GenerateFromFile(argv[1]);
    return 0;
}
