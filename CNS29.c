#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 1024
#define CAPACITY 512
#define LANE_SIZE 64
#define NUM_LANES (BLOCK_SIZE / LANE_SIZE)

int main() {
    uint64_t state[NUM_LANES] = {0}; // Initialize internal state matrix
    int num_zero_lanes = CAPACITY / LANE_SIZE; // Initialize number of zero lanes

    // Simulate message blocks
int block;
for (block = 0; block < 1000; block++) {
        // Assume each lane in the first message block has at least one nonzero bit
        int i;
		for (i = 0; i < NUM_LANES; i++) {
            state[i] ^= 1; // Simulate XOR with message block
        }

        // Count number of zero lanes
        int new_num_zero_lanes = 0;
		for (i = 0; i < NUM_LANES; i++) {
            if (state[i] == 0 && i < CAPACITY/ LANE_SIZE)
                new_num_zero_lanes++;
        }
        num_zero_lanes = new_num_zero_lanes;

        printf("Block %d: %d zero lanes\n", block, num_zero_lanes);

        // Stop when all lanes have at least one nonzero bit
        if (num_zero_lanes == 0)
            break;
    }

    return 0;
}

