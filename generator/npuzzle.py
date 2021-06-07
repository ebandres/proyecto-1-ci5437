import sys
import copy

def generate_npuzzle(n):
    ns = n*n

    with open(f"../puzzles/{ns - 1}puzzle.psvn", 'w') as file:
        file.write(f"DOMAIN tile {ns}\nb")
        for i in range(1, ns + 1):
            file.write(f" {i}")

        file.write(f"\n\n{ns} {'tile ' * ns}\n\n")

        # Cases
        # Base
        base = []
        for i in range(n):
            base += [["-"] * n]

        for y in range(n):
            for x in range(n):
                # For each tile there are 4 possible cases
                # LEFT check x - 1 >= 0
                if x - 1 >= 0:
                    write_rule(x, y, x - 1, y, file, copy.deepcopy(base))
                
                # RIGHT check x + 1 < n
                if x + 1 < n:
                    write_rule(x, y, x + 1, y, file, copy.deepcopy(base))

                # UP check y - 1 >= 0
                if y - 1 >= 0:
                    write_rule(x, y, x, y - 1, file, copy.deepcopy(base))

                # DOWN check y + 1 < n
                if y + 1 < n:
                    write_rule(x, y, x, y + 1, file, copy.deepcopy(base))
        
        file.write("\nGOAL b")
        for i in range(1, ns + 1):
            file.write(f" {i}")

def write_rule(x, y, xt, yt, f, grid):
    grid[y][x] = "b"        # Mark the blank
    grid[yt][xt] = "X"    # Mark slide target

    for row in grid:
        for i in row:
            f.write(f"{i} ")

    f.write("=> ")

    grid[y][x] = "X"
    grid[yt][xt] = "b"

    for row in grid:
        for i in row:
            f.write(f"{i} ")

    f.write("\n")

if __name__ == "__main__":
    try:
        size = int(sys.argv[1])
    except IndexError as err:
        print("Error: Not enough arguments")
        print("Syntax: 'npuzzle.py n' where n is the size of the square\ni.e. 'npuzzle.py 4' for a 4x4 square (15 puzzle)")
        sys.exit(1)
    except ValueError as err:
        print("Error: Argument is not an int")
        print("Syntax: 'npuzzle.py n' where n is the size of the square\ni.e. 'npuzzle.py 4' for a 4x4 square (15 puzzle)")
        sys.exit(1)

    generate_npuzzle(size)