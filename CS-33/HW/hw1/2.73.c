#include <limits.h>
#include <stdio.h>

/* Addition that saturates to TMin or TMax */
int saturating_add(int x, int y)
{

  //first we need to check the saturating cases                                                                        
  // by checking if x and y have the same sign                                                                         

  int mask = -1 << ((sizeof(int)*8)-1);
  int xsign = x & mask;
  int ysign = y & mask;

  // check the sign of what x+y would normally give                                                                    
  int xysum = x+y;
  int xysumsign = mask & xysum;

  //to check if it overflowed                                                                                          
  //if signs of all three are differnt, then fix                                                                       
  // sum to correct overflow amount                                                                                    
  //first check checks if x and y have negative sign and                                                               
  //sum sign is different                  
  int posO = ((~xsign) & (~ysign) & xysumsign); //posO = 1000 if true, 0000 if false
  int negO = (xsign & ysign & ~xysumsign); //negO = 1000 if true, 0000 if false
  posO = !(posO) - 1; //true turns to 1111, false to 0000                                                        
  negO = !(negO) - 1; //true turns to 1111, false to 0000                
  int noO = -1 ^ (posO | negO); //if posO or negO is true, turns noO to 0000, if both false, turns noO to 1111 
  return (posO & INT_MAX) | (xysum & noO) | (negO & INT_MIN);
}

int main(){                                                                                                                
  //print 2                                                                                                                  
  printf( "%d " , saturating_add(1,1) );                                                                                   

  //print INT_MIN                                                                                                            
  printf("%d ", saturating_add(INT_MIN,INT_MIN));                                                                          

  //print INT_MAX                                                                                                            
  printf("%d", saturating_add(INT_MAX,INT_MAX));                                                                           
  }
