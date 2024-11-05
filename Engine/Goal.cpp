#include "Goal.h"


Goal::Goal(Location loc)
	:
	loc(loc)
{
}

void Goal::Respawn(Board& brd)
{
	loc = brd.RespawnGoal(loc);
}

void Goal::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

bool Goal::IsEaten(Location snekLoc) const
{
	return snekLoc == loc;
}
