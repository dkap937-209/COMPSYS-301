#include <stack>
#include <set>
#include "A_star_header.h"
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define ROW 9
#define COL 10

// Creating a shortcut for int, int pair type
typedef pair<int, int> Pair;

// Creating a shortcut for pair<int, pair<int, int>> type
typedef pair<double, pair<int, int> > pPair;

// A structure to hold the necessary parameters
struct cell {
    // Row and Column index of its parent
    // Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
    int parent_i, parent_j;
    // f = g + h
    double f, g, h;
};

//Checks if a cell is within the bounds of the maze
bool isValid(int row, int col)
{
    // Returns true if row number and column number
    // is in range
    return (row >= 0) && (row < ROW) && (col >= 0)
        && (col < COL);
}

//Checks if a cell is blocked or not
bool isUnBlocked(int grid[][COL], int row, int col)
{
    // Returns true if the cell is not blocked else false
//    if (grid[row][col] == 1)
    if (grid[row][col] == 0)
        return (true);
    else
        return (false);
}

//Checks if we have reached the destination
bool isDestination(int row, int col, Pair dest)
{
    if (row == dest.first && col == dest.second)
        return (true);
    else
        return (false);
}

//Calculates heuristics using Manhatten Distance formula
double calculateHValue(int row, int col, Pair dest)
{
    return abs(row - dest.first) + abs(col - dest.second);
}

// A Utility Function to trace the path from the source
// to destination

//TODO: in this function once we have the full path, figure out the directions we need to move
//      eg, L,R,U,D and save the order of the movements in a character array.
//      To find what direction to move, compare position to position before and based on the value that has changed
//      figure out what direction we have moved
//      Then return the character array
vector<string> tracePath(cell cellDetails[][COL], Pair dest, int grid[][COL])
{
    int row = dest.first;
    int col = dest.second;

    stack<Pair> Path;
    stack<Pair> dupPath;
    Pair currentPair, nextPair;



    while (!(cellDetails[row][col].parent_i == row
        && cellDetails[row][col].parent_j == col)) {
        Path.push(make_pair(row, col));
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }
    Path.push(make_pair(row, col));
    vector<string> directions;

    dupPath = Path;


    //Compare the current position to the next position and determine how we 
    //moved to get to that position
    currentPair = dupPath.top();
    dupPath.pop();
    nextPair = dupPath.top();
    for (int i = 0; i < Path.size() - 1; i++) {
        if (currentPair.first - 1 == nextPair.first) {

            directions.emplace_back("U");
        }
        else if (currentPair.second + 1 == nextPair.second) {
            directions.emplace_back("R");
        }
        else if (currentPair.first + 1 == nextPair.first) {
            directions.emplace_back("D");
        }
        else if (currentPair.second - 1 == nextPair.second) {
            directions.emplace_back("L");
        }
        dupPath.pop();
        currentPair = nextPair;
        nextPair = dupPath.top();
    }

    printf("\nThe Path is ");
    while (!Path.empty()) {
        pair<int, int> p = Path.top();
        Path.pop();
        printf("-> (%d,%d) ", p.first, p.second);
        grid[p.first][p.second] = 9;
    }

    //    cout<<"\nMaze with path shown (by 9's)"<<endl;
    //    for(int i=0; i<ROW; i++){
    //        for(int j=0; j<COL; j++){
    //           printf("%d ", grid[i][j]);
    //        }
    //        cout<<"\n";
    //    }

    return directions;

}

