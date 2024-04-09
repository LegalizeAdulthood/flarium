// rw1.cpp : implementation file
//

#include "stdafx.h"
#include "itriazon.h"
#include "rw1.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRW1 dialog


CRW1::CRW1(CWnd* pParent /*=NULL*/)
	: CDialog(CRW1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRW1)
	m_RW1_n = 0;
	//}}AFX_DATA_INIT
}


void CRW1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRW1)
	DDX_Text(pDX, IDC_EDIT_N, m_RW1_n);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRW1, CDialog)
	//{{AFX_MSG_MAP(CRW1)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CRW1 message handlers
