
//=============================includes========================================

#pragma once
#include "Ghost.h"

//=============================forward declerations============================

class Board;

//====================class decerations========================================

class SmartGhost : public Ghost
{
public:
	SmartGhost(int, Board&);
	~SmartGhost();
	Direction getNextStep();
};

