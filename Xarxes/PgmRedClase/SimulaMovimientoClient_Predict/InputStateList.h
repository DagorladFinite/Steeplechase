#pragma once
#include "InputState.h"
#include <vector>

class InputStateList: private std::vector<InputState>
{
private:
	int counter;
public:
	InputStateList():counter(0) {}
	
	void Add(InputState& _inputState)
	{
		counter++;
		push_back(_inputState);
	}

	int GetCounter()
	{
		return counter;
	}

	bool Acknowledge(int _id, int _ackPosition)
	{
		int posRemove = -1;
		
		for (int i = 0; i < size(); i++)
		{
			InputState inputState = this->at(i);
			if (_id == inputState.GetId())
			{
				posRemove = i;
				if (inputState.GetAbsolutePosition() != _ackPosition)
				{
					erase(begin() + posRemove, begin()+size()-posRemove);
					std::cout << "Corrijo de " << inputState.GetAbsolutePosition() << " a " << _ackPosition << std::endl;
					return false;
				}
				
				break;
			}
		}

		if (posRemove > -1)
		{
			std::cout << "Borro de la 0 a la " << posRemove << std::endl;
			erase(begin(), begin() + posRemove + 1);
		}
		
		return true;
	}
};