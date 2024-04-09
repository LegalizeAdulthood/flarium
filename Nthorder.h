// nthorder.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNthOrder dialog

class CNthOrder : public CDialog
{
// Construction
public:
	CNthOrder(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CNthOrder)
	enum { IDD = IDD_NTH_ORDER };
	double	m_RealNthOrder;
	double	m_ImaginaryNthOrder;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CNthOrder)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
