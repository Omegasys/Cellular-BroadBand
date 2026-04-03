#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/rand.h>
#include <openssl/hmac.h>
#include <time.h>
#include <stdlib.h>
#include <json-c/json.h>

#define PASSWORD_HASH_SIZE SHA256_DIGEST_LENGTH  // Size of the SHA-256 hash
#define SALT_SIZE 16  // Size of the salt used for hashing

// Function to generate a random salt of the given size
int generate_random_salt(unsigned char *salt, size_t salt_len) {
    if (RAND_bytes(salt, salt_len) != 1) {
        fprintf(stderr, "Error generating random salt\n");
        return -1;
    }
    return 0;
}

// Function to hash a password using SHA-256 and a salt
int hash_password(const char *password, unsigned char *hashed_password, unsigned char *salt, size_t salt_len) {
    unsigned char salted_password[256];
    size_t password_len = strlen(password);

    // Combine password and salt
    memcpy(salted_password, password, password_len);
    memcpy(salted_password + password_len, salt, salt_len);

    // Perform SHA-256 hashing
    SHA256_CTX sha256_ctx;
    SHA256_Init(&sha256_ctx);
    SHA256_Update(&sha256_ctx, salted_password, password_len + salt_len);
    SHA256_Final(hashed_password, &sha256_ctx);

    return 0;
}

// Function to verify a password against a stored hash and salt
int verify_password(const char *input_password, unsigned char *stored_hash, unsigned char *salt, size_t salt_len) {
    unsigned char hash[SHA256_DIGEST_LENGTH];

    // Hash the input password with the stored salt
    if (hash_password(input_password, hash, salt, salt_len) != 0) {
        return -1;
    }

    // Compare the hashes
    if (memcmp(hash, stored_hash, SHA256_DIGEST_LENGTH) == 0) {
        return 0;  // Password matches
    }

    return -1;  // Password does not match
}

// Function to generate a JWT (for example, a simple token with user info)
char *generate_jwt(const char *username, const char *secret_key) {
    json_object *jwt_header = json_object_new_object();
    json_object *jwt_claims = json_object_new_object();

    // JWT Header
    json_object_object_add(jwt_header, "alg", json_object_new_string("HS256"));
    json_object_object_add(jwt_header, "typ", json_object_new_string("JWT"));

    // JWT Claims (Payload)
    time_t now = time(NULL);
    json_object_object_add(jwt_claims, "iat", json_object_new_int(now)); // Issued at time
    json_object_object_add(jwt_claims, "exp", json_object_new_int(now + 3600)); // Expiry time (1 hour)
    json_object_object_add(jwt_claims, "username", json_object_new_string(username));

    // Convert header and claims to JSON strings
    const char *header_json = json_object_to_json_string(jwt_header);
    const char *claims_json = json_object_to_json_string(jwt_claims);

    // Base64 encode header and claims (implement base64 encoding or use a library)
    char *base64_header = base64_encode(header_json); // This function needs to be implemented
    char *base64_claims = base64_encode(claims_json); // This function needs to be implemented

    // Create the unsigned part of the JWT
    char unsigned_jwt[1024];
    snprintf(unsigned_jwt, sizeof(unsigned_jwt), "%s.%s", base64_header, base64_claims);

    // Sign the JWT (HMAC with SHA-256)
    unsigned char signature[SHA256_DIGEST_LENGTH];
    unsigned char *key = (unsigned char *)secret_key;
    HMAC_CTX *hmac_ctx = HMAC_CTX_new();
    HMAC_Init_ex(hmac_ctx, key, strlen(secret_key), EVP_sha256(), NULL);
    HMAC_Update(hmac_ctx, (unsigned char *)unsigned_jwt, strlen(unsigned_jwt));
    HMAC_Final(hmac_ctx, signature, NULL);
    HMAC_CTX_free(hmac_ctx);

    // Base64 encode the signature
    char *base64_signature = base64_encode(signature); // This function needs to be implemented

    // Combine everything into the final JWT
    static char jwt_token[2048];
    snprintf(jwt_token, sizeof(jwt_token), "%s.%s", unsigned_jwt, base64_signature);

    // Clean up JSON objects
    json_object_put(jwt_header);
    json_object_put(jwt_claims);

    return jwt_token;
}

int main() {
    // Example usage for password hashing and verification
    const char *password = "securepassword";
    unsigned char stored_hash[SHA256_DIGEST_LENGTH];
    unsigned char salt[SALT_SIZE];

    // Generate a random salt
    if (generate_random_salt(salt, SALT_SIZE) != 0) {
        return -1;
    }

    // Hash the password with the salt
    if (hash_password(password, stored_hash, salt, SALT_SIZE) != 0) {
        return -1;
    }

    // Verify the password
    if (verify_password("securepassword", stored_hash, salt, SALT_SIZE) == 0) {
        printf("Password verified successfully.\n");
    } else {
        printf("Password verification failed.\n");
    }

    // Example usage for JWT generation
    const char *secret_key = "supersecretkey";
    const char *username = "user123";
    char *jwt_token = generate_jwt(username, secret_key);
    printf("Generated JWT: %s\n", jwt_token);

    return 0;
}
