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

#### Notations
| Notation         | Meaning |
| ---------------- |:------------------------------------------------:|
| _u,v,w_          | 32-bit variables                                 |
| 0x67452301       | Hexidecimal 32-bit integer                       |
| +                | addition modulo 2^32                             |
| _!u_             | Bitwise complement                               |
| _u <- s_         | Result of rotating _u_ through _s_ positions     |
| _uv_             | Bitwise AND                                      |
| _u_ V _v_|       | Bitwise inclusive-OR                             |
| _u⊕v_            | Bitwise exclusive-OR                             |
| _f(u,v,w)_       | _uv_ V _!uw_                                     |
| _g(u,v,w)_       | _uv_ V _uw_ V _vw_                               |
| _h(u,v,w)_       | _u⊕v⊕w_                                          | 
| `(X1,...,Xj) <-` | Simultanious assignments `(Xi <- Yi)`            |
| `(Y1,...,Yj)`    | Where `(Y1,...,Yj)` evaluated before assignments |

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
* This application has 4 differnt run options
* Digest from String, run:
* `$ ./md5 -s"HelloWorld"`
* Display test suite, run:
* `$ ./md5 -t`
* Display test help, run:
* `$ ./md5 -h`
* Digest from file, run:
* `$ ./md5 <file_name>`


## Test
__Explain how to run the tests included in your code.__
* To test application, run:
* `$ ./md5 -t`
* This will display the test suite for digest comparision

#### Test Vectors
| Name | String                         | Hash Value                       |
| ---- |:------------------------------:|:--------------------------------:|
| MD5  | ""                             | d41d8cd98f00b204e9800998ecf8427e |
|      | "a"                            | 0cc175b9c0f1b6a831c399e269772661 |
|      | "abc"                          | 900150983cd24fb0d6963f7d28e17f72 |
|      | "abcdefghijklmnopqrstuvwxyz"   | c3fcd3d76192e4007dfb496cca67e13b |

