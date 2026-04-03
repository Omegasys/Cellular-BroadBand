#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <stdint.h>

#define AES_KEY_SIZE 16  // AES 128-bit key (16 bytes)
#define AES_BLOCK_SIZE 16 // AES block size (16 bytes)

// Function Prototypes

/**
 * @brief Encrypts the given input using AES encryption in CBC mode.
 * 
 * @param input The plaintext input data to encrypt.
 * @param output The buffer where the encrypted data will be stored.
 * @param key The AES encryption key (128-bit).
 * @param iv The Initialization Vector (IV) for AES encryption.
 * @return 0 on success, -1 on failure.
 */
int aes_encrypt(const unsigned char *input, unsigned char *output, const unsigned char *key, const unsigned char *iv);

/**
 * @brief Decrypts the given encrypted data using AES decryption in CBC mode.
 * 
 * @param input The encrypted input data to decrypt.
 * @param output The buffer where the decrypted data will be stored.
 * @param key The AES decryption key (128-bit).
 * @param iv The Initialization Vector (IV) for AES decryption.
 * @return 0 on success, -1 on failure.
 */
int aes_decrypt(const unsigned char *input, unsigned char *output, const unsigned char *key, const unsigned char *iv);

/**
 * @brief Generates a secure random Initialization Vector (IV) for AES encryption/decryption.
 * 
 * @param iv The buffer where the IV will be stored.
 * @return 0 on success, -1 on failure.
 */
int generate_random_iv(unsigned char *iv);

#endif // ENCRYPTION_H
