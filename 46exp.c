#include <stdio.h>
#include <string.h>

void frequency_analysis(char *ciphertext) {
    int freq[26] = {0};
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            freq[ciphertext[i] - 'a']++;
        }
    }
    for (int i = 0; i < 26; i++) {
        printf("%c: %d\n", 'a' + i, freq[i]);
    }
}

int main() {
    char ciphertext[] = "cxknxawxccxkncqjcrbcqnzdnbcrxwfruurjvbqjtnbynjan";
    frequency_analysis(ciphertext);
    return 0;
}
