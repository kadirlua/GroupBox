#include "StdAfx.h"
#include "GroupBox.h"
#include "GroupBoxObject.h"
#include "LuaFunctions.h"
#include "PropertiesDlg.h"

CGroupBoxObject::CGroupBoxObject(void)
{
	for(int i = 0; i < NUM_OB_EVENTS; i++)
		m_pEvents[i] = NULL;

	m_pEvents[0] = new IRPluginEventInfo;
	lstrcpy(m_pEvents[0]->m_szName,"On PosChange");
	lstrcpy(m_pEvents[0]->m_szArgs,"number e_Pos");

	m_pEvents[1] = new IRPluginEventInfo;
	lstrcpy(m_pEvents[1]->m_szName,"On Key");
	lstrcpy(m_pEvents[1]->m_szArgs,"number e_Key, table e_Modifiers");

	m_pEvents[2] = new IRPluginEventInfo;
	lstrcpy(m_pEvents[2]->m_szName,"On Focus");
	lstrcpy(m_pEvents[2]->m_szArgs,"");

	lstrcpy(m_szObjectID,"IR_GROUPBOX_OBJECT");

	m_pGroupBoxHolder = NULL;

	strText = "Label Text";
	nType = 1;
	m_strFaceName = "Arial";
	m_nHeight = 12;
	m_nWidth = 0;
	m_nEscapement = 0;
	m_nOrientation = 0;
	m_nWeight = FW_NORMAL;
	m_bItalic = FALSE;
	m_bUnderline = FALSE;
	m_bStrikeOut = 0;
	m_bCharSet = ANSI_CHARSET;
	m_bOutPrecision = OUT_DEFAULT_PRECIS;
	m_bClipPrecision = CLIP_DEFAULT_PRECIS;
	m_bQuality = DEFAULT_QUALITY;
	m_bPitchAndFamily = DEFAULT_PITCH | FF_SWISS;
	clrText = RGB(0,0,0);
	clrBackGround = RGB(240,240,240);
	clrBorder = RGB(192,192,192);
}

CGroupBoxObject::~CGroupBoxObject(void)
{
	for(int i = 0; i < NUM_OB_EVENTS; i++)
	{
		delete m_pEvents[i];
		m_pEvents[i] = NULL;
	}

	DestroyGroupBox();
}

void CGroupBoxObject::DestroyGroupBox()
{
	if(m_pGroupBoxHolder)
	{
		if(IsWindow(m_pGroupBoxHolder->m_hWnd))
		{
			m_pGroupBoxHolder->ShowWindow(SW_HIDE);
			m_pGroupBoxHolder->DestroyWindow();
		}

		delete m_pGroupBoxHolder;
		m_pGroupBoxHolder = NULL;
	}
}

HWND CGroupBoxObject::GetWindowHandle()
{
	if(m_pGroupBoxHolder)
	{
		if(IsWindow(m_pGroupBoxHolder->m_hWnd))
		{
			//To work with sizing
			return m_pGroupBoxHolder->m_hWnd;
			/*
			if(m_pSliderHolder->m_pSliderCtrl)
			{
				if(IsWindow(m_pSliderHolder->m_pSliderCtrl->m_hWnd))
				{
					return m_pSliderHolder->m_pSliderCtrl->m_hWnd;
				}
			}
			*/
		}
	} 
	return NULL;
}

