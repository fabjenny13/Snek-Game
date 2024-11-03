#pragma once
#include "Location.h"
#include "Graphics.h"
#include "Vec2.h"
#include <random>

class Board
{
	enum class CellContents
	{
		Empty,
		Goal,
		Obstacle,
		Poison,
	};

	class Cell
	{
	private:
		CellContents content = CellContents::Empty;
		Location loc;
	public:
		Cell() = default;
		Cell(Location loc);
		void Draw(Vec2 topLeft, Graphics& gfx) const;
		bool IsEmpty() const;
		bool HasPoison() const;
		bool HasObstacle() const;
		bool HasGoal() const;
		void ChangeContent(CellContents newContent);
		void RemoveContent();
	};

private:
	Graphics& gfx;
	static const int leftBound = 10;
	static const int rightBound = Graphics::ScreenWidth - leftBound;
	static const int upBound = 10;
	static const int downBound = Graphics::ScreenHeight - upBound;
	Vec2 topLeft = { leftBound, upBound };
	static const int cellDimensions = 25;
	static const int nCols = (rightBound - leftBound) / cellDimensions;
	static const int nRows = (downBound - upBound) / cellDimensions;
	Cell cells[nCols * nRows];

	int nPoison;
	int maxObstacles;
	int currObstacles = 0;



public:
	Board(int nPoison, int maxObstacles, Graphics& gfx);
	void SpawnObstacle();
	void SpawnPoison();
	void Draw() const;
	//void RespawnGoal();
	
};

