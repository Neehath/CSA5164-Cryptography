#include <stdio.h>

void caesar_cipher(char *message, int shift) {
    for (int i = 0; message[i] != '\0'; i++) {
        char c = message[i];
        if (c >= 'a' && c <= 'z')
            c = ((c - 'a' + shift) % 26) + 'a';
        else if (c >= 'A' && c <= 'Z')
            c = ((c - 'A' + shift) % 26) + 'A';
        printf("%c", c);
    }
    printf("\n");
}

int main() {
    char message[] = "defend the east wall of the castle";
    int key = 1;
    
    printf("Encrypted: ");
    caesar_cipher(message, key);

    printf("Decrypted: ");
    caesar_cipher(message, 26 - key);

    return 0;
}
