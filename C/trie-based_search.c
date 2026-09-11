// Node structure for linked list
struct HashMap {
    char* hash_buckets; // A pointer to an array of characters (represents the hash buckets)
    int size; // Number of buckets in the hash map
};


// Node structure for trie
struct Trie_Node {
    struct LinkedList_Node** children;
    char val;
    bool is_end_of_word;
}


// Trie structure
struct Trie {
    struct Node* root;
}