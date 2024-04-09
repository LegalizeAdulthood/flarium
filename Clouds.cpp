// Clouds.cpp : implementation file
//

#include "stdafx.h"
#include "flarium24.h"
#include "Clouds.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClouds dialog


CClouds::CClouds(CWnd* pParent /*=NULL*/)
	: CDialog(CClouds::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClouds)
	m_Bottom = 0.0;
	m_Left = 0.0;
	m_Right = 0.0;
	m_Top = 0.0;
	//}}AFX_DATA_INIT
}


void CClouds::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClouds)
	DDX_Text(pDX, IDC_BOTTOM, m_Bottom);
	DDX_Text(pDX, IDC_LEFT, m_Left);
	DDX_Text(pDX, IDC_RIGHT, m_Right);
	DDX_Text(pDX, IDC_TOP, m_Top);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CClouds, CDialog)
	//{{AFX_MSG_MAP(CClouds)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClouds message handlers
