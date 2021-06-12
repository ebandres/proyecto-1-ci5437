import sys

def generate_hanoi(n, m):
    nm = n * m
    with open(f"../puzzles/hanoi_{n}p{m}d.psvn", 'w') as file:
        file.write(f"{nm}\n")
        file.write("2 " * nm + "\n\n")

        seen = set()

        for disc in range(1, m + 1): # Iterate through discs
            for i in range(1, n + 1): 
                peg_from = i
                for j in range(1, n):
                    if j >= i:
                        peg_to = j + 1
                    else:
                        peg_to = j

                    left = ""
                    right = ""

                    for k in range(1, m + 1):
                        for l in range(1, n + 1):

                            if peg_from == l and k <= disc:
                                left += "1 " if k == disc else "0 "
                            else:
                                left += "0 " if peg_to == l and k <= disc else "- "
                            
                            #right += (["1"] if k==disc else ["0"]) if (toPeg==l and k<=dii) else (["0"] if (fromPeg==l and k<=di) else ["-"]) 
                            if peg_to == l and k <= disc:
                                right += "1 " if k == disc else "0 "
                            else:
                                right += "0 " if peg_from == l and k <= disc else "- "
                        left += " "
                        right += " "

                    rule = left + "=> " + right
                    inverse_rule = right + "=> " + left
                    if rule not in seen:
                        file.write(rule)
                        seen.add(rule)
                        seen.add(inverse_rule)
                        file.write("\n")

            file.write("\n")

        goal = "1 " + "0 " * (n - 1)
        file.write("\nGOAL " + goal * m)
                    

if __name__ == "__main__":
    try:
        pegs = int(sys.argv[1])
        discs = int(sys.argv[2])
    except IndexError as err:
        print("Error: Not enough arguments")
        print("Syntax: 'hanoi_nm.py n m' where n is the number of pegs and m is the number of discs")
        print("i.e. 'hanoi_nm.py 4 12' for a puzzle with 4 pegs and 12 discs")
        sys.exit(1)
    except ValueError as err:
        print("Error: Argument is not an int")
        print("Syntax: 'hanoi_nm.py n m' where n is the number of pegs and m is the number of discs")
        print("i.e. 'hanoi_nm.py 4 12' for a puzzle with 4 pegs and 12 discs")

        sys.exit(1)

    generate_hanoi(pegs, discs)