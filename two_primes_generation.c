#include "two_primes_generation.h"  // Include the corresponding header file
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <gmp.h>  // GMP library for big numbers

// Function definitions
void generate_random_number(mpz_t result, int bits) {
    gmp_randstate_t state;
    gmp_randinit_mt(state);            
    gmp_randseed_ui(state, time(NULL));
    mpz_urandomb(result, state, bits);  
    mpz_setbit(result, bits - 1);       
    mpz_setbit(result, 0);              
    gmp_randclear(state);               
}

int is_prime(mpz_t n, int iterations) {
    return mpz_probab_prime_p(n, iterations);
}

void generate_prime(mpz_t prime, int bits) {
    do {
        generate_random_number(prime, bits); 
    } while (!is_prime(prime, 25));          
}

int key_generate() {
    int key_length = 2048;   
    int prime_bits = key_length / 2; 

    mpz_t p, q;  
    mpz_init(p);
    mpz_init(q);

    generate_prime(p, prime_bits);
    gmp_printf("Prime p: %Zd\n", p);

    generate_prime(q, prime_bits);
    gmp_printf("Prime q: %Zd\n", q);

    mpz_clear(p);
    mpz_clear(q);

    return 0;
}

void checkinclude() {
    printf("EIMAI TO ALLO ARXEIO");
}
