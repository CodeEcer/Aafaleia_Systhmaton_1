#include <stdio.h>
#include "key_generation.h"
#include <gmp.h>
#include "encrypt_rsa.h"
#include "decrypt_rsa.h"
#include <string.h>
#include <stdlib.h>
#include "performance.h"

int main(int argc, char *argv[])
{

    char *input_file = NULL;
    char *output_file = NULL;
    char *key_file = NULL;
    int key_length = 0;
    int encrypt_flag = 0;
    int decrypt_flag = 0;
    int performance_flag = 0;

    // Loop through the command-line arguments
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-i") == 0 && (i + 1) < argc)
        {
            input_file = argv[++i]; // Get input file path
        }
        else if (strcmp(argv[i], "-o") == 0 && (i + 1) < argc)
        {
            output_file = argv[++i]; // Get output file path
        }
        else if (strcmp(argv[i], "-k") == 0 && (i + 1) < argc)
        {
            key_file = argv[++i]; // Get key file path
        }
        else if (strcmp(argv[i], "-g") == 0 && (i + 1) < argc)
        {
            key_length = atoi(argv[++i]); // Convert key length to integer
        }
        else if (strcmp(argv[i], "-e") == 0)
        {
            encrypt_flag = 1; // Set encryption mode
        }
        else if (strcmp(argv[i], "-d") == 0)
        {
            decrypt_flag = 1; // Set decryption mode
        }
        else if (strcmp(argv[i], "-a") == 0)
        {
            performance_flag = 1;
        }
        else if (strcmp(argv[i], "-h") == 0)
        {
            // Display help message
            printf("Usage: ./rsa_tool [OPTIONS]\n");
            printf("Options:\n");
            printf("  -i path      Path to the input file\n");
            printf("  -o path      Path to the output file\n");
            printf("  -k path      Path to the key file\n");
            printf("  -g length    Generate RSA key-pair with given key length\n");
            printf("  -d           Decrypt input and store results to output\n");
            printf("  -e           Encrypt input and store results to output\n");
            printf("  -a           Compare performance with different key lengths\n");
            printf("  -h           Show this help message\n");
            return 0; // Exit after displaying help
        }
    }

    if (key_length)
    {
        printf("Generating RSA key-pair with length: %d\n", key_length);
        // Call key-pair generation function
        key_generate(key_length);
    }

    // At this point, we can check for required arguments and proceed with the encryption or decryption
    if (encrypt_flag)
    {
        printf("Encrypting...\n");
        printf("Input file: %s\n", input_file);
        printf("Output file: %s\n", output_file);
        printf("Key file: %s\n", key_file);
        // Call encryption function
        encrypt(key_file, input_file, output_file);
    }
    else if (decrypt_flag)
    {
        printf("Decrypting...\n");
        printf("Input file: %s\n", input_file);
        printf("Output file: %s\n", output_file);
        printf("Key file: %s\n", key_file);
        // Call decryption function
        decrypt(key_file, input_file, output_file);
    }

    if (performance_flag)
    {
        test_performance();
    }

    return 0;
}