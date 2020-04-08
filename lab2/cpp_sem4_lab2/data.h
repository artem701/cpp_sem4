#pragma once

#include <list>
#include <iostream>
#include <fstream> 
#include <sstream>
#include <iterator>
#include <algorithm>

using namespace std;

template <typename T> class Data
{
private:
	list<T> l;
	bool sorted = false;
	
	void fill(istream& is)
	{
		istream_iterator<T> begin(is);
		istream_iterator<T> end;
		l.clear();
		while (begin != end)
			l.push_back(*begin++);
		sorted = false;
	}

	void print(ostream& os) const
	{
		ostream_iterator<T> oit(os);

		for (T t : l)
			*oit++ = t;
		//os << "\n";
	}

public:

	typedef function<bool(const Product&)> Predicate;

	int count() const
	{
		return l.size();
	}

	/*
	T& operator [](int index)
	{
		return l.at(index);
	}*/

	void sort(function<bool(const T& a, const T& b)> lt)
	{
		l.sort(lt);
		sorted = true;
	}

	/*
	int indexof(bool (*p)(const T& item)) const
	{
		for (int i = 0; i < l.size(); ++i)
			if (p(l[i]))
				return i;
		return -1;
	}*/

	bool find(Predicate p) const
	{
		for (auto i : l)
			if (p(i))
				return true;
		return false;
	}

	/* ���� dir < 0 ������� ������� �����, > 0 - ������, ����� ����� */
	int indexof_binary(function<int(const T& item)> dir)  // int(*dir)(const T& item))
	{
		if (!sorted)
		{
			cerr << "��������� �� ������������, ������ ������������ �������� ��������� ������\n";
			return -2;
		}

		int min = 0, max = l.size() - 1;
		do {
			int i = (min + max) / 2;
			int d = dir(l[i]);
			if (d == 0)
				return i;
			if (d < 0)
				max = i;
			else
				min = i;
		} while (min < max);

		return -1;
	}

	Data<T> select(Predicate p)
	{
		Data<T> subdata;

		for (auto i : l)
			if (p(i))
				subdata.add(i);
		return subdata;
	}

	void add(const T& val)
	{
		l.push_back(val);
		sorted = false;
	}

	void remove(const T& val)
	{
		l.remove(val);
	}

	void remove_if(Predicate p)
	{
		l.remove_if(p);
	}

	void fill(const char* filename)
	{
		ifstream fin(filename);
		if (!fin)
			cerr << "����� �������������� ����\n";
		else
			fill(fin);
		fin.close();
		sorted = false;
	}

	void print() const
	{
		for (auto i : l)
			cout << i;
	}

	void print(const char* filename) const
	{
		ofstream fout(filename);
		print(fout);
		fout.close();
	}
};
