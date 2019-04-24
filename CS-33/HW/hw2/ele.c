#define R 7
#define S 5
#define T 8

long A[R][S][T];

long
ele (long i, long j, long k)
{
  return A[R - i][1 - j][k - 1];
}
// 1) The expansion of the equation is
// for T D[A][B][C], the memory address is
// &D[i][j][k] = x + L((i*B+j)*C+k)
// where L is the size of type T

// 2) To get R, the first two insns show that 
// %rdi is the variable i, and rax contains 
// 7 stored in %eax. Thus the first two commands
// show that R = 7. The next two insns cause 
// %rax = 5(7-i)-j, this is equivalent to 
// (i*B+j) in the equation above, thus S = 5.
// The next instrucion causes 
// %rax = k + (5(7-i)-j)*8 + 7.
// the 8 is equivalent to the C in the equation
// above, thus T = 8.
