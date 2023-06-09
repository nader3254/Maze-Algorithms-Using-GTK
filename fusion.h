#ifndef FUSION_H
#define FUSION_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include "aldos-broder.h"
#include <random>

class fusion
{
public:
    fusion(int xsize, int ysize);
    bool canImove(cell pos);
    bool CheckWin();
    void rst();
    std::vector<cell> getVisited();
    cell getRandom();

private:
    std::vector<cell> visited;
    std::vector<cell> winVector;
    int winNumberx, winNumbery;
};
#endif // HEADER_FILE_NAME_H
