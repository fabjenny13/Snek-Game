#include "Board.h"

Board::Board(int nCols, int nRows, int cellDimensions, Vec2 topLeft, Graphics& gfx)
	:
	nCols(nCols),
	nRows(nRows),
	cellDimensions(cellDimensions),
	topLeft(topLeft),
	gfx(gfx)
{
}

void Board::DrawCell(Location loc, Color c)
{
	int loc_x = loc.x * cellDimensions;
	int loc_y = loc.y * cellDimensions;

	for (int x = loc_x; x < loc_x + cellDimensions; x++)
	{
		for (int y = loc_y; y < loc_y + cellDimensions; y++)
		{
			gfx.PutPixel((int)topLeft.x + x, (int)topLeft.y + y, c);
		}
	}
}
