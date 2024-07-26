#include <stdio.h>
#include <stdlib.h>

#define MATRIX_SIZE 2
#define ALPHABET_SIZE 26
int char_to_index(char c) {
    return c - 'A';
}
char index_to_char(int index) {
    return index + 'A';
}
void solve_key_matrix(int plaintext[MATRIX_SIZE][MATRIX_SIZE], int ciphertext[MATRIX_SIZE][MATRIX_SIZE], int key[MATRIX_SIZE][MATRIX_SIZE]) {
    int A[4] = {plaintext[0][0], plaintext[0][1], plaintext[1][0], plaintext[1][1]};
    int B[4] = {ciphertext[0][0], ciphertext[0][1], ciphertext[1][0], ciphertext[1][1]};
    int determinant = A[0] * A[3] - A[1] * A[2];
    determinant = (determinant % ALPHABET_SIZE + ALPHABET_SIZE) % ALPHABET_SIZE; // Ensure positive
    int inv_det = 0;
    for (int i = 1; i < ALPHABET_SIZE; i++) {
        if ((determinant * i) % ALPHABET_SIZE == 1) {
            inv_det = i;
            break;
        }
    }
    
    int A_inv[4];
    A_inv[0] = A[3] * inv_det % ALPHABET_SIZE;
    A_inv[1] = -A[1] * inv_det % ALPHABET_SIZE;
    A_inv[2] = -A[2] * inv_det % ALPHABET_SIZE;
    A_inv[3] = A[0] * inv_det % ALPHABET_SIZE;
    for (int i = 0; i < 4; i++) {
        A_inv[i] = (A_inv[i] + ALPHABET_SIZE) % ALPHABET_SIZE;
    }
    key[0][0] = (A_inv[0] * B[0] + A_inv[1] * B[2]) % ALPHABET_SIZE;
    key[0][1] = (A_inv[0] * B[1] + A_inv[1] * B[3]) % ALPHABET_SIZE;
    key[1][0] = (A_inv[2] * B[0] + A_inv[3] * B[2]) % ALPHABET_SIZE;
    key[1][1] = (A_inv[2] * B[1] + A_inv[3] * B[3]) % ALPHABET_SIZE;
}
void print_matrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%2d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int plaintext[MATRIX_SIZE][MATRIX_SIZE] = {
        {char_to_index('M'), char_to_index('E')},
        {char_to_index('E'), char_to_index('T')}
    };
    int ciphertext[MATRIX_SIZE][MATRIX_SIZE] = {
        {char_to_index('G'), char_to_index('S')},
        {char_to_index('S'), char_to_index('D')}
    };
    
    int key[MATRIX_SIZE][MATRIX_SIZE];
    solve_key_matrix(plaintext, ciphertext, key);
    printf("Recovered Key Matrix:\n");
    print_matrix(key);
    
    return 0;
}
