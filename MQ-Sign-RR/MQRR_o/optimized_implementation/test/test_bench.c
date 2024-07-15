#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <immintrin.h>

#include "../mqs_config.h"
#include "../blas_matrix_avx2.h"
#include "../utils_prng.h"
#include "../api.h"

// Test Parameters 
#define TEST_KEYGEN		100
#define TEST_LOOPS		10000
#define TEST_PASSED		1
#define TEST_FAILED		0

#define OS_WIN       1
#define OS_LINUX     2

#if defined(__WINDOWS__)        // Microsoft Windows OS
#define OS_TARGET OS_WIN
#else // Linux OS
#define OS_TARGET OS_LINUX 
#endif

#if defined(__i386__)

static __inline__ unsigned long long rdtsc(void)
{
	unsigned long long int x;
	__asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
	return x;
}
#elif defined(__x86_64__)


static __inline__ unsigned long long rdtsc(void)
{
	unsigned hi, lo;
	__asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
	return ((unsigned long long)lo) | (((unsigned long long)hi) << 32);
}

#elif defined(__powerpc__)
static __inline__ unsigned long long rdtsc(void)
{
	unsigned long long int result = 0;
	unsigned long int upper, lower, tmp;
	__asm__ volatile(
		"0:                  \n"
		"\tmftbu   %0           \n"
		"\tmftb    %1           \n"
		"\tmftbu   %2           \n"
		"\tcmpw    %2,%0        \n"
		"\tbne     0b         \n"
		: "=r"(upper), "=r"(lower), "=r"(tmp)
		);
	result = upper;
	result = result << 32;
	result = result | lower;

	return(result);
}
#endif

int64_t cpucycles(void);
int cryptotest_sig(void);
int cryptorun_sig(void);

static int cmp_uint64(const void *a, const void *b) {
  if(*(unsigned long long *)a < *(unsigned long long *)b) return -1;
  if(*(unsigned long long *)a > *(unsigned long long *)b) return 1;
  return 0;
}

static unsigned long long median(unsigned long long *l, size_t llen) {
  qsort(l,llen,sizeof(unsigned long long),cmp_uint64);

  if(llen%2) return l[llen/2];
  else return (l[llen/2-1]+l[llen/2])/2;
}

static unsigned long long average(unsigned long long *t, size_t tlen) {
  size_t i;
  unsigned long long acc=0;

  for(i=0;i<tlen;i++)
    acc += t[i];

  return acc/tlen;
}

int64_t cpucycles(void)
{ // Access system counter for benchmarking
#if (OS_TARGET == OS_WIN) && (TARGET == TARGET_AMD64 || TARGET == TARGET_x86)
	return __rdtsc();
#elif (OS_TARGET == OS_WIN) && (TARGET == TARGET_ARM)
	return __rdpmccntr64();
#elif (OS_TARGET == OS_LINUX) && (TARGET == TARGET_AMD64 || TARGET == TARGET_x86)
	unsigned int hi, lo;

	__asm__ __volatile__("rdtsc\n\t" : "=a" (lo), "=d"(hi));
	return ((int64_t)lo) | (((int64_t)hi) << 32);
#elif (OS_TARGET == OS_LINUX) && (TARGET == TARGET_ARM || TARGET == TARGET_ARM64)
	struct timespec time;

	clock_gettime(CLOCK_REALTIME, &time);
	return (int64_t)(time.tv_sec * 1e9 + time.tv_nsec);
#else
	return 0;
#endif
}

int cryptotest_sig(void)
{
	uint32_t i;
	uint8_t msg[20] = { 0, };
	unsigned long long smlen = 0;
	unsigned long long mlen = 20;
	uint8_t  entropy_input[48];
	// unsigned char pk[CRYPTO_PUBLICKEYBYTES] = { 0, };
	//unsigned char sk[CRYPTO_SECRETKEYBYTES] = { 0, };
	uint8_t ss[CRYPTO_BYTES + 20] = { 0, };
	int32_t ret = TEST_PASSED;
	int32_t r = 0;
	int32_t rr = 0;
	uint32_t cnt_fail = 0;
	uint32_t cnt_succ = 0;


	srand(time(NULL));
	for (i = 0; i < 48; i++)
		entropy_input[i] = rand() % 256;

	randombytes_init(entropy_input, NULL, 256);
	randombytes(msg, mlen);

	unsigned char* pk = (unsigned char*)malloc(CRYPTO_PUBLICKEYBYTES);
	unsigned char* sk = (unsigned char*)malloc(CRYPTO_SECRETKEYBYTES);

	// for (int depth = 0; depth <= MAX_DEPTH; depth++)
	int depth = 1;
	{
		printf("\n\nTESTING MULTIVARIATE-BASED DIGITAL SIGNATURE - %s with depth %d  \n", CRYPTO_ALGNAME, depth);
		printf("--------------------------------------------------------------------------------------------------------\n\n");
		for (i = 0; i < 100; i++)
		{
			crypto_sign_keypair(pk, sk);

			rr = crypto_sign(ss, &smlen, msg, mlen, sk);
			r = crypto_sign_open(msg, &mlen, ss, mlen + CRYPTO_BYTES, pk);

			if (r)
			{
				ret = TEST_FAILED;
				break;
				cnt_fail++;
			}
			else
			{
				cnt_succ++;
			}

		}
		if (ret == TEST_PASSED)
		{
			printf("  Signature Verification tests .................................................... PASSED \n");
			printf(" Test Loop : %d \n", i);
		}
		else
		{
			printf("\n\n%d\n\n", i);
			printf("\n\n%d\n\n", rr);
			printf("  Signature Verification tests ... FAILED"); printf("\n");

			return TEST_FAILED;
		}
		printf("\n");
	}

	//printf(" Fail : %d \n", cnt_fail);
	//printf(" Success : %d \n", cnt_succ);

	free(pk);
	free(sk);

	return ret;

}

