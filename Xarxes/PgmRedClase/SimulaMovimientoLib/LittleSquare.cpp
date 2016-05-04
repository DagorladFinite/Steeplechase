#pragma once
#include "LittleSquare.h"



LittleSquare::LittleSquare(int _position) :position(_position) 
{
}

LittleSquare::LittleSquare(const LittleSquare& littleSquare) : LittleSquare(littleSquare.position)
{
	
}

int LittleSquare::GetPosition() 
{ 
	return position; 
}

void LittleSquare::SetPosition(int _position) 
{ 
	position = _position; 
}

LittleSquare::~LittleSquare() 
{
}