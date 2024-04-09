// Affine.cpp : implementation file
//

#include "stdafx.h"
#include "flarium24.h"
#include "Affine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAffine dialog


CAffine::CAffine(CWnd* pParent /*=NULL*/)
	: CDialog(CAffine::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAffine)
	m_A01 = 0.0;
	m_A02 = 0.0;
	m_A03 = 0.0;
	m_A04 = 0.0;
	m_A05 = 0.0;
	m_A06 = 0.0;
	m_A07 = 0.0;
	m_A08 = 0.0;
	m_A09 = 0.0;
	m_A10 = 0.0;
	m_A11 = 0.0;
	m_A12 = 0.0;
	m_Counts = 0;
	m_Formulae = 0;
	m_A13 = 0.0;
	m_A14 = 0.0;
	m_A15 = 0.0;
	m_A16 = 0.0;
	m_A17 = 0.0;
	m_A18 = 0.0;
	m_A19 = 0.0;
	m_A20 = 0.0;
	m_A21 = 0.0;
	m_A22 = 0.0;
	m_A23 = 0.0;
	m_A24 = 0.0;
	m_A25 = 0.0;
	m_A26 = 0.0;
	m_A27 = 0.0;
	m_A28 = 0.0;
	m_A29 = 0.0;
	m_A30 = 0.0;
	//}}AFX_DATA_INIT
}

CAffine::CAffine(CView* pAffineView)   // Modeless Constructor
	: CDialog()
{
	m_pAffineView = pAffineView;
}

void CAffine::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAffine)
	DDX_Text(pDX, IDC_A01, m_A01);
	DDX_Text(pDX, IDC_A02, m_A02);
	DDX_Text(pDX, IDC_A03, m_A03);
	DDX_Text(pDX, IDC_A04, m_A04);
	DDX_Text(pDX, IDC_A05, m_A05);
	DDX_Text(pDX, IDC_A06, m_A06);
	DDX_Text(pDX, IDC_A07, m_A07);
	DDX_Text(pDX, IDC_A08, m_A08);
	DDX_Text(pDX, IDC_A09, m_A09);
	DDX_Text(pDX, IDC_A10, m_A10);
	DDX_Text(pDX, IDC_A11, m_A11);
	DDX_Text(pDX, IDC_A12, m_A12);
	DDX_Text(pDX, IDC_COUNTS, m_Counts);
	DDX_Text(pDX, IDC_FORMULAE, m_Formulae);
	DDV_MinMaxInt(pDX, m_Formulae, 0, 200);
	DDX_Text(pDX, IDC_A13a, m_A13);
	DDX_Text(pDX, IDC_A14a, m_A14);
	DDX_Text(pDX, IDC_A15, m_A15);
	DDX_Text(pDX, IDC_A16, m_A16);
	DDX_Text(pDX, IDC_A17, m_A17);
	DDX_Text(pDX, IDC_A18, m_A18);
	DDX_Text(pDX, IDC_A19, m_A19);
	DDX_Text(pDX, IDC_A20, m_A20);
	DDX_Text(pDX, IDC_A21a, m_A21);
	DDX_Text(pDX, IDC_A22a, m_A22);
	DDX_Text(pDX, IDC_A23a, m_A23);
	DDX_Text(pDX, IDC_A24a, m_A24);
	DDX_Text(pDX, IDC_A25a, m_A25);
	DDX_Text(pDX, IDC_A26a, m_A26);
	DDX_Text(pDX, IDC_A27a, m_A27);
	DDX_Text(pDX, IDC_A28a, m_A28);
	DDX_Text(pDX, IDC_A29a, m_A29);
	DDX_Text(pDX, IDC_A30, m_A30);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAffine, CDialog)
	//{{AFX_MSG_MAP(CAffine)
	ON_BN_CLICKED(IDC_RANDOM, OnRandom)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAffine message handlers

BOOL CAffine::Create()
{
	return CDialog::Create(CAffine::IDD);
}

void CAffine::OnClose() 
{
	m_pAffineView->PostMessage(WM_DLGAFFINE, ID_DLGCLOSE);
	
	CDialog::OnClose();
}

void CAffine::OnRandom() 
{
	AfxGetMainWnd()->PostMessage(WM_COMMAND, ID_DRAW_REPEAT);
}

void CAffine::OnOK() 
{
	UpdateData(TRUE);
	m_pAffineView->PostMessage(WM_DLGAFFINE, ID_APPLY);
}

