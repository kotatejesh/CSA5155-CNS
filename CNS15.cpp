#include <stdio.h>
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

// Function to calculate letter frequencies in a text
void calculate_frequencies(const char* text, double freq[ALPHABET_SIZE]) {
    int count[ALPHABET_SIZE] = {0};
    int length = strlen(text);
    
    for (int i = 0; i < length; i++) {
        if (isalpha(text[i])) {
            int index = toupper(text[i]) - 'A';
            count[index]++;
        }
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freq[i] = (count[i] * 100.0) / length;
    }
}

// Function to decrypt a ciphertext with a given shift
void decrypt(const char* ciphertext, int shift, char* plaintext) {
    int length = strlen(ciphertext);
    for (int i = 0; i < length; i++) {
        if (isalpha(ciphertext[i])) {
            int index = toupper(ciphertext[i]) - 'A';
            int new_index = (index - shift + ALPHABET_SIZE) % ALPHABET_SIZE;
            plaintext[i] = new_index + 'A';
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[length] = '\0';
}

// Function to calculate the score based on frequency match
double score_frequency(const double freq[ALPHABET_SIZE]) {
    double score = 0.0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        score -= (freq[i] - english_freq[i]) * (freq[i] - english_freq[i]);
    }
    return score;
}

// Function to perform the frequency attack and display top N results
void frequency_attack(const char* ciphertext, int top_n) {
    char plaintext[MAX_CIPHERTEXT_LENGTH];
    double freq[ALPHABET_SIZE];
    double scores[ALPHABET_SIZE];
    char results[ALPHABET_SIZE][MAX_CIPHERTEXT_LENGTH];
    
    for (int shift = 0; shift < ALPHABET_SIZE; shift++) {
        decrypt(ciphertext, shift, plaintext);
        calculate_frequencies(plaintext, freq);
        scores[shift] = score_frequency(freq);
        strcpy(results[shift], plaintext);
    }
    
    // Find top N results
    for (int i = 0; i < top_n; i++) {
        int best_index = 0;
        for (int j = 1; j < ALPHABET_SIZE; j++) {
            if (scores[j] > scores[best_index]) {
                best_index = j;
            }
        }
        printf("Possible plaintext #%d (Shift %d): %s\n", i + 1, best_index, results[best_index]);
        scores[best_index] = -1; // Mark as used
    }
}

int main() {
    char ciphertext[MAX_CIPHERTEXT_LENGTH];
    int top_n;
    
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; 
    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &top_n);
    
    if (top_n > TOP_N) {
        top_n = TOP_N;
    }
    
    frequency_attack(ciphertext, top_n);
    
    return 0;
}
