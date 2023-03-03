#pragma once

#include <vector>
#include <iostream>
struct Point {
    int x, y;
    Point(int a, int b) : x(a), y(b) {}
};
class Game {
public:
    Game(unsigned int s);

    void PrintBoard();
    void UpdateBoard();
    void ChangeTile(int row, int col);

    std::vector<Point> currentBoard;
    std::vector<Point> nextBoard;

private:

    bool DoesTileExist(int row, int col) const;
    void RemoveTile(int row, int col);
    unsigned int CountNeighbors(int row, int col) const;
    int GetMinMax(unsigned int index, int minmax) const;
};