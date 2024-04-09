// Shift.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Shift dialog

class Shift : public CDialog
{
// Construction
public:
	Shift(CWnd* pParent = NULL);   // standard constructor
	CView* m_pShiftView;
	Shift(CView* pColorShift);
	BOOL Create();

// Dialog Data
	//{{AFX_DATA(Shift)
	enum { IDD = IDD_SHIFT };
	CButton	m_Cycle_Button;
	int		m_Shift_Red;
	int		m_Shift_Green;
	int		m_Shift_Blue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Shift)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Shift)
	virtual void OnOK();
	afx_msg void OnApply();
	afx_msg void OnClose();
	afx_msg void OnReverse();
	afx_msg void OnCycle();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
