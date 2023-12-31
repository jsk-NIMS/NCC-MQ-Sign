#include <stdint.h>
#include "params.h"
#include "rounding.h"

int32_t power2round(int32_t *a0, int32_t a) {
	int32_t a1;

	a1 = (a + (1 << (D - 1)) - 1) >> D;
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
		*a0 -= (2 * GAMMA2);
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

unsigned int make_hint(int32_t a0, int32_t a1) {
	if (a0 <= GAMMA2 || a0 > Q - GAMMA2 || (a0 == Q - GAMMA2 && a1 == 0))
		return 0;

	return 1;
}

int32_t use_hint(int32_t a, unsigned int hint) {
	int32_t a0, a1;

	a1 = decompose(&a0, a);
	if (hint == 0)
		return a1;

#if N==1201
	if (a0 > 0)
		return (a1 == 34) ? 0 : a1 + 1;
	else
		return (a1 == 0) ? 34 : a1 - 1;
#elif N==1607
	if (a0 > 0)
		return (a1 == 29) ? 0 : a1 + 1;
	else
		return (a1 == 0) ? 29 : a1 - 1;
#elif N==2039
	if (a0 > 0)
		return (a1 == 28) ? 0 : a1 + 1;
	else
		return (a1 == 0) ? 28 : a1 - 1;
#endif
}
