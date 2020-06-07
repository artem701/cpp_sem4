﻿#pragma once

#include <vector>
#include <iostream>
#include <fstream> 
#include <sstream>
#include <iterator>
#include <algorithm>
#include <functional>

using namespace std;

template <typename T> class Data
{
private:
	/* vector, т.к. в приоритете добавление и удаление элементов, а вектор реализует их достаточно быстро, 
	 * к тому же бинарный поиск не имеет смысла без случайного доступа */
	vector<T> v;
	
	void fill(istream& is)
	{
		istream_iterator<T> begin(is);
		istream_iterator<T> end;
		v.clear();
		while (begin != end)
			v.push_back(*begin++);
	}

	void print(ostream& os) const
	{
		ostream_iterator<T> oit(os);

		for (T t : v)
		{
			*oit++ = t;
		}
	}

public:

	typedef function<bool(const T&)> Predicate;

	int count() const
	{
		return v.size();
	}

	void sort(function<bool(const T& a, const T& b)> lt)
	{
		std::sort(v.begin(), v.end(), lt);
	}

	bool find(Predicate p) const
	{
		for (auto i : v)
			if (p(i))
				return true;
		return false;
	}

	/* Если dir < 0 искомый элемент левее, > 0 - правее, иначе равен */
	int indexof_binary(function<int(const T& item)> dir) 
	{
		int min = 0, max = v.size() - 1;
		while (min < max) {
			int i = (min + max) / 2;
			int d = dir(v[i]);
			if (d == 0)
				return i;
			if (d < 0)
				max = i;
			else
				min = i + 1;
		}

		if (min == max && dir(v[min]) == 0)
			return min;

		return -1;
	}

	Data<T> select(Predicate p)
	{
		Data<T> subdata;

		for (auto i : v)
			if (p(i))
				subdata.add(i);
		return subdata;
	}

	void forEach(function<void(T& item)> f)
	{
		for (T& i : v)
		{
			f(i);
		}
	}

	void add(const T& val)
	{
		v.push_back(val);
	}

	void remove(const T& val)
	{
		v.remove(val);
	}

	void remove_if(Predicate p)
	{
		auto end = v.begin();
		for (auto i = v.begin(); i < v.end(); ++i)
		{
			if (!p(*i))
			{
				if (end != i)
					*end = *i;
				++end;
			}
		}
		v.erase(end, v.end());
	}

	void fill(string filename)
	{
		ifstream fin(filename);
		if (!fin)
			cerr << "Задан несуществующий файл\n";
		else
			fill(fin);
		fin.close();
	}

	void print() const
	{
		for (auto i : v)
			cout << i;
	}

	void print(string filename) const
	{
		ofstream fout(filename);
		print(fout);
		fout.close();
	}
};

