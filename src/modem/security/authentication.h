#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <stdint.h>
#include <stddef.h>

// Constants for password hashing
#define PASSWORD_HASH_SIZE SHA256_DIGEST_LENGTH  // Size of the SHA-256 hash
#define SALT_SIZE 16  // Size of the salt (16 bytes for randomization in password hashing)

// Function Prototypes

/**
 * @brief Generates a random salt for password hashing.
 * 
 * @param salt The buffer where the generated salt will be stored.
 * @param salt_len The length of the salt.
 * @return 0 on success, -1 on failure.
 */
int generate_random_salt(unsigned char *salt, size_t salt_len);

/**
 * @brief Hashes a password using SHA-256 and a salt.
 * 
 * @param password The password to hash.
 * @param hashed_password The buffer to store the resulting hash.
 * @param salt The salt to use for the hashing process.
 * @param salt_len The length of the salt.
 * @return 0 on success, -1 on failure.
 */
int hash_password(const char *password, unsigned char *hashed_password, unsigned char *salt, size_t salt_len);

/**
 * @brief Verifies an input password against a stored hash and salt.
 * 
 * @param input_password The input password to verify.
 * @param stored_hash The stored hash to compare against.
 * @param salt The salt used during the initial hashing process.
 * @param salt_len The length of the salt.
 * @return 0 if password matches, -1 if password does not match.
 */
int verify_password(const char *input_password, unsigned char *stored_hash, unsigned char *salt, size_t salt_len);

/**
 * @brief Generates a JSON Web Token (JWT) based on the provided username and secret key.
 * 
 * @param username The username for which to generate the token.
 * @param secret_key The secret key used to sign the token.
 * @return A dynamically allocated string containing the JWT token, or NULL on error.
 */
char *generate_jwt(const char *username, const char *secret_key);

#endif // AUTHENTICATION_H
