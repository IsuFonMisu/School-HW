
// iberat_THE5.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Ciberat_THE5App:
// See iberat_THE5.cpp for the implementation of this class
//

class Ciberat_THE5App : public CWinApp
{
public:
	Ciberat_THE5App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Ciberat_THE5App theApp;