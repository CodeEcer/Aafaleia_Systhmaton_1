#include <stdio.h>
#include <gmp.h>
#include "prime_generation.h"
#include "key_generation.h"
#include <stdlib.h>


// Function to generate the key using two prime numbers
void key_generate(int key_length) {
    mpz_t p, q,n, lambda,e,d;                // Declare GMP types
    int prime_length = key_length / 2;      // Set the prime length (e.g., 512 bits if key_length is 1024)

    mpz_inits(p, q,n, lambda,e,d, NULL);


    // Generate two prime numbers
    init_random_state();
    prime_generate(p, prime_length);        // Generate prime p
    do {
    prime_generate(q, prime_length);        // Generate prime q =!p
    }
    while (mpz_cmp(p, q) == 0);



    // Calculate n = p * q
    mpz_mul(n, p, q);                  

    // Calculate lambda = (p - 1) * (q - 1)
    mpz_t p_minus_1, q_minus_1;
    mpz_init(p_minus_1);
    mpz_init(q_minus_1);
    
    mpz_sub_ui(p_minus_1, p, 1);            // p_minus_1 = p - 1
    mpz_sub_ui(q_minus_1, q, 1);            // q_minus_1 = q - 1

    mpz_mul(lambda, p_minus_1, q_minus_1);  // lambda = (p - 1) * (q - 1)


    mpz_t gcd_result, mod_result;

    // Initialize temporary variables
    mpz_init(gcd_result);
    mpz_init(mod_result);

    // Loop to generate e untill it satisfies all conditions
    do {
        prime_generate(e, 18);  // Generate a prime e (size 18 bits in this case, does not have to be very large in order to save computational time in encryption)

        // Compute e % lambda
        mpz_mod(mod_result, e, lambda);  

        // Compute gcd(e, lambda)
        mpz_gcd(gcd_result, e, lambda); 

    } while (mpz_cmp(e, lambda) >= 0 || mpz_cmp_ui(mod_result, 0) == 0 || mpz_cmp_ui(gcd_result, 1) != 0);

    //Calculate d as modular inverse of e,lambda
    mpz_invert(d, e, lambda);

    //write keys n,e,d to file
    write_keys_to_file(n,e,d,key_length);

    // Clear memory for GMP variables
    mpz_clears(p,q_minus_1 ,p_minus_1,q, n, e, lambda, d,gcd_result,mod_result, NULL);
}

void write_keys_to_file(mpz_t n, mpz_t e, mpz_t d, int key_length) {
    // Create filenames for public and private key files
    char public_key_file[256];
    char private_key_file[256];

    // Format the filenames like "public_<length>.key" and "private_<length>.key"
    snprintf(public_key_file, sizeof(public_key_file), "public_%d.key", key_length);
    snprintf(private_key_file, sizeof(private_key_file), "private_%d.key", key_length);

    // Write the public key (n, e) to the public key file
    FILE* public_file = fopen(public_key_file, "w");
    if (!public_file) {
        printf("Error: Could not open file %s for writing\n", public_key_file);
        return;
    }
    gmp_fprintf(public_file, "%Zd\n", n);  // Write modulus (n)
    gmp_fprintf(public_file, "%Zd\n", e);  // Write public exponent (e)
    fclose(public_file);
    printf("Public key successfully written to %s\n", public_key_file);

    // Write the private key (n, d) to the private key file
    FILE* private_file = fopen(private_key_file, "w");
    if (!private_file) {
        printf("Error: Could not open file %s for writing\n", private_key_file);
        return;
    }
    gmp_fprintf(private_file, "%Zd\n", n);  // Write modulus (n)
    gmp_fprintf(private_file, "%Zd\n", d);  // Write private exponent (d)
    fclose(private_file);
    printf("Private key successfully written to %s\n", private_key_file);
}