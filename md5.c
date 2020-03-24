// Morgan Reilly
// G00303598

// -- MD5 Message Digest Algorithm --

// References:
// [1] http://cacr.uwaterloo.ca/hac/about/chap9.pdf
// [2] https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf
// [3] https://www.iusmentis.com/technology/hashfunctions/md5/
// [4] http://practicalcryptography.com/hashes/md5-hash/
// [5] https://www.ietf.org/rfc/rfc1321.txt
// [6] https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf
// [7] https://www.geeksforgeeks.org/bitwise-operators-in-c-cpp/
// [8] https://www.cs.bu.edu/teaching/c/file-io/intro/ -- File IO
// About MD5:
// MD5 was designed as a strengthened version of MD4, prior to actual MD4 collisions being found.
// MD5 is obtained from MD4 by making modifications.
// These changes will be outlined in this project where implemented.
// MD5 operates on 32-bit words.

// Terminology -- Reference [5 (2)]:
// word: 32-bit quantity
// byte: 8-bit quantity
// x_i : x sub i

// Algorithm Steps (Overview) -- Reference [5 (3)]:
// Step 1: Append Padding Bits
// Step 2: Append Length
// Step 3:

// Symbols and Operations --> See Reference [6] Section 2.2.2

#pragma region IMPORTS
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h> // Includes formatters for printf
#pragma endregion

#pragma region PREPROCESSING SETUP
// Preprocessing
// Create union 512int blocks
union block {
    uint64_t sixfour[8];   // 64 * 8 = 512 -- 8 64bit intger array
    uint32_t threetwo[16]; // 32 * 16 = 512 -- 16 32bit integer array
    uint8_t eight[64];     // 8 * 64 = 512 -- 64 8bit integer array
};
#pragma endregion

#pragma region PARSE STATUS
// Represent current parse status
enum flag
{
    READ, // Not EOF -- Read OG file
    PAD0, // Pad with 0's
    FINISH
};
#pragma endregion

#pragma region CONSTANTS DECLARATION
// Constants definition -- Based on MD4 -- ([1]Section 9.49)
// Four word buffer --> A,B,C,D
const uint32_t IV[] = {0x67452301,  // A
                       0xefcdab89,  // B
                       0x98badcfe,  // C
                       0x10325476}; // D
#pragma endregion

#pragma region AUXILLARY FUNCTIONS
// -- Auxillary Functions --
// Input 3 32-bit words --> Produce as output one 32-bit word
// Function Declaratin -- Reference [4]
// F acts as conditional: if X then Y else Z
#define F(x,y,z) (((x) & (y)) | ((~x) & (z)))

//NOTE: G,H,I act in "bitwise parallel" to produce output from bits of X, Y, Z

// Function Declaration -- Reference [4]
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))

// Function Declaration -- Reference [4]
#define H(x, y, z) ((x) ^ (y) ^ (z))

// Function Declaration -- Reference [4]
#define I(x, y, z) ((y) ^ ((x) | (~z)))

// Function to rotate x left n bits
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

#pragma endregion

// Check number of zero bytes
uint64_t no_zero_bytes(uint64_t no_bits)
{
    uint64_t res = 512 - (no_bits % 512ULL);

    if (res < 65)
        res += 512;

    res -= 72;

    return (res / 8ULL);
}

