
//=============================includes========================================

#include "Cookie.h"

// C-tor
Cookie::Cookie(int color)
{
	m_image = ImageResource::getSource().getCookie(color);// getting image of cookie

	//set factors
	switch (color)// setting cookie defenitions
	{
	case 0:
		m_factor = 1;
		m_time = 0;
		break;

	case 1:
		m_factor = 0.9;
		m_time = 7;
		break;

	case 2:
		m_factor = 1.2;
		m_time = 14;
		break;
	}	
}

//=============================================================================

//D-tor
Cookie::~Cookie()
{
}
