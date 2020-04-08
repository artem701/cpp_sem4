#pragma once

#include <iostream>

using namespace std;

const int months[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

struct Date
{
public:
	int d, m, y;
	int h, min;

	Date(int _d = 1, int _m = 1, int _y = 2020/*, int _h = 0, int _min = 0*/);

	int monthdays() const;

	/* -1 ���� ������ ���� ������ date, 1 ���� ������, ����� 0*/
	int compare(const Date& date) const;

	Date operator +(int days) const;

	static Date get_today();
};

istream& operator >>(istream& is, Date& date);
ostream& operator <<(ostream& os, const Date& date);