void CGroupBoxObject::DrawDesign(HDC hDC, HWND hMainWnd, RECT rcObRect,BOOL bVisible,BOOL bEnabled)
{
	if(bVisible)
	{
		bEnabled = FALSE; // Always disabled at design-time

		if(!m_pGroupBoxHolder)
			m_pGroupBoxHolder = new CControlHolderWnd;
		
		m_pGroupBoxHolder->m_bIsDesignTime = TRUE;

		DWORD dwStyle;

		dwStyle = WS_CHILD|WS_VISIBLE;
		if(!bEnabled)
		{
			dwStyle |= WS_DISABLED;
		}

		if(!IsWindow(m_pGroupBoxHolder->m_hWnd))
		{
			if(!m_pGroupBoxHolder->Create(NULL,"ir_GroupBox",dwStyle,rcObRect,CWnd::FromHandle(hMainWnd),
				6262))
			{
				DestroyGroupBox();
				return;
			} else
			{
				m_pGroupBoxHolder->m_pGroupBoxObject = this;
				//Font Properties
			   m_font.CreateFont(
			   m_nHeight,                        // nHeight
			   m_nWidth,                         // nWidth
			   m_nEscapement,                         // nEscapement
			   m_nOrientation,                         // nOrientation
			   m_nWeight,                 // nWeight
			   m_bItalic,                     // bItalic
			   m_bUnderline,                     // bUnderline
			   m_bStrikeOut,                         // cStrikeOut
			   m_bCharSet,              // nCharSet
			   m_bOutPrecision,        // nOutPrecision
			   m_bClipPrecision,       // nClipPrecision
			   m_bQuality,           // nQuality
			   m_bPitchAndFamily,  // nPitchAndFamily
			   m_strFaceName);
			   LOGFONT lf;
			   m_font.GetLogFont(&lf);
			   m_pGroupBoxHolder->m_pGroupBoxCtrl->SetFont(lf);
			   m_font.DeleteObject();
			   m_pGroupBoxHolder->m_pGroupBoxCtrl->SetCatptionTextColor(clrText);
			   m_pGroupBoxHolder->m_pGroupBoxCtrl->SetBackgroundColor(clrBackGround);
			   m_pGroupBoxHolder->m_pGroupBoxCtrl->SetBorderColor(clrBorder);
			   m_pGroupBoxHolder->m_pGroupBoxCtrl->SetText(strText);
			   if (nType == 0)
				{
					m_pGroupBoxHolder->m_pGroupBoxCtrl->SetAlignment(SS_CENTER);
				}
				else if (nType == 1)
				{
					m_pGroupBoxHolder->m_pGroupBoxCtrl->SetAlignment(SS_LEFT);
				}
				else if (nType == 2)
				{
					m_pGroupBoxHolder->m_pGroupBoxCtrl->SetAlignment(SS_RIGHT);
				}
			}
		}

		m_pGroupBoxHolder->MoveWindow(&rcObRect);
	} else
	{
		DestroyGroupBox();
	}
}

void CGroupBoxObject::DrawRuntime(HDC hDC, HWND hMainWnd, RECT rcObRect,BOOL bVisible,BOOL bEnabled)
{
	if(!m_pGroupBoxHolder)
		m_pGroupBoxHolder = new CControlHolderWnd;

	m_pGroupBoxHolder->m_bIsDesignTime = FALSE;
	m_pGroupBoxHolder->m_bEnabledRT = bEnabled;

	DWORD dwStyle;

	dwStyle = WS_CHILD | WS_DISABLED;
	
	if(bVisible)
	{
		dwStyle |= WS_VISIBLE;
	}

	if(!IsWindow(m_pGroupBoxHolder->m_hWnd))
	{
		if(!m_pGroupBoxHolder->CreateEx(WS_EX_TRANSPARENT,NULL,"ir_GroupBox",dwStyle,rcObRect,CWnd::FromHandle(hMainWnd),
			6262))
		{
			DestroyGroupBox();
			return;
		} else
		{
			m_pGroupBoxHolder->m_pGroupBoxObject = this;
				//Font Properties
			   m_font.CreateFont(
			   m_nHeight,                        // nHeight
			   m_nWidth,                         // nWidth
			   m_nEscapement,                         // nEscapement
			   m_nOrientation,                         // nOrientation
			   m_nWeight,                 // nWeight
			   m_bItalic,                     // bItalic
			   m_bUnderline,                     // bUnderline
			   m_bStrikeOut,                         // cStrikeOut
			   m_bCharSet,              // nCharSet
			   m_bOutPrecision,        // nOutPrecision
			   m_bClipPrecision,       // nClipPrecision
			   m_bQuality,           // nQuality
			   m_bPitchAndFamily,  // nPitchAndFamily
			   m_strFaceName);
			   LOGFONT lf;
			   m_font.GetLogFont(&lf);
			   m_pGroupBoxHolder->m_pGroupBoxCtrl->SetFont(lf);
			   m_font.DeleteObject();
			   m_pGroupBoxHolder->m_pGroupBoxCtrl->SetCatptionTextColor(clrText);
			   m_pGroupBoxHolder->m_pGroupBoxCtrl->SetText(strText);
			   m_pGroupBoxHolder->m_pGroupBoxCtrl->SetBackgroundColor(clrBackGround);
			   m_pGroupBoxHolder->m_pGroupBoxCtrl->SetBorderColor(clrBorder);
			   if (nType == 0)
				{
					m_pGroupBoxHolder->m_pGroupBoxCtrl->SetAlignment(SS_CENTER);
				}
				else if (nType == 1)
				{
					m_pGroupBoxHolder->m_pGroupBoxCtrl->SetAlignment(SS_LEFT);
				}
				else if (nType == 2)
				{
					m_pGroupBoxHolder->m_pGroupBoxCtrl->SetAlignment(SS_RIGHT);
				}
		}
	}

	m_pGroupBoxHolder->MoveWindow(&rcObRect);

	ShowWindow(bVisible);
}

