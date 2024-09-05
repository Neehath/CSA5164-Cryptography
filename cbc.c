#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <openssl/des.h>

// Function to apply 3DES encryption in CBC mode
void triple_des_encrypt_cbc(const uint8_t *data, uint8_t *encrypted, const uint8_t *key, const uint8_t *iv, size_t length) {
    DES_key_schedule ks1, ks2, ks3;
    DES_cblock key1, key2, key3;
    DES_cblock ivec;
    DES_cblock input_block;
    DES_cblock output_block;

    // Set the 3DES keys
    memcpy(key1, key, 8);
    memcpy(key2, key + 8, 8);
    memcpy(key3, key + 16, 8);

    DES_set_key_unchecked(&key1, &ks1);
    DES_set_key_unchecked(&key2, &ks2);
    DES_set_key_unchecked(&key3, &ks3);

    // Set the IV
    memcpy(ivec, iv, 8);

    // CBC mode encryption
    DES_cbc_encrypt(data, encrypted, length, &ks1, &ivec, DES_ENCRYPT);
    DES_cbc_encrypt(encrypted, encrypted, length, &ks2, &ivec, DES_DECRYPT);
    DES_cbc_encrypt(encrypted, encrypted, length, &ks3, &ivec, DES_ENCRYPT);
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
    // Example key and IV (16 bytes key for 3DES)
    const uint8_t key[24] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 
                             0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10, 
                             0x0F, 0x1E, 0x2D, 0x3C, 0x4B, 0x5A, 0x69, 0x78};
    const uint8_t iv[8] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
    
    // Example plaintext (must be a multiple of 8 bytes)
    uint8_t plaintext[16] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 
                             0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10};
    uint8_t encrypted[16];

    // Encrypt the plaintext
    triple_des_encrypt_cbc(plaintext, encrypted, key, iv, sizeof(plaintext));
    
    // Print the results
    print_hex("Plaintext: ", plaintext, sizeof(plaintext));
    print_hex("Encrypted: ", encrypted, sizeof(encrypted));
    
    return 0;
}
