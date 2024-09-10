#include <stdio.h>
#include <openssl/des.h>

int main() {
    DES_cblock key = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};
    DES_key_schedule schedule;
    DES_set_key_unchecked(&key, &schedule);

    const char *message = "HelloWorld";
    unsigned char output[8];

    DES_ecb_encrypt((DES_cblock*)message, (DES_cblock*)output, &schedule, DES_ENCRYPT);
    printf("Encrypted: ");
    for (int i = 0; i < 8; i++) {
        printf("%02X", output[i]);
    }
    printf("\n");
    return 0;
}
