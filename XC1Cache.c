// Author: Devon Beal
//
/*
Results of the three new tests with different block sizes:

Block Size: 2 words
Test 1:
- Hit rate: 75%
- Miss rate: 25%
Test 2:
- Hit rate: 75%
- Miss rate: 25%
Test 3:
- Hit rate: 0%
- Miss rate: 100%

Block Size: 4 words
Test 1:
- Hit rate: 75%
- Miss rate: 25%
Test 2:
- Hit rate: 75%
- Miss rate: 25%
Test 3:
- Hit rate: 0%
- Miss rate: 100%

Block Size: 16 words
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
The hit and miss rates remain consistent across different block sizes for Tests 1 and 2. 
This consistency suggests that the cache's behavior is not greatly influenced by the block size in these tests. However, 
est 3 consistently shows a 0% hit rate and a 100% miss rate, indicating that random access patterns are less likely to match addresses already present in the cache, 
leading to cache misses regardless of the block size.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RAM_SIZE 1048576    // 2^20 words
#define CACHE_SIZE 16       // Number of blocks in cache
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
void access_cache(int address, int block_size) {
    int index = (address / WORD_SIZE / block_size) % CACHE_SIZE; // Calculate index of cache block
    int tag = address / (WORD_SIZE * block_size * CACHE_SIZE);   // Calculate tag of address
    
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

    // Block size: 2 words
    initialize_cache();
    printf("Block Size: 2 words\n");
    // Test 1: Sequential access to every word in RAM
    printf("Test 1:\n");
    for (int i = 0; i < RAM_SIZE * WORD_SIZE; i += WORD_SIZE) {
        access_cache(i, 2);
    }

    // Test 2: Access every word in RAM in increments of the block size
    printf("\nTest 2:\n");
    for (int block_offset = 0; block_offset < 2; block_offset++) {
        for (int i = block_offset; i < RAM_SIZE * WORD_SIZE; i += 2 * WORD_SIZE) {
            access_cache(i, 2);
        }
    }

    // Test 3: Random access to words in RAM
    printf("\nTest 3:\n");
    for (int i = 0; i < RAM_SIZE; i++) {
        int random_address = rand() % (RAM_SIZE * WORD_SIZE);
        access_cache(random_address, 2);
    }

    // Block size: 4 words
    initialize_cache();
    printf("\nBlock Size: 4 words\n");
    // Test 1
    printf("Test 1:\n");
    for (int i = 0; i < RAM_SIZE * WORD_SIZE; i += WORD_SIZE) {
        access_cache(i, 4);
    }

    // Test 2
    printf("\nTest 2:\n");
    for (int block_offset = 0; block_offset < 4; block_offset++) {
        for (int i = block_offset; i < RAM_SIZE * WORD_SIZE; i += 4 * WORD_SIZE) {
            access_cache(i, 4);
        }
    }

    // Test 3
    printf("\nTest 3:\n");
    for (int i = 0; i < RAM_SIZE; i++) {
        int random_address = rand() % (RAM_SIZE * WORD_SIZE);
        access_cache(random_address, 4);
    }

    // Block size: 16 words
    initialize_cache();
    printf("\nBlock Size: 16 words\n");
    // Test 1
    printf("Test 1:\n");
    for (int i = 0; i < RAM_SIZE * WORD_SIZE; i += WORD_SIZE) {
        access_cache(i, 16);
    }

    // Test 2
    printf("\nTest 2:\n");
    for (int block_offset = 0; block_offset < 16; block_offset++) {
        for (int i = block_offset; i < RAM_SIZE * WORD_SIZE; i += 16 * WORD_SIZE) {
            access_cache(i, 16);
        }
    }

    // Test 3
    printf("\nTest 3:\n");
    for (int i = 0; i < RAM_SIZE; i++) {
        int random_address = rand() % (RAM_SIZE * WORD_SIZE);
        access_cache(random_address, 16);
    }

    return 0;
}
