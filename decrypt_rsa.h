#ifndef DECRYPT_RSA_H
#define DECRYPT_RSA_H

#include <gmp.h>

// Declaration of the RSA decryption function
void decrypt(mpz_t n, mpz_t d);

// Declaration of the function to read encrypted numbers from a file
void read_encrypted_file(const char* filename, mpz_t** ciphertext, int* length);

// Declaration of the function to write the decrypted message to a file
void write_deciphered_file(const char* filename, const char* message);

#endif // DECRYPT_RSA_H
