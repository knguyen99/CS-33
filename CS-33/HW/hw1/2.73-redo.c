#include <limits.h>
#include <stdio.h>

/*Addition that saturates to TMin or TMax */

int saturating_add(int x, int y){

  int sum = x+y;
  //provided by instructor                                                                                                 
  int overflow = __builtin_add_overflow_p (x, y, (__typeof__ ((x) + (y))) 0);

  // create a mask to check the sign of sum                                                                                
  int mask = (-1) << ((sizeof(int)*8)-1);

  //check sign of x                                                                                                         
  int xsign = x & mask; //x is 1000 if negative, 0000 if positive
  xsign = !(xsign) -1; // x is 0000 if positive and 1111 if negative
  overflow--; //if overflow is true, overflow becomes 0000, if overflow is false, turns to 1111
  return (~overflow & xsign & INT_MIN) | ((~overflow) & (~xsign) & INT_MAX) | (sum & overflow);
        

}

int main(){                                                                                                                    
  //print 2                                                                                                                
  printf( "%d " , saturating_add(1,1) );                                                                                    

  ////print INT_MIN                                                                                                          
  printf("%d ", saturating_add(INT_MIN,INT_MIN));                                                                            

  ////print INT_MAX                                                                                                          
    printf("%d ", saturating_add(INT_MAX,INT_MAX));                                                                             
  }