int cryptorun_sig(void)
{
	uint32_t i;
	uint8_t* pk = (uint8_t*)malloc(CRYPTO_PUBLICKEYBYTES);
	uint8_t* sk = (uint8_t*)malloc(CRYPTO_SECRETKEYBYTES);
	uint8_t ss[CRYPTO_BYTES + 20] = { 0, };
	uint8_t msg[20] = { 0, };
	int32_t ret = TEST_PASSED;
	unsigned long long smlen = 0;
	unsigned long long mlen = 20;
	unsigned long long cycles[TEST_LOOPS] = { 0, };
	unsigned long long cycles1, cycles2;

	randombytes(msg, mlen);

	for (i = 0; i < TEST_KEYGEN; i++)
	{
		cycles1 = cpucycles();
		// Key Generation
		crypto_sign_keypair(pk, sk);
		cycles2 = cpucycles();
		cycles[i] = cycles2 - cycles1;
	}

	printf("  Key generation runs in ................................. %10llu cycles/ticks (median)", median(cycles, TEST_KEYGEN));
	printf("\n");
	printf("  Key generation runs in ................................. %10llu cycles/ticks (average)", average(cycles, TEST_KEYGEN));
	printf("\n");

	// for (int depth = 0; depth <= MAX_DEPTH; depth++)
	int depth = 1;
	{
		printf("\n\nBENCHMARKING MULTIVARIATE-BASED DIGITAL SIGNATURE - %s with depth %d \n", CRYPTO_ALGNAME, depth);
		printf("--------------------------------------------------------------------------------------------------------\n\n");

		for (i = 0; i < TEST_LOOPS; i++)
		{
			cycles1 = cpucycles();
			// Signature Generation
			//randombytes(msg, mlen);
			crypto_sign(ss, &smlen, msg, mlen, sk);
			cycles2 = cpucycles();
			cycles[i] = cycles2 - cycles1;
		}

		printf("  Signature Generation runs in ................................. %10llu cycles/ticks (median)", median(cycles, TEST_LOOPS));
		printf("\n");
		printf("  Signature Generation runs in ................................. %10llu cycles/ticks (average)", average(cycles, TEST_LOOPS));
		printf("\n");

		for (i = 0; i < TEST_LOOPS; i++)
		{
			cycles1 = cpucycles();
			// Signature Verification
			//randombytes(msg, mlen);
			crypto_sign_open(msg, &mlen, ss, mlen + CRYPTO_BYTES, pk);
			cycles2 = cpucycles();
			cycles[i] = cycles2 - cycles1;
		}

		printf("  Signature Verification runs in ................................. %10llu cycles/ticks (median)", median(cycles, TEST_LOOPS));
		printf("\n");
		printf("  Signature Verification runs in ................................. %10llu cycles/ticks (average)", average(cycles, TEST_LOOPS));
		printf("\n");
	}
	free(pk);
	free(sk);
	return ret;
}


int main()
{
	int ret = TEST_PASSED;

	ret = cryptotest_sig();
	if (ret != TEST_PASSED)
	{
		printf("\n\n   Error detected: SIGNATURE_VERIFICATION_FAILED \n\n");
	}

	cryptorun_sig();

	printf("\n\n");
	printf("CRYPTO_ALGNAME : %s \n", CRYPTO_ALGNAME);
	printf("_SEC_KEY_LEN : %ld \n", (_SEC_KEY_LEN));
	printf("_PUB_KEY_LEN : %d \n", (_PUB_KEY_LEN));
	printf("CRYPTO_BYTES: %d \n", CRYPTO_BYTES);
	printf("TEST_LOOPS : %d \n", TEST_LOOPS);

	return ret;
}
