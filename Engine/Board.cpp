#include "Board.h"


Board::Board(int nPoison, int maxObstacles, Graphics& gfx)
	:
	nPoison(nPoison),
	maxObstacles(maxObstacles),
	gfx(gfx)
{
	int i = 0;
	for (int y = 0; y < nRows; y++)
	{
		for (int x = 0; x < nCols; x++)
		{
			cells[i] = Cell({ x,y });
			i++;
		}
	}
}

void Board::SpawnObstacle()
{
	if (currObstacles < maxObstacles)
	{
		std::mt19937 rng;
		std::uniform_int_distribution<int> xDist(0, nCols - 1);
		std::uniform_int_distribution<int> yDist(0, nRows - 1);

		int x = xDist(rng);
		int y = yDist(rng);
		while (!cells[y * nCols + x].IsEmpty())
		{
			x = xDist(rng);
			y = yDist(rng);
		}
		cells[y * nCols + x].ChangeContent(CellContents::Obstacle);
		currObstacles++;
	}

}

void Board::SpawnPoison()
{
	std::mt19937 rng;
	std::uniform_int_distribution<int> xDist(0, nCols - 1);
	std::uniform_int_distribution<int> yDist(0, nRows - 1);

	for (int i = 0; i < nPoison; i++)
	{
		int x = xDist(rng);
		int y = yDist(rng);
		while (!cells[y * nCols + x].IsEmpty())
		{
			x = xDist(rng);
			y = yDist(rng);
		}
		cells[y * nCols + x].ChangeContent(CellContents::Poison);
	}
}

void Board::Draw() const
{
	for (int y = 0; y < nRows; y++)
	{
		for (int x = 0; x < nCols; x++)
		{
			cells[y * nCols + x].Draw(topLeft, gfx);
		}
	}
}

void Board::DrawCell(Location loc, Color c) const
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

bool Board::IsPoisonConsumed(Location snekLoc) 
{
	int checkIndex = snekLoc.y * nCols + snekLoc.x;
	bool consumed = cells[checkIndex].HasPoison();
	if (consumed)
	{
		cells[checkIndex].RemoveContent();
	}
	return consumed;
}

bool Board::IsObstacleHit(Location snekLoc)
{
	return cells[snekLoc.y * nCols + snekLoc.x].HasObstacle();
}

bool Board::IsWallHit(Location snekLoc)
{
	return (snekLoc.x < 0 || snekLoc.x > nCols - 1 || snekLoc.y < 0 || snekLoc.y > nRows - 1);
}

Location Board::RespawnGoal(Location prev_loc)
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> xDist(0, nCols - 1);
	std::uniform_int_distribution<int> yDist(0, nRows - 1);
	int x = xDist(rng);
	int y = yDist(rng);
	while (!(cells[y * nCols + x].IsEmpty()))
	{
		x = xDist(rng);
		y = yDist(rng);
	}
	cells[y * nCols + x].ChangeContent(CellContents::Goal);
	cells[prev_loc.y * nCols + prev_loc.x].RemoveContent();

	return { x,y };
}

Board::Cell::Cell(Location loc)
	:
	loc(loc)
{
}

void Board::Cell::Draw(Vec2 topLeft, Graphics& gfx) const
{
	int loc_x = loc.x * cellDimensions;
	int loc_y = loc.y * cellDimensions;

	Color c = Colors::Black;
	switch (content)
	{
	case CellContents::Obstacle:
		c = Colors::Gray;
		break;
	case CellContents::Poison:
		c = Colors::MakeRGB(50, 24, 58);
		break;
	case CellContents::Goal:
		c = Colors::Yellow;
		break;
	default:
		break;
	}

	for (int x = loc_x; x < loc_x + cellDimensions; x++)
	{
		for (int y = loc_y; y < loc_y + cellDimensions; y++)
		{
			gfx.PutPixel((int)topLeft.x + x, (int)topLeft.y + y, c);
		}
	}
}

bool Board::Cell::IsEmpty() const
{
	return(content == CellContents::Empty);
}

bool Board::Cell::HasPoison() const
{
	return(content == CellContents::Poison);
}

bool Board::Cell::HasObstacle() const
{
	return(content == CellContents::Obstacle);
}

bool Board::Cell::HasGoal() const
{
	return(content == CellContents::Goal);
}

void Board::Cell::ChangeContent(CellContents newContent)
{
	content = newContent;
}

void Board::Cell::RemoveContent()
{
	ChangeContent(CellContents::Empty);
}
