#ifndef PRIME_GENERATION_H
#define PRIME_GENERATION_H

#include <gmp.h>  // GMP library

// Declare functions from key_generation.c
void generate_random_number(mpz_t result, int bits);
int is_prime(mpz_t n, int iterations);
void generate_prime(mpz_t prime, int bits);
void prime_generate(mpz_t prime, int prime_length);

#endif  // _PRIME_GENERATION_H
