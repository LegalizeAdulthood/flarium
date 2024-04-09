// PrtScale.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPrtScale dialog

class CPrtScale : public CDialog
{
// Construction
public:
	CPrtScale(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPrtScale)
	enum { IDD = IDD_PRINT_SCALING };
	BOOL	m_Fit_To_Page;
	int		m_PrintFactor;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrtScale)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPrtScale)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
