#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Function to calculate GCD using Euclid's algorithm
uint64_t gcd(uint64_t a, uint64_t b) {
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}

// Function to calculate the multiplicative inverse
uint64_t mod_inverse(uint64_t a, uint64_t m) {
    uint64_t m0 = m, x0 = 0, x1 = 1;
    while (a > 1) {
        uint64_t q = a / m;
        uint64_t t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    return x1 + m0;
}

void generate_new_keys(uint64_t *e, uint64_t *d, uint64_t p, uint64_t q) {
    uint64_t n = p * q;
    uint64_t phi = (p - 1) * (q - 1);
    *e = 65537; // Common public exponent
    *d = mod_inverse(*e, phi);
}

int main() {
    uint64_t p = 61; // Bob's original prime
    uint64_t q = 53; // Bob's original prime
    uint64_t e, d; // Bob's original keys

    generate_new_keys(&e, &d, p, q);
    printf("Bob's original keys: e = %llu, d = %llu\n", e, d);

    // Bob leaks his private key and generates a new key pair
    uint64_t p_new = 67; // Bob's new prime
    uint64_t q_new = 59; // Bob's new prime
    uint64_t e_new, d_new; // Bob's new keys

    generate_new_keys(&e_new, &d_new, p_new, q_new);
    printf("Bob's new keys: e = %llu, d = %llu\n", e_new, d_new);

    // Attack: Use the leaked private key to factorize n
    uint64_t n = p * q;
    uint64_t factor = gcd(n, p_new * q_new);
    printf("Factor: %llu\n", factor);

    return 0;
}

