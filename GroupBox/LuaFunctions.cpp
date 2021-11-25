#include "stdafx.h"
#include "LuaFunctions.h"
#include "GroupBoxObject.h"
#include "IRPluginHelperFunctions.h"

// LUA FUNCTIONS:

luaL_reg lib_GroupBox[] = {
		{"SetBorderColor", GroupBox_SetBorderColor},
		{"SetLabelText", GroupBox_SetLabelText},
		{"SetCaptionTextColor",GroupBox_SetCaptionTextColor},
		{"SetBackGroundColor",GroupBox_SetBackGroundColor},
		{NULL, NULL}
	};

int GroupBox_SetLabelText(lua_State* luaState)
{
	IRLUA_PLUGIN_ResetLastError(luaState);
	int nLastError = 0;

	CString strObjectName;
	CString strText;
	
	IRLUA_PLUGIN_CheckNumArgs(luaState,2);
	strObjectName = IRLUA_PLUGIN_CheckString(luaState,1);
	strText = IRLUA_PLUGIN_CheckString(luaState,2);
	
	CIRPluginObject* pObject = NULL;
	pObject = IRLUA_PLUGIN_GetObjectPtr(luaState,strObjectName);
	if(pObject)
	{
		int nSize = 1000;
		char szObjectID[1000];
		pObject->GetObjectID(szObjectID,&nSize);

		if(lstrcmp(szObjectID,"IR_GROUPBOX_OBJECT") == 0)
		{
			CGroupBoxObject* pGroupBox = (CGroupBoxObject*) pObject;
			if(pGroupBox->m_pGroupBoxHolder)
			{
				if(pGroupBox->m_pGroupBoxHolder->m_pGroupBoxCtrl)
				{
					if(IsWindow(pGroupBox->m_pGroupBoxHolder->m_pGroupBoxCtrl->m_hWnd))
					{
						pGroupBox->m_pGroupBoxHolder->m_pGroupBoxCtrl->SetText(strText);
					}
				}
			}
		} else
		{
			nLastError = 1100; // "The specified object could not be found."
		}
	} else
	{
		nLastError = 1100; // "The specified object could not be found."
	}

	IRLUA_PLUGIN_SetLastError(luaState,nLastError);
	return 0;
}

int GroupBox_SetBorderColor(lua_State* luaState)
{
	IRLUA_PLUGIN_ResetLastError(luaState);
	int nLastError = 0;

	CString strObjectName;
	COLORREF clrBorder;
	
	IRLUA_PLUGIN_CheckNumArgs(luaState,2);
	strObjectName = IRLUA_PLUGIN_CheckString(luaState,1);
	clrBorder = (COLORREF)IRLUA_PLUGIN_CheckNumber(luaState,2);
	
	CIRPluginObject* pObject = NULL;
	pObject = IRLUA_PLUGIN_GetObjectPtr(luaState,strObjectName);
	if(pObject)
	{
		int nSize = 1000;
		char szObjectID[1000];
		pObject->GetObjectID(szObjectID,&nSize);

		if(lstrcmp(szObjectID,"IR_GROUPBOX_OBJECT") == 0)
		{
			CGroupBoxObject* pGroupBox = (CGroupBoxObject*) pObject;
			if(pGroupBox->m_pGroupBoxHolder)
			{
				if(pGroupBox->m_pGroupBoxHolder->m_pGroupBoxCtrl)
				{
					if(IsWindow(pGroupBox->m_pGroupBoxHolder->m_pGroupBoxCtrl->m_hWnd))
					{
						pGroupBox->m_pGroupBoxHolder->m_pGroupBoxCtrl->SetBorderColor(clrBorder);
					}
				}
			}
		} else
		{
			nLastError = 1100; // "The specified object could not be found."
		}
	} else
	{
		nLastError = 1100; // "The specified object could not be found."
	}

	IRLUA_PLUGIN_SetLastError(luaState,nLastError);
	return 0;
}

int GroupBox_SetCaptionTextColor(lua_State* luaState)
{
	IRLUA_PLUGIN_ResetLastError(luaState);
	int nLastError = 0;

	CString strObjectName;
	COLORREF clrText;
	
	IRLUA_PLUGIN_CheckNumArgs(luaState,2);
	strObjectName = IRLUA_PLUGIN_CheckString(luaState,1);
	clrText = (COLORREF)IRLUA_PLUGIN_CheckNumber(luaState,2);
	
	CIRPluginObject* pObject = NULL;
	pObject = IRLUA_PLUGIN_GetObjectPtr(luaState,strObjectName);
	if(pObject)
	{
		int nSize = 1000;
		char szObjectID[1000];
		pObject->GetObjectID(szObjectID,&nSize);

		if(lstrcmp(szObjectID,"IR_GROUPBOX_OBJECT") == 0)
		{
			CGroupBoxObject* pGroupBox = (CGroupBoxObject*) pObject;
			if(pGroupBox->m_pGroupBoxHolder)
			{
				if(pGroupBox->m_pGroupBoxHolder->m_pGroupBoxCtrl)
				{
					if(IsWindow(pGroupBox->m_pGroupBoxHolder->m_pGroupBoxCtrl->m_hWnd))
					{
						pGroupBox->m_pGroupBoxHolder->m_pGroupBoxCtrl->SetCatptionTextColor(clrText);
					}
				}
			}
		} else
		{
			nLastError = 1100; // "The specified object could not be found."
		}
	} else
	{
		nLastError = 1100; // "The specified object could not be found."
	}

	IRLUA_PLUGIN_SetLastError(luaState,nLastError);
	return 0;
}

int GroupBox_SetBackGroundColor(lua_State* luaState)
{
	IRLUA_PLUGIN_ResetLastError(luaState);
	int nLastError = 0;

	CString strObjectName;
	COLORREF clrBackGround;
	
	IRLUA_PLUGIN_CheckNumArgs(luaState,2);
	strObjectName = IRLUA_PLUGIN_CheckString(luaState,1);
	clrBackGround = (COLORREF)IRLUA_PLUGIN_CheckNumber(luaState,2);
	
	CIRPluginObject* pObject = NULL;
	pObject = IRLUA_PLUGIN_GetObjectPtr(luaState,strObjectName);
	if(pObject)
	{
		int nSize = 1000;
		char szObjectID[1000];
		pObject->GetObjectID(szObjectID,&nSize);

		if(lstrcmp(szObjectID,"IR_GROUPBOX_OBJECT") == 0)
		{
			CGroupBoxObject* pGroupBox = (CGroupBoxObject*) pObject;
			if(pGroupBox->m_pGroupBoxHolder)
			{
				if(pGroupBox->m_pGroupBoxHolder->m_pGroupBoxCtrl)
				{
					if(IsWindow(pGroupBox->m_pGroupBoxHolder->m_pGroupBoxCtrl->m_hWnd))
					{
						pGroupBox->m_pGroupBoxHolder->m_pGroupBoxCtrl->SetBackgroundColor(clrBackGround);
					}
				}
			}
		} else
		{
			nLastError = 1100; // "The specified object could not be found."
		}
	} else
	{
		nLastError = 1100; // "The specified object could not be found."
	}

	IRLUA_PLUGIN_SetLastError(luaState,nLastError);
	return 0;
}

void GroupBox_RegisterLuaFunctions(lua_State* luaState)
{
	luaL_openlib(luaState, "GroupBox", lib_GroupBox, 0);
}