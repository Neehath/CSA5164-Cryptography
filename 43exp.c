#include <stdio.h>
#include <openssl/aes.h>

int main() {
    AES_KEY enc_key, dec_key;
    unsigned char key[16] = "AESKeyExample12";
    unsigned char input[] = "welcome to CSE";
    unsigned char enc_out[16], dec_out[16];

    AES_set_encrypt_key(key, 128, &enc_key);
    AES_encrypt(input, enc_out, &enc_key);
    printf("Encrypted: ");
    for (int i = 0; i < 16; i++) printf("%02X", enc_out[i]);
    
    AES_set_decrypt_key(key, 128, &dec_key);
    AES_decrypt(enc_out, dec_out, &dec_key);
    printf("\nDecrypted: %s\n", dec_out);
    
    return 0;
}
