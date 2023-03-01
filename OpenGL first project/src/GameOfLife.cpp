#include "GameOfLife.h"

Game::Game(unsigned int a)
{
	
}

Game::~Game()
{

}

void Game::PrintBoard() {

	int MaxRows = returnminmax(0, 1);
	int MinRows = returnminmax(0, -1);
	int MaxCollums = returnminmax(1, 1);
	int MinCollums = returnminmax(1, -1);

	for (int i = MinRows; i <= MaxRows; ++i) {
		for (int j = MinCollums; j <= MaxCollums; ++j) {
			std::cout << DoesTileExsist(i, j, Board)<<"|";
		}
		std::cout << std::endl;
	}
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
	Board.push_back({row,collum});
}

void Game::RemoveTile(int Row, int Collum, std::vector<std::vector<int>> OldBoard) {
	const int Boardsize = Board.size();
	int i = 0;
	while (i <= Boardsize) {
		if (Board[i][0] == Row && Board[i][1] == Collum) {
			Board.erase(Board.begin() + i);
			return;
		}
		i++;
	}
	std::cout << "no was found";
}
void Game :: UpdateTile(int row,int collum,std::vector<std::vector<int>> OldBoard)
{
	unsigned int Neighbors = CountNeighbors(row, collum,OldBoard);
	if (DoesTileExsist(row, collum, OldBoard)) {
		if (Neighbors != 3 && Neighbors != 2) {
			RemoveTile(row, collum,OldBoard);
		}
	}
	else if (Neighbors == 3) {
		AddTile(row, collum,OldBoard);
	}
}

int Game::returnminmax(unsigned int index, int minmax) {

	int output = -minmax * 2147483647;
	for (int i = 0; i < Board.size(); i++) {
		output = Board[i][index] * ((minmax * Board[i][index]) >=( minmax * output)) + output * ((minmax * Board[i][index]) < (minmax * output));
	}
	return output;
}



void Game::UpdateBoard()
{	
	int MaxRows = returnminmax(0, 1);
	int MinRows = returnminmax(0, -1);
	int MaxCollums = returnminmax(1, 1);
	int MinCollums = returnminmax(1, -1);
	std::vector<std::vector<int>> OldBoard = Board;

	for (int i = MinRows-1; i <= MaxRows+1; ++i) {
		for (int j = MinCollums -1; j <= MaxCollums+1; ++j) {
			UpdateTile(i, j, OldBoard);
		}
	}
}