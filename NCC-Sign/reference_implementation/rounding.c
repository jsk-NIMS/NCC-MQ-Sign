#include <stdint.h>
#include "params.h"
#include "rounding.h"
int32_t power2round(int32_t *a0, int32_t a)  {
  int32_t a1;
  a1 = (a + (1 << (D-1)) - 1) >> D;
  *a0 = a - (a1 << D);
  return a1;

}

int32_t decompose(int32_t *a0, int32_t a) {
  int32_t a1;

  a = a % Q;
  if (a < 0)
	  a += Q;
  *a0 = a % (2 * GAMMA2);
  if (*a0 > GAMMA2)
	  *a0 -= (2*GAMMA2);
  if (a - (*a0) == (Q - 1)) 
  {
	  a1 = 0;
	  *a0 = *a0 - 1;
  }
  else
  {
	  a1 = (a - (*a0)) / (2 * GAMMA2);
  }
  return a1;
}

unsigned int make_hint(int32_t a0, int32_t a1) { // a0:w-cs2+ct0의 lowbits, a1:w-cs2의 highbits
  if(a0 > GAMMA2 || a0 < - GAMMA2 || (a0 == -GAMMA2 && a1 != 0)) //if(a0 <= GAMMA2 || a0 > Q - GAMMA2 || (a0 == Q - GAMMA2 && a1 == 0)) //Q는 왜 있지?-> ct0더할때 modQ로 양수로 만들어버렸으니까
    return 1;

  return 0;
}

int32_t use_hint(int32_t a, unsigned int hint) {
  int32_t a0, a1;
  
  a1 = decompose(&a0, a);
  if(hint == 0)
    return a1;

#if N==2304
  if(a0 > 0)
    return (a1 == 15) ?  0 : a1 + 1;
  else
    return (a1 ==  0) ? 15 : a1 - 1;
#else
 if(a0 > 0)
    return (a1 == 31) ?  0 : a1 + 1;
  else
    return (a1 ==  0) ? 31 : a1 - 1;
#endif
}
