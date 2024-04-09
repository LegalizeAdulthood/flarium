// Lattoof.cpp : implementation file
//

#include "stdafx.h"
#include "Flarium24.h"
#include "Lattoof.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLattoof dialog


CLattoof::CLattoof(CWnd* pParent /*=NULL*/)
	: CDialog(CLattoof::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLattoof)
	m_Bottom = 0.0;
	m_Left = 0.0;
	m_ma = 0.0;
	m_mb = 0.0;
	m_mx = 0.0;
	m_my = 0.0;
	m_Right = 0.0;
	m_Top = 0.0;
	m_Count = 0;
	m_mc = 0.0;
	m_md = 0.0;
	m_Formulae = 0;
	//}}AFX_DATA_INIT
}


void CLattoof::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLattoof)
	DDX_Text(pDX, IDC_BOTTOM, m_Bottom);
	DDX_Text(pDX, IDC_LEFT, m_Left);
	DDX_Text(pDX, IDC_MA, m_ma);
	DDX_Text(pDX, IDC_MB, m_mb);
	DDX_Text(pDX, IDC_MX, m_mx);
	DDX_Text(pDX, IDC_MY, m_my);
	DDX_Text(pDX, IDC_RIGHT, m_Right);
	DDX_Text(pDX, IDC_TOP, m_Top);
	DDX_Text(pDX, IDC_COUNT, m_Count);
	DDX_Text(pDX, IDC_MC, m_mc);
	DDX_Text(pDX, IDC_MD, m_md);
	DDX_Text(pDX, IDC_FORMULAE, m_Formulae);
	DDV_MinMaxInt(pDX, m_Formulae, 0, 200);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLattoof, CDialog)
	//{{AFX_MSG_MAP(CLattoof)
	ON_BN_CLICKED(IDC_RESET, OnReset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLattoof message handlers

void CLattoof::OnReset() 
{
	// Latoocarfian variables
	m_ma  = -1;
	m_mb  =  3;

  m_mc=0.8;
	m_md=0.8;
  
  m_mx=0.1;
	m_my=0.1;																							
  m_Count = 400000;

  m_Bottom  = -2.0;
	m_Left    = -2.0;
	m_Right   = 2;
	m_Top     = 2;

  UpdateData(FALSE);

}


