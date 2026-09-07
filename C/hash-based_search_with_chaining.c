// Node structure for both linked list
struct LinkedList_Node {
    char val;
    struct LinkedList_Node* next;
};


// Node structure for the hash map
struct HashMap_Node {
    char val;
    struct HashMap_Node* next;
    struct LinkedList_Node** linked_list_head; // Pointer to the head of the linked list for chaining
};


// HashMap structure
struct HashMap {
    struct HashMap_Node** head; // A pointer to a pointer (points to the head of the hash map)
    int size; // Number of elements in the hash map
};


// Create an empty hash map with a given size
struct HashMap* create_hash_map(int size) {
    struct HashMap* map = (struct HashMap*)malloc(sizeof(struct HashMap));

    map->size = size;
    map->head = (struct HashMap_Node**)malloc(size * sizeof(struct HashMap_Node*));

    struct HashMap_Node** last_hashmap_node = map->head;

    // Allocate memory for each node in the hash map and initialize them
    for (int i = 0; i < size; i++) {
        last_hashmap_node->next = (struct HashMap_Node**)malloc(size * sizeof(struct HashMap_Node*));
        last_hashmap_node = last_hashmap_node->next;

        last_hashmap_node->val = '\0'; // Initialize the value to null character
        last_hashmap_node->linked_list_head = (struct LinkedList_Node**)malloc(sizeof(struct LinkedList_Node*));
    }

    // Return the pointer to the created hash map
    return map;
}


// Computes and returns the index for a given value in the HashMap
int hash_map_function(char val, int size) {
    return atoi(val) % size;
}


// Inserts a value into the linked list at the given head pointer
void insert_to_linked_list(struct LinkedList_Node** head, char val) {
    struct LinkedList_Node* new_node = (struct LinkedList_Node*)malloc(sizeof(struct LinkedList_Node));
    struct LinkedList_Node* current = *head;

    while (current != NULL) {
        current = current->next;
    }
    current->val = val;
}


// Inserts a value into the HashMap using chaining for collision resolution
void insert_to_hash_map(struct HashMap* map, char val) {
    int index = hash_map_function(val, map->size);
    insert_to_linked_list(map->head[index]->linked_list_head, val);
}


// Display the hash map and its contents
void display_hash_map(struct HashMap* map) {
}


// Free all memory allocated for the hash map and its linked lists
void free_hash_map_and_contents(struct HashMap* map) {
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