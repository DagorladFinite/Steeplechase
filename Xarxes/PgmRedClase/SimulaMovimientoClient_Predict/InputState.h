#pragma once
#include <string>
#include "GameClientConstants.h"


class InputState
{
private:
	int absolutePosition;
	int moveHorizontal;
	int id;

public:
	InputState(): moveHorizontal(0)
	{
		
	}

	InputState(const InputState& _inputState)
	{
		moveHorizontal = _inputState.moveHorizontal;
		id = _inputState.id;
		absolutePosition = _inputState.absolutePosition;
	}

	int GetId()
	{
		return id;
	}

	void SetId(int _id)
	{
		id = _id;
	}

	int GetAbsolutePosition()
	{
		return absolutePosition;
	}

	void SetAbsolutePosition(int _absolutePosition)
	{
		absolutePosition = _absolutePosition;
	}

	void AddLeft()
	{
		moveHorizontal--;
		//std::cout << "Izquierda: " << moveHorizontal << std::endl;
	}

	void AddRight()
	{
		moveHorizontal++;
		//std::cout << "Derecha: " << moveHorizontal << std::endl;
	}

	int GetMove()
	{
		return moveHorizontal;
	}

	bool Serialize(std::string& _move)
	{
		if (moveHorizontal != 0)
		{
			_move = std::string(HEADER_TRYPOSITION) + "_" + std::to_string(id) + "_" + std::to_string(moveHorizontal);
			return true;
		}
		return false;
	}

	void ResetMove()
	{
		moveHorizontal = 0;
	}

	~InputState() {}
};

