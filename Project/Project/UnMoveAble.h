
//=============================includes========================================

#pragma once
#include "GameObjects.h"

//====================class decerations========================================

class UnMoveAble: public GameObjects
{
public:
	UnMoveAble();
	virtual ~UnMoveAble() = 0 {}
	// handling loaction of static onbject on board
	void setRowAndCol(int row, int col);
	int getRow()const { return m_row; };
	int getCol()const { return m_col; };
	
protected:

	// row and column of static object in board
	int m_col;
	int m_row;
};

