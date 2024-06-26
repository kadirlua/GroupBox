// GroupBox.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "GroupBox.h"
#include "IRPluginObject.h"
#include "GroupBoxObject.h"
#include "IRPluginHelperFunctions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

char szInformation[] = "GroupBox Object for AutoPlay Media Studio\r\nCreated by Kadir Altındağ\r\n"
					   "Copyright © 2013";
char szObjectName[] = "GroupBox";
char szXML[10000];

CIRPluginObject* irPlg_Object_CreateObject()
{
	return new CGroupBoxObject;
}

void irPlg_Object_DeleteObject(CIRPluginObject* pObject)
{
	if(pObject)
	{
		delete pObject;
		pObject = NULL;
	}
}


int irPlg_GetPluginName(char* szBuffer, int* pnBufferSize)
{
	// The proper name of the object as it will appear on the Plugins menu
	int nLength = lstrlen(szObjectName);
	if(*pnBufferSize < nLength)
	{
		*pnBufferSize = nLength;
		return -1;
	} else
	{
		memset(szBuffer,0,*pnBufferSize);
		lstrcpy(szBuffer,szObjectName);
		return nLength;
	}
}

int irPlg_GetPluginVersion(char* szBuffer, int* pnBufferSize)
{
	int nLength = lstrlen("1.5.2.0");
	if(*pnBufferSize < nLength)
	{
		*pnBufferSize = nLength;
		return -1;
	} else
	{
		memset(szBuffer,0,*pnBufferSize);
		lstrcpy(szBuffer,"1.5.2.0");
		return nLength;
	}
}

int irPlg_GetIRPluginObjectVersion()
{
	// Always returns this, do not remove or modify...
	return IR_PLUGIN_CLASS_VERSION;
}

int irPlg_GetAuthorInfo(char* szBuffer, int* pnBufferSize)
{
	int nLength = lstrlen(szInformation);
	if(*pnBufferSize < nLength)
	{
		*pnBufferSize = nLength;
		return -1;
	} else
	{
		memset(szBuffer,0,*pnBufferSize);
		lstrcpy(szBuffer,szInformation);
		return nLength;
	}
}

int irPlg_GetPluginActionXML(char* szBuffer, int* pnBufferSize)
{
	memset(szXML,0,10000);
	if(!IR_PLUGIN_GetTextFromResourceFile("TEXTFILE",IDR_ACTIONSXML,szXML,10000))
	{
		lstrcpy(szXML,"");
	}

	int nLength = lstrlen(szXML);
	if(*pnBufferSize < nLength)
	{
		*pnBufferSize = nLength;
		return -1;
	} else
	{
		memset(szBuffer,0,*pnBufferSize);
		lstrcpy(szBuffer,szXML);
		return nLength;
	}
}

bool irPlg_ShowHelpForAction(char* lpszActionName, char* lpszPluginPath, HWND hParentWnd)
{
	CString strHelpFile;
	CString strFullHelpLink;

	strHelpFile.Format("%s\\GroupBox_Help.htm",lpszPluginPath);
	strFullHelpLink.Format("%s#%s",strHelpFile,lpszActionName);

	if(GetFileAttributes(strHelpFile) == -1)
	{
		return FALSE;
	} else
	{
		ShellExecute(hParentWnd,"open",strHelpFile,NULL,NULL,SW_NORMAL);
	}

	return TRUE;
}

bool irPlg_ShowHelpForPlugin(char* lpszPluginPath, HWND hParentWnd)
{
	CString strHelpFile;

	strHelpFile.Format("%s\\GroupBox_Help.htm",lpszPluginPath);

	if(GetFileAttributes(strHelpFile) == -1)
	{
		return FALSE;
	} else
	{
		ShellExecute(hParentWnd,"open",strHelpFile,NULL,NULL,SW_NORMAL);
	}

	return TRUE;
}

bool irPlg_ValidateLicense(char* lpszLicenseInfo)
{
	return TRUE;
}

int irPlg_GetLuaVersion(char* szBuffer, int* pnBufferSize)
{
	int nLength = lstrlen(LUA_VERSION);
	if(*pnBufferSize < nLength)
	{
		*pnBufferSize = nLength;
		return -1;
	} else
	{
		memset(szBuffer,0,*pnBufferSize);
		lstrcpy(szBuffer,LUA_VERSION);
		return nLength;
	}
}

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CGroupBoxApp

BEGIN_MESSAGE_MAP(CGroupBoxApp, CWinApp)
END_MESSAGE_MAP()


// CGroupBoxApp construction

CGroupBoxApp::CGroupBoxApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CGroupBoxApp object

CGroupBoxApp theApp;


// CGroupBoxApp initialization

BOOL CGroupBoxApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}