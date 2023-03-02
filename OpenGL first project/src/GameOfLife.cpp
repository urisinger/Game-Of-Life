#include "GameOfLife.h"


Game::Game(unsigned int a)
{
	
}


void Game::PrintBoard() {

	int MaxRows = returnminmax(0, 1);
	int MinRows = returnminmax(0, -1);
	int MaxCollums = returnminmax(1, 1);
	int MinCollums = returnminmax(1, -1);

	for (int i = MinRows; i <= MaxRows; ++i) {
		for (int j = MinCollums; j <= MaxCollums; ++j) {
			std::cout << DoesTileExsist(i, j)<<"|";
		}
		std::cout << std::endl;
	}
}

bool Game::DoesTileExsist(int row, int colllum)
{
	const int Boardsize = CurrentBoard.size();
	int i = 0;
	while (i < Boardsize) {
		if (CurrentBoard[i].x == row && CurrentBoard[i].y == colllum) {
			return true;
		}
		i++;
	}

	return false;
}
unsigned int Game :: CountNeighbors(int row, int collum)
{
	unsigned int counter = 0;
	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			if (!(j == 0 && i == 0)) {
				counter += DoesTileExsist(row + i, collum + j);
			}
		}
	}
	return counter;
}

void Game::RemoveTile(int Row, int Collum) {
	const int Boardsize = NextBoard.size();
	int i = 0;
	while (i < Boardsize) {
		if (NextBoard[i].x == Row && NextBoard[i].y == Collum) {
			NextBoard.erase(NextBoard.begin() + i);
			return;
		}
		i++;
	}
	std::cout << "no was found";
}

int Game::returnminmax(unsigned int index, int minmax) {

	int output = -minmax * 2147483647;
	if (index == 0) {
		for (int i = 0; i < CurrentBoard.size(); i++) {
			output = CurrentBoard[i].x * ((minmax * CurrentBoard[i].x) >= (minmax * output)) + output * ((minmax * CurrentBoard[i].x) < (minmax * output));
		}
	}
	else
	{
		for (int i = 0; i < CurrentBoard.size(); i++) {
			output = CurrentBoard[i].y * ((minmax * CurrentBoard[i].y) >= (minmax * output)) + output * ((minmax * CurrentBoard[i].y) < (minmax * output));
		}
	}
	return output;
}



void Game::UpdateBoard()
{	
	int MaxRows = returnminmax(0, 1);
	int MinRows = returnminmax(0, -1);
	int MaxCollums = returnminmax(1, 1);
	int MinCollums = returnminmax(1, -1);

	NextBoard = CurrentBoard;

	for (int i = MinRows-1; i <= MaxRows+1; ++i) {
		for (int j = MinCollums -1; j <= MaxCollums+1; ++j) {
			unsigned int Neighbors = CountNeighbors(i, j);
			if (DoesTileExsist(i, j)) {
				if (Neighbors != 3 && Neighbors != 2) {
					RemoveTile(i, j);
				}
			}
			else if (Neighbors == 3) {
				NextBoard.emplace_back(i, j);
			}
		}
	}
	CurrentBoard = NextBoard;
}

void Game::ChangeTile(int Row,int Collum) {
	if (DoesTileExsist(Row, Collum)) {
		const int Boardsize = CurrentBoard.size();
		int i = 0;
		while (i < Boardsize) {
			if (CurrentBoard[i].x == Row && CurrentBoard[i].y == Collum) {
				CurrentBoard.erase(CurrentBoard.begin() + i);
				return;
			}
			i++;
		}
	}
	else {
		CurrentBoard.emplace_back(Row, Collum);
	}
}