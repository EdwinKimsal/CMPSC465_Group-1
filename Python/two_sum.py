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
    print(a1)


# Start function
if __name__ == "__main__":
    main()