#include <stdlib.h>
#include <stdio.h>

// Node structure for linked lists
struct LinkedList_Node {
    char val;
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
int hash_map_function(char val, int size) {
    return (unsigned char)val % size;
}


// Inserts a value into the linked list at the given head pointer
void insert_to_linked_list(struct LinkedList_Node** head, char val) {
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
void insert_to_hash_map(struct HashMap* map, char val) {
    if (!map || map->size <= 0) return; // Map safty check
    
    // Index based on hash map function
    int index = hash_map_function(val, map->size);

    // Insert the value into the linked list at the computed index
    insert_to_linked_list(&map->hash_buckets[index], val);
}


// Display the hash map and its contents
void display_hash_map(struct HashMap* map) {
    printf("Index | Linked list\n");
    printf("------+------------\n");

    for (int i = 0; i < map->size; i++) {
        struct LinkedList_Node* current = map->hash_buckets[i];

        printf("%5d | [", i);
        while (current != NULL) {
            printf("%c", current->val);
            current = current->next;

            if (current != NULL) {
                printf(", ");
            }
        }
        printf("]\n");
    }
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
struct TwoSumResult two_sum(int* arr, int target, int size) {
    struct HashMap* map = create_hash_map(size);
    struct TwoSumResult result = {-1, -1};

    for (int i=0; i < (sizeof arr) / (sizeof arr[0]); i++) {
        char complement = target - arr[i];
        int index = hash_map_function(complement, map->size);
        struct LinkedList_Node* current = map->hash_buckets[index];

        while (current != NULL) {
            if (current->val == complement) {
                result.index1 = i;
                result.index2 = index; // This is a simplification; in a real scenario, you'd need to track the actual index of the complement
                free_hash_map_and_contents(map);
                return result;
            }
            current = current->next;
        }

        insert_to_hash_map(map, arr[i]);
    }

    return result;
} 


// Driver code to test the hash map implementation
int main() {
    int n = 10; // Size of the hash map

    int arr1[] = {2, 7, 11, 15};
    struct TwoSumResult result1 = two_sum(arr1, 9, n);
    // display

    // End termination
    return 0;
}