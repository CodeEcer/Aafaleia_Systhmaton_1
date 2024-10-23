#include <gmp.h>
#include <time.h>
#include <stdio.h>

// Global Initializaation of state for faster generation
gmp_randstate_t state;

void init_random_state() {
    gmp_randinit_mt(state);             // Initialize the random state (Mersenne Twister algorithm)
    gmp_randseed_ui(state, time(NULL)); // Seed the random state with the current time
}

// Function to generate a random number with 'bits' length
void generate_random_number(mpz_t result, int bits) {
    mpz_urandomb(result, state, bits);  // Generate a random number with the specified number of bits
    mpz_setbit(result, bits - 1);       // Ensure the number has the correct bit length by setting the most significant bit
                                        // for example make 000011 -> 100011
    mpz_setbit(result, 0);              // Ensure the number is odd by setting the least significant bit
                                        // for example make the 1000 = 8 into 1001 = 9
}

// Function to check if a number is prime using GMP's probabilistic prime check.
int is_prime(mpz_t n, int iterations) {
    return mpz_probab_prime_p(n, iterations);; /*Returns 2 if n is definitely prime, return 1 if n is probably prime (without being certain), or return 0 if n is definitely non-prime.*/
}

// Function to generate a prime number with 'bits' length
void generate_prime(mpz_t prime, int bits) {
    do {
        generate_random_number(prime, bits); // Generate a random number of the desired bit length
    } while (is_prime(prime, 30) == 0);      // Repeat until the number is probably prime
}

// Function to generate a prime and return it by setting the 'prime' parameter
void prime_generate(mpz_t prime, int prime_length) {
    generate_prime(prime, prime_length);   // Generate a prime number of the specified bit length
}
