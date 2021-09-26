import queue
import numpy as np


# Following section of code produces the maze as a 2-D list by reading from the map.txt file
maze = []
with open('map.txt', 'r') as f:
    # For loop to go through all lines of the map.txt file, remove the '\n' from each line, 
    # then append onto our maze variable.
    for i in range (15):                                     
        lines = f.readline()
        lines = list(lines)
        lines.pop()
        maze.append(lines)
    f.close()

# Function to print the max to terminal once shortest path has been found.
def printMaze(maze, startPosX, startPosY, endPosX, endPosY, path=""):
    i = startPosX
    j = startPosY
    pos = set()
    for move in path:
        if move == "L":
            i -= 1

        elif move == "R":
            i += 1

        elif move == "U":
            j -= 1

        elif move == "D":
            j += 1
        pos.add((j, i))

    maze[startPosY][startPosX] = "-"
    maze[endPosY][endPosX] = "X"

    for j, row in enumerate(maze):
        for i, col in enumerate(row):
            if col == "X":
                print(col + " ", end="")
            elif (j, i) in pos:
                print("  ", end="")
            elif col == "@":
                print("0" + " ", end="")       
            else:
                print(col + " ", end="")
        print()
        

def valid(maze, moves, startPosX, startPosY):

    i = startPosX
    j = startPosY
    latestMove = ""
    for move in (moves):
        if (move == "L") and (latestMove != "R"):
            i -= 1
            latestMove = "L"

        elif (move == "R") and (latestMove != "L"):
            i += 1
            latestMove = "R"

        elif (move == "U") and (latestMove != "D"):
            j -= 1
            latestMove = "U"

        elif (move == "D") and (latestMove != "U"):
            j += 1
            latestMove = "D"

    if not(0 <= i < len(maze[0]) and 0 <= j < len(maze)):       # If co-ordinate is outside the maze, return false.
        return False
    elif (maze[j][i] == "1"):                                   # If co-ordinate is a wall, return false
        return False
    elif (maze[j][i] == "@"):                                   # IF co-ordinate has already been visited, return false.
        return False

    maze[j][i] = "@"                                            #This is only reached when a valid path has been taken, 
                                                                # mark it with unique symbol.
    return True

# Function to evaluate if our path reaches the target position.
def findEnd(maze, moves, startPosX, startPosY, endPosX, endPosY):
    i = startPosX
    j = startPosY
    for move in moves:
        if move == "L":
            i -= 1

        elif move == "R":
            i += 1

        elif move == "U":
            j -= 1

        elif move == "D":
            j += 1

    if j == endPosY:
        if i == endPosX:
            print("Found: " + moves)
            printMaze(maze, startPosX, startPosY, endPosX, endPosY, moves)
            return True
    return False

# MAIN ALGORITHM
nums = queue.Queue()
nums.put("")
add = ""
# Declare and define starting X and Y co-ordinate of Robot. (NOTE: Axis values start at 0)
startPosX = 1
startPosY = 1
# Declare and define X an Y co-ordinate of target. (NOTE: Axis values start at 0)
endPosX = 1
endPosY = 13

if ((maze[startPosY][startPosX]=="1")|(maze[endPosY][endPosX]=="1")):       # If statement to check if given start and end position are valid
    print ("\nError: Invalid Start and/or End position\n")
else:
    while not findEnd(maze, add, startPosX, startPosY, endPosX, endPosY): 
        add = nums.get()
        for j in ["L", "R", "U", "D"]:
            put = add + j
            if valid(maze, put, startPosX, startPosY):
                nums.put(put)
        if nums.empty():                                                    # If queue is empty, that means all paths have been evaluated and no path to target was found.
            print("\nNo path found\n")
            break