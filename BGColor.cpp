// BGColor.cpp : implementation file
//

#include "stdafx.h"
#include "flarium24.h"
#include "BGColor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBGColor dialog


CBGColor::CBGColor(CWnd* pParent /*=NULL*/)
	: CDialog(CBGColor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBGColor)
	m_BlueBack = 0;
	m_GreenBack = 0;
	m_RedBack = 0;
	//}}AFX_DATA_INIT
}


void CBGColor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBGColor)
	DDX_Text(pDX, IDC_BLUEBACK, m_BlueBack);
	DDV_MinMaxInt(pDX, m_BlueBack, 0, 255);
	DDX_Text(pDX, IDC_GREENBACK, m_GreenBack);
	DDV_MinMaxInt(pDX, m_GreenBack, 0, 255);
	DDX_Text(pDX, IDC_REDBACK, m_RedBack);
	DDV_MinMaxInt(pDX, m_RedBack, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBGColor, CDialog)
	//{{AFX_MSG_MAP(CBGColor)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBGColor message handlers