## Algorithm
__Give an overview and explanation of the main algorithm(s)
in your code. You might use a well-thought out diagram here.__
Since the MD5 algorithm is based on the MD4 algorithm, I have decided to include both algorithms, describing the changes from MD4 to MD5. The following algorithms are adapted from chapter 9 of the [applied handbook of cryptography](http://cacr.uwaterloo.ca/hac/).

### MD4
The following instructions are based from chapter 9 of the [applied handbook of cryptography](http://cacr.uwaterloo.ca/hac/):
* INPUT: bitstring _x_ of arbirtary bitlength _b >= 0_
* OUTPUT: 128-bit hash-code of _x_
1. _Define Constants_ : Define four 32-bit initial chaining values: `h1 = 0x67452301, h2 = 0xefcdab89, h3 = 0x98badcfe, h4 = 0x10325476`
   1. Define 32-bit constants:
      * y[j] = 0, 0 <= j <= 15;
      * y[j] = 0x5a827999, 16 <= j <= 31;
      * y[j] = 0x6ed9eba1, 32 <= j <= 47;
   2. Define order of accessing source words
      * z[0..15] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
      * z[16..31] = [0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15]
      * z[32..47] = [0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15]
   3. Define number of bit positions for left shifts
      * s[0..15] = [3, 7, 11, 19, 3, 7, 11, 19, 3, 7, 11, 19, 3, 7, 11, 19]
      * s[16..31] = [3, 5, 9, 13, 3, 5, 9, 13, 3, 5, 9, 13, 3, 5, 9, 13]
      * s[32..47] = [3, 9, 11, 15, 3, 9, 11, 15, 3, 9, 11, 15, 3, 9, 11, 15]
2. _Preprocessing_ : Pad out _x_ so that the number of bits it contains is a multiple of 512. This is done by:
   1. Appending a single 1-bit
   2. Appending _r -1 (>= 0)_ 0-bits for the smallest _r_ which will result in a bitlength 64 less than a multiple of 512.
   3. Finally, append the 64-bit representation of _b mod 2^64_, as two 32-bit words in little-endien. Let _m_ be the number of 512-bit blocks in the string result. This formatted input will consist of 16_m_ 32-bit words. Initialise: `(H1, H2, H3, H4) <- (h1, h2, h3, h4)`
3. _Processing_ : For each _i_ from 0 to _m-1_ copy the _ith_ block of 16 32-bit words into a temporary store, then process them in three 16-step rounds before updating the chaining variables:
   1. Initialise working variables: `(A, B, C, D) <- (H1, H2, H3, H4)`
   2. Round 1: For _j_ 0 to 15 do: 
   `t <- (A + f(B,C,D) + X[z[j]] + y[j]),  (A, B, C, D) <- (D, t <- s[j], B, C)` 
   3. Round 2: For _j_ 16 to 31 do:
   `t <- (A + g(B,C,D) + X[z[j]] + y[j]),  (A, B, C, D) <- (D, t <- s[j], B, C)` 
   4. Round 3: For _j_ 32 to 47 do:
   `t <- (A + h(B,C,D) + X[z[j]] + y[j]),  (A, B, C, D) <- (D, t <- s[j], B, C)` 
   5. Update chaining values: `(H1, H2, H3, H4) <- (H1 + A, H2 + B, H3 + C, + H4 + D)`
4. Completion: The hashing is now complete and is the concatenation: `H1 || H2 || H3 || H4`

#### Differences between md4 and md5:
The MD5 was designed to be a strengthened version of the Message Digest 4 algorithm, but this was before any collisions were found in MD4. As per the Handbook of Applied Cryptography, the following changes from MD4 to MD5 were made:
1. An addition of a fourth round of 16 steps, along with a new Round 4 function
2. The replacement of the Round 2 function with a new function
3. The modification of the access order for the message words in Round 2 and Round 3
4. The modification of the shift amounts
5 . The use of unique additive constants in each of the 4 x 16 steps, which are based on the integer part of 2^32 x sin(j) for step j
6 . The addition of output form the previous step into each of the 64 steps

### MD5
* INPUT: bitstring _x_ of arbirtary bitlength _b >= 0_
* OUTPUT: 128-bit hash-code of _x_
_The following changes made to MD4 will result in MD5_
1. _Notation_ : Replace Round 2 function by: `g(u, v, w) = uw V !uw`
   1. Define a Round 4 function: `k(u, v, w) = v ⊕ (u V !w)`
2. _Constants Definition_
   1. Redefine unique additive constants:
      * _y[j]_ = first 32-bits binary value _abs( sin( j + 1 ))_, 0 <= _j_ <= 63
   2. Redefine access order for Round 2 and Round 3, also define Round 4
      * _z_[16..31] = [1, 6, 11, 0, 5, 10, 15, 4, 9, 14, 3, 8, 13, 2, 7, 12]
      * _z_[32..47] = [5, 8, 11, 14, 1, 4, 7, 10, 13, 0, 3, 6, 9, 12, 15, 2]
      * _z_[48..63] = [0, 7, 14, 5, 12, 3, 10, 1, 8, 15, 6, 13, 4, 11, 2, 9]
   3. Redefine number of bit positions for left shifts
      * _s_[0..15] = [7, 12, 17, 22, 7, 12, 7, 12, 17, 22, 7, 12, 17, 22,  7, 12, 17, 22]
      * _s_[16..31] = [5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20]
      * _s_[32..47] = [4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23]
      * _s_[48..63] = [6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21]
3. _Preprocessing_: Same as MD4
4. _Processing_: 
   1. In Rounds 1-3, replace `B <- (t <- s[j])` with `B <- B + ( t <- s[j])`
   2. Immediately after Round 3, add Round 4 transformation routine:
      1. `t <- ( A + k(B, C, D) + X[z[j]] + y[j], (A, B, C, D) <- (D, B + (t <- s[j]), B, C)`
5. _Completion_: MD5 is now compete, see MD4 for details  

## Complexity
__This should be the most significant part of the report.
You must give an analysis of the complexity of the MD5 algorithm,
including the complexity of algorithms that attempt to reverse the
algorithm. That is, algorithms that attempt to find an input for
which the MD5 algorithm produces a given output. You should
research this topic before writing this section and your analysis
should be carefully referenced.__

In terms of time complexity the MD5 algorithm performs in O(n) time and is quite fast, and in terms of design, uses the “trail-and-error” paradigm. 
However, a more comprehensive understanding of the hash function would be through understanding how various attack strategies work in relation to the hash functions.

When given a specific hash function, a desirable outcome is to prove a lower bound on the complexity of the attack in specific scenarios, with as few weak sets of assumptions as possible. This, however, is quite hard to do and the results are subsequently scarce. Typically it is better, in terms of security, for a hash function to look at the complexity of the applicable attack, which results in the upper bound on security. The storage complexity of the attack is something which should also be considered.

| Hash Type | Design Goal                | Ideal Strength         | Adversary's Goal              |
| --------- | -------------------------- |:----------------------:| ----------------------------- |
| OWHF      | Preimage Resistance;       | _2^n_                  | Produce Preimage;             |
|           | Second Preimage Resistance | _2^n_                  | Find Second input, same image |
| CRHF      | Collision Resistance       | _2^n/2_                | Produce any collision         |
| MAC       | Key Non-Recovery;          | _2^t_                  | Deduce MAC key;               |
|           | Computation Resistance     | _Pf = max(2^-t, 2^-n)_ | Produce new (msg, MAC)        |
_Design objectives for n-bit hash functions. Where Pt = Probabilty of forgery for correctly guessing a MAC. Adapted from section 9.3.4 [1](http://cacr.uwaterloo.ca/hac/)_

### Overview of Attacks
There are many various types of attacks which can be performed on hash algorithms. At a high level these are:
* Premiage Attacks: This is where you try to find the input which hashes to the already determined output.
* Second Permiage Attacks: These are similar to premiage attacks, but the attacker would have additional information about the message that will be hashed to the determined digest.
* Collision Attacks: This is where you try to find two messages which hash to the same digest. Once found, sign one message but pretend to sign the second. With this, collision attacks can be further broken down into 3 sub-categories:
   * Pseudo collisions: This is where the initial values differ, but the input message stays the same.
   * Collisions in compression function: This is where the initial values remain the same but the input message differ. However, the initial values cannot be selected.
   * Full collisions: This is similar to the collisions in compressions function, but the difference being that only the initial values can be selected.
* Birthday Attacks: These are brute force attacks against a one-way hash function.
* Differential Attacks: These work by checking if there is a change in input, and then producing an XOR difference in the chaining variables. If the XOR difference is set to zero at the end, the collision will be detected.
* One bit difference attack: This is where by you take two inputs in such way that all input words are the same bar one word with an XOR difference of 1-bit. Assume word[i] is included in the final round. It can be assumed that there is a collision if we get the same chaining variables at the final position since all input variables are the same.

### Attacks on bitsize of MDC
Given a fixed message _m_ with _n-bit_ hash _h(x)_, a simple method for checking input collision with _x_ is to pick a random bitstring _x1_ and just checking if _h(x) = h(x1)_. The cost of this is quite low, equating to the evaluation of one compression function, with a negligible memory cost. If it’s assumed that the hash-code approximates to a systematic random variable, the probability of a match is _2^-n_. 

When using basic hash attacks for a _n-bit_ hash function _h_, a guessing attack should find a preimage or second preimage within _2^n_ operations. If the attacker can choose the message(s), a birthday attack allows colliding pairs of messages _x,x1_ with _h(x) = h(x1)_ to be found in roughly _2^n/2_ operations, with quite a low memory cost. By this we find that that an _n-bit_ unkeyed hash function has an ideal security if 2 conditions are met:
1. Given hash output, production of a preimage and second preimage requires roughly _2^n_ operations.
2. Production of a collision requires roughly _2^n/2_ operations.


### Birthday Attacks
This is an algorithm independent attack, which means it can be applied to any hash function, where-by you treat the hash function as a black box whose only significant characteristic is the output it gives, which in the case of the MD4 and MD5, is the bitlength n, and the running time for one hash operation. In this case it is normally assumed that the hash output approximates to a uniform random variable.

#### Yuval's Birthday Attack
An algorithmic example of this would be Yuval’s birthday attack. This was one of the first of many applications, in a cryptographic sense, from the birthday paradox, which arose from the classical occupancy distribution. This means that when choosing elements in a random fashion, with replacement, from a set of _N_ elements, with high probability that a repeated element will be encountered after O(_√N_) selections (These are more commonly called _square-root attacks_). The relevance of this is that it is much easier to find collisions to a one-way hash function than it is when compared to collision detection for the likes of pre-images, second pre-images, or even for specific hash values. The result of this being that signature schemes which use a one-way hash function may be vulnerable to Yuvals attack. This attack can be applied to any unkeyed hash function with a running time of O(_2^m/2_) with a varying bitlength _m_ of the hash.

##### Algorithm
* INPUT: genuine message _x1_; fake message _x2_; _m-bit_ one-way hash function _h_.
* OUTPUT: The result of minor modifications of _x1_, _x2_ with _h(x1) = h(x2)_
1. Generate _t = 2^m/2_ minor modifications _x1_ of _x1_
2. Hash each modified message, then store the hash-values in a way where they can be searched by hash-value.
3. Generate minor modifications _x2_ of _x2_, computing _h(x2)_ for each, checking for matches with any _x1_,  continuing until a match is found.

#### Memory-less variation of Birthday Attack
If you remove the memory requirement of Yuvals birthday attack, a deterministic mapping could be used in lieu of the memory aspect which would approximate to a random walk through the hash-value space. For this we would expect to encounter a point a second time after O(2^m/2) steps, after which the walk will begin to cycle. To implement this, following the above algorithm, let _g(x1, H) = x1_ , which would be a minor modification, determined by the hash-value _H_ of message _x1_ . Should _x1_ be fixed, then _g_ should map to a hash-result of the message. This search technique is used to find two inputs to _r_ which should collide. If _h_ behaves in a random fashion, with a probability of 0.5, then the parity will be different in the output _H_ for the colliding input values.

### Chaining Attacks
Chaining attacks are based around the hash functions iterative nature, along with the use of chaining variables, with a focus on compression function _f_ rather than the overall hash function _h_ .
An example of this would be: If we consider an iterative hash function _h_ which produces a 128-bit hash-result, which is also collision resistant, with a compression function _f_ which takes its inputs as a 512-bit message block _xi_, along with a 128-bit chaining variable _Hi (H0 = IV)_ and producing output _Hi+1 = f(Hi, Xi)_. For a 10-block fixed message _x_ , let _H = h(x)_. If any of the blocks which affect _H_ are replaced with a different block, and if _h_ behaves like a random mapping, the number of 512-bit blocks should approximate to _ 2^512 / 2^128 = 2^384 _. Any method in which you would find any one of the 2^384 blocks which are distinct from the original block set would be considered an attack on _h_. The challenge with this is that the blocks are a sparse subset of the complete block set, which leaves a _1 in 2^128_ chance.

#### Meet in the Middle Chaining Attacks
These attacks are quite similar to Yuvals birthday attack, but have less collisions on intermediate result. They allow the finding of a message with a pre-specified hash on either a collision or a 2nd-preimiage attack. The point of attack is identified between the blocks of a fraudulent message. Variations of the blocks are generated at this point. The variations are hashed forward from the algorithm-specified IV, and backwards from the final target hash-result, seeking collisions at the attack point for variable _Hi_. The attacker must be able to traverse through the chain backwards for this attack to work properly.

#### Fixed Point Chaining Attack
A fixed point for a compression function is a pair _(Hi-1, xi)_ where by _f(Hi-1, xi) = Hi-1_. Based on this pair (message block, chaining value), the hash on a message isn’t changed upon the insertion of a capricious number of identical blocks _xi_ at the chaining point where the chaining value arises. These attacks are a concern if the chaining variable has a value where by the the fixed point in known. Fixed points can allow for collisions and 2nd-preimages to be produced; the inclusion of a trailing length block can counter this effect. 

#### Differential Chaining Attack
Differential chaining attacks prove to be quite a powerful tool for the cryptoanalysis of hash functions and block ciphers. For multi-round block ciphers this method examines XOR input differences to round functions and their corresponding differences in output, while searching for anomalies in the statistical information. For hash functions, it examines the input differences to compression functions along with the corresponding differences in output.

## References
_Provide a list of references used in your project. The
references should not just be a list of websites. Instead, there
should be a short explanation of why each reference is relevant to
your document._

1. [HandBook of Applied Cryptography, Chapter 9.49](http://cacr.uwaterloo.ca/hac/about/chap9.pdf)
   * I found this to be my go-to guide for both the SHA256 tutorial we were doing in class, and also for the MD5 project. It is a very comprehensive guide and allowed me to get an introduction to what cryptographic functions are, gave me a diagrammatic view of how the compression functions are applied and just was an overall great aid to the code, aiding in conceptualising the algorithm itself, and a massive help to the report, aiding in.  

2. [MD5 Diagram - Block Processing](https://www.iusmentis.com/technology/hashfunctions/md5/)
	* This was used to verify I had the correct inputs, to undertand how the table of constants were generated, to understand the auxialliary functions, and also has a nice diagram.

3. [MD5 Specification](http://practicalcryptography.com/hashes/md5-hash/)
   * This link was just as useful as The HandBook of Applied Cryptography, gave a nice understanding of how the algorithm worked and what was needed to make it work, but didn’t really explain much more apart from that.

4. [ietf MD5 Spec](https://www.ietf.org/rfc/rfc1321.txt)
   * This was the specification which was linked to the project. This was a great and invaluable source of information of which I would have been lost without. I have used this to adapt code from in various stages of the project.

5. [Bitwise Operations](https://www.geeksforgeeks.org/bitwise-operators-in-c-cpp/)
   * Great table and information on the bitwise opertations used in the projects and the tutorials

6. [MD4 code -- used for helping me understand the rounds](https://code.woboq.org/linux/linux/crypto/md4.c.html)
   * Code for the MD4 algorithm. This was useful when I just couldn’t get my head around how the rounds worked. I knew this wouldn’t give me the full answer but would give me an accurate enough result for me to base my understanding off of. (This was used before I saw that reference 4 actually contained the code for the MD5…)

7. [MD5 Algorithm Overview](http://www.herongyang.com/Cryptography/MD5-Message-Digest-Algorithm-Overview.html)
   * This was used to get an understanding of what was expected in the code without it being specifically written in C. This was great in that I could conceptualise the algorithm and see how the rounds worked without getting bogged down into the complexity of bits and bytes.

8. [Cryptographic Hashing Functions - MD5](https://cs.indstate.edu/~fsagar/doc/paper.pdf)
   * This was a nice paper on the MD5, not sure of the language, looks like python but mainly used it for the table generation which is on the top of page 5. Good explination of the algorithm and setup.

9. [Cryptoanalysis of MD4 and MD5](https://www.researchgate.net/publication/317096093_Cryptanalyzing_of_Message_Digest_Algorithms_MD4_and_MD5)
   * This paper was used to help get an understanding of the different types of attacks which can be performed on the MD4 and MD5 hashing algorithms