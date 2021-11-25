#include "StdAfx.h"
#include "GroupBox.h"
#include "ControlHolderWnd.h"
#include "IRPluginHelperFunctions.h"

CControlHolderWnd::CControlHolderWnd(void)
{
	m_pGroupBoxCtrl = NULL;
	m_pGroupBoxObject = NULL;
	m_bIsDesignTime = TRUE;
	m_bEnabledRT = TRUE;
}

CControlHolderWnd::~CControlHolderWnd(void)
{
	DestroyGroupBoxCtrl();
}

BEGIN_MESSAGE_MAP(CControlHolderWnd, CWnd)
	//{{AFX_MSG_MAP(CControlHolderWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CControlHolderWnd message handlers
void CControlHolderWnd::DestroyGroupBoxCtrl()
{
	if(m_pGroupBoxCtrl)
	{
		if(IsWindow(m_pGroupBoxCtrl->m_hWnd))
		{
			m_pGroupBoxCtrl->ShowWindow(SW_HIDE);
			m_pGroupBoxCtrl->DestroyWindow();
		}

		delete m_pGroupBoxCtrl;
		m_pGroupBoxCtrl = NULL;
	}
}

int CControlHolderWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	
	// TODO: Add your specialized creation code here

	DWORD dwStyle = WS_CHILD|WS_VISIBLE|BS_GROUPBOX;

	if(m_bIsDesignTime == FALSE)
	{
		if(m_bEnabledRT == FALSE)
		{
			dwStyle |= WS_DISABLED;
		}
	}
	
	m_pGroupBoxCtrl = new CXPGroupBox;
	if(!m_pGroupBoxCtrl->Create("BUTTON","",dwStyle,CRect(0,0,0,0),this,ID_GROUPBOX_WINDOW))
	{
		return -1;
	}
	
	return 0;
}

void CControlHolderWnd::PositionChild()
{
	if(!m_pGroupBoxCtrl) return;
	if(!IsWindow(m_pGroupBoxCtrl->m_hWnd)) return;

	CRect rcClient;
	GetClientRect(&rcClient);

	m_pGroupBoxCtrl->MoveWindow(&rcClient);
}

void CControlHolderWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	PositionChild();	
}

void CControlHolderWnd::DoAutoTab(BOOL bNextField)
{
	if(m_pGroupBoxObject)
	{
		IRLUA_PLUGIN_DoAutoTab(m_pGroupBoxObject->m_pLuaState,bNextField);
	}
}