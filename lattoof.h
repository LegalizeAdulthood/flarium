// Lattoof.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLattoof dialog

class CLattoof : public CDialog
{
// Construction
public:
	CLattoof(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLattoof)
	enum { IDD = IDD_LATOOF };
	double	m_Bottom;
	double	m_Left;
	double	m_ma;
	double	m_mb;
	double	m_mx;
	double	m_my;
	double	m_Right;
	double	m_Top;
	int		m_Count;
	double	m_mc;
	double	m_md;
	int		m_Formulae;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLattoof)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLattoof)
	afx_msg void OnReset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
