#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Permutation tables and shift schedule for DES
static const int PC1[56] = {57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18, 10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36, 63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22, 14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4};
static const int PC2[48] = {14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2, 41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32};
static const int shift_schedule[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

// Permutation function
uint64_t permute(uint64_t input, const int* table, int size) {
    uint64_t output = 0;
    for (int i = 0; i < size; i++) {
        output <<= 1;
        output |= (input >> (64 - table[i])) & 0x1;
    }
    return output;
}

// Key generation function
void generate_keys(uint64_t key, uint64_t* subkeys) {
    uint64_t permuted_key = permute(key, PC1, 56);
    uint32_t C = (permuted_key >> 28) & 0xFFFFFFF;
    uint32_t D = permuted_key & 0xFFFFFFF;

    for (int i = 0; i < 16; i++) {
        int shift = shift_schedule[i];
        C = ((C << shift) | (C >> (28 - shift))) & 0xFFFFFFF;
        D = ((D << shift) | (D >> (28 - shift))) & 0xFFFFFFF;

        uint64_t combined_key = ((uint64_t)C << 28) | D;
        subkeys[i] = permute(combined_key, PC2, 48);
    }
}

// Main function
int main() {
    uint64_t key = 0x133457799BBCDFF1;  // Example key
    uint64_t subkeys[16];

    generate_keys(key, subkeys);

    // Print subkeys
    for (int i = 0; i < 16; i++) {
        printf("Subkey %d: %016llX\n", i + 1, subkeys[i]);
    }

    return 0;
}
