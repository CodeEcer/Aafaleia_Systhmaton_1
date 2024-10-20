#include <gmp.h>
#include <time.h>

// Function to generate a random number with 'bits' length
void generate_random_number(mpz_t result, int bits) {
    gmp_randstate_t state;
    gmp_randinit_mt(state);             // Initialize the random state
    gmp_randseed_ui(state, time(NULL)); // Seed the random state with the current time
    mpz_urandomb(result, state, bits);  // Generate a random number with the specified number of bits
    mpz_setbit(result, bits - 1);       // Ensure the number has the correct bit length by setting the most significant bit
    mpz_setbit(result, 0);              // Ensure the number is odd by setting the least significant bit
    gmp_randclear(state);               // Clear the random state
}

// Function to check if a number is prime using GMP's probabilistic prime check
int is_prime(mpz_t n, int iterations) {
    return mpz_probab_prime_p(n, iterations); // Returns > 0 if n is probably prime
}

// Function to generate a prime number with 'bits' length
void generate_prime(mpz_t prime, int bits) {
    do {
        generate_random_number(prime, bits); // Generate a random number of the desired bit length
    } while (!is_prime(prime, 25));          // Repeat until the number is prime (25 iterations for probabilistic check)
}

// Function to generate a prime and return it by setting the 'prime' parameter
void prime_generate(mpz_t prime, int prime_length) {
    generate_prime(prime, prime_length);   // Generate a prime number of the specified bit length
    gmp_printf("Generated Prime p: %Zd\n", prime);  // Print the generated prime
}
