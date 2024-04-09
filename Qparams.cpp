// Qparams.cpp : implementation file
//

#include "stdafx.h"
#include "flarium24.h"
#include "Qparams.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQparams dialog


CQparams::CQparams(CWnd* pParent /*=NULL*/)
	: CDialog(CQparams::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQparams)
	m_qk1 = 0.0;
	m_qk2 = 0.0;
	m_qt1 = 0.0;
	m_qt2 = 0.0;
	//}}AFX_DATA_INIT
}


void CQparams::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQparams)
	DDX_Text(pDX, IDC_QK1, m_qk1);
	DDX_Text(pDX, IDC_QK2, m_qk2);
	DDX_Text(pDX, IDC_QT1, m_qt1);
	DDX_Text(pDX, IDC_QT2, m_qt2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CQparams, CDialog)
	//{{AFX_MSG_MAP(CQparams)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQparams message handlers
