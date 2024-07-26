#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to generate the monoalphabetic cipher alphabet based on a keyword
void generate_cipher_alphabet(const char *keyword, char cipher_alphabet[])
{
    int used[26] = {0}; // Array to track used letters
    int key_len = strlen(keyword);
    int i, j;

    // Initialize the cipher alphabet with the keyword
    strcpy(cipher_alphabet, keyword);

    // Mark characters from the keyword as used
    for (i = 0; i < key_len; i++) {
        if (isalpha(keyword[i])) {
            used[toupper(keyword[i]) - 'A'] = 1;
        }
    }

    // Append unused characters in normal order
    j = key_len;
    for (i = 0; i < 26; i++) {
        if (!used[i]) {
            cipher_alphabet[j++] = 'A' + i;
        }
    }

    // Null-terminate the cipher alphabet string
    cipher_alphabet[j] = '\0';
}

// Function to encrypt plaintext using monoalphabetic substitution cipher
void monoalphabetic_encrypt(char plaintext[], const char cipher_alphabet[], char ciphertext[])
{
    int i;
    int len = strlen(plaintext);

    // Encrypt each character in plaintext
    for (i = 0; i < len; i++) {
        char c = plaintext[i];

        if (isalpha(c)) {
            if (isupper(c)) {
                ciphertext[i] = cipher_alphabet[c - 'A'];
            } else {
                ciphertext[i] = tolower(cipher_alphabet[toupper(c) - 'A']);
            }
        } else {
            ciphertext[i] = c; // Non-alphabetic characters remain unchanged
        }
    }
    ciphertext[i] = '\0';
}

int main()
{
    char keyword[] = "CIPHER";
    char plaintext[] = "Hello, World!";
    char cipher_alphabet[27]; // 26 letters + null terminator
    char ciphertext[1000];

    // Generate the monoalphabetic cipher alphabet from the keyword
    generate_cipher_alphabet(keyword, cipher_alphabet);

    // Output the generated cipher alphabet (for verification)
    printf("Generated cipher alphabet: %s\n", cipher_alphabet);

    // Encrypt the plaintext using the generated cipher alphabet
    monoalphabetic_encrypt(plaintext, cipher_alphabet, ciphertext);

    // Output the encrypted ciphertext
    printf("Encrypted ciphertext: %s\n", ciphertext);

    return 0;
}

