#include "Location.h"

Location::Location(int x, int y)
    :
    x(x),
    y(y)
{
}

Location Location::operator+(Location rhs) const
{
    return Location( x + rhs.x, y + rhs.y );
}

Location& Location::operator+=(Location rhs)
{
    return *this = *this + rhs;
}
