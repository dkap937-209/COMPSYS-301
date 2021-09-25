import queue
import numpy as np

maze = []
with open('map.txt', 'r') as f:
    
    for i in range (15):                                     
        lines = f.readline()
        lines = list(lines)
        lines.pop()
        maze.append(lines)
    f.close()


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
            else:
                print(col + " ", end="")
        print()
        

def valid(maze, moves, startPosX, startPosY):

    i = startPosX
    j = startPosY
    latestMove = ""
    for move in (moves):
        if (move == "L"):
            if (latestMove == "R"):
                return False
            else:
                i-= 1
                latestMove = "L"
        elif (move == "R"):
            if (latestMove == "L"):
                return False
            else:
                i += 1
                latestMove = "R"
        elif (move == "U"):
            if (latestMove == "D"):
                return False
            else:
                j -= 1
                latestMove = "U"

        elif (move == "D"):
            if (latestMove == "U"):
                return False
            else: 
                j += 1
                latestMove = "D"

    if not(0 <= i < len(maze[0]) and 0 <= j < len(maze)):                       # If co-ordinate is outside the maze, return false.
        return False
    elif (maze[j][i] == "1"):                                                   # If co-ordinate is a wall, return false
        return False

    return True

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
startPosX = 1
startPosY = 1
endPosX = 1
endPosY = 13

if ((maze[startPosY][startPosX]=="1")|(maze[endPosY][endPosX]=="1")): 
    print ("\nError: Invalid Start and/or End position\n")
else:
    while not findEnd(maze, add, startPosX, startPosY, endPosX, endPosY): 
        add = nums.get()
        for j in ["L", "R", "U", "D"]:
            put = add + j
            if valid(maze, put, startPosX, startPosY):
                nums.put(put)
        if nums.empty():
            print("\nNo path found\n")
            break

    