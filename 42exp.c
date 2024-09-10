#include <stdio.h>
#include <openssl/des.h>

int main() {
    DES_cblock key = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};
    DES_key_schedule schedule;
    DES_set_key_unchecked(&key, &schedule);

    const char *message = "Meet me very urgently";
    unsigned char encrypted[24];
    unsigned char decrypted[24];

    DES_ecb_encrypt((DES_cblock*)message, (DES_cblock*)encrypted, &schedule, DES_ENCRYPT);
    printf("Encrypted: %s\n", encrypted);

    DES_ecb_encrypt((DES_cblock*)encrypted, (DES_cblock*)decrypted, &schedule, DES_DECRYPT);
    printf("Decrypted: %s\n", decrypted);
    
    return 0;
}
