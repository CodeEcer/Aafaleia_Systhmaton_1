#ifndef ENCRYPT_RSA_H
#define ENCRYPT_RSA_H

#include <gmp.h>  // GMP library

// Declaration of the RSA encryption function
void encrypt(const char* key_file,const char* original_message,const char* encrypted_message, int key_length);
void read_keys_from_file(const char* filename,int BUFFER_SIZE,mpz_t n, mpz_t e);

// Declaration of the function to read a message from a file
char* read_file(const char* filename);

// Declaration of the function to write the encrypted message to a file
void write_file(const char* filename, mpz_t* ciphertext, int length);

#endif // ENCRYPT_RSA_H
