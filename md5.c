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

// Symbols and Operations --> See Reference [6] Section 2.2.2

#include <stdio.h>
#include <stdint.h>

// Constants definition -- Based on MD4 -- ([1]Section 9.49)
// Four word buffer --> A,B,C,D
const uint32_t IV[] = {0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476};

// -- Auxillary Functions --
// Input 3 32-bit words --> Produce as output one 32-bit word

// Function Declaratin -- Reference [4]
uint32_t F(uint32_t x, uint32_t y, uint32_t z)
{
    return (x & y) | (~x & z);
}

// Function Declaration -- Reference [4]
uint32_t G(uint32_t x, uint32_t y, uint32_t z)
{
    return (x & y) | (y & ~z);
}

// Function Declaration -- Reference [4]
uint32_t H(uint32_t x, uint32_t y, uint32_t z)
{
    return (x ^ y ^ z);
}

// Function Declaration -- Reference [4]
uint32_t I(uint32_t x, uint32_t y, uint32_t z)
{
    return (y ^ (x | ~z));
}

void display_header()
{
    printf("\n");
    printf("\n------------------------------\n");
    // printf("\n|                         |\n");
    printf("\n|     MD5 Message Digest     |");
    printf("\n|         G00303598          |\n");
    printf("|                            |");
    printf("\n|       Morgan Reilly        |\n");
    // printf("\n                              \n");
    printf("\n------------------------------\n");
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
