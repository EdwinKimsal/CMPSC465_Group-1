# Two Sum with Hash Based Search
def two_sum(numbers, target):
    num_dict = {}
    for i, num in enumerate(numbers):
        diff = target - num

        if diff in num_dict:
            return (num_dict[diff], i)

        num_dict[num] = i

    return [-1, -1]


# Main function
def main():
    a1 = two_sum([2, 7, 11, 15], 9)
    print(f"Test Case 1:")
    print("Array: [2, 7, 11, 15] Target: 9")
    print("Answer: ", a1)
    print()

    a2 = two_sum([3, 2, 4], 6)
    print(f"Test Case 2:")
    print("Array: [3, 2, 4] Target: 6")
    print("Answer: ", a2)
    print()

    a3 = two_sum([3, 3], 6)
    print(f"Test Case 3:")
    print("Array: [3, 3] Target: 6")
    print("Answer: ", a3)
    print()

    a4 = two_sum([-1, -2, -3, -4, -5], -8)
    print(f"Test Case 4:")
    print("Array: [-1, -2, -3, -4, -5] Target: -8")
    print("Answer: ", a4)

    a5 = two_sum([0, 4, 3, 0], 0)
    print(f"Test Case 5:")
    print("Array: [0, 4, 3, 0] Target: 0")
    print("Answer: ", a5)
    print()

    a6 = two_sum([1, 5, 2, 8, -4], 4)
    print(f"Test Case 6:")
    print("Array: [1, 5, 2, 8, -4] Target: 4")
    print("Answer: ", a6)
    print()


# Start function
if __name__ == "__main__":
    main()