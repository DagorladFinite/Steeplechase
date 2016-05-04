#pragma once
#include <vector>

template <class T>
class List : public std::vector<T>
{
public:
	int IndexOf(T element)
	{
		for (size_t i = 0; i < size(); i++)
		{
			T elementAct = at(i);
			if (elementAct == element)
			{
				return i;
			}
		}
		return -1;
	}
};