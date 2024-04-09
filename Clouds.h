// Clouds.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClouds dialog

class CClouds : public CDialog
{
// Construction
public:
	CClouds(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CClouds)
	enum { IDD = IDD_CLOUDS };
	double	m_Bottom;
	double	m_Left;
	double	m_Right;
	double	m_Top;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClouds)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CClouds)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
