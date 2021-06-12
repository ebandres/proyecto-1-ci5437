import sys

def flip(my_list, i, x):
    # Flips x elements starting at index i
    # Could use my_list[i:i + x] = reversed(my_list[i:i+x])
    # But doesn't work for i + x > len(mylist)

    tmp = []
    for j in range(i, i + x):
        tmp += [my_list[j % len(my_list)]]
    
    tmp.reverse()

    for j in range(x):
        my_list[(i + j) % len(my_list)] = tmp[j]
    


def generate_topspin(n):
    with open(f"../puzzles/topspin_{n}_4.psvn", 'w') as file:
        file.write(f"{n}\n\n" + f"{n} " * n + "\n\n")

        tokens = ["X1", "X2", "X3", "X4"]
        base = ["-"] * n
        for i in range(n):
            rule = base[:]

            for j in range(4):
                rule[(i + j) % len(rule)] = tokens[j]
            
            for j in rule:
                file.write(f"{j} ")

            file.write("=> ")

            flip(rule, i, 4)

            for j in rule:
                file.write(f"{j} ")
            
            file.write("\n")

        file.write("\nGOAL ")
        for i in range(n):
            file.write(f"{i} ")


if __name__ == "__main__":
    try:
        n = int(sys.argv[1])
    except IndexError as err:
        print("Error: Not enough arguments")
        print("Syntax: 'topspin_n4.py n' where n is the number of tokens\ni.e. 'topspin_n4.py 12' for a puzzle with 12 numbers")
        sys.exit(1)
    except ValueError as err:
        print("Error: Argument is not an int")
        print("Syntax: 'topspin_n4.py n' where n is the number of tokens\ni.e. 'topspin_n4.py 12' for a puzzle with 12 numbers")
        sys.exit(1)

    generate_topspin(n)