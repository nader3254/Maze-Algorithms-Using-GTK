#include "aldos-broder.h"

aldosBroder::aldosBroder(int xsize, int ysize)
{
    winNumberx = xsize ;
    winNumbery = ysize ;

    visited.push_back({0, 0});
}
bool aldosBroder::canImove(cell pos)
{

    for (int i = 0; i < visited.size(); i++)
    {

    }

    int a = 0;
    for (int i = 0; i < visited.size(); i++)
    {
        if ((pos.x == visited.at(i).x) && (pos.y == visited.at(i).y))
        {
            a++;
            break;
        }
        else
        {
        }
    }
    if (a == 0)
    {
        std::cout << "inserting visited" << visited.size() << " " << (winNumberx * winNumbery) << std::endl;
        visited.push_back(pos);
        return true;
    }
    return true;
}
bool aldosBroder::CheckWin()
{

    int score = 0;
    std::vector<cell> tmp;

    if ((visited.size() - 1) == (winNumberx * winNumbery)-2)
    {
        return true;
    }
    else
    {
        return false;
    }
}
std::vector<cell> aldosBroder::getVisited()
{
    std::cout << "\nlastx" << visited.at(visited.size() - 1).x << "\nlasty" << visited.at(visited.size() - 1).y << "\n";
    return visited;
}