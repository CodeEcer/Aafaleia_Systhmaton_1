#include <gmp.h>
#include "prime_generation.h"
#include "key_generation.h"


// Function to generate the key using two prime numbers
void key_generate(int key_length) {
    mpz_t p, q, n, lambda,e,d;                 // Declare GMP large integer types
    int prime_length = key_length / 2;      // Set the prime length (e.g., 512 bits if key_length is 1024)

    // Initialize the mpz_t variables
    mpz_init(p);
    mpz_init(q);
    mpz_init(n);
    mpz_init(lambda);
    mpz_init(e);
    mpz_init(d);

    // Generate two prime numbers
    prime_generate(p, prime_length);        // Generate prime p
    prime_generate(q, prime_length);        // Generate prime q

    // Calculate n = p * q
    mpz_mul(n, p, q);                       // n = p * q

    // Calculate lambda = (p - 1) * (q - 1)
    mpz_t p_minus_1, q_minus_1;
    mpz_init(p_minus_1);
    mpz_init(q_minus_1);
    
    mpz_sub_ui(p_minus_1, p, 1);            // p_minus_1 = p - 1
    mpz_sub_ui(q_minus_1, q, 1);            // q_minus_1 = q - 1

    mpz_mul(lambda, p_minus_1, q_minus_1);  // lambda = (p - 1) * (q - 1)

    // Print the results
    gmp_printf("p: %Zd\n", p);
    gmp_printf("q: %Zd\n", q);
    gmp_printf("n: %Zd\n", n);
    gmp_printf("lambda: %Zd\n", lambda);

    // Clear memory for GMP variables
    mpz_clear(p);
    mpz_clear(q);
    mpz_clear(n);
    mpz_clear(lambda);
    mpz_clear(p_minus_1);
    mpz_clear(q_minus_1);
}
