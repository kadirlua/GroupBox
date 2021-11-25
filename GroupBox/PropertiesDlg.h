#pragma once
#include "ColourPicker.h"

// CPropertiesDlg dialog

class CPropertiesDlg : public CDialog
{
	DECLARE_DYNAMIC(CPropertiesDlg)

public:
	CPropertiesDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPropertiesDlg();

	CEdit c_EditStrText;
	CString strText;
	int nType;
	CFont m_font;
	CString m_strFaceName;
	int m_nHeight;
	int m_nWidth;
	int m_nEscapement;
	int m_nOrientation;
	int m_nWeight;
	BYTE m_bItalic;
	BYTE m_bUnderline;
	BYTE m_bStrikeOut;
	BYTE m_bCharSet;
	BYTE m_bOutPrecision;
	BYTE m_bClipPrecision;
	BYTE m_bQuality;
	BYTE m_bPitchAndFamily;
	COLORREF clrText;
	CColourPicker c_btnBackGroundColor;
	COLORREF clrBackGround;
	CColourPicker c_btnBorderColor;
	COLORREF clrBorder;
	//}}AFX_DATA

	CString m_strHelpPath;

// Dialog Data
	enum { IDD = IDD_PROPERTIESDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnHelp();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedFontButton();
};
