#if !defined(AFX_ONENUM_H__959FD441_9C79_11D0_9063_444553540000__INCLUDED_)
#define AFX_ONENUM_H__959FD441_9C79_11D0_9063_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// OneNum.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COneNum dialog

class COneNum : public CDialog
{
// Construction
public:
	COneNum(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COneNum)
	enum { IDD = IDD_DIALOG_1RW };
	double	m_RW1_n;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COneNum)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COneNum)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ONENUM_H__959FD441_9C79_11D0_9063_444553540000__INCLUDED_)
