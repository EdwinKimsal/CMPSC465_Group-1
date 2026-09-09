class Node:
    def __init__(self):
        self.children = {}
        self.val = None
        self.is_end_of_word = False


class Trie:
    def __init__(self):
        self.root = Node()

    def insert(self, word):
        curr = self.root
        for char in word:
            if char in curr.children:
                curr = curr.children[char]
            else:
                new_node = Node()
                curr.children[char] = new_node
                curr = new_node
        curr.val = word
        curr.is_end_of_word = True

    def search_word(self, curr):
        is_end = False

        while is_end is False:
            if curr.is_end_of_word:
                is_end = True
            else:
                curr = next(iter(curr.children.values()))
        return curr.val

    def search_node(self, word):
        curr = self.root

        for char in word:
            if char in curr.children:
                curr = curr.children[char]
            else:
                return None
        return curr
    
    def delete(self, word):
        curr = self.root
        path = []

        for char in word:
            if char not in curr.children:
                return False
            path.append((curr, char))
            curr = curr.children[char]
        
        if not curr.is_end_of_word:
            return False
        
        curr.is_end_of_word = False
        curr.val = None

        # Remove associated non-words
        for par, char in reversed(path):
            child = par.children[char]

            if child.is_end_of_word == true or len(child.children) > 0:
                break
            del par.children[char]
        return True

    """
    Generate the display_trie function that uses the terminal and print statements to properly display the trie based on this code [Code with a blank display_trie function here]

    Used: Sonnet 5 (High Effort)
    """
    def display_trie(self):
        """Print the trie as an indented tree in the terminal.
 
        Each edge label is the character stored on that link. A node
        that completes a word is marked with '*' followed by the word
        itself, so full words are easy to spot even when they share a
        path with longer words (e.g. "car" inside "carrot").
        """
        print(".")
        self._display(self.root, prefix="")
        print("\n")
 
    def _display(self, node, prefix):
        chars = sorted(node.children.keys())
        for i, char in enumerate(chars):
            child = node.children[char]
            is_last = (i == len(chars) - 1)
            connector = "└── " if is_last else "├── "
 
            label = char
            if child.is_end_of_word:
                label += f"  *[{child.val}]"
 
            print(prefix + connector + label)
 
            extension = "    " if is_last else "│   "
            self._display(child, prefix + extension)


def main():
    trie = Trie()
    words = ["bar", "bat", "bike", "cat", "car", "carrot", "dog", "dot", "free", "freedom"]

    for word in words:
        trie.insert(word)

    trie.display_trie()



main()
