// nthorder.cpp : implementation file
//

#include "stdafx.h"
#include "flarium24.h"
#include "nthorder.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNthOrder dialog


CNthOrder::CNthOrder(CWnd* pParent /*=NULL*/)
	: CDialog(CNthOrder::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNthOrder)
	m_RealNthOrder = 0.0;
	m_ImaginaryNthOrder = 0.0;
	//}}AFX_DATA_INIT
}

void CNthOrder::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNthOrder)
	DDX_Text(pDX, IDC_EDIT1, m_RealNthOrder);
	DDX_Text(pDX, IDC_EDIT2, m_ImaginaryNthOrder);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CNthOrder, CDialog)
	//{{AFX_MSG_MAP(CNthOrder)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CNthOrder message handlers
