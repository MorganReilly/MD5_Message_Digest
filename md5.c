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

// Symbols and Operations --> See Reference [6] Section 2.2.2

#include <stdio.h>
#include <stdint.h>

// Constants definition -- Based on MD4 -- ([1]Section 9.49)
const uint32_t IV[] = {0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476};

// Define constants -- ([1] Section 9.49)
uint32_t y[47];

// Function Declaration -- Reference [4]
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

int main(int argc, char *argv[])
{

    // // Define constants ? (Probably not the correct way..) -- ([1] Section 9.49)
    // // y[j] = 0, 0 <= j <= 15;
    // for (int j = 0; j <= 15; j++)
    // {
    //     printf("y[j]          = %08x\n", y[j]);
    //     y[j] = j;
    // };

    // // Define constants -- ([1] Section 9.49)
    // //
    // // for (int j=16; )

    printf("IV[2]         = %08x\n", IV[2]);

    return 0;
}
