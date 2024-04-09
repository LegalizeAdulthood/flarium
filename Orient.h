// Orient.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COrient dialog

class COrient : public CDialog
{
// Construction
public:
	COrient(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COrient)
	enum { IDD = IDD_ORIENT };
	double	m_Imag;
	double	m_Real;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COrient)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COrient)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
