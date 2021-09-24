import queue
import numpy as np


def createMaze4():
    maze = []
    with open ("map.txt") as TextFile:
        for line in TextFile:
            objects = [line.strip() for item in line]
            maze.append(objects)
    print(maze)

mymaze = []
with open('map.txt', 'r') as f:
    
    for i in range (15):
        lines = f.readline()
        lines = list(lines)
        lines.pop()
        mymaze.append(lines)
    f.close()

    print (mymaze)


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
    for move in moves:
        if move == "L":
            i -= 1

        elif move == "R":
            i += 1

        elif move == "U":
            j -= 1

        elif move == "D":
            j += 1

        if not(0 <= i < len(maze[0]) and 0 <= j < len(maze)):
            return False
        elif (maze[j][i] == "1"):
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
<<<<<<< HEAD
maze  = mymaze
startPosX = 1
startPosY = 1
endPosX = 2
endPosY = 5
=======
maze1 = createMaze4()
maze  = createMaze3()
>>>>>>> 397d23179783163f93bb1a8989ad2eedda5b72a1

while not findEnd(maze, add, startPosX, startPosY, endPosX, endPosY): 
    add = nums.get()
    #print(add)
    for j in ["L", "R", "U", "D"]:
        put = add + j
        if valid(maze, put, startPosX, startPosY):
            nums.put(put)