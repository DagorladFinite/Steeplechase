#pragma once

class InputState
{
private:
	int desiredXs;

	/*
	int moveHorizontal;
	int id;
	*/

public:
	InputState():desiredXs(0) {}

	/*InputState(const InputState& _inputState)
	{
		moveHorizontal = _inputState.moveHorizontal;
		id = _inputState.id;
		absolutePosition = _inputState.absolutePosition;
	}*/

	void AddLeft()
	{
		desiredXs--;
	}
	void AddRight()
	{
		desiredXs++;
	}
	int GetXs()
	{
		return desiredXs;
	}
	void Reset()
	{
		desiredXs = 0;
	}

	/*int GetId()
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
	}*/
	~InputState() {}
};