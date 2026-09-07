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
    printf("\n");
}


// Driver code to test the hash map implementation
int main() {
    int n = 10; // Size of the hash map

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