#include <stdio.h>

int main() {
    char *str = "Hello world";
    for (int i = 0; str[i] != '\0'; i++) {
        printf("%c", str[i] ^ 0);
    }
    return 0;
}
