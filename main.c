#include <stdio.h>
#include "key_generation.h"
#include <gmp.h>
#include "encrypt_rsa.h"


int main() {

    mpz_t n,e,d;
    mpz_inits(n,e,d,NULL);

    key_generate(n,e,d,1024);

    encrypt(n,e);

    return 0;
}
