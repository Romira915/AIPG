#include "Pos.h"



Pos::Pos()
{
}

Pos::Pos(int x1, int y1)
{
	x = x1;
	y = y1;
}


Pos::~Pos()
{
}

bool Pos::operator<(const Pos a) const
{
	return x < a.x;
}

Pos Pos::operator=(Pos a)
{
	x = a.x;
	y = a.y;
	return *this;
}

bool Pos::operator==(Pos a)
{
	if (x == a.x && y == a.y)
	{
		return true;
	}
	else
	{
		return false;
	}
	return false;
}
