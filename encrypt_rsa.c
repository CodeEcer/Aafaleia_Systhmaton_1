#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>
#include <string.h>
#include "encrypt_rsa.h"

// RSA encryption function
void encrypt(const char* key_file, const char* original_message, const char* encrypted_message) {
    printf("Inside encrypt function\n");

    mpz_t n, e;
    mpz_inits(n, e, NULL);

    // Read the public key (n, e) from the key file
    read_public_key_from_file(key_file, n, e);

    // Read the original message from the file "original_message"
    char* text = read_file(original_message);
    int length = strlen(text);  // Get the length of the original message

    // Dynamically allocate an array of mpz_t for the ciphertext
    mpz_t* ciphertext = (mpz_t*)malloc(length * sizeof(mpz_t));
    if (ciphertext == NULL) {
        printf("Memory allocation error\n");
        mpz_clears(n, e, NULL);
        free(text);
        return;
    }

    // Initialize each mpz_t element in the array
    for (int i = 0; i < length; ++i) {
        mpz_init(ciphertext[i]);
    }

    mpz_t m;  // Temporary variable to hold the message (ASCII value)
    mpz_init(m);  // Initialize the temporary variable

    // Encrypt each character
    for (int i = 0; i < length; ++i) {
        int ascii_value = (unsigned char)text[i];  // Get ASCII value of the character
        mpz_set_ui(m, ascii_value);  // Set m to the ASCII value of the character

        // Perform ciphertext[i] = m^e % n (modular exponentiation)
        mpz_powm(ciphertext[i], m, e, n);
    }

    // Write the encrypted message (ciphertext) to the file "encrypted_message"
    write_file(encrypted_message, ciphertext, length);

    printf("Encryption complete. Ciphertext written to '%s'.\n", encrypted_message);

    // Clear mpz_t variables
    for (int i = 0; i < length; ++i) {
        mpz_clear(ciphertext[i]);  // Clear each element in the array
    }
    free(ciphertext);  // Free the dynamically allocated memory for the ciphertext array
    mpz_clear(m);  // Clear the temporary variable
    mpz_clears(n, e, NULL);  // Clear the key values (n, e)
    free(text);  // Free the dynamically allocated memory for the message
}


#include <gmp.h>
#include <stdio.h>

void read_public_key_from_file(const char* filename, mpz_t n, mpz_t e) {
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

    // Read e using gmp_fscanf (just the number, no "e: " label)
    if (gmp_fscanf(file, "%Zd\n", e) != 1) {
        printf("Error reading e from file %s\n", filename);
        fclose(file);
        exit(1);
    }

    fclose(file);
    printf("Public key successfully read from %s\n", filename);
}



// Function to read the original message from a file
char* read_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file %s\n", filename);
        exit(1);
    }

    // Move the file pointer to the end of the file
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file); // Move the file pointer back to the start

    // Allocate memory for the file content
    char* content = (char*)malloc(file_size + 1);
    if (!content) {
        printf("Memory allocation error\n");
        fclose(file);
        exit(1);
    }

    // Read the file into memory
    fread(content, 1, file_size, file);
    content[file_size] = '\0'; // Null-terminate the string

    fclose(file);
    return content;
}

// Function to write the encrypted message to a file
void write_file(const char* filename, mpz_t* ciphertext, int length) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error: Could not open file %s\n", filename);
        exit(1);
    }

    // Loop through the ciphertext array and use gmp_fprintf to write each number
    for (int i = 0; i < length; ++i) {
        // gmp_fprintf writes the mpz_t number directly to the file
        gmp_fprintf(file, "%Zd\n", ciphertext[i]);
    }

    fclose(file);
    printf("Ciphertext successfully written to %s.\n", filename);
}