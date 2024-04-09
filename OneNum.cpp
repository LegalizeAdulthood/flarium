// OneNum.cpp : implementation file
//

#include "stdafx.h"
#include "flarium24.h"
#include "OneNum.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COneNum dialog


COneNum::COneNum(CWnd* pParent /*=NULL*/)
	: CDialog(COneNum::IDD, pParent)
{
	//{{AFX_DATA_INIT(COneNum)
	m_RW1_n = 0.0;
	//}}AFX_DATA_INIT
}


void COneNum::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COneNum)
	DDX_Text(pDX, IDC_EDIT_N, m_RW1_n);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COneNum, CDialog)
	//{{AFX_MSG_MAP(COneNum)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COneNum message handlers
