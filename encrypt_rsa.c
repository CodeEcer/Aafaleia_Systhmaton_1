#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    // Buffer to store the formatted output
    char buffer[1024];  // Adjust size if needed

    for (int i = 0; i < length; ++i) {
        gmp_sprintf(buffer, "%Zd\n", ciphertext[i]); // Format the number as a string
        fprintf(file, "%s", buffer);  // Write the string to the file
    }

    fclose(file);
}
// RSA encryption function
void encrypt(mpz_t n, mpz_t e) {
    printf("Inside encrypt function\n");

    // Read the message from the file "original_message"
    char* text = read_file("original_message");
    int length = strlen(text);  // Length of the message

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
        mpz_set_ui(m, ascii_value); // Set m to the ASCII value of the character

        // Perform ciphertext[i] = m^e % n (modular exponentiation)
        mpz_powm(ciphertext[i], m, e, n);
    }

    // Write the encrypted message to the file "ciphered_message"
    write_file("ciphered_message", ciphertext, length);

    printf("Encryption complete. Ciphertext written to 'ciphered_message'.\n");

    // Clear mpz_t variables
    for (int i = 0; i < length; ++i) {
        mpz_clear(ciphertext[i]);  // Clear each element in the array
    }
    mpz_clear(m);  // Clear the temporary variable
    free(text);  // Free the dynamically allocated memory for the message
}
