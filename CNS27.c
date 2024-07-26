#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Function to encrypt a message using RSA
uint64_t rsa_encrypt(uint64_t message, uint64_t e, uint64_t n) {
    uint64_t ciphertext = 1;
    int i;
	for (i = 0; i < e; i++)
        ciphertext = (ciphertext * message) % n;
    return ciphertext;
}

int main() {
    uint64_t n = 3233; // Large modulus
    uint64_t e = 65537; // Large public exponent

    char message[] = "HELLO"; // Message to encrypt
    uint64_t encrypted_message[strlen(message)];

    // Encrypt each character separately
    int i;
	for (i = 0; i < strlen(message); i++) {
        uint64_t plaintext = message[i] - 'A'; // Convert character to integer (0-25)
        encrypted_message[i] = rsa_encrypt(plaintext, e, n);
        printf("Encrypted character %c: %llu\n", message[i], encrypted_message[i]);
    }
return 0;
}
