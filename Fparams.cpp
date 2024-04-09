// fparams.cpp : implementation file
//

#include "stdafx.h"
#include "Flarium24.h"
#include "fparams.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFParams dialog


CFParams::CFParams(CWnd* pParent /*=NULL*/)
	: CDialog(CFParams::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFParams)
	m_Iterations = 0;
	m_Bailout = 0.0;
	m_BayFact1 = 0.0;
	m_BayFact2 = 0.0;
	m_FilterFactor = 0;
	m_Strands = 0.0;
	m_Julia_X = 0.0;
	m_Julia_Y = 0.0;
	m_dMIN = 0.0;
	m_cn_Real = 0.0;
	m_cn_Imag = 0.0;
	m_Magnification = 0.0;
	m_X_Mid = 0.0;
	m_Y_Mid = 0.0;
	//}}AFX_DATA_INIT
}


void CFParams::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFParams)
	DDX_Text(pDX, IDC_ITERATIONS, m_Iterations);
	DDX_Text(pDX, IDC_BAILOUT, m_Bailout);
	DDX_Text(pDX, IDC_BAY_EDIT1, m_BayFact1);
	DDX_Text(pDX, IDC_BAY_EDIT3, m_BayFact2);
	DDX_Text(pDX, IDC_FILTER_FACTOR2, m_FilterFactor);
	DDX_Text(pDX, IDC_STRANDS1, m_Strands);
	DDX_Text(pDX, IDC_JULIA_X, m_Julia_X);
	DDX_Text(pDX, IDC_JULIA_Y, m_Julia_Y);
	DDX_Text(pDX, IDC_NTYPEMIN, m_dMIN);
	DDX_Text(pDX, IDC_CN_REAL, m_cn_Real);
	DDX_Text(pDX, IDC_CN_IMAG, m_cn_Imag);
	DDX_Text(pDX, IDC_MAGNIFICATION, m_Magnification);
	DDX_Text(pDX, IDC_X_MID, m_X_Mid);
	DDX_Text(pDX, IDC_Y_MID, m_Y_Mid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFParams, CDialog)
	//{{AFX_MSG_MAP(CFParams)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CFParams message handlers
