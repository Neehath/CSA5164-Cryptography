#include <stdio.h>
#include <stdint.h>
#include <math.h>

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
    int n = 3599; // Example n
    int e = 31;   // Example public exponent
    int m = 59;   // Example plaintext block (this should be known to share common factor with n)

    // Find common factor with n
    int common_factor = gcd(m, n);

    // If common factor is found, factorize n
    if (common_factor > 1 && common_factor < n) {
        printf("Common factor found: %d\n", common_factor);

        int p = common_factor;
        int q = n / p;

        printf("p = %d, q = %d\n", p, q);

        // Compute φ(n) = (p - 1) * (q - 1)
        int phi = (p - 1) * (q - 1);
        printf("φ(n) = %d\n", phi);

        // Compute d, the modular inverse of e modulo φ(n)
        int d = mod_inverse(e, phi);
        if (d == -1) {
            printf("No modular inverse exists.\n");
            return 1;
        }

        printf("Private key d = %d\n", d);
    } else {
        printf("No common factor found.\n");
    }

    return 0;
}
