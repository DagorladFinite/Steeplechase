#pragma once
#include "LittleSquare.h"
#include <iostream>


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

void LittleSquare::AddRight()
{
	position++;
	std::cout << "Cuadrado en: " << position << std::endl;
}

void LittleSquare::AddLeft()
{
	position--;
	std::cout << "Cuadrado en: " << position << std::endl;
}

LittleSquare::~LittleSquare() 
{
}