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
	:
	headLoc(loc)
{
	segments[0] = SnakeSegment(headLoc, Colors::Yellow);
}

void Snake::Move(Location delta_loc)
{
	segments[0].Move(delta_loc);
	for (int i = 1; i < curSegments; i++)
	{
		segments[i].Follow(segments[i - 1]);
	}
}

void Snake::Grow()
{
	curSegments++;
	segments[curSegments] = SnakeSegment(segments[curSegments - 1].GetLocation(), Colors::Green);
}

void Snake::Draw(Board& brd) const
{
	for (int i = 0; i < curSegments; i++)
	{
		brd.DrawCell(segments[i].GetLocation(), segments[i].GetColor());
	}
}
