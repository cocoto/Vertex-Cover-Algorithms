#include "Couple.h"

Couple::Couple(const int &id, const int &deg)
{
	_id  = id;
	_deg = deg;
}

int Couple::id() const
{
	return _id;
}

int Couple::deg() const
{
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

bool Couple::operator < (const Couple &c) const
{
	return _deg < c.deg();
}
