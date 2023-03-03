#include "GameOfLife.h"

Game::Game(unsigned int a)
{

}

void Game::PrintBoard() {

	int maxRow = GetMinMax(0, 1);
	int minRow = GetMinMax(0, -1);
	int maxCol = GetMinMax(1, 1);
	int minCol = GetMinMax(1, -1);

	for (int i = minRow; i <= maxRow; ++i) {
		for (int j = minCol; j <= maxCol; ++j) {
			std::cout << DoesTileExist(i, j) << "|";
		}
		std::cout << std::endl;
	}
}

bool Game::DoesTileExist(int row, int col) const
{
	const int boardSize = currentBoard.size();
	int i = 0;
	while (i < boardSize) {
		if (currentBoard[i].x == row && currentBoard[i].y == col) {
			return true;
		}
		i++;
	}
	return false;
}

unsigned int Game::CountNeighbors(int row, int col) const
{
	unsigned int counter = 0;
	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			if (!(j == 0 && i == 0)) {
				counter += DoesTileExist(row + i, col + j);
			}
		}
	}
	return counter;
}

void Game::RemoveTile(int row, int col) {
	const int boardSize = nextBoard.size();
	int i = 0;
	while (i < boardSize) {
		if (nextBoard[i].x == row && nextBoard[i].y == col) {
			nextBoard.erase(nextBoard.begin() + i);
			return;
		}
		i++;
	}
	std::cout << "Tile not found.";
}

int Game::GetMinMax(unsigned int index, int minMax) const{

	int output = -minMax * 2147483646;
	if (index == 0) {
		for (int i = 0; i < currentBoard.size(); i++) {
			output = currentBoard[i].x * ((minMax * currentBoard[i].x) >= (minMax * output)) + output * ((minMax * currentBoard[i].x) < (minMax * output));
		}
	}
	else {
		for (int i = 0; i < currentBoard.size(); i++) {
			output = currentBoard[i].y * ((minMax * currentBoard[i].y) >= (minMax * output)) + output * ((minMax * currentBoard[i].y) < (minMax * output));
		}
	}
	return output;
}

void Game::UpdateBoard()
{
	int maxRow = GetMinMax(0, 1);
	int minRow = GetMinMax(0, -1);
	int maxCol = GetMinMax(1, 1);
	int minCol = GetMinMax(1, -1);

	nextBoard = currentBoard;

	for (int i = minRow - 1; i <= maxRow + 1; ++i) {
		for (int j = minCol - 1; j <= maxCol + 1; ++j) {
			unsigned int neighbors = CountNeighbors(i, j);
			if (DoesTileExist(i, j)) {
				if (neighbors != 3 && neighbors != 2) {
					RemoveTile(i, j);
				}
			}
			else if (neighbors == 3) {
				nextBoard.emplace_back(i, j);
			}
		}
	}
	currentBoard = nextBoard;
}

void Game::ChangeTile(int Row, int Collum) {
	if (DoesTileExist(Row, Collum)) {
		const int Boardsize = currentBoard.size();
		int i = 0;
		while (i < Boardsize) {
			if (currentBoard[i].x == Row && currentBoard[i].y == Collum) {
				currentBoard.erase(currentBoard.begin() + i);
				return;
			}
			i++;
		}
	}
	else {
		currentBoard.emplace_back(Row, Collum);
	}
}