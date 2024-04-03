// Author: Devon Beal
//
// Test 1: seemed to have no hits a straight 0% while miss rate was at 100%.
// This might be due to sequential access to every word. Also since the cahe is initially empty and each new block is empty.
//
//Test 2: This one was better once I Fixed it. Hits where about 25% and Miss
//rate was about 75%. Every word in RAM is accessed in increments of the block 
//size. This might be due to the cache being small and direct-mapped.
//
//Test 3: As put in the veriables the hit and miss rate was dependant on random
//addresses, and I think I got maybe 1 hit both times I ran this. Since the 
//addresses coincide with the address already in the cache then the cache hits
//else does not. 
//
//Might need to do some minor changes before submitting  

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

    // Test 2: Access every word in RAM in increments of the block size
    printf("\nTest 2:\n");
    for (int i = 0; i < RAM_SIZE * WORD_SIZE; i += BLOCK_SIZE * WORD_SIZE) {
        access_cache(i);
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