// A Function to find the shortest path between
// a given source cell to a destination cell according
// to A* Search Algorithm
vector<string> aStar(int grid[][COL], Pair src, Pair dest)
{

    vector<string> emptyVector;
    // If the source is out of range
    if (!isValid(src.first, src.second)) {
        printf("Source is invalid\n");
        return emptyVector;
    }

    // If the destination is out of range
    if (!isValid(dest.first, dest.second)) {
        printf("Destination is invalid\n");
        return emptyVector;
    }

    // Either the source or the destination is blocked
    if (!isUnBlocked(grid, src.first, src.second)
        || !isUnBlocked(grid, dest.first, dest.second)) {
        printf("Source or the destination is blocked\n");
        return emptyVector;
    }

    // If the destination cell is the same as source cell
    if (isDestination(src.first, src.second, dest)) {
        printf("We are already at the destination\n");
        return emptyVector;
    }

    // Create a closed list and initialise it to false which
    // means that no cell has been included yet This closed
    // list is implemented as a boolean 2D array
    bool closedList[ROW][COL];
    memset(closedList, false, sizeof(closedList));

    //2D array of cells
    cell cellDetails[ROW][COL];

    int i, j;

    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }

    // Initialising the parameters of the starting node
    i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;

    /*
    Create an open list having information as-
    <f, <i, j>>
    where f = g + h,
    and i, j are the row and column index of that cell
    Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
    This open list is implemented as a set of pair of
    pair.*/
    set<pPair> openList;

    // Put the starting cell on the open list and set its
    // 'f' as 0
    openList.insert(make_pair(0.0, make_pair(i, j)));

    // We set this boolean value as false as initially
    // the destination is not reached.
    bool foundDest = false;

    while (!openList.empty()) {
        pPair p = *openList.begin();

        // Remove this vertex from the open list
        openList.erase(openList.begin());

        // Add this vertex to the closed list
        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;


        // To store the 'g', 'h' and 'f' of the  directions
        double gNew, hNew, fNew;

        //----------- 1st Successor (North) ------------

        // Check if valid
        if (isValid(i - 1, j)) {
            // If the destination cell is the same as the
            // current successor
            if (isDestination(i - 1, j, dest)) {
                // Set the Parent of the destination cell
                cellDetails[i - 1][j].parent_i = i;
                cellDetails[i - 1][j].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest, grid);
                foundDest = true;
                return tracePath(cellDetails, dest, grid);;
            }
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (!closedList[i - 1][j]
                && isUnBlocked(grid, i - 1, j)) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i - 1, j, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //			 OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i - 1][j].f == FLT_MAX
                    || cellDetails[i - 1][j].f > fNew) {
                    openList.insert(make_pair(
                        fNew, make_pair(i - 1, j)));

                    // Update the details of this cell
                    cellDetails[i - 1][j].f = fNew;
                    cellDetails[i - 1][j].g = gNew;
                    cellDetails[i - 1][j].h = hNew;
                    cellDetails[i - 1][j].parent_i = i;
                    cellDetails[i - 1][j].parent_j = j;
                }
            }
        }

        //----------- 2nd Successor (South) ------------

        // Check if valid
        if (isValid(i + 1, j)) {
            // If updated cell position is the destination
            if (isDestination(i + 1, j, dest)) {
                // Set the Parent of the destination cell
                cellDetails[i + 1][j].parent_i = i;
                cellDetails[i + 1][j].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest, grid);
                foundDest = true;
                return tracePath(cellDetails, dest, grid);;
            }
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (!closedList[i + 1][j]
                && isUnBlocked(grid, i + 1, j)) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i + 1, j, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //			 OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i + 1][j].f == FLT_MAX
                    || cellDetails[i + 1][j].f > fNew) {
                    openList.insert(make_pair(
                        fNew, make_pair(i + 1, j)));
                    // Update the details of this cell
                    cellDetails[i + 1][j].f = fNew;
                    cellDetails[i + 1][j].g = gNew;
                    cellDetails[i + 1][j].h = hNew;
                    cellDetails[i + 1][j].parent_i = i;
                    cellDetails[i + 1][j].parent_j = j;
                }
            }
        }

        //----------- 3rd Successor (East) ------------

        // Check if valid
        if (isValid(i, j + 1)) {
            // If updated cell position is the destination
            if (isDestination(i, j + 1, dest)) {
                // Set the Parent of the destination cell
                cellDetails[i][j + 1].parent_i = i;
                cellDetails[i][j + 1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest, grid);
                foundDest = true;
                return tracePath(cellDetails, dest, grid);;
            }

            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (!closedList[i][j + 1]
                && isUnBlocked(grid, i, j + 1)) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j + 1, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //			 OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i][j + 1].f == FLT_MAX
                    || cellDetails[i][j + 1].f > fNew) {
                    openList.insert(make_pair(
                        fNew, make_pair(i, j + 1)));

                    // Update the details of this cell
                    cellDetails[i][j + 1].f = fNew;
                    cellDetails[i][j + 1].g = gNew;
                    cellDetails[i][j + 1].h = hNew;
                    cellDetails[i][j + 1].parent_i = i;
                    cellDetails[i][j + 1].parent_j = j;
                }
            }
        }

        //----------- 4th Successor (West) ------------

        // Check if valid
        if (isValid(i, j - 1)) {
            // If updated cell position is the destination
            if (isDestination(i, j - 1, dest)) {
                // Set the Parent of the destination cell
                cellDetails[i][j - 1].parent_i = i;
                cellDetails[i][j - 1].parent_j = j;
                printf("The destination cell is found\n");
                foundDest = true;
                return tracePath(cellDetails, dest, grid);;
            }

            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (!closedList[i][j - 1]
                && isUnBlocked(grid, i, j - 1)) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j - 1, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //			 OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i][j - 1].f == FLT_MAX
                    || cellDetails[i][j - 1].f > fNew) {
                    openList.insert(make_pair(
                        fNew, make_pair(i, j - 1)));

                    // Update the details of this cell
                    cellDetails[i][j - 1].f = fNew;
                    cellDetails[i][j - 1].g = gNew;
                    cellDetails[i][j - 1].h = hNew;
                    cellDetails[i][j - 1].parent_i = i;
                    cellDetails[i][j - 1].parent_j = j;
                }
            }
        }

    }

    // When the destination cell is not found and the open
    // list is empty, then we conclude that we failed to
    // reach the destination cell. This may happen when the
    // there is no way to destination cell (due to
    // blockages)
    printf("Failed to find the Destination Cell\n");
    return emptyVector;
}
