#include "GameOfLife.h"

Game::Game(int RowCount, int CollumCount)
{
	Board.reserve(RowCount);
	for (int i = 0; i < RowCount; ++i)
	{
		Board[i].reserve(CollumCount);
		for (int j = 0; j < CollumCount; ++j)
		{
			Board[i][j] = false;
		}
	}
}

Game::~Game()
{

}

unsigned int Game :: CountNeighbors(unsigned int row, unsigned int collum)
{
	int counter = 0;
	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			if (Board[row + i][row + j] && (i == 0 && j == 0)) {
				counter++;
			}
		}
	}
	return counter;
}
void Game :: UpdateTile(unsigned int row, unsigned int collum)
{
	unsigned int neighbers = CountNeighbors(row, collum);
	if (Board[row][collum] == true) {
		if (neighbers != 2 && neighbers != 3)
			Board[row][collum] = false;
	}
	else if (neighbers == 3) {
		Board[row][collum] = true;
	}
	//maybe write straight into memory address
}

void Game :: ChangeTile(unsigned int row, unsigned int collum)
{
	Board[row][collum] = !Board[row][collum];
}


void Game::UpdateBoard()
{
	//scale rows up by 1
	std::vector<bool> v1(Board[0].size(),false);
	v1.reserve(Board[0].capacity());
	Board.insert(Board.begin(),v1);
	Board.push_back(v1);


	for (int i = 0; i < Board.size();++i) {
		//scale collums up by 1
		Board[i].insert(Board[i].begin(), false);
		Board[i].push_back(false);
		for (int j = 0; j < Board[i].size(); ++j) {
			UpdateTile(i, j);
		}
	}
}