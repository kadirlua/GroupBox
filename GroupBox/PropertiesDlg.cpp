// PropertiesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GroupBox.h"
#include "PropertiesDlg.h"


// CPropertiesDlg dialog

IMPLEMENT_DYNAMIC(CPropertiesDlg, CDialog)

CPropertiesDlg::CPropertiesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPropertiesDlg::IDD, pParent)
{
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
	m_strHelpPath.Empty();

}

CPropertiesDlg::~CPropertiesDlg()
{
}

void CPropertiesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//
	DDX_Text(pDX, IDC_TEXT, strText);
	DDX_CBIndex(pDX, IDC_ALIGNMENT, nType);
	DDX_Control(pDX,IDC_BACKGROUND_COLOR,c_btnBackGroundColor);
	DDX_ColourPicker(pDX,IDC_BACKGROUND_COLOR,clrBackGround);
	DDX_Control(pDX,IDC_BORDER_COLOR,c_btnBorderColor);
	DDX_ColourPicker(pDX,IDC_BORDER_COLOR,clrBorder);
}


BEGIN_MESSAGE_MAP(CPropertiesDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_HELP, OnBtnHelp)
	ON_BN_CLICKED(IDC_FONT_BUTTON, &CPropertiesDlg::OnBnClickedFontButton)
END_MESSAGE_MAP()


// CPropertiesDlg message handlers

BOOL CPropertiesDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//c_EditStrText.SetWindowTextA(strText);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPropertiesDlg::OnBtnHelp() 
{
	// TODO: Add your control notification handler code here
	if(GetFileAttributes(m_strHelpPath) != -1)
	{
		ShellExecute(m_hWnd,"open",m_strHelpPath,NULL,NULL,SW_NORMAL);
	}
}

void CPropertiesDlg::OnBnClickedFontButton()
{
	UpdateData(TRUE);

	// get font for current dialog, just to fill in LOGFONT
	LOGFONT lf;
	CFont *pFont = GetFont();
	pFont->GetLogFont(&lf);

	// use last font height
	lf.lfHeight = m_nHeight;
	lf.lfWidth = m_nWidth;
	lf.lfEscapement = m_nEscapement;
	lf.lfOrientation = m_nOrientation;
	lf.lfWeight = m_nWeight;
	lf.lfItalic = m_bItalic;
	lf.lfUnderline = m_bUnderline;
	lf.lfStrikeOut = m_bStrikeOut;
	lf.lfCharSet = m_bCharSet;
	lf.lfOutPrecision = m_bOutPrecision;
	lf.lfClipPrecision = m_bClipPrecision;
	lf.lfQuality = m_bQuality;
	lf.lfPitchAndFamily = m_bPitchAndFamily;

	// use last face name
	_tcscpy(lf.lfFaceName, m_strFaceName);

	// display CFontDialog
	CFontDialog dlg(&lf);
	//if (m_nFonts == 3)
	dlg.m_cf.rgbColors = clrText;
	//dlg.m_cf.Flags &= ~CF_EFFECTS;		// remove the Effects controls
	//dlg.m_cf.Flags |= CF_NOSCRIPTSEL;		// disable the script combo

	if (dlg.DoModal() == IDOK)
	{

		dlg.GetCurrentFont(&lf);
		m_nHeight = lf.lfHeight;
		m_strFaceName = lf.lfFaceName;
		m_nWidth = lf.lfWidth;
		m_nEscapement = lf.lfEscapement;
		m_nOrientation = lf.lfOrientation;
		m_nWeight = lf.lfWeight;
		m_bItalic = lf.lfItalic;
		m_bUnderline = lf.lfUnderline;
		m_bStrikeOut = lf.lfStrikeOut;
		m_bCharSet = lf.lfCharSet;
		m_bOutPrecision = lf.lfOutPrecision;
		m_bClipPrecision = lf.lfClipPrecision;
		m_bQuality = lf.lfQuality;
		m_bPitchAndFamily = lf.lfPitchAndFamily;
		clrText = dlg.GetColor();
	}
	// TODO: Add your control notification handler code here
}
