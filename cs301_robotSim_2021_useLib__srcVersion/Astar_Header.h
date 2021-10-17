
using namespace std;

#ifndef ASTAR_A_STAR_HEADER_H
#define ASTAR_A_STAR_HEADER_H

constexpr auto ROW = 15;
constexpr auto COL = 19;
//constexpr auto MAX = 99999;
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
#include <sstream>
typedef pair<int, int> Pair;
typedef tuple<double, int, int> Tuple;
typedef pair<string, pair<int, int> > pPair;


vector<pPair> aStarSearch(const array<array<int, COL>, ROW>& grid,const Pair& src, const Pair& dest);
#endif //ASTAR_A_STAR_HEADER_H