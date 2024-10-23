# RSA Algorithm Implementation

This program is a simple implementation of the RSA algorithm, featuring a command-line interface for encryption, decryption, and key generation.

## Description

The program provides functionality for:
- Generating RSA key pairs (public and private).
- Encrypting plaintext using a public key.
- Decrypting ciphertext using a private key.
- Measuring the performance of the encryption and decryption processes.

The tool supports any key length, not just the standard 1024, 2048, or 4096 bits. Prime numbers are generated probabilistically, significantly improving time efficiency compared to traditional primality tests. In the current implementation, a probabilistic prime check with 30 iterations is used, which results in a very low error rate (~4^-30), making the generated numbers highly likely to be prime.

### Key Generation Features

- The key generation process creates a public key (`n`, `e`) and a private key (`n`, `d`).
- The exponent `e` in the public key is chosen to be smaller than `n` and `d` for better performance. Typically, `e` is set to 17–20 bits, as larger values slow down encryption without providing additional security benefits. For example, with a 1024-bit key, `n` will be 512 bits, `e` will be 18 bits, and `d` will be 512 bits.
- A minor mathematical caveat: While the program checks if `e < λ(n)` (where `λ(n)` is the totient function), it does not explicitly check if `e > 1`. This is because the prime generation ensures that `e` is a large enough value by setting the most significant bit to 1.

## Usage Instructions

### Command-Line Options

The program can be run using different command-line options, as shown below:

- **Key Generation**:
  ```bash
  ./rsa_assign_1 -g 1024

This generates a public-private key pair of 1024 bits.

- **Encryption**:

./rsa_assign_1 -i message.txt -o ciphertext.txt -k public_1024.key -e

This encrypts the contents of message.txt into ciphertext.txt using the public key from public_1024.key.

- **Decryption**:

./rsa_assign_1 -i ciphertext.txt -o original_message.txt -k private_1024.key -d

This decrypts ciphertext.txt (created from the previous encryption step) and outputs the original message into original_message.txt using the private key from private_1024.key.

- **Performance Testing**:

./rsa_assign_1 -a performance.txt

This generates three sets of key pairs (1024, 2048, and 4096 bits), encrypts the contents of test_performance.txt into output.txt, and records the performance metrics (encryption and decryption time, memory usage) in performance.txt. Note that key generation performance is not measured, as it is a one-time setup step.

## Error Handling

If a required file (e.g., key file or message file) is not provided, the program will output an error message, such as: "Error: Could not open file"
For that reason ensure that all necessary arguments are provided in the correct format to avoid these errors.

## Compilation and Running the Program

1. Navigate to the directory containing the source code.
2. Run: make

After compilation, use the following format to run the program:

./rsa_assign_1 <arguments>
Replace <arguments> with the appropriate options (e.g., -g, -e, -d, etc.) depending on the operation you wish to perform.