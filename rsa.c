#include <stdio.h>

// Function to compute the greatest common divisor using Euclidean Algorithm
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to find the modular inverse using Extended Euclidean Algorithm
int mod_inverse(int e, int phi) {
    int t = 0;
    int new_t = 1;
    int r = phi;
    int new_r = e;
    
    while (new_r != 0) {
        int quotient = r / new_r;
        int temp_t = t;
        t = new_t;
        new_t = temp_t - quotient * new_t;
        
        int temp_r = r;
        r = new_r;
        new_r = temp_r - quotient * new_r;
    }
    
    if (r > 1) {
        return -1; // No modular inverse exists
    }
    
    if (t < 0) {
        t = t + phi;
    }
    
    return t;
}

// Function to factorize n into primes (p and q)
void factorize(int n, int* p, int* q) {
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            *p = i;
            *q = n / i;
            return;
        }
    }
    *p = *q = -1; // Factorization failed
}

int main() {
    int e = 31;
    int n = 3599;
    
    // Step 1: Factorize n
    int p, q;
    factorize(n, &p, &q);
    if (p == -1 || q == -1) {
        printf("Failed to factorize n.\n");
        return 1;
    }
    
    printf("p = %d, q = %d\n", p, q);
    
    // Step 2: Compute φ(n) = (p - 1) * (q - 1)
    int phi = (p - 1) * (q - 1);
    printf("φ(n) = %d\n", phi);
    
    // Step 3: Compute d, the modular inverse of e modulo φ(n)
    int d = mod_inverse(e, phi);
    if (d == -1) {
        printf("No modular inverse exists.\n");
        return 1;
    }
    
    printf("Private key d = %d\n", d);
    
    return 0;
}
