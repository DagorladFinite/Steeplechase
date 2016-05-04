#pragma once
#include <vector>
#include <SocketAddress.h>

class Lista :private std::vector<SocketAddress>
{
	int IndexOf(SocketAddress sa)
	{
		for (size_t i = 0; i < size(); i++)
		{
			if (at(i) == sa)
			{
				return i;
			}
		}
		return -1;
	}
public:
	void Add(SocketAddress sa)
	{
		push_back(sa);
	}

	int Size()
	{
		return size();
	}

	bool Contains(SocketAddress sa)
	{
		int pos = IndexOf(sa);
		if (pos == -1)
			return false;
		return true;
	}

	void Remove(SocketAddress sa)
	{
		int pos = IndexOf(sa);
		if (pos > -1)
		{
			erase(begin() + pos);
		}
	}
};