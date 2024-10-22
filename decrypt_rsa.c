#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>

// Function to read the encrypted numbers from the file

// RSA decryption function
void decrypt(const char* key_file,const char* encrypted_message,const char* original_message, int key_length) {
    printf("Inside decrypt function\n");

    mpz_t n,d;
    mpz_inits(n,d,NULL);

    read_keys_from_file(key_file,key_length,n,d);

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

void read_keys_from_file(const char* filename,int BUFFER_SIZE,mpz_t n, mpz_t d) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file %s\n", filename);
        exit(1);
    }

    // Buffer to read strings from the file
    char buffer[BUFFER_SIZE];

    // Read n
    if (fscanf(file, "n: %1023s\n", buffer) == 1) {
        mpz_set_str(n, buffer, 10);  // Convert string to mpz_t
    }

    // Read e
    if (fscanf(file, "d: %1023s\n", buffer) == 1) {
        mpz_set_str(d, buffer, 10);  // Convert string to mpz_t
    }
    fclose(file);
    printf("Keys successfully read from %s\n", filename);
}

void read_encrypted_file(const char* filename, mpz_t** ciphertext, int* length) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file %s\n", filename);
        exit(1);
    }

    // Count how many numbers are in the file
    *length = 0;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        (*length)++;
    }

    // Allocate memory for the ciphertext array
    *ciphertext = (mpz_t*)malloc(sizeof(mpz_t) * (*length));
    if (!*ciphertext) {
        printf("Memory allocation error\n");
        fclose(file);
        exit(1);
    }

    // Rewind the file to read the numbers again
    rewind(file);

    // Read the ciphertext numbers as strings and convert them to mpz_t
    for (int i = 0; i < *length; ++i) {
        mpz_init((*ciphertext)[i]);
        if (fgets(buffer, sizeof(buffer), file)) {
            mpz_set_str((*ciphertext)[i], buffer, 10); // Convert string to mpz_t (base 10)
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
