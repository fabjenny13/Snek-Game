#include "Snake.h"

Snake::SnakeSegment::SnakeSegment(Location loc, Color c)
	:
	loc(loc),
	c(c)
{
}

void Snake::SnakeSegment::Follow(SnakeSegment prev)
{
	loc = prev.loc;
}

Location Snake::SnakeSegment::GetLocation() const
{
	return loc;
}

Color Snake::SnakeSegment::GetColor() const
{
	return c;
}

void Snake::SnakeSegment::Move(Location delta_loc)
{
	loc += delta_loc;
}

Snake::Snake(Location loc)
{
	segments[0] = SnakeSegment(loc, Colors::Yellow);
}

void Snake::Move(Location delta_loc)
{
	for (int i = curSegments - 1; i >= 1; i--)
	{
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].Move(delta_loc);
}

void Snake::Grow()
{
	curSegments++;
	segments[curSegments - 1] = SnakeSegment(segments[curSegments - 2].GetLocation(), Colors::Green);
}

void Snake::Draw(Board& brd) const
{
	for (int i = 0; i < curSegments; i++)
	{
		brd.DrawCell(segments[i].GetLocation(), segments[i].GetColor());
	}
}

Location Snake::GetHeadLocation() const
{
	return segments[0].GetLocation();
}
