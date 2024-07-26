#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define MAX_CIPHERTEXT_LENGTH 1000
#define TOP_N 10

// English letter frequency distribution (simplified)
const double english_freq[ALPHABET_SIZE] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153,
    0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.316, 9.056,
    2.758, 0.978, 2.360, 0.150, 1.929, 0.074
};

// Function to convert a character to its corresponding index (A=0, B=1, ..., Z=25)
int char_to_index(char c) {
    return toupper(c) - 'A';
}

// Function to convert an index to its corresponding character
char index_to_char(int index) {
    return index + 'A';
}

// Function to calculate letter frequencies in a text
void calculate_frequencies(const char* text, double freq[ALPHABET_SIZE]) {
    int count[ALPHABET_SIZE] = {0};
    int length = strlen(text);

    for (int i = 0; i < length; i++) {
        if (isalpha(text[i])) {
            int index = char_to_index(text[i]);
            count[index]++;
        }
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freq[i] = (count[i] * 100.0) / length;
    }
}

// Function to score a frequency distribution based on English letter frequencies
double score_frequency(const double freq[ALPHABET_SIZE]) {
    double score = 0.0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        score -= (freq[i] - english_freq[i]) * (freq[i] - english_freq[i]);
    }
    return score;
}

// Function to decrypt a ciphertext using a given key permutation
void decrypt(const char* ciphertext, const int* key, char* plaintext) {
    int length = strlen(ciphertext);
    for (int i = 0; i < length; i++) {
        if (isalpha(ciphertext[i])) {
            int index = char_to_index(ciphertext[i]);
            plaintext[i] = index_to_char(key[index]);
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[length] = '\0';
}

// Function to generate permutations of the alphabet
void permute(int* key, int start, int end, const char* ciphertext, double* best_scores, char best_plaintexts[][MAX_CIPHERTEXT_LENGTH], int top_n) {
    if (start == end) {
        char plaintext[MAX_CIPHERTEXT_LENGTH];
        double freq[ALPHABET_SIZE];
        calculate_frequencies(plaintext, freq);
        double score = score_frequency(freq);
        int index = 0;
        while (index < top_n && best_scores[index] > score) {
            index++;
        }
        if (index < top_n) {
            for (int i = top_n - 1; i > index; i--) {
                best_scores[i] = best_scores[i - 1];
                strcpy(best_plaintexts[i], best_plaintexts[i - 1]);
            }
            best_scores[index] = score;
            strcpy(best_plaintexts[index], plaintext);
        }
        return;
    }
    for (int i = start; i <= end; i++) {
        int temp = key[start];
        key[start] = key[i];
        key[i] = temp;
        permute(key, start + 1, end, ciphertext, best_scores, best_plaintexts, top_n);
        key[i] = key[start];
        key[start] = temp;
    }
}

// Main function
int main() {
    char ciphertext[MAX_CIPHERTEXT_LENGTH];
    int top_n;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; // Remove newline character

    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &top_n);

    if (top_n > TOP_N) {
        top_n = TOP_N;
    }

    // Initialize key as a permutation of the alphabet
    int key[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        key[i] = i;
    }

    double best_scores[TOP_N];
    char best_plaintexts[TOP_N][MAX_CIPHERTEXT_LENGTH];

    for (int i = 0; i < TOP_N; i++) {
        best_scores[i] = -1;
    }

    permute(key, 0, ALPHABET_SIZE - 1, ciphertext, best_scores, best_plaintexts, top_n);

    printf("Top %d possible plaintexts:\n", top_n);
    for (int i = 0; i < top_n; i++) {
        printf("Possible plaintext #%d (Score: %.2f): %s\n", i + 1, best_scores[i], best_plaintexts[i]);
    }

    return 0;
}
