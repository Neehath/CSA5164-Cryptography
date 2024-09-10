#include <stdio.h>
#include <string.h>

void rail_fence_encrypt(char *message, int rails) {
    int len = strlen(message);
    char rail[rails][len];
    
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < len; j++) {
            rail[i][j] = '\n';
        }
    }

    int row = 0, down = 1;
    for (int i = 0; i < len; i++) {
        rail[row][i] = message[i];
        if (row == 0) down = 1;
        else if (row == rails - 1) down = 0;
        row = down ? row + 1 : row - 1;
    }

    printf("Encrypted: ");
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < len; j++) {
            if (rail[i][j] != '\n') printf("%c", rail[i][j]);
        }
    }
    printf("\n");
}

int main() {
    char message[] = "RAILFENCE";
    int rails = 3;
    rail_fence_encrypt(message, rails);
    return 0;
}
