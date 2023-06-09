#ifndef ALDOS_H
#define ALDOS_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <set>

typedef struct {
  int x;
  int y;
} cell;



class aldosBroder
{
public:
    aldosBroder(int xsize, int ysize);
    bool canImove(cell pos);
    bool CheckWin();
    void rst();
    std::vector<cell> getVisited();

private:
    std::vector<cell> visited;
    std::vector<cell> winVector;
    int winNumberx, winNumbery;
};
#endif // HEADER_FILE_NAME_H
