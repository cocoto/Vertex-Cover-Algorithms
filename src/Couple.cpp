#include "Couple.h"

Couple::Couple(const int &id, const int &deg)
{
	_id  = id;
	_deg = deg;
}

int Couple::id()
{
	return _id;
}

int Couple::deg()
}
	return _deg;
}

void Couple::min()
{
	--_deg;
}

void Couple::min(const int &k)
{
	_deg -= k;
}

void Couple::add()
{
	++_deg;
}

Couple operator < (const &Couple c)
{
	return _deg < c.deg();
}
