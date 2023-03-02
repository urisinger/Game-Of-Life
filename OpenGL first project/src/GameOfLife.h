#include <vector>
#include <iostream>
#include <algorithm>


struct cell
{
	int x;
	int y;
	cell(int Row, double Collum) {
		x = Row;
		y = Collum;
	}

};

class Game
{
private:
	unsigned int CountNeighbors(int row, int collum);
	bool DoesTileExsist(int row, int colllum);
	int returnminmax(unsigned int index,int minmax);
public:
	std::vector<cell> CurrentBoard;
	std::vector<cell> NextBoard;
	Game(unsigned int a);

	void ChangeTile(int Row, int Collum);
	void AddTile(int Row, int Collum);
	void RemoveTile(int Row, int Collum);

	void UpdateBoard();

	void PrintBoard();
};