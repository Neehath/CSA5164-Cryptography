#include <stdio.h>

int main() {
    char *str = "Hello world";
    for (int i = 0; str[i] != '\0'; i++) {
        printf("AND: %c, XOR: %c\n", str[i] & 127, str[i] ^ 127);
    }
    return 0;
}
