#include <gmp.h>

void decrypt(mpz_t n, mpz_t d) {

    char text[] = "Hello World!";
    int length = sizeof(text) / sizeof(text[0]);

    // Declare an array of mpz_t for ciphertext and initialize each element
    mpz_t ciphertext[length];
    for (int i = 0; i < length; ++i) {
        mpz_init(ciphertext[i]);  // Initialize each mpz_t variable in the array
    }

    mpz_t m;  // Temporary variable to hold the message (ASCII value)
    mpz_init(m);  // Initialize the temporary variable

    // Encrypt each character
    for (int i = 0; i < length; ++i) {   
        int ascii_value = text[i];  // Get ASCII value of the character

        // Set m to the ASCII value of the character
        mpz_set_ui(m, ascii_value);

        // Perform ciphertext[i] = m^e % n (modular exponentiation)
        mpz_powm(ciphertext[i], m, d, n);
    }

    // Print encrypted message as ciphertext - output file
    printf("Encrypted message: ");
    for (int i = 0; i < length; ++i) {
        gmp_printf("%Zd ", ciphertext[i]);
    }
    printf("\n");

    // Clear mpz_t variables
    for (int i = 0; i < length; ++i) {
        mpz_clear(ciphertext[i]);  // Clear each element in the array
    }
    mpz_clear(m);  // Clear the temporary variable


}