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
	unsigned int indexs[6] =
	{
		0,1,2,
		0,1,3
	};
	Board();
	void draw(std::vector<Point> inputarray);
};