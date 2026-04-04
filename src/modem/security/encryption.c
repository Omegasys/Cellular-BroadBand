#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

// Function to encrypt data using AES CBC mode
int aes_encrypt(const unsigned char *input, unsigned char *output, const unsigned char *key, const unsigned char *iv) {
    AES_KEY encrypt_key;
    
    // Set encryption key (256-bit)
    if (AES_set_encrypt_key(key, 256, &encrypt_key) < 0) {
        fprintf(stderr, "AES_set_encrypt_key failed.\n");
        return -1;
    }

    // Perform AES encryption in CBC mode
    AES_cbc_encrypt(input, output, strlen((char *)input) + 1, &encrypt_key, (unsigned char *)iv, AES_ENCRYPT);

    return 0;
}

// Function to decrypt data using AES CBC mode
int aes_decrypt(const unsigned char *input, unsigned char *output, const unsigned char *key, const unsigned char *iv) {
    AES_KEY decrypt_key;
    
    // Set decryption key (256-bit)
    if (AES_set_decrypt_key(key, 256, &decrypt_key) < 0) {
        fprintf(stderr, "AES_set_decrypt_key failed.\n");
        return -1;
    }

    // Perform AES decryption in CBC mode
    AES_cbc_encrypt(input, output, strlen((char *)input) + 1, &decrypt_key, (unsigned char *)iv, AES_DECRYPT);

    return 0;
}

// Function to generate a random IV (Initialization Vector) for AES
int generate_random_iv(unsigned char *iv) {
    if (!RAND_bytes(iv, AES_BLOCK_SIZE)) {
        fprintf(stderr, "RAND_bytes failed to generate random IV.\n");
        return -1;
    }
    return 0;
}

int main() {
    // 256-bit key and AES_BLOCK_SIZE for IV
    unsigned char key[32] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                             0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 
                             0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 
                             0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F};  // 256-bit key

    unsigned char iv[AES_BLOCK_SIZE];  // Initialization Vector (16 bytes)

    // Example plaintext to encrypt
    unsigned char input[] = "Hello, this is a test message!";
    unsigned char encrypted[128];  // Buffer to store the encrypted text
    unsigned char decrypted[128];  // Buffer to store the decrypted text

    // Generate a random IV
    if (generate_random_iv(iv) != 0) {
        return -1;
    }

    // Encrypt the input text
    if (aes_encrypt(input, encrypted, key, iv) != 0) {
        return -1;
    }

    printf("Encrypted text:\n");
    for (int i = 0; i < strlen((char *)input) + 1; i++) {
        printf("%02x ", encrypted[i]);
    }
    printf("\n");

    // Decrypt the encrypted text
    if (aes_decrypt(encrypted, decrypted, key, iv) != 0) {
        return -1;
    }

    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
