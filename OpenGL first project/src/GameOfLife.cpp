#include "GameOfLife.h"

Game::Game(unsigned int a)
{
	
}

Game::~Game()
{

}

void Game::PrintBoard() {

}

bool Game::DoesTileExsist(int row, int colllum, std::vector<std::vector<int>> OldBoard)
{
	const int Boardsize = OldBoard.size();
	int i = 0;
	while (i < Boardsize) {
		if (OldBoard[i][0] == row && OldBoard[i][1] == colllum) {
			return true;
		}
		i++;
	}

	return false;
}
unsigned int Game :: CountNeighbors(int row, int collum, std::vector<std::vector<int>> OldBoard)
{
	unsigned int counter = 0;
	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			if (!(j == 0 && i == 0) && DoesTileExsist(row + i, collum + j,OldBoard)) {
				counter++;
			}
		}
	}
	return counter;
}
void Game :: AddTile(int row, int collum, std::vector<std::vector<int>> OldBoard)
{
	const int Boardsize = OldBoard.size();
	int i = 0;
	while (i < Boardsize && OldBoard[i][0]<row && (i+1 < Boardsize && OldBoard[i + 1][0]<row)) {
		i++;
	}

	while (i < Boardsize && OldBoard[i][1] <= collum) {
		i++;
	}

	OldBoard.insert(OldBoard.begin() + i, { row,collum });
}

void Game::RemoveTile(int Row, int Collum,std::vector<std::vector<int>> OldBoard) {
	const int Boardsize = OldBoard.size();
	int i = 0;
	while (i < Boardsize && OldBoard[i][0] != Row) {
		i++;
	}
	if (OldBoard[i][0] == Row) {
		while (i < Boardsize && OldBoard[i][1] != Collum && OldBoard[i][1]==Row) {
			i++;
		}

		if (OldBoard[i][1] == Collum && OldBoard[i][1] == Row) {
			OldBoard.erase(OldBoard.begin() + i);
		}
		else
			std::cout << "tile does not exsist" << std::endl;
	}
	else
		std::cout << "tile does not exsist" << std::endl;
}
void Game :: UpdateTile(unsigned int row, unsigned int collum,std::vector<std::vector<int>> OldBoard)
{
	unsigned int Neighbors = CountNeighbors(row, collum,OldBoard);
	std::cout << Neighbors;
	if (DoesTileExsist(row, collum, OldBoard)) {
		if (Neighbors != 3 && Neighbors != 2) {
			RemoveTile(row, collum,OldBoard);
		}
	}
	else if (Neighbors == 3) {
		AddTile(row, collum,OldBoard);
	}
}


void Game::UpdateBoard()
{
	std::vector<std::vector<int>> OldBoard = Board;

	for (int i = 0; i < OldBoard.size(); ++i) {
		for (int j = 0; j <= OldBoard.size(); ++j) {
			UpdateTile(i, j, OldBoard);
		}
	}
	Board = OldBoard;
}