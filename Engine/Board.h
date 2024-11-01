#pragma once
#include "Location.h"
#include "Graphics.h"
#include "Vec2.h"

class Board
{
private:
	int nCols;
	int nRows;
	int cellDimensions;
	Vec2 topLeft;
	Graphics& gfx;

public:
	Board(int nCols, int nRows, int cellDimensions, Vec2 topLeft, Graphics& gfx);
	void DrawCell(Location loc, Color c);
};

