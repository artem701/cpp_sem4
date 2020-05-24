#include "mydate.h"

#include <time.h>

Date::Date(int _d, int _m, int _y) : d(_d), m(_m), y(_y)
{
}

#define RET if (dif != 0) {return dif;}
int Date::compare(const Date & date) const
{
	int dif = y - date.y;
	RET;

	dif = m - date.m;
	RET;

	dif = d - date.d;
	RET;
	return dif;
}
#undef RET

int Date::monthdays() const
{
	if (m != 2)
		return months[m - 1];

	return (y % 4 == 0) ? 29 : 28;
}

Date Date::operator+(int days) const
{
	Date date(*this);
	date.d += days;
	bool loop = true;

	while (loop)
	{
		loop = false;
		if (date.d > date.monthdays())
		{
			loop = true;
			date.d -= date.monthdays();
			date.m += 1;
			if (date.m > 12)
			{
				date.m = 1;
				date.y += 1;
			}
		}
	}

	return date;
}

Date Date::get_today()
{
	time_t t;
	tm *tk = new tm;

	time(&t);
	localtime_s(tk, &t);

	return Date(tk->tm_mday, tk->tm_mon + 1, tk->tm_year + 1900);
}

istream & operator>>(istream & is, Date & date)
{
	char delim;

	is >> date.d >> delim >> date.m >> delim >> date.y;

	return is;
}

#define OUT(x) if ((x) < 10) os << 0; os << (x)
ostream & operator<<(ostream & os, const Date & date)
{
	OUT(date.d) << ".";

	OUT(date.m) << "." << date.y;

	return os;
}
#undef OUT
