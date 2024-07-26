#include <stdio.h>
#include <string.h>

#define KEY_SIZE 2
#define MOD 26

void encrypt(char* plaintext, int key[KEY_SIZE][KEY_SIZE], char* ciphertext) {
    int i, j, k;
    for (i = 0; i < strlen(plaintext); i += 2) {
        int x = plaintext[i] - 'a';
        int y = plaintext[i + 1] - 'a';
        ciphertext[j = 2 * i / 2] = (key[0][0] * x + key[0][1] * y) % MOD + 'a';
        ciphertext[j + 1] = (key[1][0] * x + key[1][1] * y) % MOD + 'a';
    }
    ciphertext[strlen(plaintext)] = '\0';
}

void decrypt(char* ciphertext, int key[KEY_SIZE][KEY_SIZE], char* plaintext) {
    int i, j, k;
    int det = key[0][0] * key[1][1] - key[0][1] * key[1][0];
    int inv_det = 0;
    for (inv_det = 1; (inv_det * det) % MOD != 1; inv_det++);
    int inv_key[KEY_SIZE][KEY_SIZE] = {
        (key[1][1] * inv_det) % MOD,
        (-key[0][1] * inv_det) % MOD,
        (-key[1][0] * inv_det) % MOD,
        (key[0][0] * inv_det) % MOD
    };
    for (i = 0; i < strlen(ciphertext); i += 2) {
        int x = ciphertext[i] - 'a';
        int y = ciphertext[i + 1] - 'a';
        plaintext[j = 2 * i / 2] = (inv_key[0][0] * x + inv_key[0][1] * y) % MOD + 'a';
        plaintext[j + 1] = (inv_key[1][0] * x + inv_key[1][1] * y) % MOD + 'a';
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    char plaintext[] = "9 4 5 7";
    int key[KEY_SIZE][KEY_SIZE] = {{9, 4}, {5, 7}};
    char ciphertext[strlen(plaintext) + 1];
    encrypt(plaintext, key, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    char decrypted[strlen(ciphertext) + 1];
    decrypt(ciphertext, key, decrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}