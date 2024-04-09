// Two_Num.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTwo_Num dialog

class CTwo_Num : public CDialog
{
// Construction
public:
	CTwo_Num(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTwo_Num)
	enum { IDD = IDD_CMPLX2 };
	double	m_cn_real;
	double	m_cn_imag;
	double	m_cr_imag;
	double	m_cr_real;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTwo_Num)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTwo_Num)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