void CGroupBoxObject::ShowWindow(BOOL bVisible)
{
	if(bVisible)
	{
		if(m_pGroupBoxHolder)
		{
			if(m_pGroupBoxHolder->m_pGroupBoxCtrl)
			{
				if(IsWindow(m_pGroupBoxHolder->m_pGroupBoxCtrl->m_hWnd))
				{
					m_pGroupBoxHolder->m_pGroupBoxCtrl->ShowWindow(SW_SHOW);
				}
			}
			if(IsWindow(m_pGroupBoxHolder->m_hWnd))
			{
				m_pGroupBoxHolder->ShowWindow(SW_SHOW);
			}
		}
	} else
	{
		if(m_pGroupBoxHolder)
		{
			if(m_pGroupBoxHolder->m_pGroupBoxCtrl)
			{
				if(IsWindow(m_pGroupBoxHolder->m_pGroupBoxCtrl->m_hWnd))
				{
					m_pGroupBoxHolder->m_pGroupBoxCtrl->ShowWindow(SW_HIDE);
				}
			}
			if(IsWindow(m_pGroupBoxHolder->m_hWnd))
			{
				m_pGroupBoxHolder->ShowWindow(SW_HIDE);
			}
		}
	}
}

int CGroupBoxObject::GetCustomProperties(char* szBuffer, int* pnBufferSize)
{
	memset(m_szPropertiesString,0,1000);

	wsprintf(m_szPropertiesString,"%s,%d,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u,%u,%u",
		strText,nType,m_strFaceName,m_nHeight,m_nWidth,m_nEscapement,m_nOrientation,m_nWeight,m_bItalic,m_bUnderline,m_bStrikeOut,m_bCharSet,m_bOutPrecision,m_bClipPrecision,m_bQuality,m_bPitchAndFamily,clrText,clrBackGround,clrBorder);
	
	int nLength = lstrlen(m_szPropertiesString);
	if(*pnBufferSize < nLength)
	{
		*pnBufferSize = nLength;
		return -1;
	} else
	{
		memset(szBuffer,0,*pnBufferSize);
		lstrcpy(szBuffer,m_szPropertiesString);
		return nLength;
	}
}

void CGroupBoxObject::SetCustomProperties(char* szPropsList)
{
	int nTokens = 0;
	CString sToken;

	CToken tok(szPropsList);
	tok.SetToken(",");

	while(tok.MoreTokens())
	{
		switch(nTokens)
		{
		case 0: // strtext
			strText = tok.GetNextToken();
			break;
		case 1:
			nType = atoi(tok.GetNextToken());
			break;
		case 2:
			m_strFaceName = tok.GetNextToken();
			break;
		case 3:
			m_nHeight = atoi(tok.GetNextToken());
			break;
		case 4:
			m_nWidth = atoi(tok.GetNextToken());
			break;
		case 5:
			m_nEscapement = atoi(tok.GetNextToken());
			break;
		case 6:
			m_nOrientation = atoi(tok.GetNextToken());
			break;
		case 7:
			m_nWeight = atoi(tok.GetNextToken());
			break;
		case 8:
			m_bItalic = atoi(tok.GetNextToken());
			break;
		case 9:
			m_bUnderline = atoi(tok.GetNextToken());
			break;
		case 10:
			m_bStrikeOut = atoi(tok.GetNextToken());
			break;
		case 11:
			m_bCharSet = atoi(tok.GetNextToken());
			break;
		case 12:
			m_bOutPrecision = atoi(tok.GetNextToken());
			break;
		case 13:
			m_bClipPrecision = atoi(tok.GetNextToken());
			break;
		case 14:
			m_bQuality = atoi(tok.GetNextToken());
			break;
		case 15:
			m_bPitchAndFamily = atoi(tok.GetNextToken());
			break;
		case 16:
			clrText = atol(tok.GetNextToken());
			break;
		case 17:
			clrBackGround = atol(tok.GetNextToken());
			break;
		case 18:
			clrBorder = atol(tok.GetNextToken());
			break;
		}

		nTokens++;
	}
}

