#define FLT_MAX 999999
#include "Astar_Header.h"
using namespace std;

// Creating a shortcut for int, int pair type
typedef pair<int, int> Pair;
// Creating a shortcut for tuple<int, int, int> type
typedef tuple<double, int, int> Tuple;

// A structure to hold the necessary parameters
struct cell {
    // Row and Column index of its parent
    Pair parent;
    // f = g + h
    double f, g, h;
    cell()
        : parent(-1, -1)
        , f(-1)
        , g(-1)
        , h(-1)
    {
    }
};

// A Utility Function to check whether given cell (row, col)
// is a valid cell or not.
//template <size_t ROW, size_t COL>
bool isValid(const array<array<int, COL>, ROW>& grid, const Pair& point)
{ // Returns true if row number and column number is in
// rang
    if (ROW > 0 && COL > 0)
        return (point.first >= 0) && (point.first < ROW)
        && (point.second >= 0)
        && (point.second < COL);

    return false;
}

// A Utility Function to check whether the given cell is
// blocked or not
//template <size_t ROW, size_t COL>
bool isUnBlocked(const array<array<int, COL>, ROW>& grid,
    const Pair& point)
{
    if (grid[point.first][point.second] == 0)
        return true;
    return false;
}

// A Utility Function to check whether destination cell has
// been reached or not
bool isDestination(const Pair& position, const Pair& dest) {
    return position == dest;
}

// A Utility Function to calculate the 'h' heuristics.
double calculateHValue(const Pair& src, const Pair& dest)
{
    // h is estimated with the two points distance formula
    return sqrt(pow((src.first - dest.first), 2.0)
        + pow((src.second - dest.second), 2.0));
}

// A Utility Function to trace the path from the source to
// destination

vector<pPair> tracePath(
    const array<array<cell, COL>, ROW>& cellDetails,
    const Pair& dest)
{
    printf("\nThe Path is ");

    stack<Pair> Path;
    stack<Pair> dupPath;
    Pair currentPair, nextPair;

    int row = dest.first;
    int col = dest.second;

    while (!(cellDetails[row][col].parent.first == row
        && cellDetails[row][col].parent.second == col)) {
        Path.push(make_pair(row, col));
        int temp_row = cellDetails[row][col].parent.first;
        int temp_col = cellDetails[row][col].parent.second;
        row = temp_row;
        col = temp_col;
    }
    Path.push(make_pair(row, col));
    vector<pPair> directions;

    dupPath = Path;

    currentPair = dupPath.top();
    dupPath.pop();
    nextPair = dupPath.top();
    for (int i = 0; i < Path.size() - 1; i++) {
        if (currentPair.first - 1 == nextPair.first) {

            directions.emplace_back(make_pair("U", currentPair));
        }
        else if (currentPair.second + 1 == nextPair.second) {
            directions.emplace_back(make_pair("R", currentPair));
        }
        else if (currentPair.first + 1 == nextPair.first) {
            directions.emplace_back(make_pair("D", currentPair));
        }
        else if (currentPair.second - 1 == nextPair.second) {
            directions.emplace_back(make_pair("L", currentPair));
        }
        dupPath.pop();
        currentPair = nextPair;
        if (dupPath.size() != 0) {
            nextPair = dupPath.top();
        }
    }

    /*while (!Path.empty()) {
        pair<int, int> p = Path.top();
        Path.pop();
        printf("-> (%d,%d) ", p.first, p.second);
    }*/

    return directions;
}

