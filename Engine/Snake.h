#pragma once
#include "Board.h"
#include "Location.h"

class Snake
{
private:
	class SnakeSegment
	{
	private:
		Color c;
		Location loc;
	public:
		SnakeSegment() = default;
		SnakeSegment(Location loc, Color c);
		void Follow(SnakeSegment prev);
		Location GetLocation() const;
		Color GetColor() const;
		void Move(Location delta_loc);
	};

private:
	static const int maxSegments = Board::totalBoardCells;
	int curSegments = 1;
	SnakeSegment segments[maxSegments];
	

public:
	Snake() = default;
	Snake(Location loc);
	void Move(Location delta_loc);
	void Grow();
	void Draw(Board& brd) const;
	Location GetHeadLocation() const;
	bool CollidedWithSelf(Location nextHeadLoc) const;


};

