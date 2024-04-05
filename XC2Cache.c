// Author: Devon Beal
//
/*
Results of the three new tests with different cache sizes:

Cache Size: 8 blocks
Test 1:
- Hit rate: 50%
- Miss rate: 50%
Test 2:
- Hit rate: 50%
- Miss rate: 50%
Test 3:
- Hit rate: 0%
- Miss rate: 100%

Cache Size: 32 blocks
Test 1:
- Hit rate: 75%
- Miss rate: 25%
Test 2:
- Hit rate: 75%
- Miss rate: 25%
Test 3:
- Hit rate: 0%
- Miss rate: 100%

Cache Size: 64 blocks
Test 1:
- Hit rate: 75%
- Miss rate: 25%
Test 2:
- Hit rate: 75%
- Miss rate: 25%
Test 3:
- Hit rate: 0%
- Miss rate: 100%

Analysis:
As the cache size increases, the hit rates for Tests 1 and 2 also increase.
This is because larger caches have more space to store frequently accessed blocks, reducing the likelihood of cache misses. However, 
the hit rates remain at 0% for Test 3 across all cache sizes, as random access patterns are less likely to match addresses already present in the cache, 
leading to cache misses regardless of cache size.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RAM_SIZE 1048576    // 2^20 words
#define WORD_SIZE 4         // Size of a word in bytes

typedef struct {
    int valid;  // Valid bit
    int tag;    // Tag field
} CacheBlock;

// Cache array
CacheBlock cache[64];  // Maximum cache size

// Function to initialize cache
void initialize_cache(int cache_size) {
    for (int i = 0; i < cache_size; i++) {
        cache[i].valid = 0; // Set valid bit to 0 to indicate invalid blocks
    }
}

// Function to simulate cache access
void access_cache(int address, int block_size, int cache_size) {
    int num_blocks = cache_size / block_size;
    int index = (address / WORD_SIZE / block_size) % num_blocks; // Calculate index of cache block
    int tag = address / (WORD_SIZE * block_size * num_blocks);   // Calculate tag of address
    
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

    // Cache Size: 8 blocks
    initialize_cache(8);
    printf("Cache Size: 8 blocks\n");
    // Test 1: Sequential access to every word in RAM
    printf("Test 1:\n");
    for (int i = 0; i < RAM_SIZE * WORD_SIZE; i += WORD_SIZE) {
        access_cache(i, 4, 8);
    }

    // Test 2: Access every word in RAM in increments of the block size
    printf("\nTest 2:\n");
    for (int block_offset = 0; block_offset < 4; block_offset++) {
        for (int i = block_offset; i < RAM_SIZE * WORD_SIZE; i += 4 * WORD_SIZE) {
            access_cache(i, 4, 8);
        }
    }

    // Test 3: Random access to words in RAM
    printf("\nTest 3:\n");
    for (int i = 0; i < RAM_SIZE; i++) {
        int random_address = rand() % (RAM_SIZE * WORD_SIZE);
        access_cache(random_address, 4, 8);
    }

    // Cache Size: 32 blocks
    initialize_cache(32);
    printf("\nCache Size: 32 blocks\n");
    // Test 1
    printf("Test 1:\n");
    for (int i = 0; i < RAM_SIZE * WORD_SIZE; i += WORD_SIZE) {
        access_cache(i, 4, 32);
    }

    // Test 2
    printf("\nTest 2:\n");
    for (int block_offset = 0; block_offset < 4; block_offset++) {
        for (int i = block_offset; i < RAM_SIZE * WORD_SIZE; i += 4 * WORD_SIZE) {
            access_cache(i, 4, 32);
        }
    }

    // Test 3
    printf("\nTest 3:\n");
    for (int i = 0; i < RAM_SIZE; i++) {
        int random_address = rand() % (RAM_SIZE * WORD_SIZE);
        access_cache(random_address, 4, 32);
    }

    // Cache Size: 64 blocks
    initialize_cache(64);
    printf("\nCache Size: 64 blocks\n");
    // Test 1
    printf("Test 1:\n");
    for (int i = 0; i < RAM_SIZE * WORD_SIZE; i += WORD_SIZE) {
        access_cache(i, 4, 64);
    }

    // Test 2
    printf("\nTest 2:\n");
    for (int block_offset = 0; block_offset < 4; block_offset++) {
        for (int i = block_offset; i < RAM_SIZE * WORD_SIZE; i += 4 * WORD_SIZE) {
            access_cache(i, 4, 64);
        }
    }

    // Test 3
    printf("\nTest 3:\n");
    for (int i = 0; i < RAM_SIZE; i++) {
        int random_address = rand() % (RAM_SIZE * WORD_SIZE);
        access_cache(random_address, 4, 64);
    }

    return 0;
}

