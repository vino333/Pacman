
//=============================includes========================================

#pragma once
#include "Ghost.h"

//=============================classes prototypes==============================

class Board;

//====================class decerations========================================

class StupidGhost : public Ghost
{
public:
	StupidGhost(int, Board&);
	~StupidGhost();
	Direction getNextStep();
};

