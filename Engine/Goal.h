#pragma once
#include "Location.h"
#include "Colors.h"
#include "Board.h"

class Goal
{
private:
	Location loc;
	Color c = Colors::Red;

public:
	Goal() = default;
	Goal(Location loc);
	void Respawn(Board& brd);
	void Draw(Board& brd) const;
};

