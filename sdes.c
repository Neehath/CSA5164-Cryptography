#include <stdio.h>
#include <stdint.h>
#include <string.h>

// S-DES functions (placeholders, need real implementations)

// S-DES key schedule and encryption/decryption functions
// For simplicity, we use placeholders. Real implementations should be used.
void sdes_key_schedule(uint8_t key[10], uint8_t *K1, uint8_t *K2) {
    // Placeholder function for generating K1 and K2 from key
    memcpy(K1, key, 8); // Dummy copy
    memcpy(K2, key + 8, 8); // Dummy copy
}

void sdes_encrypt_block(uint8_t plaintext[8], uint8_t key[8], uint8_t ciphertext[8]) {
    // Placeholder function for S-DES encryption
    memcpy(ciphertext, plaintext, 8); // Dummy copy
}

void sdes_decrypt_block(uint8_t ciphertext[8], uint8_t key[8], uint8_t plaintext[8]) {
    // Placeholder function for S-DES decryption
    memcpy(plaintext, ciphertext, 8); // Dummy copy
}

// CBC encryption function for S-DES
void sdes_cbc_encrypt(const uint8_t *data, uint8_t *encrypted, const uint8_t *key, const uint8_t *iv, size_t length) {
    uint8_t K1[8], K2[8];
    sdes_key_schedule(key, K1, K2);

    uint8_t block[8];
    uint8_t xor_block[8];

    memcpy(xor_block, iv, 8);

    for (size_t i = 0; i < length; i += 8) {
        // XOR plaintext with IV or previous ciphertext
        for (int j = 0; j < 8; ++j) {
            block[j] = data[i + j] ^ xor_block[j];
        }

        // Encrypt the block
        sdes_encrypt_block(block, K1, encrypted + i);

        // Update XOR block to the current ciphertext
        memcpy(xor_block, encrypted + i, 8);
    }
}

// CBC decryption function for S-DES
void sdes_cbc_decrypt(const uint8_t *data, uint8_t *decrypted, const uint8_t *key, const uint8_t *iv, size_t length) {
    uint8_t K1[8], K2[8];
    sdes_key_schedule(key, K1, K2);

    uint8_t block[8];
    uint8_t xor_block[8];

    memcpy(xor_block, iv, 8);

    for (size_t i = 0; i < length; i += 8) {
        // Decrypt the block
        sdes_decrypt_block(data + i, K1, block);

        // XOR with IV or previous ciphertext
        for (int j = 0; j < 8; ++j) {
            decrypted[i + j] = block[j] ^ xor_block[j];
        }

        // Update XOR block to the current ciphertext
        memcpy(xor_block, data + i, 8);
    }
}

// Helper function to print data in binary format
void print_binary(const char *label, const uint8_t *data, size_t length) {
    printf("%s", label);
    for (size_t i = 0; i < length; i++) {
        for (int j = 7; j >= 0; j--) {
            printf("%d", (data[i] >> j) & 1);
        }
        printf(" ");
    }
    printf("\n");
}

int main() {
    // Example key (10 bits for S-DES, will be handled as byte array here)
    uint8_t key[10] = {0x1F, 0xFD};  // 01111 11101 in binary

    // Example IV (8 bytes)
    uint8_t iv[8] = {0xAA}; // 1010 1010 in binary

    // Example plaintext (must be a multiple of 8 bytes)
    uint8_t plaintext[8] = {0x01, 0x23};  // 0000 0001 0010 0011 in binary
    size_t plaintext_length = sizeof(plaintext);
    
    uint8_t encrypted[8];
    uint8_t decrypted[8];

    // Encrypt in CBC mode
    sdes_cbc_encrypt(plaintext, encrypted, key, iv, plaintext_length);
    print_binary("CBC Encrypted: ", encrypted, plaintext_length);

    // Decrypt in CBC mode
    sdes_cbc_decrypt(encrypted, decrypted, key, iv, plaintext_length);
    print_binary("CBC Decrypted: ", decrypted, plaintext_length);

    return 0;
}
