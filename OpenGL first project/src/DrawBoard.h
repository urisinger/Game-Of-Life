#pragma once

#include <vector>
#include "GameOfLife.h"
#include "IndexBuffer.h"
#include "vertexbuffer.h"

static void GLclearerrors();
static void GLCheckErrros();

class Board
{
private:
	void genBoardVertexBuffer(int Row, int Collum, float OutputArray[8]);
public:
	VertexBuffer vb;
	IndexBuffer ib;
	Board(std::vector<cell> inputarray);
	void draw(std::vector<cell> inputarray);
};