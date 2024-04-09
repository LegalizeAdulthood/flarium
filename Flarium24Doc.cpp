// Flarium24Doc.cpp : implementation of the CFlarium24Doc class
//

#include "stdafx.h"
#include "Flarium24.h"
#include "Flarium24Doc.h"
#include <math.h>
#include "external.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFlarium24Doc

IMPLEMENT_DYNCREATE(CFlarium24Doc, CDocument)

BEGIN_MESSAGE_MAP(CFlarium24Doc, CDocument)
	//{{AFX_MSG_MAP(CFlarium24Doc)
	ON_COMMAND(ID_APPLICATION_IDLE, OnApplicationIdle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlarium24Doc construction/destruction

CFlarium24Doc::CFlarium24Doc()
{
	m_sizeDoc = CSize(1,1);     // dummy value to make CScrollView happy
	doc_PathName = "";

  CMainFrame *pMain = (CMainFrame *)AfxGetApp()->m_pMainWnd;

	doc_PathName = "";
	m_sizeDoc = CSize(1,1);     // dummy value to make CScrollView happy
	bPrinting = FALSE;
	nColorIndex = 0;
	r = g = b = 0;
	bInvert = FALSE;
	bNewView = TRUE;
	nMergeMode = 0;
	bMerge = FALSE;

	// Initialize Rubber Banding
	m_tracker.m_rect.SetRectEmpty();	
  m_tracker.m_nStyle = CRectTracker::resizeOutside |
  	CRectTracker::hatchedBorder;

	// Initialize color table variables
	ColorTable = NULL;
	nRed = 2;
	nGrn = 3;
	nBlu = 4;
	nRGB = 0;
	
	nRedSave = red = 0;
	nGrnSave = grn = 0;
	nBluSave = blu = 96;

	bGradient = FALSE;
	min = 0;
	max = 255;

	bImageRGB			= FALSE;	
	bImageCMY			= FALSE;
	bImageMIX			= TRUE;
	nRGB_Mix			= 4;								// default
	strcpy(szGradient, "mix");
	bImageMBC			= FALSE;
	bImageYGC			= FALSE;
	bCranberry		= FALSE;
	bCaramel			= FALSE;
	bInvertPixel	= FALSE;

	Save_MaxColors = 0;
	nLevel = 1;

}

CFlarium24Doc::~CFlarium24Doc()
{

}

BOOL CFlarium24Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	doc_PathName = "";

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CFlarium24Doc diagnostics

#ifdef _DEBUG
void CFlarium24Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFlarium24Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFlarium24Doc commands

void CFlarium24Doc::OnApplicationIdle() 
{
	if (!bPrinting)
		UpdateAllViews(NULL, ID_APPLICATION_IDLE);
}

BOOL CFlarium24Doc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	m_dib.Close();
	
	doc_PathName = lpszPathName;
	SetPathName(lpszPathName);

	if (!m_dib.Open(lpszPathName))
	{
		AfxMessageBox("error opening file: " + doc_PathName);	
		return FALSE;
	}
		
	m_sizeDoc = m_dib.GetSize();	

	return TRUE;
}

BOOL CFlarium24Doc::OnSaveDocument(LPCTSTR lpszPathName) 
{
  doc_PathName = lpszPathName;
	CWaitCursor cursor;	// this will automatically display a wait cursor

	if (!m_dib.Save(doc_PathName))
	{
		AfxMessageBox("Error Saving File");
		return FALSE;
	}

	AfxGetMainWnd()->PostMessage(WM_COMMAND, ID_SAVE_DIB);
	return TRUE;	
}

