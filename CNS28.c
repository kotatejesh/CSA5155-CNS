#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Function to calculate the power of a number modulo q
uint64_t power_mod(uint64_t base, uint64_t exponent, uint64_t q) {
    uint64_t result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % q;
        exponent /= 2;
        base = (base * base) % q;
    }
    return result;
}

int main() {
    uint64_t q = 23; // Public prime number
    uint64_t a = 5; // Public base number

    // Alice selects a secret number x and sends Bob ax mod q
    uint64_t x = 6;
    uint64_t A = power_mod(a, x, q);
    printf("Alice sends Bob: %llu\n", A);
uint64_t y = 15;
    uint64_t B = power_mod(a, y, q);
    printf("Bob sends Alice: %llu\n", B);

    // Alice computes the shared secret key
    uint64_t k_alice = power_mod(B, x, q);
    printf("Alice's shared secret key: %llu\n", k_alice);

    // Bob computes the shared secret key
    uint64_t k_bob = power_mod(A, y, q);
    printf("Bob's shared secret key: %llu\n", k_bob);

    return 0;
}

