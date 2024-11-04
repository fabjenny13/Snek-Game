#pragma once
class Location
{
public:
	int x;
	int y;
	Location() = default;
	Location(int x, int y);
	Location operator+(Location rhs) const;
	Location& operator+=(Location rhs);
};

