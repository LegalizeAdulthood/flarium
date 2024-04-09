// rw1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRW1 dialog

class CRW1 : public CDialog
{
// Construction
public:
	CRW1(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRW1)
	enum { IDD = IDD_DIALOG_1RW };
	double	m_RW1_n;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRW1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRW1)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
