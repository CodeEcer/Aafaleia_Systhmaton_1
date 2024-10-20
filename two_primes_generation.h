#ifndef TWO_PRIMES_GENERATION_H
#define TWO_PRIMES_GENERATION_H

#include <gmp.h>  // GMP library

// Declare functions from key_generation.c
void generate_random_number(mpz_t result, int bits);
int is_prime(mpz_t n, int iterations);
void generate_prime(mpz_t prime, int bits);
int key_generate();
void checkinclude();

#endif  // TWO_PRIMES_GENERATION_H
