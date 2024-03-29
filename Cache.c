#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RAM_SIZE 1048576    // 2^20 words
#define CACHE_SIZE 16       // Number of blocks in cache
#define BLOCK_SIZE 4        // Number of words in a block
#define WORD_SIZE 4         // Size of a word in bytes

typedef struct {
    int valid;  // Valid bit
    int tag;    // Tag field
} CacheBlock;

// Cache array
CacheBlock cache[CACHE_SIZE];

// Function to initialize cache
void initialize_cache() {
    for (int i = 0; i < CACHE_SIZE; i++) {
        cache[i].valid = 0; // Set valid bit to 0 to indicate invalid blocks
    }
}

// Function to simulate cache access
void access_cache(int address) {
    int index = (address / WORD_SIZE) % CACHE_SIZE; // Calculate index of cache block
    int tag = address / (WORD_SIZE * CACHE_SIZE);   // Calculate tag of address
    
    // Check if the cache block at the calculated index contains the requested data
    if (cache[index].valid && cache[index].tag == tag) {
        printf("Hit\n");
    } else {
        printf("Miss\n");
        // Update cache block with new tag
        cache[index].valid = 1;
        cache[index].tag = tag;
    }
}

int main() {
    srand(time(NULL)); // Seed for random number generation

    initialize_cache();

    // Test 1: Sequential access to every word in RAM
    printf("Test 1:\n");
    int hits = 0, misses = 0;
    for (int i = 0; i < RAM_SIZE; i++) {
        access_cache(i * WORD_SIZE);
    }

    // Test 2: Access every word in RAM in increments of the block size
    printf("\nTest 2:\n");
    initialize_cache(); // Reset cache for the next test
    for (int i = 0; i < RAM_SIZE; i += BLOCK_SIZE) {
        access_cache(i * WORD_SIZE);
    }

    // Test 3: Random access to words in RAM
    printf("\nTest 3:\n");
    initialize_cache(); // Reset cache for the next test
    for (int i = 0; i < RAM_SIZE; i++) {
        int random_address = rand() % RAM_SIZE * WORD_SIZE;
        access_cache(random_address);
    }

    return 0;
}
