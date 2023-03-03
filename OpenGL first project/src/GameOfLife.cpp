#include "GameOfLife.h"

Game::Game(unsigned int a)
{

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
	nextBoard.clear();
	std::unordered_set<std::pair<int, int>,hash_pair> processedCells;

	for (const auto& cell : currentBoard) {
		for (int i = -1; i <= 1; ++i) {
			for (int j = -1; j <= 1; ++j) {
				processedCells.emplace(cell.first + i, cell.second + j);
				unsigned int neighbors = CountNeighbors(cell.first+i, cell.second+j);
				pair<int, int> p = { cell.first + i, cell.second + j };
				if (currentBoard.find(p) != currentBoard.end()) {
					if ((neighbors == 3 || neighbors == 2)) {
						nextBoard.emplace(cell.first + i, cell.second + j);
					}
				}
				else if (neighbors == 3) {
					nextBoard.emplace(cell.first + i, cell.second + j);
				}

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