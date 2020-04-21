# Overview

## Morgan Reilly | G00303598

## Introduction
_An introduction to your repository and code. Describe
what is contained in the repository and what the code does._

#### Introduction to Cryptograpic Hash Functions
Cryptographic hash functions play a largely fundamental role in day-to-day cryptography. These are often referred to simply as hash functions, and take a message as input and produce an output known as _hash-value_, _hash-code_, or just as _hash_. Hash functions are used for data integrity in tandem with digital signature schemes, which is hashed first, then the hash-value is signed in place of the original message. [[1]](http://cacr.uwaterloo.ca/hac/)

#### About MACs
Message Authentication Codes, which are a distinct class of hash functions, allow message authentication through symmetric techniques. These may be viewed as hash functions which take a message and a secret key, and produce a fixed size output. MACs are used to provide data integrity and symmetric data origin authentication.[[1]](http://cacr.uwaterloo.ca/hac/)

#### Hash Function Classes
Hash functions can be split into two classes: _unkeyed hash values_ and _keyed hash values_. An _unkeyed hash value_ dictates a single parameter input, usually called a message. Whereas a _keyed hash value_ dictates two input parameters, a message and a key. [[1]](http://cacr.uwaterloo.ca/hac/)

#### Definitions
The Definition of a hash function, according to the [handbook of applied cryptography Chapter](http://cacr.uwaterloo.ca/hac/)[9.1], is a function which has, as a minimum, the following two properties:
1. compression:
   _h_ maps an input _x_ of arbitrary finite bit length, to an output _h(x)_ of fixed bit length _n_.
2. ease of computation:
   given _h_ and an input _x_, _h(x)_ is easy to compute 
   
In more detail, a more functional classification of two types of hash functions exist. They are as follows:
1. modification detection codes (MDCs): These are also known as manipulation detection codes. The purpose of these are to provide a representative hash of a message. They fall into two categories:
i. one-way hash functions (OWHFs): These are largely difficult to find an input which hashes to a pre-specified hash value.
ii. collision resistant hash functions (CRHFs): These are difficult to find any two inputs which have the same hash-value.
2. message authentication codes (MACs): The purpose of these are to facilitate assurances in both source of a message, and its integrity. [[1]](http://cacr.uwaterloo.ca/hac/)

#### Basic Properties & Definitions
To expand further on the above definitions, as per chapter 9 of the handbook of applied cryptography, there are three properties listed for an unkeyed hash function _h_ with inputs _x_ , _x^1_ and outputs _y_, _y^1_, there are as follows:
1. preimage resistance: This is essentially for all pre-specified outputs, and is known to be computationally infeasible to find any input which hashes to that output
2. 2nd premiage resistance: This is computationally infeasible to find any second input which has the same output as any specific input
3. collision resistance: This is where it is computationally infeasible to find any two distinct inputs _x_, _x^1_ which hash out to the same output.

![hash classification](./images/ClassificationOfHash.png)

#### About MD4
MD4 was designed for software implementations on 32-bit machines. However, security concerns motivted the design of MD5, which is a more conservative version of MD4. Other versions include the SHA and RIPEMD implementations. The original MD4 (128-bit hash function) was designed in such a way that breaking it would require brute-force effort (2^64 operations) and finding a message yeilding a pre-specified hash-value (s^128 operations). MD4 was proven to never meet this goal. It serves, instead, as a convienient reference for describig and allowing coparisons between other hash functions in this family. Collisions have been found at 2^20 computations for MD4.

![md4 compression](./images/md4_compression.png)

#### About MD5
MD5 was designed as a strengthened version of MD4, prior to actual MD4 collisions being found. MD5 is obtained from MD4 by making 6 modifications. These are outline below in reference X. Currently there have been no collisions found on MD5.

![md5 compression](./images/md5_compression.png)

#### About this Repository
This repository contains the following:
* [.gitignore](./.gitignore) : This file allows git to ignore any files that are not meant to be in version control
* [LICENCE](./LICENCE)
* [README.md](./README.md) : This is a brief overview of the project, and instructions to run.
* [global.h](./global.h) : This is a header file which pre-defines global data types for use in the main file, which could be used more abstractly.
* [md5.c](./md5.c) : This is the main runner file which contains the MD5 C compiled code
* [md5.h](./md5.h) : This is a header file which pre-defines data types for specific use with the main runner file (md5.c).
* [overview.md](./overview.md) : This report on the project. 

#### About the Code
The code is written in C, and is separated out into 3 components:
1. [md5.c](./md5.c)
2. [md5.h](./md5.h)
3. [global.h](./global.h)
An overview of the purpose of these components are outlined in the section above this.
The code itself allows the user to choose via command line if they would like to input a string or a file to generate an MD5 hash. This is done by breaking the input message into blocks, padding where necessary, then applying the hashing function and returning the message.

## Run
__You should explain how to download, compile, and run your code.
Include instructions of how to install the compiler.__

#### Download Application
* Ensure you have git installed on machine
* To Download application, run:
* `$ git clone https://github.com/MorganReilly/MD5_Message_Digest.git `

#### Compile Application
* Ensure you have gcc installed on machine
* To Compile program, run: 
* `$ make md5`

#### Run Application
* To Run program, run:
* `$ ./md5`
* Select an option from in menu display
* `$ <option>`

## Test
__Explain how to run the tests included in your code.__
* To test application, run option: `x`

## Algorithm
__Give an overview and explanation of the main algorithm(s)
in your code. You might use a well-thought out diagram here.__
Since the MD5 algorithm is based on the MD4 algorithm, I have decided to include both algorithms, describing the changes from MD4 to MD5. The following algorithms are adapted from chapter 9 of the [applied handbook of cryptography](http://cacr.uwaterloo.ca/hac/).

### MD4
The following instructions are based from chapter 9 of the handbook of applied cryptography:
* INPUT: bitstring _x_ of arbirtary bitlength _b_ $\ge$ 0
* OUTPUT: 128-bit hash-code of _x_
1. _Define Constants_ : Define four 32-bit initial chaining values: _h1_ = 0x67452301, _h2_ = 0xefcdab89, _h3_ = 0x98badcfe, _h4_ = 0x10325476
i. Define 32-bit constants:
y[j] = 0, 0 <= j <= 15;
y[j] = 0x5a827999, 16 <= j <= 31;
y[j] = 0x6ed9eba1, 32 <= j <= 47;
ii. Define order of accessing source words
z[0..15] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15],
z[16..31] = [0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15],
z[32..47] = [0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15]
iii. Define number of bit positions for left shifts
s[0..15] = [3, 7, 11, 19, 3, 7, 11, 19, 3, 7, 11, 19, 3, 7, 11, 19],
s[16..31] = [3, 5, 9, 13, 3, 5, 9, 13, 3, 5, 9, 13, 3, 5, 9, 13],
s[32..47] = [3, 9, 11, 15, 3, 9, 11, 15, 3, 9, 11, 15, 3, 9, 11, 15]
2. _Preprocessing_ : Pad out _x_ so that the number of bits it contains is a multiple of 512. This is done by:
i. Appending a single 1-bit
ii. Appending _r_ -1 (>= 0) 0-bits for the smallest _r_ which will result in a bitlength 64 less than a multiple of 512.
iii. Finally, append the 64-bit representation of _b_ mod 2^64, as two 32-bit words in little-endien. Let _m_ be the number of 512-bit blocks in the string result. This formatted input will consist of 16_m_ 32-bit words. Initialise: (_H1_, _H2_, _H3_, _H4_) <- (_h1_, _h2_, _h3_, _h4_)
3. _Processing_ : For each _i_ from 0 to _m_ -1, copy the _i_th block of 16 32-bit words into a temporary store, then process them in three 16-step rounds before updating the chaining variables:
i. Initialise working variables: (_A_, _B_, _C_, _D_) <- (_H1_, _H2_, _H3_, _H4_)
ii. Round 1: For _j_ 0 to 15 do: 
_t_ <- (A + f(B,C,D) + X[z[j]] + y[j]),  (_A_, _B_, _C_, _D_) <- (D, t <- s[j], B, C) 
iii. Round 2: For _j_ 16 to 31 do:
_t_ <- (A + g(B,C,D) + X[z[j]] + y[j]),  (_A_, _B_, _C_, _D_) <- (D, t <- s[j], B, C) 
iv. Round 3: For _j_ 32 to 47 do:
_t_ <- (A + h(B,C,D) + X[z[j]] + y[j]),  (_A_, _B_, _C_, _D_) <- (D, t <- s[j], B, C) 
v. Update chaining values: (_H1_, _H2_, _H3_, _H4_) <- (_H1_ + _A_, _H2_ + _B_, _H3_ + _C_, + _H4_ + _D_)
4. Completion: The hashing is now complete and is the concatenation: _H1_||_H2_||_H3_||_H4_

Differences between md4 and md5:
The MD5 was designed to be a strengthened version of the Message Digest 4 algorithm, but this was before any collisions were found in MD4. As per the Handbook of Applied Cryptography, the following changes from MD4 to MD5 were made:
1. An addition of a fourth round of 16 steps, along with a new Round 4 function
2. The replacement of the Round 2 function with a new function
3. The modification of the access order for the message words in Round 2 and Round 3
4. The modification of the shift amounts
5 . The use of unique additive constants in each of the 4 x 16 steps, which are based on the integer part of 2^32 x sin(j) for step j
6 . The addition of output form the previous step into each of the 64 steps

## Complexity
__This should be the most significant part of the report.
You must give an analysis of the complexity of the MD5 algorithm,
including the complexity of algorithms that attempt to reverse the
algorithm. That is, algorithms that attempt to find an input for
which the MD5 algorithm produces a given output. You should
research this topic before writing this section and your analysis
should be carefully referenced.__

## References
__Provide a list of references used in your project. The
references should not just be a list of websites. Instead, there
should be a short explanation of why each reference is relevant to
your document.__
