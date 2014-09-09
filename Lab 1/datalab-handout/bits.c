/* 
 * CS:APP Data Lab 
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#include "btest.h"
#include <limits.h>

/*
 * Instructions to Students:
 *
 * STEP 1: Fill in the following struct with your identifying info.
 */
team_struct team =
{
   /* Team name: Replace with either:
      Your login ID if working as a one person team
      or, ID1+ID2 where ID1 is the login ID of the first team member
      and ID2 is the login ID of the second team member */

    "A01625825+A01393116",  //I'm assuming A#'s are ID's

   /* Student name 1: Replace with the full name of first team member */
   "David Petrizze",
   /* Login ID 1: Replace with the login ID of first team member */
   "A01625825",

   /* The following should only be changed if there are two team members */
   /* Student name 2: Full name of the second team member */
   "Cody Herndon",
   /* Login ID 2: Login ID of the second team member */
   "A01393116"
};

#if 0
/*
 * STEP 2: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.
#endif
/*
 * STEP 3: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the btest test harness to check that your solutions produce 
 *      the correct answers. Watch out for corner cases around Tmin and Tmax.
 */
/* 
 * bitNor - ~(x|y) using only ~ and & 
 *   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitNor(int x, int y) {
       //uses De Morgan's law:
       //~(x|y) == (~x) & (~y)
       int var1 = ~x;
       int var2 = ~y;
       return var1 & var2;

}

/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 2
 */
int bitXor(int x, int y) {

	//heh, there's a circuit for this
	return ~(~(~(x & y) & y) & ~(~(x & y) & x));
}
/* 
 * isNotEqual - return 0 if x == y, and 1 otherwise 
 *   Examples: isNotEqual(5,5) = 0, isNotEqual(4,5) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNotEqual(int x, int y) {
  //the xor will result in 0 for equivalence, and nonzero for inequality
  //normalize the results with logical nots.
  int var1 = !(x^y);
  return !var1;

}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {

	//Right shift and mask

	int nbits = n << 3;

	return 0xFF & (x >> nbits);
}
/* 
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int copyLSB(int x) {
  //uses arithmetic or "sticky" shift to copy MSb into all positions
  int var1 = x << 31; //make LSb into MSb
  return (var1 >> 31); //right shift copies MSb to all positions 

}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 1 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3 
 */
int logicalShift(int x, int n) {

	//If the number is negative
	int highbit = (x >> 31) & 0x1;

	//arithmetic shift
	x = x >> n;

	//duplicate the high bit into the upper n - 1 bits (using arithmetic shift)
	int topbits = ((highbit << 31) >> n) << 1;

	x = x ^ topbits; //Invert where this is one, a.k.a. invert the copied "sign" bits

	return x;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  //uses the Hamming weight function to calculate the
  //number of nonzero states in an int

  //setup masks
  int var1 = 0x55 | 0x55 << 8;
  int var2 = var1 | var1 << 16; //mask 1
  
  int var3 = 0x33 | 0x33 << 8;
  int var4 = var3 | var3 << 16; //mask 2

  int var5 = 0x0F | 0x0F << 8;
  int var6 = var5 | var5 << 16; //mask 3

  int var7 = 0xFF | 0xFF << 16; //mask 4

  int var8 = 0xFF | 0xFF << 8; //mask 5

  int var9 = (x & var2) + ((x >> 1) & var2);
  int var10 = (var9 & var4) + ((var9 >> 2) & var4);
  int var11 = (var10 & var6) + ((var10 >> 4) & var6);
  int var12 = (var11 & var7) + ((var11 >> 8) & var7);
  int var13 = (var12 & var8) + ((var12 >> 16) & var8);

  return var13;

}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {

	int negx = ~x + 1;

	int hibit = (x >> 31) & 0x1;
	int neghibit = (negx >> 31) & 0x1;

	return ~(hibit | neghibit) & 0x1;
}
/* 
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 4 
 */
int leastBitPos(int x) {
  //~0010->1101
  //1101+1->1110
  //1110&0010->0010
  int var1 = ~x;
  int var2 = var1 + 1;
  return var2 & x;

}
/* 
 * TMax - return maximum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmax(void) {
  //places 1 in MSb, and does a bitwise not defines the positive max of an int
  int var1=0x1;
  int var2 = var1 << 31; //place 1 in MSb
  return ~var2; //bitwise not
}
/* 
 * isNonNegative - return 1 if x >= 0, return 0 otherwise 
 *   Example: isNonNegative(-1) = 0.  isNonNegative(0) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int isNonNegative(int x) {
  return !(x >> 31);
}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
  //if x == y (== 0), then x^y == 0
  //if -x and y (== 0), then !x[31] & y[31] == 0
  //if x and -y (== 1), then x[31] & !y[31] == 1
  //if x and y (== ?)
  //  if x>y (== 1), then ((~x + y))[31] = 1 (x should be more negative by at least one if its greater)
  
  int var1 = x^y; //test raw inequality
  int var2 = x >> 31; //x MSb mask
  int var3 = y >> 31; //y MSb mask
  
  int var4 = !var2;
  int var5 = var4 & var3; //if x > 0 && y < 0 <= 1

  int var6 = ~x;
  int var7 = var6 + y;
  int var8 = var7 >> 31; //if x>y, (~x+y)[31] == 1

  int var9 = var2 ^ var3;
  int var10 = !var9;
  int var11 = var8 & var10;
  int var12 = !var5;
  int var13 = var12 & var11;
  int var14 = var5 || var13;
  int var15 = var14 && var1;

  //int var12 = var1 && (var5 || (!var5 && var11));

  return var15;

}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {

	//Grab the high bit
	int highbit = (x >> 31) & 0x01;

	//If negative, take two's complement. Else invert.
	x = ~x + highbit;

	int toptop = ((x >> 31) & 0x01) & highbit;

	//Arithmetic shift right (duplicates msb bit, that's what we want)
	x = x >> n;

	//If negative, take two's complement. Else invert.
	x = ~x + highbit;


	//If toptop (special case of 0x80000000), perform twos complement again
	int allval = ((toptop << 31) >> 31);

	//printf("allval: %d\n", allval);

	x = ((x ^ allval) + toptop);

	return x;
}
/* 
 * abs - absolute value of x (except returns TMin for TMin)
 *   Example: abs(-1) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int abs(int x) {
  //use the MSb and arithmetic shift property to mask off the
  //incorrect return value
  int var1 = x >> 31;
  int var2 = var1 & (~x + 1); //negative value, if x is negative, mask is 0xF...F
  int var3 = ~var1 & (x); //positive value, if x is positive, mask is 0x0...0
  return var2 | var3;

}
/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {

	int signx = (x >> 31) & 0x01;
	int signy = (y >> 31) & 0x01;

	//Put the two signs into one number
	int signxy = signx | (signy << 1);

	//Perform the action
	int res = x + y;

	//Look at its sign
	int signres = (res >> 31) & 0x01;

	//Duplicate the bit
	signres |= (signres << 1);

	//Check if the xor'd value == 0b00.  This effectively checks whether 
	//the original x, y signs are the same, and if so, checks whether they 
	//changed after the operation.
	return !!((~(signxy ^ signres)) & 0x03);
}
