#ifndef DECRYPT_RSA_H
#define DECRYPT_RSA_H

#include <gmp.h>

// Declaration of the RSA decryption function
void decrypt(const char* key_file,const char* encrypted_message,const char* original_message, int key_length);

// Declaration of the function to read encrypted numbers from a file
void read_keys_from_file(const char* filename,int BUFFER_SIZE,mpz_t n, mpz_t d);

void read_encrypted_file(const char* filename, mpz_t** ciphertext, int* length);

// Declaration of the function to write the decrypted message to a file
void write_deciphered_file(const char* filename, const char* message);

#endif // DECRYPT_RSA_H
