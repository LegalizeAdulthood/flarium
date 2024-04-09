#if !defined(AFX_QPARAMS_H__448F9001_B8F2_11D0_9E81_444553540000__INCLUDED_)
#define AFX_QPARAMS_H__448F9001_B8F2_11D0_9E81_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Qparams.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQparams dialog

class CQparams : public CDialog
{
// Construction
public:
	CQparams(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CQparams)
	enum { IDD = IDD_QUATERNION };
	double	m_qk1;
	double	m_qk2;
	double	m_qt1;
	double	m_qt2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQparams)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CQparams)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QPARAMS_H__448F9001_B8F2_11D0_9E81_444553540000__INCLUDED_)
