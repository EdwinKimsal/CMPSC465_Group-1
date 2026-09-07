#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Node structure for linked lists
struct LinkedList_Node {
    int val;
    struct LinkedList_Node* next;
};


// HashMap structure
struct HashMap {
    struct LinkedList_Node** hash_buckets; // A pointer to a pointer (points to the that position's hash bucket)
    int size; // Number of buckets in the hash map
};


// Two sum result structure
struct TwoSumResult {
    int index1;
    int index2;
};


// Create an empty hash map with a given size
struct HashMap* create_hash_map(int size) {
    struct HashMap* map = malloc(sizeof(struct HashMap));

    map->size = size;
    map->hash_buckets = malloc(size * sizeof(struct LinkedList_Node*));

    for (int i = 0; i < size; i++) {
        map->hash_buckets[i] = NULL;
    }

    // Return the pointer to the created hash map
    return map;
}


// Computes and returns the index for a given value in the HashMap
int hash_map_function(int val, int size) {
    return (unsigned int)val % size;
}


// Inserts a value into the linked list at the given head pointer
void insert_to_linked_list(struct LinkedList_Node** head, int val) {
    struct LinkedList_Node* new_node = malloc(sizeof(struct LinkedList_Node));
    new_node->val = val;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    new_node->next = *head;
    *head = new_node;
}


// Inserts a value into the HashMap using chaining for collision resolution
void insert_to_hash_map(struct HashMap* map, int val) {
    if (!map || map->size <= 0) return; // Map safty check
    
    // Index based on hash map function
    int index = hash_map_function(val, map->size);

    // Insert the value into the linked list at the computed index
    insert_to_linked_list(&map->hash_buckets[index], val);
}


bool search_in_hash_map(struct HashMap* map, int val) {
    if (!map || map->size <= 0) return false; // Map safty check

    // Index based on hash map function
    int index = hash_map_function(val, map->size);

    // Search for the value in the linked list at the computed index
    struct LinkedList_Node* current = map->hash_buckets[index];
    while (current != NULL) {
        if (current->val == val) {
            return true; // Value found
        }
        current = current->next;
    }

    return false; // Value not found
}


// Display the hash map and its contents
void display_two_sum_result(int arr[], int target, struct TwoSumResult result, int arrSize) {
    printf("Input array: [");
    for (int i = 0; i < arrSize; i++) {
        printf("%d", arr[i]);
        if (i < arrSize - 1) {
            printf(", ");
        }
    }
    printf("]\n");
    printf("Target: %d\n", target);
    printf("Indices: (%d, %d)\n", result.index1, result.index2);
    printf("\n");
}


// Free all memory allocated for the hash map and its linked lists
void free_hash_map_and_contents(struct HashMap* map) {
    // Empty map safty check
    if (!map || map->size <= 0) return;

    for (int i = 0; i < map->size; i++) {
        struct LinkedList_Node* current_linked_list_node = map->hash_buckets[i];
        while (current_linked_list_node != NULL) {
            struct LinkedList_Node* temp = current_linked_list_node;
            current_linked_list_node = current_linked_list_node->next;
            free(temp);
        }
    }
    free(map->hash_buckets);
    free(map);
}


// Two sum test code
struct TwoSumResult two_sum(int arr[], int target, int mapSize, int arrSize) {
    struct HashMap* map = create_hash_map(mapSize);
    struct TwoSumResult result = {-1, -1};

    for (int i=0; i < arrSize; i++) {
        int complement = target - arr[i];

        if (search_in_hash_map(map, complement)) {
            result.index2 = i;
            // Find the index of the complement in the original array
            int j = 0;
            while (result.index1 == -1) {
                if (arr[j] == complement) {
                    result.index1 = j;
                    break;
                }
                j++;
            }
            break; // Exit the loop once a valid pair is found
        }
        insert_to_hash_map(map, arr[i]);
    }

    free_hash_map_and_contents(map); // Free the hash map and its contents

    return result;
} 


// Driver code to test the hash map implementation
int main() {
    int n = 8; // Size of the hash map

    int arr1[] = {2, 7, 11, 15};
    struct TwoSumResult result1 = two_sum(arr1, 9, n, 4);
    display_two_sum_result(arr1, 9, result1, 4);

    int arr2[] = {3, 5, 9, 14};
    struct TwoSumResult result2 = two_sum(arr2, 20, n, 4);
    display_two_sum_result(arr2, 20, result2, 4);

    int arr3[] = {2, 5, 1, 8, 9, 12, 4, 7, 11, 6};
    struct TwoSumResult result3 = two_sum(arr3, 18, n, 10);
    display_two_sum_result(arr3, 18, result3, 10);

    // End termination
    return 0;
}