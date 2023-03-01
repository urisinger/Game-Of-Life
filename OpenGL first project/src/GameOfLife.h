#include <vector>
#include <iostream>
#include <algorithm>

class Game
{
private:
	unsigned int CountNeighbors(int row, int collum, std::vector<std::vector<int>> OldBoard);
	void UpdateTile(unsigned int row, unsigned int collum, std::vector<std::vector<int>> OldBoard);
	bool DoesTileExsist(int row, int colllum, std::vector<std::vector<int>> OldBoard);
	void AddTile(int Row, int Collum, std::vector<std::vector<int>> OldBoard);
	void RemoveTile(int Row, int Collum, std::vector<std::vector<int>> OldBoard);

public:
	std::vector < std ::vector<int>> Board;
	Game(unsigned int a);
	~Game();

	void UpdateBoard();

	void PrintBoard();
};