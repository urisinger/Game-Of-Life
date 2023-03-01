#include <vector>
#include <iostream>
#include <algorithm>
#include <math.h>

class Game
{
private:
	unsigned int CountNeighbors(int row, int collum, std::vector<std::vector<int>> OldBoard);
	void UpdateTile(int row, int collum, std::vector<std::vector<int>> OldBoard);
	bool DoesTileExsist(int row, int colllum, std::vector<std::vector<int>> OldBoard);
	int returnminmax(unsigned int index,int minmax);
public:
	std::vector < std ::vector<int>> Board;
	Game(unsigned int a);
	~Game();

	void AddTile(int Row, int Collum, std::vector<std::vector<int>> OldBoard);
	void RemoveTile(int Row, int Collum, std::vector<std::vector<int>> OldBoard);

	void UpdateBoard();

	void PrintBoard();
};