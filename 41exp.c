#include <stdio.h>
#include <openssl/blowfish.h>

int main() {
    BF_KEY key;
    unsigned char bf_key[] = "BlowfishKey";
    BF_set_key(&key, sizeof(bf_key), bf_key);

    const char *message = "HelloWorld";
    unsigned char output[8];

    BF_ecb_encrypt((unsigned char*)message, output, &key, BF_ENCRYPT);
    printf("Encrypted: ");
    for (int i = 0; i < 8; i++) {
        printf("%02X", output[i]);
    }
    printf("\n");
    return 0;
}
