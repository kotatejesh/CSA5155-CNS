#include <stdio.h>
#include <string.h>

#define ALPHABET_SIZE 26
int char_to_index(char c) {
    return c - 'A';
}
char index_to_char(int index) {
    return index + 'A';
}
void encrypt(const char* plaintext, const int* key, int key_length, char* ciphertext) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            int pt_index = char_to_index(plaintext[i]);
            int key_index = key[i % key_length];
            int ct_index = (pt_index + key_index) % ALPHABET_SIZE;
            ciphertext[i] = index_to_char(ct_index);
        } else {
            ciphertext[i] = plaintext[i]; 
        }
    }
    ciphertext[len] = '\0';
}
void find_key(const char* ciphertext, const char* plaintext, int* key, int key_length) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z' && plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            int ct_index = char_to_index(ciphertext[i]);
            int pt_index = char_to_index(plaintext[i]);
            key[i % key_length] = (ct_index - pt_index + ALPHABET_SIZE) % ALPHABET_SIZE;
        }
    }
}

int main() {
    const char* plaintext = "SEND MORE MONEY";
    int key_stream[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    int key_length = sizeof(key_stream) / sizeof(key_stream[0]);
    char ciphertext[sizeof(plaintext) / sizeof(plaintext[0])];

    encrypt(plaintext, key_stream, key_length, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);
    const char* target_plaintext = "CASH NOT NEEDED";
    int key_found[key_length];
    find_key(ciphertext, target_plaintext, key_found, key_length);

    printf("Key stream for decryption:\n");
    for (int i = 0; i < key_length; i++) {
        printf("%d ", key_found[i]);
    }
    printf("\n");

    return 0;
}
