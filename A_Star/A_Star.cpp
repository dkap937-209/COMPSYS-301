#include <bits/stdc++.h>
#include "A_star_header.h"
#include <iostream>

using namespace std;

#define ROW 9
#define COL 10

// Creating a shortcut for int, int pair type
typedef pair<int, int> Pair;

// Creating a shortcut for pair<int, pair<int, int>> type
typedef pair<double, pair<int, int> > pPair;


// Driver program to test above function
int main()
{
    /* Description of the Grid-
    0--> The cell is not blocked
    1--> The cell is blocked */
    int grid[ROW][COL]
            =  { { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
                 { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
                 { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
                 { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
                 { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
                 { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
                 { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
                 { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
                 { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 } };

    // Source is the left-most bottom-most corner
    Pair src = make_pair(7, 1);

    // Destination is the left-most top-most corner
    Pair dest = make_pair(6, 2);

    aStarSearch(grid, src, dest);

    return (0);
}
