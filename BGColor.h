// BGColor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBGColor dialog

class CBGColor : public CDialog
{
// Construction
public:
	CBGColor(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBGColor)
	enum { IDD = IDD_BGCOLOR };
	int		m_BlueBack;
	int		m_GreenBack;
	int		m_RedBack;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBGColor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBGColor)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
