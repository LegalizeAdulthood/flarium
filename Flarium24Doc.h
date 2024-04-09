// Flarium24Doc.h : interface of the CFlarium24Doc class
//
/////////////////////////////////////////////////////////////////////////////

#include "dib.h"

class CFlarium24Doc : public CDocument
{
protected: // create from serialization only
	CFlarium24Doc();
	DECLARE_DYNCREATE(CFlarium24Doc)

// Attributes
public:
	CDIB m_dib;
	CString doc_PathName;
	CSize m_sizeDoc;
	BOOL bPrinting;
	int nColorIndex;
	int nPalType;
	int r, g, b;
	BOOL bCycleNewPalette;
	BOOL bShiftForward;
	BOOL bInvert;
	CRectTracker m_tracker;
	char cstr[81];
	BOOL bMerge;
	int	nMergeMode;

	// colors used to create fractal patterns
	DWORD 				*ColorTable;
	DWORD 				lColorCntr;
  long        	lMaxColors;
	DWORD     		Save_MaxColors;
	DWORD					dColorPix;

	BOOL      		bGradient;
	BOOL      		bLaunch;
	BOOL 					bRed, bGrn, bBlu;
	BOOL  				bImageRGB;	
	BOOL 					bImageCMY;
	BOOL  				bImageMIX;
	BOOL      		bImageMBC;
	BOOL      		bImageYGC;

	BOOL      		bCranberry;
	BOOL  				bCaramel;
	BOOL					bInvertPixel;
	
	int						nRGB_Mix;
	char 					szGradient[3];
	int 					red, grn, blu;
	int 					nRed, nGrn, nBlu;
	int  					min, max;
	int  					nRedSave, nGrnSave, nBluSave;
	int       		j, nRGB;
	int						nLevel;
	int       		nCycle;
	int 					temp_max;

// Operations
public:
	CSize GetDocSize() const
		{ return m_sizeDoc; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlarium24Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFlarium24Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CPalette* m_palDIB;

// Generated message map functions
protected:
	//{{AFX_MSG(CFlarium24Doc)
	afx_msg void OnApplicationIdle();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
