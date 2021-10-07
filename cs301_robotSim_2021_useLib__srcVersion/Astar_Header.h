
using namespace std;
#include <vector>
#include <string>
#ifndef ASTAR_A_STAR_HEADER_H
#define ASTAR_A_STAR_HEADER_H

#define ROW 15
#define COL 19
#define FLT_MAX 99999
typedef std::pair<int, int> Pair;

vector<string> aStar(int grid[][COL], Pair src, Pair dest);

#endif //ASTAR_A_STAR_HEADER_H
