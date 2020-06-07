
#include "storage.h"
#include "utils.h"

void Storage::console_input()
{
	cout << "Введите id склада: ";
	input(id);
	
	cout << "Введите комментарий к складу: ";
	static char comment_str[256];
	cin.getline(comment_str, 256);
	comment = string(comment_str);
}

void Storage::console_output() const
{
	cout << "Склад №" << id << " (" << comment << ")\n\n";
}

istream & operator>>(istream & is, Storage & p)
{
	if (&is == &cin)
	{
		p.console_input();
		return is;
	}
	is >> p.id; 
	static char comment_str[256];
	is.getline(comment_str, 256); // finish current line
	is.getline(comment_str, 256); // read comment
	p.comment = string(comment_str);
	return is;
}

ostream & operator<<(ostream & os, const Storage & p)
{
	if (&os == &cout)
	{
		p.console_output();
		return os;
	}

	return os << p.id << "\n" << p.comment << "\n";
}
