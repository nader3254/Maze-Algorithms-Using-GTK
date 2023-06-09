#include "fusion.h"

fusion::fusion(int xsize, int ysize)
{
    winNumberx = xsize;
    winNumbery = ysize;

    visited.push_back({0, 0});
}
cell fusion::getRandom()
{
    int x = 60; // Lower bound
    int y = 740; // Upper bound

    std::random_device rd;                         // Obtain a random seed from the hardware
    std::mt19937 eng(rd());                        // Initialize the random number engine
    std::uniform_int_distribution<int> dist(x, y); // Define the range of random numbers

    int randomNum = dist(eng);

    int x2 = 60; // Lower bound
    int y2 = 540; // Upper bound

    std::random_device rd2;                           // Obtain a random seed from the hardware
    std::mt19937 eng2(rd2());                         // Initialize the random number engine
    std::uniform_int_distribution<int> dist2(x2, y2); // Define the range of random numbers

    int randomNum2 = dist2(eng);

    int xstep = 800/winNumberx;
    int ystep = 600/winNumbery;
    cell tmp;
    tmp.x = randomNum;
    tmp.y = randomNum2;
    return tmp;
}
bool fusion::canImove(cell pos)
{

    for (int i = 0; i < visited.size(); i++)
    {
        if ((pos.x == visited.at(i).x) && (pos.y == visited.at(i).y))
        {
            return false;
        }
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
bool fusion::CheckWin()
{

    int score = 0;
    std::vector<cell> tmp;

    if ((visited.size() - 1) == (winNumberx * winNumbery) - 2)
    {
        return true;
    }
    else
    {
        return false;
    }
}
std::vector<cell> fusion::getVisited()
{
    std::cout << "\nlastx" << visited.at(visited.size() - 1).x << "\nlasty" << visited.at(visited.size() - 1).y << "\n";
    return visited;
}