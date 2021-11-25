// GroupBox.h : main header file for the GroupBox DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CGroupBoxApp
// See GroupBox.cpp for the implementation of this class
//

class CGroupBoxApp : public CWinApp
{
public:
	CGroupBoxApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
