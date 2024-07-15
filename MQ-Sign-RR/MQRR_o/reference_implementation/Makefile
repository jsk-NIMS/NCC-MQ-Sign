CC ?= /usr/bin/cc

CFLAGS += -Wall -Wextra -Wpedantic -Wmissing-prototypes -Wredundant-decls \
  -Wshadow -Wpointer-arith -O3 -std=c11 -march=native -mtune=native \
  -mpopcnt -maes -mbmi2
NISTFLAGS += -Wno-unused-result -O3 -mpopcnt -maes -mbmi2 \
  -march=native -mtune=native
SOURCES = aes.c blas_comm.c blas_matrix_ref.c blas_matrix.c fips202.c mqs_keypair_computation.c \
		mqs_keypair.c mqs.c parallel_matrix_op.c rng.c sign.c utils_hash.c utils_prng.c
HEADERS = aes.h api.h blas_comm.h blas_matrix_ref.h blas_matrix.h blas_u32.h blas.h crypto_declassify.h \
		fips202.h gf16.h hash_len_config.h mpkc.h mqs_blas.h mqs_config.h mqs_keypair_computation.h \
		mqs_keypair.h mqs.h parallel_matrix_op.h rng.h utils_hash.h utils_malloc.h utils_prng.h

.PHONY: all test_bench PQCgenKAT_sign clean

all: \
	test_bench \
	PQCgenKAT_sign

test_bench: \
	test/test_bench1 \
	test/test_bench3 \
	test/test_bench5

PQCgenKAT_sign: \
	PQCgenKAT_sign1 \
	PQCgenKAT_sign3 \
	PQCgenKAT_sign5

test/test_bench1: test/test_bench.c $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -D_MQS256_72_46 \
		-o $@ $< $(SOURCES)

test/test_bench3: test/test_bench.c $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -D_MQS256_112_72 \
		-o $@ $< $(SOURCES)

test/test_bench5: test/test_bench.c $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -D_MQS256_148_96 \
		-o $@ $< $(SOURCES)

PQCgenKAT_sign1: PQCgenKAT_sign.c $(SOURCES) $(HEADERS)
	$(CC) $(NISTFLAGS) -D_MQS256_72_46 \
		-o $@ $< $(SOURCES)

PQCgenKAT_sign3: PQCgenKAT_sign.c $(SOURCES) $(HEADERS)
	$(CC) $(NISTFLAGS) -D_MQS256_112_72 \
		-o $@ $< $(SOURCES)

PQCgenKAT_sign5: PQCgenKAT_sign.c $(SOURCES) $(HEADERS)
	$(CC) $(NISTFLAGS) -D_MQS256_148_96 \
		-o $@ $< $(SOURCES)

clean:
	rm -f test/test_bench1
	rm -f test/test_bench3
	rm -f test/test_bench5
	rm -f PQCgenKAT_sign1
	rm -f PQCgenKAT_sign3
	rm -f PQCgenKAT_sign5


