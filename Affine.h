// Affine.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAffine dialog

class CAffine : public CDialog
{
// Construction
public:
	CAffine(CWnd* pParent = NULL);   // standard constructor
	CView* m_pAffineView;
	CAffine(CView* pAffineView);

// Implementation
	BOOL Create();

// Dialog Data
	//{{AFX_DATA(CAffine)
	enum { IDD = IDD_AFFINE };
	double	m_A01;
	double	m_A02;
	double	m_A03;
	double	m_A04;
	double	m_A05;
	double	m_A06;
	double	m_A07;
	double	m_A08;
	double	m_A09;
	double	m_A10;
	double	m_A11;
	double	m_A12;
	int		m_Counts;
	int		m_Formulae;
	double	m_A13;
	double	m_A14;
	double	m_A15;
	double	m_A16;
	double	m_A17;
	double	m_A18;
	double	m_A19;
	double	m_A20;
	double	m_A21;
	double	m_A22;
	double	m_A23;
	double	m_A24;
	double	m_A25;
	double	m_A26;
	double	m_A27;
	double	m_A28;
	double	m_A29;
	double	m_A30;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAffine)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAffine)
	afx_msg void OnRandom();
	afx_msg void OnClose();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
