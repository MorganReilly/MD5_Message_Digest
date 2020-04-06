/* Morgan Reilly G00303598

-- MD5 Message Digest Algorithm --
-- Global Header --
Adapted from: https://www.ietf.org/rfc/rfc1321.txt

Section A.1 global.h
Set PROTOTYPES to be one, only if the compiler supports function argument prototyping
*/
#ifndef PROTOTYPES
#define PROTOTYPES 0
#endif

/* POINTER defines a generic pointer type */
typedef unsigned char *POINTER;

/* UINT2 defines a two byte word */
typedef unsigned short int UINT2;

/* UINT4 defines a four byte word */
typedef unsigned long int UINT4;

/* PROTO_LIST is defined depending on how PROTOTYPES is defined above.
If using PROTOTYPES, then PROTO_LIST returns the list, otherwise it
  returns an empty list.
 */
#if PROTOTYPES
#define PROTO_LIST(list) list
#else
#define PROTO_LIST(list) ()
#endif 