// nextblock -- next hashing block
// Read from infile, into M, keeping track of number of bits
// it has currently read.
int nextblock(union block *M, FILE *infile, uint64_t *nobits, enum flag *status)
{
    // check current status
    if (*status == FINISH)
        return 0; // break out of while in main()

    // Check if block of zeros
    if (*status == PAD0)
    {
        for (int i = 0; i < 56; i++)
            M->eight[i] = 0;
        M->sixfour[7] = *nobits;
        *status = FINISH;
        return 1;
    }

    // Assume nobits set to 0 -- starts still by default
    size_t nobytesread = fread(M->eight, 1, 64, infile); // read into 8bit message block, 1byte, 64times, filehandler

    // Try to read 64 bytes from file
    if (nobytesread == 64)
        return 1;

    // Check now if there's enough room left in block to do all padding.
    // Need 8 bytes for 64 bit intger and a byte to stick 1 into.

    // Can still fit padding in last block, do:
    if (nobytesread < 56)
    {
        M->eight[nobytesread] = 0x80; // will be position of where to put 1 bit in byte
        for (int i = nobytesread + 1; i < 56; i++)
            M->eight[i] = 0;
        M->sixfour[7] = *nobits;
        *status = FINISH;
        return 1;
    }

    // Otherwise have read: >= 56 && < 64 bytes from file
    // Need to pad with 0's
    M->eight[nobytesread] = 0x80;
    for (int i = nobytesread + 1; i < 64; i++)
        M->eight[i] = 0;
    *status = PAD0;
    return 1;
}

// Next Hash
// Taking a block M, and calculating next block H
int nexthash(union block *M, uint32_t *H){
    // Section 3.4, reference[5]
    uint32_t W[64];
    uint32_t
}

// Check for command line input
void padd_from_file(char *fileName)
{
    FILE *inFile, *outFile;
    char *mode = "rb";
    char outputFileName[] = "outputPadding.txt";

    inFile = fopen(fileName, mode);

    // Error handling -- Can't open file
    if (inFile == NULL)
    {
        fprintf(stderr, "Can't open / missing input file!\n");
        exit(1);
    }

    outFile = fopen(outputFileName, "w");

    // Error handling -- can't open file
    if (outFile == NULL)
    {
        fprintf(stderr, "Can't open output file: %s\n", outputFileName);
        exit(1);
    }

    uint8_t b;
    // Keep track of all bits seen
    uint64_t noBits;

    // Try read file 1 byte at a time..
    // Read into b (& -> Address)
    // Read 1 byte, read 1 copy of bytes, from inFile
    for (noBits = 0; fread(&b, 1, 1, inFile) == 1; noBits += 8)
    {
        printf("%02" PRIx8, b);
        fprintf(outFile, "%02" PRIx8, b);
    }

    // TODO: Figure out what this is used for
    printf("%02" PRIx8, 0x80); // Bits: 1000 0000

    for (uint64_t i = (no_zero_bytes(noBits)); i > 0; i--)
    {
        printf("%02" PRIx8, 0x00); // Print value of 0x00
        // Append to file value of 0x00
        fprintf(outFile, "%02" PRIx8, 0x00);
    }

    printf("%016" PRIx64 "\n", noBits);
    fprintf(outFile, "%016" PRIx64 "\n", noBits);

    printf("\n");

    // Close files
    fclose(inFile);
    fclose(outFile);
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
    display_header();

    // Let M = Message to be hashed
    // M should be padded so that length = 448 % 512
    // Padded message should be 64 bits less than multiple of 512
    // Padding should be appended as 64 bit block

    // Let M = Message
    // Let N = number of 32-bit words in (padded) message

    // // Process each 16-word block
    // for (int i = 0; i <= 32 / 16 - 1; i++)
    // {
    //     // Copy block i into X
    //     for (int j = 0; j <= 15; j++)
    //     {
    //         uint32_t X = 0;
    //     }
    // }
    // char fileName[] = "./inputFile.txt";
    padd_from_file(argv[1]);

    // Read in padded string from file here ?

    uint32_t x = IV[0];
    uint32_t y = IV[1];
    uint32_t z = IV[2];

    printf("x  IV[0]            = %08x\n", IV[0]);
    printf("y  IV[1]            = %08x\n", IV[1]);
    printf("z  IV[2]            = %08x\n", IV[2]);

    printf("F(x,y,z)            = %08x\n", F(IV[0], IV[1], IV[2]));
    printf("G(x,y,z)            = %08x\n", G(IV[0], IV[1], IV[2]));
    printf("H(x,y,z)            = %08x\n", H(IV[0], IV[1], IV[2]));
    printf("I(x,y,z)            = %08x\n", I(IV[0], IV[1], IV[2]));

    return 0;
}
