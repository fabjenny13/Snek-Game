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
	Vec2 topLeft = { leftBound, upBound };
	static const int cellDimensions = 25;

public:
	static constexpr int leftBound = 10;
	static constexpr int rightBound = Graphics::ScreenWidth - leftBound;
	static constexpr int upBound = 10;
	static constexpr int downBound = Graphics::ScreenHeight - upBound;
	static constexpr int nCols = (rightBound - leftBound) / cellDimensions;
	static constexpr int nRows = (downBound - upBound) / cellDimensions;
	static constexpr int totalBoardCells = nRows * nCols;

private:
	Cell cells[nCols * nRows];
	int nPoison;
	int maxObstacles;
	int currObstacles = 0;

public:
	Board(int nPoison, int maxObstacles, Graphics& gfx);
	void SpawnObstacle();
	void SpawnPoison();
	void Draw() const;
	void DrawCell(Location loc, Color c) const;
	bool IsPoisonConsumed(Location snekLoc);
	Location RespawnGoal(Location prev_loc);
	
};

