/*
*   Structures
*/

// Node structure for trie
struct HashMap;

struct Trie_Node {
    struct HashMap *hashmap;
    char *val;
    char character;
    bool is_end_of_word;
};


// Hash map structure
struct HashMap {
    struct Trie_Node **hash_buckets; // A pointer to an array of child nodes
    int size; // Number of buckets in the hash map
};



/*
*    Hash
*/

// Create an empty hash map with a given size
struct HashMap* create_hash_map() {
    struct HashMap* map = malloc(sizeof(struct HashMap));

    map->size = 26;
    map->hash_buckets = malloc(map->size * sizeof(struct Trie_Node*));

    for (int i = 0; i < map->size; i++) {
        map->hash_buckets[i] = NULL; // Initialize each bucket to null character
    }

    // Return the pointer to the created hash map
    return map;
};

// Computes and returns the index for a given value in the HashMap
int hash_map_function(char val) {
    return (unsigned char)(val-'a') % 26;
}


// Inserts a value into the HashMap
void insert_to_hash_map(struct HashMap* map, struct Trie_Node *node) {
    int index = hash_map_function(node->character);

    if (index < 0 || index >= map->size) return; // Invalid index check

    map->hash_buckets[index] = node;
}


// Free all memory allocated for the hash map and its contents
void free_hash_map_and_contents(struct HashMap* map) {
    // Empty map safty check
    if (!map) return;

    free(map->hash_buckets);
    free(map);
}



/*
*    Trie
*/

// Function for inserting into the trie
void insert_node(struct Trie_Node *root, char *word) {
    struct Trie_Node *curr_node = root;
    for (int i=0; word[i] != '\0'; i++) {
        char c = word[i];
        if (curr_node->hashmap->hash_buckets[hash_map_function(c)] != NULL) {
            curr_node = curr_node->hashmap->hash_buckets[hash_map_function(c)];
        } else {
            struct Trie_Node *new_node = malloc(sizeof(struct Trie_Node));
            new_node->hashmap = create_hash_map();
            new_node->val = NULL;
            new_node->character = c;
            new_node->is_end_of_word = false;
            insert_to_hash_map(curr_node->hashmap, new_node);
            curr_node = new_node;
        }
    }

    curr_node->is_end_of_word = true;
    curr_node->val = word;
}


// Function to search for word
char* search_word(struct Trie_Node *root, char *needle) {
    struct Trie_Node *curr_node = root;

    if (needle == NULL || needle[0] == '\0') {
        return NULL;
    }

    for (int i=0; needle[i] != '\0'; i++) {
        char c = needle[i];
        if (curr_node->hashmap->hash_buckets[hash_map_function(c)] == NULL) {
            if (curr_node->is_end_of_word == true) {
                return curr_node->val;
            } else {
                return NULL;
            }
        } else {
            curr_node = curr_node->hashmap->hash_buckets[hash_map_function(c)];
        }
    }

    while (curr_node->is_end_of_word == false) {
        Struct Trie_Node *temp_node = NULL;
        for (int i=0; i<curr_node->hashmap->size) {
            if (curr_node->hashmap->hash_buckets[i] != NULL) {
                temp_node = curr_node->hashmap->hash_buckets[i];
                break;
            }
        }

        if (temp_node == NULL) {
            return NULL;
        } else {
            curr_node = temp_node;
        }
    }
    return curr_node->val;
}


// Function to search for a specific node
struct Trie_Node *search_node(struct Trie_Node *root, char *word) {
    struct Trie_Node *curr_node = root;
    bool is_end = false;
    for (int i=0; word[i] != '\0'; i++) {
        char c = word[i];
        if (curr_node->hashmap->hash_buckets[hash_map_function(c)] != NULL) {
            curr_node = curr_node->hashmap->hash_buckets[hash_map_function(c)];
        } else {
            return NULL;
        }
    }
    return curr_node;
}


// Function to delete node from trie
bool delete_node(struct Trie_Node *root, char *word) {

}


// Function to delete trie
void delete_trie(struct Trie_Node *root) {

}


// Function to display trie
void display_trie(struct Trie_Node *root) {

}


// Driver code
int main() {
    struct Trie_Node *trie = malloc(sizeof(struct Trie_Node));
    trie->hashmap = create_hash_map();
    trie->val = NULL;
    trie->character = '\0';
    trie->is_end_of_word = false;

    insert_node(trie, "bar");
    insert_node(trie, "bat");
    insert_node(trie, "bike");
    insert_node(trie, "cat");
    insert_node(trie, "car");
    insert_node(trie, "carrot");
    insert_node(trie, "dog");
    insert_node(trie, "dot");
    insert_node(trie, "free");
    insert_node(trie, "freedom");

    display_trie(trie);

    delete_trie(trie);
}