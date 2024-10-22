
#ifndef KEY_GENERATION_H
#define KEY_GENERATION_H
#include <gmp.h>  // GMP library

void init_random_state();
void key_generate(const char* filename,int key_length);
void write_keys_to_file(const char* filename, mpz_t n, mpz_t e, mpz_t d, int BUFFER_SIZE); // Declaration only

#endif // KEY_GENERATION_H
