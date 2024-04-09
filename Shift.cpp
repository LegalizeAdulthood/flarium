// Shift.cpp : implementation file
//

#include "stdafx.h"
#include "flarium24.h"
#include "Shift.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Shift dialog


Shift::Shift(CWnd* pParent /*=NULL*/)
	: CDialog(Shift::IDD, pParent)
{
	//{{AFX_DATA_INIT(Shift)
	m_Shift_Red = 0;
	m_Shift_Green = 0;
	m_Shift_Blue = 0;
	//}}AFX_DATA_INIT
}

Shift::Shift(CView* pColorShift)  // Modeless Constructor
	: CDialog()
{
	m_pShiftView = pColorShift;
}

void Shift::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Shift)
	DDX_Control(pDX, IDC_CYCLE, m_Cycle_Button);
	DDX_Text(pDX, IDC_SHIFT_BLUE, m_Shift_Red);
	DDV_MinMaxInt(pDX, m_Shift_Red, -255, 255);
	DDX_Text(pDX, IDC_SHIFT_GREEN, m_Shift_Green);
	DDV_MinMaxInt(pDX, m_Shift_Green, -255, 255);
	DDX_Text(pDX, IDC_SHIFT_RED, m_Shift_Blue);
	DDV_MinMaxInt(pDX, m_Shift_Blue, -255, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Shift, CDialog)
	//{{AFX_MSG_MAP(Shift)
	ON_BN_CLICKED(IDC_APPLY, OnApply)
	ON_BN_CLICKED(IDC_CLOSE, OnClose)
	ON_BN_CLICKED(IDC_REVERSE, OnReverse)
	ON_BN_CLICKED(IDC_CYCLE, OnCycle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Shift message handlers

BOOL Shift::Create()
{
	return CDialog::Create(Shift::IDD);
}

void Shift::OnOK() 
{
	//AfxMessageBox("Close");
	UpdateData(TRUE);
	if (m_pShiftView != NULL)
	{
		m_pShiftView->PostMessage(WM_DLGSHIFT, ID_SHIFTCLOSE);
	}		
}

void Shift::OnApply() 
{
	UpdateData(TRUE);
	if (m_pShiftView != NULL)
	{
		m_pShiftView->PostMessage(WM_DLGSHIFT, ID_SHIFTAPPLY);
	}		
}

void Shift::OnClose() 
{
	//AfxMessageBox("Close");
	m_pShiftView->PostMessage(WM_DLGSHIFT, ID_SHIFTCLOSE);
	
	//CDialog::OnClose();	
}

void Shift::OnReverse() 
{
	UpdateData(TRUE);
	if (m_pShiftView != NULL)
	{
		m_pShiftView->PostMessage(WM_DLGSHIFT, ID_SHIFTREVERSE);
	}		
}

void Shift::OnCycle() 
{
	m_pShiftView->PostMessage(WM_COMMAND, ID_SHIFT_START);	
}