vector<pPair> aStarSearch(const array<array<int, COL>, ROW>& grid,
    const Pair& src, const Pair& dest)
{

    // If the source is out of range
    if (!isValid(grid, src)) {
        printf("Source is invalid\n");
        return {};
    }

    // If the destination is out of range
    if (!isValid(grid, dest)) {
        printf("Destination is invalid\n");
        return {};
    }

    // Either the source or the destination is blocked
    if (!isUnBlocked(grid, src)) {
        printf("Source is blocked\n");
        return {};
    }

    if (!isUnBlocked(grid, dest)) {
        printf("destination is blocked\n");
        return {};
    }

    // If the destination cell is the same as source cell
    if (isDestination(src, dest)) {
        printf("We are already at the destination\n");
        return {};
    }

    // Create a closed list and initialise it to false which
    // means that no cell has been included yet This closed
    // list is implemented as a boolean 2D array
    bool closedList[ROW][COL];
    memset(closedList, false, sizeof(closedList));

    // Declare a 2D array of structure to hold the details
    // of that cell
    array<array<cell, COL>, ROW> cellDetails;
    int i, j;

    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent = { -1, -1 };
        }
    }

    // Initialising the parameters of the starting node
    i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent = { i, j };
    typedef pair<double, pair<int, int> > pPair;
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

        // To store the 'g', 'h' and 'f' of the 8 successors
        double gNew, hNew, fNew;

        //----------- 1st Successor (North) ------------

        Pair position(i - 1, j);
        // Only process this cell if this is a valid one
        if (isValid(grid, position)) {
            // If the destination cell is the same as the
            // current successor
            if (isDestination(position, dest)) {
                // Set the Parent of the destination cell
                cellDetails[i - 1][j].parent.first = i;
                cellDetails[i - 1][j].parent.second = j;
                printf("The destination cell is found\n");
                foundDest = true;
                return tracePath(cellDetails, dest);
            }
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (!closedList[i - 1][j]
                && isUnBlocked(grid, position)) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(position, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
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
                    cellDetails[i - 1][j].parent.first = i;
                    cellDetails[i - 1][j].parent.second = j;
                }
            }
        }

        //----------- 2nd Successor (South) ------------

        Pair positionSouth(i + 1, j);
        // Only process this cell if this is a valid one
        if (isValid(grid, positionSouth)) {
            // If the destination cell is the same as the
            // current successor
            if (isDestination(positionSouth, dest)) {
                // Set the Parent of the destination cell
                cellDetails[i + 1][j].parent.first = i;
                cellDetails[i + 1][j].parent.second = j;
                printf("The destination cell is found\n");
                printf("Destination is (%d, %d)\n", dest.first, dest.second);
                printf("I and J, (%d, %d)\n", i, j);
                foundDest = true;
                return tracePath(cellDetails, dest);
            }
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (!closedList[i + 1][j]
                && isUnBlocked(grid, positionSouth)) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(positionSouth, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
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
                    cellDetails[i + 1][j].parent.first = i;
                    cellDetails[i + 1][j].parent.second = j;
                }
            }
        }

        //----------- 3rd Successor (East) ------------

        Pair positionEast(i, j + 1);
        // Only process this cell if this is a valid one
        if (isValid(grid, positionEast)) {
            // If the destination cell is the same as the
            // current successor
            if (isDestination(positionEast, dest)) {
                // Set the Parent of the destination cell
                cellDetails[i][j + 1].parent.first = i;
                cellDetails[i][j + 1].parent.second = j;
                printf("The destination cell is found\n");
                foundDest = true;
                return tracePath(cellDetails, dest);
            }

            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (!closedList[i][j + 1]
                && isUnBlocked(grid, positionEast)) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(positionEast, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
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
                    cellDetails[i][j + 1].parent.first = i;
                    cellDetails[i][j + 1].parent.second = j;
                }
            }
        }

        //----------- 4th Successor (West) ------------

        Pair positionWest(i, j - 1);
        // Only process this cell if this is a valid one
        if (isValid(grid, positionWest)) {
            // If the destination cell is the same as the
            // current successor
            if (isDestination(positionWest, dest)) {
                // Set the Parent of the destination cell
                cellDetails[i][j - 1].parent.first = i;
                cellDetails[i][j - 1].parent.second = j;
                printf("The destination cell is found\n");
                foundDest = true;
                return tracePath(cellDetails, dest);
            }

            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (!closedList[i][j - 1]
                && isUnBlocked(grid, positionWest)) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(positionWest, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
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
                    cellDetails[i][j - 1].parent.first = i;
                    cellDetails[i][j - 1].parent.second = j;
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
    return {};
}

