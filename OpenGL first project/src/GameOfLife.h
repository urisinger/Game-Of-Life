#pragma once

#include <vector>
#include <iostream>
#include <unordered_set>

using namespace std;
struct hash_pair {
    size_t operator()(const std::pair<int, int>& p) const {
        return (size_t)(p.first * 1000 + p.second); // any reasonable hash of p.first with p.second will do
    }
};


class Game {
public:
    Game() {};

    void UpdateBoard();
    void ChangeTile(int row, int col);


    unordered_set<pair<int,int>, hash_pair> currentBoard;
    unordered_set<pair<int,int>, hash_pair> nextBoard;

private:
    unsigned int CountNeighbors(int row, int col) const;
};