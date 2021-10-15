
using namespace std;

#ifndef ASTAR_A_STAR_HEADER_H
#define ASTAR_A_STAR_HEADER_H

constexpr auto ROW = 15;
constexpr auto COL = 19;
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


vector<string> aStarSearch(int grid[][COL], Pair src, Pair dest);

#endif //ASTAR_A_STAR_HEADER_H