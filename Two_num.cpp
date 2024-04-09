// Two_Num.cpp : implementation file
//

#include "stdafx.h"
#include "flarium24.h"
#include "Two_Num.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTwo_Num dialog


CTwo_Num::CTwo_Num(CWnd* pParent /*=NULL*/)
	: CDialog(CTwo_Num::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTwo_Num)
	m_cn_real = 0.0;
	m_cn_imag = 0.0;
	m_cr_imag = 0.0;
	m_cr_real = 0.0;
	//}}AFX_DATA_INIT
}


void CTwo_Num::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTwo_Num)
	DDX_Text(pDX, IDC_CN_REAL, m_cn_real);
	DDX_Text(pDX, IDC_CN_IMAG, m_cn_imag);
	DDX_Text(pDX, IDC_CR_IMAG, m_cr_imag);
	DDX_Text(pDX, IDC_CR_REAL, m_cr_real);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTwo_Num, CDialog)
	//{{AFX_MSG_MAP(CTwo_Num)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTwo_Num message handlers
