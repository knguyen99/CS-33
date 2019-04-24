/* 
 * CS:APP Data Lab 
 * 
 * <Khoi Nguyen, 804993073>
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

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
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
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
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

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
    //0 is the only value where the two's complement
    //is also 0. thus for all other numbers, either
    //x or the negated x will be negative. by using
    //or, x and twosComp will produce a negative number
    // shifting right by 31 gives the sign of the answer
    //and adding one adjusts to give true of false value
    int twosComp = ~x +1;
    return ((twosComp | x) >> 31) + 1;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
    // the idea is to break down x into parts and count the bits
    // mask1 is every other bit, mask2 is every 2 bits, and so on
    // with these masks, you break down x into intervals
    int mask1, mask2, mask3, mask4, mask5, sum;
    mask1 = 0x55 | (0x55 << 8);
    mask1 = mask1 | (mask1 << 16); // mask of 0101 0101 0101 0101 0101 0101 0101 0101
    mask2 = 0x33 | (0x33 << 8);
    mask2 = mask2 | (mask2 << 16); // mask of 0011 0011 0011 0011 0011 0011 0011 0011
    mask3 = 0xF | (0xF << 8);
    mask3 = mask3 | (mask3 << 16); // mask of 0000 1111 0000 1111 0000 1111 0000 1111
    mask4 = 0xFF | (0xFF << 16);// mask of 0000 0000 1111 1111 0000 0000 1111 1111
    mask5 = 0xFF | (0xFF << 8); // mask of 0000 0000 0000 0000 1111 1111 1111 1111
    sum = (x & mask1) + ((x>>1) & mask1);
    sum = (sum & mask2) + ((sum >> 2) & mask2);
    sum = (sum & mask3) + ((sum >> 4) & mask3);
    sum = (sum & mask4) + ((sum >> 8) & mask4);
    sum = (sum & mask5) + ((sum >> 16) & mask5);
    return sum;
}
/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
    //to get the bitOr, I realized that only two zeros
    //give a 0 value to return, thus you complement x and y
    //and 'and' them so that it returns which positions are
    //both 0 and represents as 1. You complement that number
    // and what is returned is all positions that did not
    //have both 0's in the position
  return ~(~x & ~y);
}
/*
 * bitRepeat - repeat x's low-order n bits until word is full.
 *   Can assume that 1 <= n <= 32.
 *   Examples: bitRepeat(1, 1) = -1
 *             bitRepeat(7, 4) = 0x77777777
 *             bitRepeat(0x13f, 8) = 0x3f3f3f3f
 *             bitRepeat(0xfffe02, 9) = 0x10080402
 *             bitRepeat(-559038737, 31) = -559038737
 *             bitRepeat(-559038737, 32) = -559038737
 *   Legal ops: int and unsigned ! ~ & ^ | + - * / % << >>
 *             (This is more general than the usual integer coding rules.)
 *   Max ops: 40
 *   Rating: 4
 */
int bitRepeat(int x, int n) {
    int mask = ~(-1 << (n%32)) | ~((n/32) -1); // mask of 1's in lower bits and 0 in higher bits
    int lowerbits = mask & x;
    int shiftPossible = !(n/32); //1 <= n <= 31, then a repeat is possible, creates mask of 1111 if shift is possible
    int toreturn = lowerbits | ((lowerbits << n)*shiftPossible);
    shiftPossible = !(n/16); //if n < 16, then need to copy and shift again
    toreturn = toreturn | ((toreturn << n*2)*shiftPossible);
    shiftPossible = !(n/8); //if n < 8, then need to copy and shift again
    toreturn = toreturn | ((toreturn << n*4)*shiftPossible);
    shiftPossible = !(n/4); //if n < 4, then need to copy and shift again
    toreturn = toreturn | ((toreturn << n*8)*shiftPossible);
    shiftPossible = !(n/2); //if n < 2, then need to copy and shift again
    return toreturn | ((toreturn << n*16)*shiftPossible);
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
    //if we shift x by 32-n and shift it back
    //then the two numbers should be exactly the
    // same, otherwise it does not fit in the bits
    //by shifting, we clear higher order bits
    int xshift = (x << (33 + ~n))>> (33 + ~n);
    return !(x ^ xshift);
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
    // x is shifted by multiples of 8 since for every two numbers
    // in the hex number is a byte, thus that becomes a binary
    //number with 8 bits. The mask is 16, which is 1111 1111
    //so what is returned is the bytes after shifting accordingly
    int xshift = x >> (n<<3);
    return xshift & 0xFF;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    //if x and y have different signs and x is negative, then x is
    // automatically smaller than x. if x and y and the same sign
    // and y-x was nonnegative, then x is equal to or smaller than x
    int xydiffsign = ((x >> 31) & 0x1) ^ ((y >> 31) & 0x1); //0001 if different signs, 0000 if same signs
    int ysubxsign = ( (y + (~x + 1)) >> 31) & 1;
    return (xydiffsign & ((x>>31) & 0x1)) | (!xydiffsign & !ysubxsign);
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
    //because positive numbers have a 0 in the sign bit
    //we need to flip x so that positive numbers would have
    //a 1 as the sign bit. we check if it is zero, if it is zero
    //then the return should also be zero
    int notZero = !!(x & ~0);
    return (~x>>31) & notZero;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
    //the mask needed to be created is something with
    // 0's in the shifted positions, and 1's in the rest.
    // to make the mask, shift 1 by 31 to make INT_MIN
    // then right shift arithmetically by n to give amount
    //shifted, left shift by one because you had an extra 1
    // since only shifting 31. Complement the mask and & the
    // arithmetically shifted x and return
    int mask = ~(((0x1<<31) >> n)<< 1);
    return mask & (x>>n);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
    //shifts 1 by the int's size -1 (31 bits), to give 100.. or 0x80000000 which is int min
  return 0x1 << 31;
}
