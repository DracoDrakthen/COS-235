// Author: Devon Beal
//
/*
Results of the three tests:

Test 1:
- Hit rate: 75%
- Miss rate: 25%
In Test 1, sequential access to every word in RAM results in a hit rate of 75% and a miss rate of 25%. 
This unexpected hit rate shows that some patterns might be emerging in the memory access, allowing certain blocks to stay in the cache.

Test 2:
- Hit rate: 75%
- Miss rate: 25%
This might not be a fully accurate reprsentation of test 2 if I counted the test wrong.
Despite the patterned access, the hit rate remains consistent with Test 1, the cache's behavior might not be greatly affected by the access pattern due to conflicts in the direct-mapped cache.

Test 3:
- Hit rate: 0%
- Miss rate: 100%
In Test 3, random access to words in RAM results in a 0% hit rate and a 100% miss rate. 
This is expected since random access patterns are less likely to match addresses already present in the cache, leading to cache misses.
*/

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
    int index = (address / WORD_SIZE / BLOCK_SIZE) % CACHE_SIZE; // Calculate index of cache block
    int tag = address / (WORD_SIZE * BLOCK_SIZE * CACHE_SIZE);   // Calculate tag of address
    
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
    for (int i = 0; i < RAM_SIZE * WORD_SIZE; i += WORD_SIZE) {
        access_cache(i);
    }

    initialize_cache();

    printf("\nTest 2:\n");
    for (int block_offset = 0; block_offset < BLOCK_SIZE; block_offset++) {
        for (int i = block_offset; i < RAM_SIZE * WORD_SIZE; i += BLOCK_SIZE * WORD_SIZE) {
            access_cache(i);
        }
    }

    initialize_cache();

    // Test 3: Random access to words in RAM
    printf("\nTest 3:\n");
    for (int i = 0; i < RAM_SIZE; i++) {
        int random_address = rand() % (RAM_SIZE * WORD_SIZE);
        access_cache(random_address);
    }

    return 0;
}
