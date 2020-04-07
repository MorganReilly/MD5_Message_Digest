/* Morgan Reilly G00303598

-- MD5 Message Digest Algorithm --
-- Global Header --
Adapted from: https://www.ietf.org/rfc/rfc1321.txt

Section A.1 global.h
Set ARGTYPES to be one, only if the compiler supports function argument
*/
#ifndef ARGTYPES   /*Define directive if conditions met */
#define ARGTYPES 0 /*Set directive value */
#endif

/* POINTER defines a generic pointer type */
typedef unsigned char *POINTER;

/* UINT4 defines a four byte word */
typedef unsigned long int UINT4;

/* ARG_LIST is defined depending on how PROTOTYPES is defined above.
If using PROTOTYPES, then ARG_LIST returns the list, otherwise it
  returns an empty list.
 */
#if ARGTYPES
#define ARG_LIST(list) list
#else
#define ARG_LIST(list) ()
#endif