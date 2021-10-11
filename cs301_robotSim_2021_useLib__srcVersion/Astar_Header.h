
using namespace std;

#ifndef ASTAR_A_STAR_HEADER_H
#define ASTAR_A_STAR_HEADER_H

#define ROW 9
#define COL 10
#include <vector>
#include <string>
#include <queue>
#include <array>
#include <cmath>
#include "A_star_header.h"
#include <array>
#include <chrono>
#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <tuple>
#include <vector>
#include <string>
#include <stack>
typedef pair<int, int> Pair;
typedef tuple<double, int, int> Tuple;
typedef pair<double, pair<int, int> > pPair;

vector<string> aStarSearch(const array<array<int, COL>, ROW>& grid, const Pair& src, const Pair& dest);
#endif //ASTAR_A_STAR_HEADER_H