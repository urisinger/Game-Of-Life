#include "GameOfLife.h"

Game::Game(unsigned int a)
{

}

void DrawBoard() {

}

unsigned int Game::CountNeighbors(int row, int col) const
{
	unsigned int counter = 0;
	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			if (j == 0 && i == 0) continue;
			counter += currentBoard.find({ row + i, col + j }) != currentBoard.end();
		}
	}
	return counter;
}


void Game::UpdateBoard()
{
	int maxRow = INT_MIN;
	int minRow = INT_MAX;
	int maxCol = INT_MIN;
	int minCol = INT_MAX;

	for (const auto& cell : currentBoard) {
		maxRow = std::max(maxRow, cell.first);
		minRow = std::min(minRow, cell.first);
		maxCol = std::max(maxCol, cell.second);
		minCol = std::min(minCol, cell.second);
	}

	nextBoard.clear();

	for (int i = minRow - 1; i <= maxRow + 1; ++i) {
		for (int j = minCol - 1; j <= maxCol + 1; ++j) {
			unsigned int neighbors = CountNeighbors(i, j);
			pair<int, int> p = { i, j };
			if (currentBoard.find(p) != currentBoard.end()) {
				if ((neighbors == 3 || neighbors == 2)) {
					nextBoard.emplace(i, j);
				}
			}
			else if (neighbors == 3) {
				nextBoard.emplace(i,j);
			}

		}
	}
	currentBoard = nextBoard;
}

void Game::ChangeTile(int Row, int Column) {
	pair<int, int> p = { Row, Column };
	auto itor = currentBoard.find(p);
		if (itor == currentBoard.end()) {
			currentBoard.emplace(Row,Column);
		}
		else {
			currentBoard.erase(p);
		}
}