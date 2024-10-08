#include <stdio.h>
#include <stdint.h>

// Initial and final permutation tables
int IP[64] = {58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4, 
              62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8, 
              57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3, 
              61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7};

int FP[64] = {40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31, 
              38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29, 
              36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27, 
              34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25};

// Permutation choice 1 and 2 tables
int PC1[56] = {57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18, 10, 2, 
               59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36, 63, 55, 47, 39, 
               31, 23, 15, 7, 62, 54, 46, 38, 30, 22, 14, 6, 61, 53, 45, 37, 
               29, 21, 13, 5, 28, 20, 12, 4};

int PC2[48] = {14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19, 12, 4, 
               26, 8, 16, 7, 27, 20, 13, 2, 41, 52, 31, 37, 47, 55, 30, 40, 
               51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32};

// Shift schedule for key generation
int shift_schedule[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

// Expand table (32-bit to 48-bit)
int E[48] = {32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10, 11, 12, 13, 
             12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 
             24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1};

// Permutation function P
int P[32] = {16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10, 
             2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25};

// S-boxes (S1-S8)
int S[8][4][16] = {
    {{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
     {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
     {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
     {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}},

    {{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
     {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
     {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
     {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}},

    {{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
     {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
     {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
     {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}},

    {{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
     {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
     {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
     {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}},

    {{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
     {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
     {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
     {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}},

    {{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
     {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
     {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
     {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}},

    {{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
     {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
     {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
     {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}},

    {{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
     {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
     {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
     {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}}
};

// Function to permute bits based on a table
uint64_t permute(uint64_t input, const int* table, int size) {
    uint64_t output = 0;
    for (int i = 0; i < size; i++) {
        output <<= 1;
        output |= (input >> (64 - table[i])) & 0x1;
    }
    return output;
}

// Function to apply the S-boxes
uint32_t Sbox(uint64_t input) {
    uint32_t output = 0;
    for (int i = 0; i < 8; i++) {
        uint8_t block = (input >> (42 - 6 * i)) & 0x3F;
        uint8_t row = ((block >> 4) & 0x2) | (block & 0x1);
        uint8_t col = (block >> 1) & 0xF;
        output <<= 4;
        output |= S[i][row][col];
    }
    return output;
}

// Feistel function
uint32_t f(uint32_t R, uint64_t K) {
    uint64_t expanded_R = permute(R, E, 48);
    uint64_t xor_result = expanded_R ^ K;
    uint32_t sbox_result = Sbox(xor_result);
    return permute(sbox_result, P, 32);
}

// DES encryption/decryption function
uint64_t DES(uint64_t input, uint64_t* subkeys, int decrypt) {
    input = permute(input, IP, 64);
    uint32_t L = (input >> 32) & 0xFFFFFFFF;
    uint32_t R = input & 0xFFFFFFFF;

    for (int i = 0; i < 16; i++) {
        int round = decrypt ? 15 - i : i;
        uint32_t new_R = L ^ f(R, subkeys[round]);
        L = R;
        R = new_R;
    }

    uint64_t pre_output = ((uint64_t)R << 32) | L;
    return permute(pre_output, FP, 64);
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
    uint64_t key = 0x133457799BBCDFF1;
    uint64_t subkeys[16];
    generate_keys(key, subkeys);

    uint64_t plaintext = 0x0123456789ABCDEF;
    uint64_t ciphertext = DES(plaintext, subkeys, 0);
    printf("Ciphertext: %016lX\n", ciphertext);

    uint64_t decrypted = DES(ciphertext, subkeys, 1);
    printf("Decrypted text: %016lX\n", decrypted);

    return 0;
}
