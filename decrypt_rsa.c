#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>
#include "decrypt_rsa.h"

void decrypt(const char* key_file,const char* encrypted_message,const char* original_message) {
    
    mpz_t n,d;
    mpz_inits(n,d,NULL);

    read_private_key_from_file(key_file,n,d);

    // Read the encrypted numbers from "ciphered_message"
    mpz_t* ciphertext;
    int length;
    read_encrypted_file(encrypted_message, &ciphertext, &length);

    // Prepare to store the decrypted message
    char* decrypted_message = (char*)malloc(length + 1);
    if (!decrypted_message) {
        printf("Memory allocation error\n");
        exit(1);
    }

    mpz_t m;  // Temporary variable to hold the decrypted ASCII value
    mpz_init(m);  // Initialize the temporary variable

    // Decrypt each number
    for (int i = 0; i < length; ++i) {
        // Perform m = ciphertext[i]^d % n (modular exponentiation)
        mpz_powm(m, ciphertext[i], d, n);

        // Convert the decrypted number (ASCII value) back to a character
        decrypted_message[i] = (char)mpz_get_ui(m);  // Convert mpz_t to unsigned int and cast to char
    }

    decrypted_message[length] = '\0';  // Null-terminate the string

    // Write the decrypted message to "deciphered_message"
    write_deciphered_file(original_message,decrypted_message);

    printf("Decryption complete. Deciphered text written to 'deciphered_message'.\n");

    // Clear mpz_t variables
    for (int i = 0; i < length; ++i) {
        mpz_clear(ciphertext[i]);  // Clear each element in the ciphertext array
    }
    free(ciphertext);  // Free the allocated memory for ciphertext array
    mpz_clear(m);  // Clear the temporary variable
    free(decrypted_message);  // Free the dynamically allocated memory for the decrypted message
}

void read_private_key_from_file(const char* filename, mpz_t n, mpz_t d) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file %s\n", filename);
        exit(1);
    }

    // Read n using gmp_fscanf (just the number, no "n: " label)
    if (gmp_fscanf(file, "%Zd\n", n) != 1) {
        printf("Error reading n from file %s\n", filename);
        fclose(file);
        exit(1);
    }

    // Read d using gmp_fscanf (just the number, no "d: " label)
    if (gmp_fscanf(file, "%Zd\n", d) != 1) {
        printf("Error reading d from file %s\n", filename);
        fclose(file);
        exit(1);
    }

    fclose(file);
    printf("Private key successfully read from %s\n", filename);
}



#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>

void read_encrypted_file(const char* filename, mpz_t** ciphertext, int* length) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file %s\n", filename);
        exit(1);
    }

    // First pass: Count how many numbers are in the file
    *length = 0;
    mpz_t temp;
    mpz_init(temp);
    while (gmp_fscanf(file, "%Zd", temp) != EOF) {
        (*length)++;
    }
    mpz_clear(temp);

    // Allocate memory for the ciphertext array
    *ciphertext = (mpz_t*)malloc(sizeof(mpz_t) * (*length));
    if (!*ciphertext) {
        printf("Memory allocation error\n");
        fclose(file);
        exit(1);
    }

    // Initialize the mpz_t elements in the array
    for (int i = 0; i < *length; ++i) {
        mpz_init((*ciphertext)[i]);
    }

    // Rewind the file to start reading the numbers again
    rewind(file);

    // Second pass: Read the ciphertext numbers into the array
    for (int i = 0; i < *length; ++i) {
        if (gmp_fscanf(file, "%Zd", (*ciphertext)[i]) == EOF) {
            printf("Error reading ciphertext from file\n");
            fclose(file);
            exit(1);
        }
    }

    fclose(file);
}


// Function to write the deciphered message to a file
void write_deciphered_file(const char* filename, const char* message) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error: Could not open file %s\n", filename);
        exit(1);
    }

    fprintf(file, "%s", message);  // Write the deciphered message to the file
    fclose(file);
}
