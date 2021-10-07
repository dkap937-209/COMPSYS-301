
#ifndef ASTAR_A_STAR_HEADER_H
#define ASTAR_A_STAR_HEADER_H

#define ROW 9
#define COL 10
typedef std::pair<int, int> Pair;

void aStarSearch(int grid[][COL], Pair src, Pair dest);

#endif //ASTAR_A_STAR_HEADER_H
