#include <stdio.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

int main() {
    RSA *keypair = RSA_generate_key(2048, 3, NULL, NULL);
    char *msg = "User A's message";
    unsigned char encrypted[256];
    unsigned char decrypted[256];

    RSA_public_encrypt(strlen(msg), (unsigned char*)msg, encrypted, keypair, RSA_PKCS1_OAEP_PADDING);
    printf("Encrypted: %s\n", encrypted);

    RSA_private_decrypt(256, encrypted, decrypted, keypair, RSA_PKCS1_OAEP_PADDING);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
