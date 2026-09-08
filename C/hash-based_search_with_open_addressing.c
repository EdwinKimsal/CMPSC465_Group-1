#include <stdlib.h>
#include <stdio.h>


// HashMap structure
struct HashMap {
    char* hash_buckets; // A pointer to an array of characters (represents the hash buckets)
    int size; // Number of buckets in the hash map
};


// Create an empty hash map with a given size
struct HashMap* create_hash_map(int size) {
    struct HashMap* map = malloc(sizeof(struct HashMap));

    map->size = size;
    map->hash_buckets = malloc(size * sizeof(char));

    for (int i = 0; i < size; i++) {
        map->hash_buckets[i] = '\0'; // Initialize each bucket to null character
    }

    // Return the pointer to the created hash map
    return map;
}


// Computes and returns the index for a given value in the HashMap
int hash_map_function(char val, int size) {
    return (unsigned char)val % size;
}


// Inserts a value into the HashMap using linear probing for collision resolution
void insert_to_hash_map(struct HashMap* map, char val) {
    int index = hash_map_function(val, map->size);

    if (index < 0 || index >= map->size) return; // Invalid index check

    if (map->hash_buckets[index] == '\0') {
        map->hash_buckets[index] = val;
    } else {
        // Handle collision by finding the next available bucket
        int original_index = index;
        do {
            index = (index + 1) % map->size;
            if (map->hash_buckets[index] == '\0') {
                map->hash_buckets[index] = val;
                return;
            }
        } while (index != original_index);
    }
}


// Free all memory allocated for the hash map and its contents
void free_hash_map_and_contents(struct HashMap* map) {
    // Empty map safty check
    if (!map) return;

    free(map->hash_buckets);
    free(map);
}


// Display the hash map and its contents
void display_hash_map(struct HashMap* map) {
    printf("Index | Data\n");
    printf("------+------------\n");

    for (int i = 0; i < map->size; i++) {
        printf("%5d | %c\n", i, map->hash_buckets[i]);
    }
    printf("\n");
}


// Driver code to test the hash map implementation
int main() {
    int n = 12; // Size of the hash map

    // Create a hash map with a size of n
    struct HashMap* map = create_hash_map(n);

    // Insert values into the hash map
    insert_to_hash_map(map, 'a');
    insert_to_hash_map(map, 'b');
    insert_to_hash_map(map, 'c');
    insert_to_hash_map(map, 'd');
    insert_to_hash_map(map, 'e');
    insert_to_hash_map(map, 'f');

    insert_to_hash_map(map, 'A');
    insert_to_hash_map(map, 'B');
    insert_to_hash_map(map, 'C');
    insert_to_hash_map(map, 'D');
    insert_to_hash_map(map, 'E');
    insert_to_hash_map(map, 'F');

    // Display the contents of the hash map
    display_hash_map(map);

    // Free the memory allocated for the hash map and its contents
    free_hash_map_and_contents(map);

    // End termination
    return 0;
}