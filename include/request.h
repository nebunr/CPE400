#include <vector>
#include <utility>

struct Request
{
    std::vector<std::pair<int,int>> path;
    int totalCost;

    Request(std::vector<std::pair<int,int>> p, int c): path(p), totalCost(c) {}
};