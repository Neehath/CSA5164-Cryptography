#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <openssl/des.h>

// Function to apply 3DES encryption in ECB mode
void triple_des_encrypt_ecb(const uint8_t *data, uint8_t *encrypted, const uint8_t *key, size_t length) {
    DES_key_schedule ks1, ks2, ks3;
    DES_cblock key1, key2, key3;

    memcpy(key1, key, 8);
    memcpy(key2, key + 8, 8);
    memcpy(key3, key + 16, 8);

    DES_set_key_unchecked(&key1, &ks1);
    DES_set_key_unchecked(&key2, &ks2);
    DES_set_key_unchecked(&key3, &ks3);

    for (size_t i = 0; i < length; i += 8) {
        DES_cblock block;
        memcpy(block, data + i, 8);

        DES_ecb_encrypt(&block, &block, &ks1, DES_ENCRYPT);
        DES_ecb_encrypt(&block, &block, &ks2, DES_DECRYPT);
        DES_ecb_encrypt(&block, &block, &ks3, DES_ENCRYPT);

        memcpy(encrypted + i, block, 8);
    }
}

// Function to apply 3DES encryption in CBC mode
void triple_des_encrypt_cbc(const uint8_t *data, uint8_t *encrypted, const uint8_t *key, const uint8_t *iv, size_t length) {
    DES_key_schedule ks1, ks2, ks3;
    DES_cblock key1, key2, key3;
    DES_cblock ivec;

    memcpy(key1, key, 8);
    memcpy(key2, key + 8, 8);
    memcpy(key3, key + 16, 8);

    DES_set_key_unchecked(&key1, &ks1);
    DES_set_key_unchecked(&key2, &ks2);
    DES_set_key_unchecked(&key3, &ks3);

    memcpy(ivec, iv, 8);

    for (size_t i = 0; i < length; i += 8) {
        DES_cblock block;
        memcpy(block, data + i, 8);

        // XOR plaintext with IV or previous ciphertext
        for (int j = 0; j < 8; ++j) {
            block[j] ^= ivec[j];
        }

        DES_ecb_encrypt(&block, &block, &ks1, DES_ENCRYPT);
        DES_ecb_encrypt(&block, &block, &ks2, DES_DECRYPT);
        DES_ecb_encrypt(&block, &block, &ks3, DES_ENCRYPT);

        memcpy(encrypted + i, block, 8);
        memcpy(ivec, encrypted + i, 8);  // Update IV to the ciphertext block
    }
}

// Function to apply 3DES encryption in CFB mode
void triple_des_encrypt_cfb(const uint8_t *data, uint8_t *encrypted, const uint8_t *key, const uint8_t *iv, size_t length) {
    DES_key_schedule ks1, ks2, ks3;
    DES_cblock key1, key2, key3;
    DES_cblock ivec;
    DES_cblock temp;

    memcpy(key1, key, 8);
    memcpy(key2, key + 8, 8);
    memcpy(key3, key + 16, 8);

    DES_set_key_unchecked(&key1, &ks1);
    DES_set_key_unchecked(&key2, &ks2);
    DES_set_key_unchecked(&key3, &ks3);

    memcpy(ivec, iv, 8);

    for (size_t i = 0; i < length; i += 8) {
        DES_cblock block;
        memcpy(block, data + i, 8);

        DES_ecb_encrypt(&ivec, &temp, &ks1, DES_ENCRYPT);
        DES_ecb_encrypt(&temp, &temp, &ks2, DES_DECRYPT);
        DES_ecb_encrypt(&temp, &temp, &ks3, DES_ENCRYPT);

        // XOR the ciphertext with the plaintext
        for (int j = 0; j < 8; ++j) {
            encrypted[j] = block[j] ^ temp[j];
        }

        memcpy(ivec, encrypted + i, 8);  // Update IV to the ciphertext block
    }
}

// Padding function
void pad(uint8_t *data, size_t *length) {
    size_t padding_size = 8 - (*length % 8);
    for (size_t i = *length; i < *length + padding_size; ++i) {
        data[i] = (uint8_t)padding_size;
    }
    *length += padding_size;
}

// Remove padding function
void unpad(uint8_t *data, size_t *length) {
    size_t padding_size = data[*length - 1];
    if (padding_size > 0 && padding_size <= 8) {
        *length -= padding_size;
    }
}

// Helper function to print data in hex format
void print_hex(const char *label, const uint8_t *data, size_t length) {
    printf("%s", label);
    for (size_t i = 0; i < length; i++) {
        printf("%02X", data[i]);
    }
    printf("\n");
}

int main() {
    // Example key (24 bytes key for 3DES)
    const uint8_t key[24] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 
                             0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10, 
                             0x0F, 0x1E, 0x2D, 0x3C, 0x4B, 0x5A, 0x69, 0x78};
    const uint8_t iv[8] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

    // Example plaintext (must be a multiple of 8 bytes)
    uint8_t plaintext[16] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 
                             0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10};
    size_t plaintext_length = sizeof(plaintext);
    uint8_t padded_plaintext[32];  // Buffer to hold padded plaintext
    uint8_t encrypted[32];
    uint8_t decrypted[32];

    // Copy plaintext to padded buffer and pad
    memcpy(padded_plaintext, plaintext, plaintext_length);
    pad(padded_plaintext, &plaintext_length);

    // Encrypt in ECB mode
    triple_des_encrypt_ecb(padded_plaintext, encrypted, key, plaintext_length);
    print_hex("ECB Encrypted: ", encrypted, plaintext_length);

    // Decrypt in ECB mode (for demonstration)
    triple_des_encrypt_ecb(encrypted, decrypted, key, plaintext_length);  // Using the same function for decryption
    unpad(decrypted, &plaintext_length);
    print_hex("ECB Decrypted: ", decrypted, plaintext_length);

    // Encrypt in CBC mode
    triple_des_encrypt_cbc(padded_plaintext, encrypted, key, iv, plaintext_length);
    print_hex("CBC Encrypted: ", encrypted, plaintext_length);

    // Decrypt in CBC mode (for demonstration)
    triple_des_encrypt_cbc(encrypted, decrypted, key, iv, plaintext_length);  // Using the same function for decryption
    unpad(decrypted, &plaintext_length);
    print_hex("CBC Decrypted: ", decrypted, plaintext_length);

    // Encrypt in CFB mode
    triple_des_encrypt_cfb(padded_plaintext, encrypted, key, iv, plaintext_length);
    print_hex("CFB Encrypted: ", encrypted, plaintext_length);

    // Decrypt in CFB mode (for demonstration)
    triple_des_encrypt_cfb(encrypted, decrypted, key, iv, plaintext_length);  // Using the same function for decryption
    print_hex("CFB Decrypted: ", decrypted, plaintext_length);

    return 0;
}
