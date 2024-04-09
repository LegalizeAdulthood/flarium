// PrtScale.cpp : implementation file
//

#include "stdafx.h"
#include "flarium24.h"
#include "PrtScale.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrtScale dialog


CPrtScale::CPrtScale(CWnd* pParent /*=NULL*/)
	: CDialog(CPrtScale::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrtScale)
	m_Fit_To_Page = FALSE;
	m_PrintFactor = 0;
	//}}AFX_DATA_INIT
}


void CPrtScale::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrtScale)
	DDX_Check(pDX, IDC_FIT_TO_PAGE, m_Fit_To_Page);
	DDX_Text(pDX, IDC_ENLARGEMENT, m_PrintFactor);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrtScale, CDialog)
	//{{AFX_MSG_MAP(CPrtScale)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrtScale message handlers
