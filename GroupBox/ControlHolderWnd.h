#pragma once
#include "afxwin.h"
#include "IRPluginObject.h"
#include "XPGroupBox.h"

#define ID_GROUPBOX_WINDOW 78654

class CControlHolderWnd :
	public CWnd
{
public:
	CControlHolderWnd(void);
	virtual ~CControlHolderWnd(void);
	CXPGroupBox* m_pGroupBoxCtrl;

public:
	void DestroyGroupBoxCtrl();
	void PositionChild();

	CIRPluginObject* m_pGroupBoxObject;
	void DoAutoTab(BOOL bNextField);

	BOOL m_bIsDesignTime;
	BOOL m_bEnabledRT;

protected:
	//{{AFX_MSG(CControlHolderWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