void CGroupBoxObject::DoSetFocus()
{
	if(m_pGroupBoxHolder)
	{
		if(IsWindow(m_pGroupBoxHolder->m_hWnd))
		{
			if(m_pGroupBoxHolder->m_pGroupBoxCtrl)
			{
				if(IsWindow(m_pGroupBoxHolder->m_pGroupBoxCtrl->m_hWnd))
				{
					m_pGroupBoxHolder->m_pGroupBoxCtrl->SetFocus();
				}
			}
		}
	}
}

void CGroupBoxObject::HideInternalObject()
{
	DestroyGroupBox();
}

BOOL CGroupBoxObject::ShowProperties(char* szPluginFolder)
{
	CPropertiesDlg dlgProps;
	BOOL bRet;
	CString strHelpFile;

	strHelpFile.Format("%s",szPluginFolder);
	strHelpFile.TrimRight("\\");
	strHelpFile += "\\Slider_Help.htm";

	dlgProps.strText = strText;
	dlgProps.nType = nType;
	dlgProps.m_strHelpPath = strHelpFile;
	dlgProps.m_strFaceName = m_strFaceName;
	dlgProps.m_nHeight = m_nHeight;
    dlgProps.m_nWidth = m_nWidth;
	dlgProps.m_nEscapement = m_nEscapement;
	dlgProps.m_nOrientation = m_nOrientation;
	dlgProps.m_nWeight = m_nWeight;
	dlgProps.m_bItalic = m_bItalic;
	dlgProps.m_bUnderline = m_bUnderline;
	dlgProps.m_bStrikeOut = m_bStrikeOut;
	dlgProps.m_bCharSet = m_bCharSet;
	dlgProps.m_bOutPrecision = m_bOutPrecision;
	dlgProps.m_bClipPrecision = m_bClipPrecision;
	dlgProps.m_bQuality = m_bQuality;
	dlgProps.m_bPitchAndFamily = m_bPitchAndFamily;
	dlgProps.clrText = clrText;
	dlgProps.clrBackGround = clrBackGround;
	dlgProps.clrBorder = clrBorder;

	if(dlgProps.DoModal() == IDOK)
	{
		bRet = TRUE;

		strText = dlgProps.strText;
		nType = dlgProps.nType;
		m_strFaceName = dlgProps.m_strFaceName;
		m_nHeight = dlgProps.m_nHeight;
		m_nWidth = dlgProps.m_nWidth;
		m_nEscapement = dlgProps.m_nEscapement;
		m_nOrientation = dlgProps.m_nOrientation;
		m_nWeight = dlgProps.m_nWeight;
		m_bItalic = dlgProps.m_bItalic;
		m_bUnderline = dlgProps.m_bUnderline;
		m_bStrikeOut = dlgProps.m_bStrikeOut;
		m_bCharSet = dlgProps.m_bCharSet;
		m_bOutPrecision = dlgProps.m_bOutPrecision;
		m_bClipPrecision = dlgProps.m_bClipPrecision;
		m_bQuality = dlgProps.m_bQuality;
		m_bPitchAndFamily = dlgProps.m_bPitchAndFamily;
		clrText = dlgProps.clrText;
		clrBackGround = dlgProps.clrBackGround;
		clrBorder = dlgProps.clrBorder;
	} else
	{
		bRet = FALSE;
	}

	return bRet;
}

BOOL CGroupBoxObject::GetEvent(int nIndex, IRPluginEventInfo* pEventInfo)
{
	if((nIndex >= 0) && nIndex < NUM_OB_EVENTS)
	{
		if(m_pEvents[nIndex])
		{
			lstrcpy(pEventInfo->m_szName,m_pEvents[nIndex]->m_szName);
			lstrcpy(pEventInfo->m_szArgs,m_pEvents[nIndex]->m_szArgs);
			return TRUE;
		} else
		{
			return FALSE;
		}
	} else
	{
		return NULL;
	}
}

int CGroupBoxObject::GetNumEvents()
{
	return NUM_OB_EVENTS;
}

int CGroupBoxObject::RegisterLUAFunctions(lua_State* L)
{
	// Always call base class first
	CIRPluginObject::RegisterLUAFunctions(L);

	GroupBox_RegisterLuaFunctions(L);

	return 0;
}
