# Create an empty hash map with a given size
def create_hash_map(size):
    return [[] for _ in range(size)]


# Computes and returns the index for a given value in the HashMap
def hash_map_function(val, size):
    return ord(val) % size


# Inserts a value into the HashMap using chaining for collision resolution
def insert_to_hash_map(hash_map, value):
    index = hash_map_function(value, len(hash_map))
    hash_map[index].append(value)


# Display the hash map and its contents
def display_hash_map(hash_map):
    print("Index | Linked list")
    print("------+------------")

    for index, bucket in enumerate(hash_map):
        values = ", ".join(str(value) for value in bucket)
        print(f"{index:5d} | [{values}]")
    print()


# Driver code to test the hash map implementation
def main():
    n = 10  # Size of the HashMap

    hash_map = create_hash_map(n)

    # Insert values into the HashMap
    insert_to_hash_map(hash_map, 'a')
    insert_to_hash_map(hash_map, 'b')
    insert_to_hash_map(hash_map, 'c')
    insert_to_hash_map(hash_map, 'd')
    insert_to_hash_map(hash_map, 'e')
    insert_to_hash_map(hash_map, 'f')

    insert_to_hash_map(hash_map, 'A')
    insert_to_hash_map(hash_map, 'B')
    insert_to_hash_map(hash_map, 'C')
    insert_to_hash_map(hash_map, 'D')
    insert_to_hash_map(hash_map, 'E')
    insert_to_hash_map(hash_map, 'F')

    # Display the contents of the hash map
    display_hash_map(hash_map)


main()