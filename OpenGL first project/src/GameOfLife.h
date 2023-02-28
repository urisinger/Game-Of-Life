#include <vector>
#include <random>


class Game
{
private:
	unsigned int CountNeighbors(unsigned int row, unsigned int collum);
	void UpdateTile(unsigned int row, unsigned int collum);
public:
	std::vector<std::vector<bool>> Board;
	Game(int row, int collum);
	~Game();

	void ChangeTile(unsigned int Row,unsigned int Collum);
	void UpdateBoard();
};