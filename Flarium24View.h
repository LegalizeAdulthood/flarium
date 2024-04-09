// Flarium24View.h : interface of the CFlarium24View class
//
/////////////////////////////////////////////////////////////////////////////

#include "cmplx.h"
//#include "Expression.h"

class   		CGradient;
class				CAffine;

class CFlarium24View : public CScrollView
{
protected: // create from serialization only
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	CFlarium24View();
	DECLARE_DYNCREATE(CFlarium24View)

// Attributes
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CFlarium24Doc* GetDocument();

	CGradient* 		m_pGradView;
	CAffine* 			m_pAffineView;

	HGLOBAL				hdots;
	PUSHORT				lpDots;

	char					ctitle[150];
	char					cstr[1024];

	CString				szTemp;
	CString				mClassName;
	//CString       szTempFileName;

  CStdioFile    outFile;

	BOOL					bRedStart, bGrnStart, bBluStart;
	BOOL					bNothingButStrands;

	int 					red, grn, blu;
	int 					nRed, nGrn, nBlu;
	int  					min, max;
	int  					nRedStart, nGrnStart, nBluStart;
	int 					nXpix, nYpix;
	int						nColorMethod;
	int						nImageSize;
	int						i3, k1;
	int						nRedBack, nGrnBack, nBluBack;

	double				CrtScale;
	double				dMIN;
	double				dzx, dzy;	
	double				temp, temp1;

	double				x_temp, y_temp, length;
	double				x_temp1, y_temp1;

	int						xi, yi, ii;
	int						*rIter_Data;
	int						*gIter_Data;
	int						*bIter_Data;
	int						nColorOrder;

	double				x_rmin, x_rmax, y_rmin, y_rmax;
	double				r, rj, gj, bj, rz, rzflag;
	double				temp_x, temp_y;

  // Formulae parser variables 
  double        u_real, v_real, w_real, z_real;
  double        u_imag, v_imag, w_imag, z_imag;
  CString       strFormulae;


	// Data array pointers
	double				*pXTemp;
	double				*pYTemp;
//	int						*nIter_Data;
//	int						*mIter_Data;

	//double				*xData;
	//double				*yData;
	
	double				x_std, y_std, dm, da;

	// Fractal dimension variables
	int						i2;
	cmplx					cx_std;
	cmplx					cy_std;
	cmplx					cFDx;
	cmplx					cFDy;
	cmplx					cRng_x;
	cmplx					cRng_y;
	cmplx					cNMAX;

	double				dFDx;	// Fractal Dimension x
	double				dFDy; // Fractal Dimension y

	double				dFDx_0;	// Initial F Dimension x
	double				dFDy_0; // Initial F Dimension y

	int						nDIter_x;
	int						nDIter_y;
	int						nFDOption;

	// Average variables
	double				x_mean;
	double				y_mean;

	BOOL					bPositiveX, bPositiveY;
	BOOL					bGradient;
	BOOL					bAffine;
	BOOL					bStartup;
	BOOL  				bTracker;
	BOOL					bStretchToFit;
	BOOL					bBDown;
	BOOL					bInvertFractal;
	BOOL					bRandTest;
	BOOL					bQuickMode;
	BOOL					bQuickAbort;
	BOOL					bZeroInit;
	BOOL					bMFilter;
	BOOL					*bRed, *bGrn, *bBlu;
	BOOL					bForward;
	BOOL					b_MAX;
	//BOOL					bColorChange;
	BOOL					bInitialized;
	BOOL					bMSet;
	BOOL					bFSet;
	BOOL					bFDVariate;
	BOOL					bGenesisMode;

	HCURSOR				mHCross;
	HCURSOR				mHSize;
	HCURSOR				mWait;

	BYTE					color;

	DWORD					dwColor;

	UINT					uTimer1;

	int						nSpeed;
	int						rb_avg;
	int						cxDIB;
	int						cyDIB;

	int						rb_width;
	int						rb_height;
	int						rb_center_x;
	int						rb_center_y;
	int						dim_avg;

	CSize					dim, dim_save;
	CSize					size;

	CRect					clientRect;
	CRect					outputRect;
	CRect					DIBRect;

	CPoint				spt;  // Scroll position

	CString				ActiveTitle;

	///////////////////////////////////////////////
	// Latoofarcian variables
	double ma, mb, mc, md, mx, my, mxx, myy;
	
	// Affine mapping variables
	double af[31];
	int nDimension;

  int latoof_count;
  double mx_save, my_save;
  BOOL bXPlus;
	BOOL bYPlus;

	// Lyanpunov variables
	double dLx, dLy, dLz, dL2, mxe, mye, mze, xnew, ynew, znew;
	double df, rs, Lsum, L, x_save, y_save, z_save;
	double dx, dy, dz, d2, d3, xe, ye, ze;

  //  Lorenz variables
  double lx, ly, lz, lxx, lyy, lzz, lh;
	double xinc, yinc, frac;
  int lorenz_count;
  double lx_save, ly_save, lz_save;

	// Ikeda variables
	double c1, c2, c3, rho, xt;
	double sin_temp, cos_temp;

	// Feather variables
	//double w, u;
	int n;

	// ICON variables
	double X, Y, Z, XE, YE, ZE, N, T;
	double NL, XL, XH, YL, YH, ZL, ZH, NS, OF;
	double XNEW, YNEW, ZNEW;

	//Filter variables
	double rr, rr3, tx, ty;
	double limit;
	//double cx_hi;
	//double cx_lo;
	//double cy_hi;
	//double cy_lo;
	double dStrands, dStrands_HI, dStrands_LO;
	//double dFInv;

	////////////////////////////////		
	CSize					screen;
	CRect					rrect;
	CRect					rsave;

	double				dF28;
	double				PrtScale;
	double				fXpix, fYpix;
	CString				szPrtHeader;
	CString				szPrtFooter;
	BOOL 					bPrtParameters_are_set;
	long					lOffCenter;

  BOOL          bInvertPixel;
  BOOL          bBorder;

	double				rx, ry;

	// Constants used for mandelbrot pattern
	// define Mandelbrot set constants:
	double				CIMAX; 				//  1.2
	double				CIMIN; 				// -1.2
	double				CRMAX; 				//  1.0
	double				CRMIN; 				// -2.0

	double				CIMAX_JUL; 		//  1.5
	double				CIMIN_JUL; 		// -1.5
	double				CRMAX_JUL; 		//  1.5
	double				CRMIN_JUL; 		// -1.5

	double  			CIMAX_OLD; 		//  1.2
	double				CIMIN_OLD; 		// -1.2
	double				CRMAX_OLD; 		//  1.0
	double				CRMIN_OLD; 		// -2.0

	double				CRMID;				// rubber band x mid point
	double				CIMID;				// rubber band y mid point
	double				CRMID_Start;	// rubber band x mid point finish
	double				CIMID_Start;	// rubber band y mid point finish
	double				CRMID_Finish;	// rubber band x mid point finish
	double				CIMID_Finish;	// rubber band y mid point finish

	double				CRMID_FrameRatio;
	double				CIMID_FrameRatio;

	double  			CIMAX_NEW; 		//  1.2
	double  			CIMIN_NEW; 		// -1.2
	double  			CRMAX_NEW; 		//  1.0
	double 				CRMIN_NEW; 		// -2.0

	double				CRMID_OLD; 		
	double				CIMID_OLD; 
	double				dMag_new;
	double				dMagnification;
	double				dMagnification_Finish;

	double 				dCloud_top;
	double				dCloud_bottom;
	double				dCloud_left;	
	double				dCloud_right;			

	// Constants used for the inside & outside bay fractal gradients
	double				nBay100, nBay1000;
	BOOL 					b_GT4;

	///////////////////////////////////////////////////////
	// Variables for the Mandelbrot fractal
	BOOL bDraw;
	BOOL bLaunch;
	BOOL bAbort;
  BOOL bGeometry;

  int 					RowMax;
	int 					Row;
 	int 					Col;
  int 					ColMax;
	
	int						auto_row, auto_px, auto_py;
	double				auto_rr, auto_save, auto_save_1;

  double				CR;
  double  			DCI;
  double				DCR;
	int 					NMAX, JMAX, NMAX_Save;
	int 					temp_max;
	int 					Orig_X, Orig_Y;
	int		 				dBailout;
	double				cxx, cyy;
  int  					nDistortion;
	int						nPostFractal;

 	int niter,            /* maximum number of iterations */
    px, py,             /* current pixel */
    nx, ny,             /* number of pixels */
    nc,                 /* number of colors to use */
    i, j,               /* counters for miscellaneous use */
    jul,                /* 1 = Julia Set,  0 = Mandelbrot */
    jul_save;

	double ri;
	double				rx_ratio, ry_ratio;
	double				Radius_x, Radius_y;

	double        x, y,									/* last point on orbit */
								xsquared, ysquared,		/* used to speed up computations */
								ldx, ldy,          		/* theoretical size of pixels */
								cx, cy,           		/* number to add each iteration */
								xO, yO,           		/* starting x,y */
								xI, yI;           		/* ending x,y */

	// Real World Variables
	double				rn, rm;
	int						jrw;
	int						nFilter;
	int						nMatrix;
	int						nFF;
	double				dlz;
	int						ntemp;
	double				dmax;
	double				delta5;
	double				delta10;
	double				dzx_save, dzy_save;
	double				dzx_save_quick, dzy_save_quick;
	BOOL					bFilter_12;
	double				dFilter_12Power;
	double				dFilter_12Magnif;
	double				deg;

	int						dBiomorph;

	double				rorder_r;
	double				rorder_i;

	// Quaternion variables
	double        rmu0, rmu1, rmu2, rmu3;
  double        u,w;
	double				qk1, qk2, qt1, qt2;

	cmplx					c;  
  cmplx					z;
  cmplx         uu;
  cmplx         vv;
  cmplx         ww;
	cmplx					z1;
	cmplx					z2;
	cmplx					cn;
	cmplx					cr;
	cmplx					a;
	cmplx					b;
	cmplx					aa;
	cmplx					aaa2;
	cmplx					aa3;
	cmplx					a2;
	cmplx					t;
	cmplx					t2;
	cmplx					t3;
	cmplx					cOrient;
	cmplx					cPostOrient;
	cmplx					cOrient_save;
	cmplx					cFilter26;

	cmplx					zz,zz2;

	CRect					rubberBand, rubberBandSave;
	
	double				rb_left;
	double				rb_top;
	double				rb_right;
	double				rb_bottom;
		
	double				sxmin;
  double				symin; 
	double				sxmax;
  double				symax; 
	double				x_size;
	double				y_size;
	double 				denominator;

  #include "Expression.h"
  MExpression*  ParsedExpr;

// Operations
public:

	void Window_Pane(int nStat);
	void Status_Bar(char* bar_txt);
  void Clearselection(BOOL bValid);
  void DrawPattern();
  void GeneratePattern();
  void LaunchPattern();
  void TestPattern();
  void TestPatternSub();
  void GoDoFractal();
  void TestEquations();
	void TestEquations_Bio();
  void Equation();
  void Equation1();
	void Equation150();
	void Equation151();
	void Equation152();
	void Equation153();
	void Equation154();
	void Equation155();
  void Terminate();
	void ViewNew();
	void Saveparameters();
	void Loadparameters();
	void Delta_z();
	void Filter_Complete();
	void Apply_The_Color();
	void Shift_Step();
	void Apply_Color();
	void Generalized_Coloring_Method();		
	void Generalized_Coloring_Method1();		
	void Generalized_Coloring_Method2();		
	void Generalized_Coloring_Method3();		
	void Generalized_Coloring_Method4();		
	void Generalized_Coloring_Method5();		
	void Generalized_Coloring_Method6();		
	void Generalized_Coloring_Method7();		
	void Generalized_Coloring_Method8();		
	void Generalized_Coloring_Method9();		
	void Generalized_Coloring_Method10();		
	void Generalized_Coloring_Method11();		
	void Generalized_Coloring_Method12();		
	void Generalized_Coloring_Method13();		
	void Generalized_Coloring_Method14();		
	void Generalized_Coloring_Method15();		
	void Generalized_Coloring_Method16();		
	void Generalized_Coloring_Method17();		
	void Generalized_Coloring_Method18();		
	void Generalized_Coloring_Method19();		
	void Generalized_Coloring_Method20();		
	void Generalized_Coloring_Method21();		
	void Generalized_Coloring_Method22();		
	void Generalized_Coloring_Method23();		
	void Generalized_Coloring_Method24();		
	void Generalized_Coloring_Method25();		
	void Generalized_Coloring_Method26();		
	void Generalized_Coloring_Method27();		
	void Generalized_Coloring_Method28();		
	void Generalized_Coloring_Method29();		
	void Generalized_Coloring_Method30();		
	void Generalized_Coloring_Method31();		
	void Generalized_Coloring_Method32();		
	void Generalized_Coloring_Method33();		
	void Generalized_Coloring_Method34();		
	void Generalized_Coloring_Method35();		
	void Generalized_Coloring_Method36();		
	void Generalized_Coloring_Method37();		
	void Generalized_Coloring_Method38();		
	void Generalized_Coloring_Method39();		

	double x_y_to_degrees(double x, double y);
  void Formulae2();
  void Formulae3();
  void Formulae4();
  void Formulae5();
  void Formulae6();
  void Formulae7();
  void Formulae2_Bio();
  void Formulae3_Bio();
		
	///////////////////////////////////
	// Attractor Functions
  void StandardEquation();
	void PlotDotAt();
	void PlotDotAt_3D();
	void LyanpunovTest();
	void AdvanceXY();
	void Latoocarfian();
	void StandardLatoof();
	void SetParams();
	void SetParams_3D();
	void SubDisplay();
	void SubDisplay_3D();
	void TestSolution();
	void TestSolution_1();
	void GetLyanpunovExponent();
	void TestSolution_3D();
	void GetLyanpunovExponent_3D();
	//void Init_ICON();
	//void IterateEqn();
	//void DisplayICON();
	void OnViewBackground();
	void Complete_the_Dots();
	void Attractor_3D();
	void Affine_Data_Update();
	void FDimension();
	void adjust_coords();

  // Formulae Parser Functions
  //cmplx ParseExpression( const char* str, int& index );
  //cmplx ParseOperand( const char* str, int& index );
  MExpression* ParseExpression( const char* str, int& index );
  MExpression* ParseOperand( const char* str, int& index );
  
	///////////////////////////////////////////////////////////////////
	// Modeless Dialog message routines
	long OnApply_GradView(UINT wParam, LONG lParam);
	long OnApply_ShiftView(UINT wParam, LONG lParam);
	long OnApply_AffineView(UINT wParam, LONG lParam);
  
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlarium24View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFlarium24View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

//	afx_msg void OnSaveDib();

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFlarium24View)
	afx_msg void OnSaveDib();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnImageSize();
	afx_msg void OnWindowSizedesktop();
	afx_msg void OnViewMandel();
	afx_msg void OnUpdateViewMandel(CCmdUI* pCmdUI);
	afx_msg void OnDraw1();
	afx_msg void OnUpdateDraw1(CCmdUI* pCmdUI);
	afx_msg void OnViewZoom();
	afx_msg void OnUpdateViewZoom(CCmdUI* pCmdUI);
	afx_msg void OnViewNew();
	afx_msg void OnFileLoadparameters();
	afx_msg void OnFileSaveparameters();
	afx_msg void OnEditUndofractalselection();
	afx_msg void OnImageParams();
	afx_msg void OnDrawAbort();
	afx_msg void OnDrawInvert();
	afx_msg void OnUpdateDrawInvert(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewNew(CCmdUI* pCmdUI);
	afx_msg void OnFilter1();
	afx_msg void OnUpdateFilter1(CCmdUI* pCmdUI);
	afx_msg void OnFilter0none();
	afx_msg void OnUpdateFilter0none(CCmdUI* pCmdUI);
	afx_msg void OnFilter2();
	afx_msg void OnUpdateFilter2(CCmdUI* pCmdUI);
	afx_msg void OnFilter3();
	afx_msg void OnUpdateFilter3(CCmdUI* pCmdUI);
	afx_msg void OnFilter4();
	afx_msg void OnUpdateFilter4(CCmdUI* pCmdUI);
	afx_msg void OnFilter5();
	afx_msg void OnUpdateFilter5(CCmdUI* pCmdUI);
	afx_msg void OnFilter6();
	afx_msg void OnUpdateFilter6(CCmdUI* pCmdUI);
	afx_msg void OnDraw0();
	afx_msg void OnUpdateDraw0(CCmdUI* pCmdUI);
	afx_msg void OnDraw2();
	afx_msg void OnUpdateDraw2(CCmdUI* pCmdUI);
	afx_msg void OnDraw3();
	afx_msg void OnUpdateDraw3(CCmdUI* pCmdUI);
	afx_msg void OnDraw4();
	afx_msg void OnUpdateDraw4(CCmdUI* pCmdUI);
	afx_msg void OnDraw5();
	afx_msg void OnUpdateDraw5(CCmdUI* pCmdUI);
	afx_msg void OnDraw6();
	afx_msg void OnUpdateDraw6(CCmdUI* pCmdUI);
	afx_msg void OnDraw7();
	afx_msg void OnUpdateDraw7(CCmdUI* pCmdUI);
	afx_msg void OnDraw8();
	afx_msg void OnUpdateDraw8(CCmdUI* pCmdUI);
	afx_msg void OnDraw9();
	afx_msg void OnUpdateDraw9(CCmdUI* pCmdUI);
	afx_msg void OnDraw10();
	afx_msg void OnUpdateDraw10(CCmdUI* pCmdUI);
	afx_msg void OnImageColorparameters();
	afx_msg void OnUpdateImageColorparameters(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawAbort(CCmdUI* pCmdUI);
	afx_msg void OnDrawOrientation();
	afx_msg void OnViewJulia1();
	afx_msg void OnUpdateViewJulia1(CCmdUI* pCmdUI);
	afx_msg void OnDrawZeroinit();
	afx_msg void OnUpdateDrawZeroinit(CCmdUI* pCmdUI);
	afx_msg void OnDraw11();
	afx_msg void OnUpdateDraw11(CCmdUI* pCmdUI);
	afx_msg void OnDraw12();
	afx_msg void OnUpdateDraw12(CCmdUI* pCmdUI);
	afx_msg void OnDraw13();
	afx_msg void OnUpdateDraw13(CCmdUI* pCmdUI);
	afx_msg void OnDraw14();
	afx_msg void OnUpdateDraw14(CCmdUI* pCmdUI);
	afx_msg void OnDraw15();
	afx_msg void OnUpdateDraw15(CCmdUI* pCmdUI);
	afx_msg void OnDraw16();
	afx_msg void OnUpdateDraw16(CCmdUI* pCmdUI);
	afx_msg void OnDraw17();
	afx_msg void OnUpdateDraw17(CCmdUI* pCmdUI);
	afx_msg void OnDraw18();
	afx_msg void OnUpdateDraw18(CCmdUI* pCmdUI);
	afx_msg void OnDraw19();
	afx_msg void OnUpdateDraw19(CCmdUI* pCmdUI);
	afx_msg void OnDraw20();
	afx_msg void OnUpdateDraw20(CCmdUI* pCmdUI);
	afx_msg void OnDraw21();
	afx_msg void OnUpdateDraw21(CCmdUI* pCmdUI);
	afx_msg void OnDraw22();
	afx_msg void OnUpdateDraw22(CCmdUI* pCmdUI);
	afx_msg void OnDraw23();
	afx_msg void OnUpdateDraw23(CCmdUI* pCmdUI);
	afx_msg void OnDraw24();
	afx_msg void OnUpdateDraw24(CCmdUI* pCmdUI);
	afx_msg void OnDraw25();
	afx_msg void OnUpdateDraw25(CCmdUI* pCmdUI);
	afx_msg void OnDraw26();
	afx_msg void OnUpdateDraw26(CCmdUI* pCmdUI);
	afx_msg void OnDraw27();
	afx_msg void OnUpdateDraw27(CCmdUI* pCmdUI);
	afx_msg void OnFractalBiomorphnone();
	afx_msg void OnUpdateFractalBiomorphnone(CCmdUI* pCmdUI);
	afx_msg void OnFractal1biomorphxory();
	afx_msg void OnUpdateFractal1biomorphxory(CCmdUI* pCmdUI);
	afx_msg void OnFractalBiomorph();
	afx_msg void OnUpdateFractalBiomorph(CCmdUI* pCmdUI);
	afx_msg void OnFractalBiomorphtestxory();
	afx_msg void OnUpdateFractalBiomorphtestxory(CCmdUI* pCmdUI);
	afx_msg void OnFilter7();
	afx_msg void OnUpdateFilter7(CCmdUI* pCmdUI);
	afx_msg void OnFilter8();
	afx_msg void OnUpdateFilter8(CCmdUI* pCmdUI);
	afx_msg void OnFilter9();
	afx_msg void OnUpdateFilter9(CCmdUI* pCmdUI);
	afx_msg void OnFilter10();
	afx_msg void OnUpdateFilter10(CCmdUI* pCmdUI);
	afx_msg void OnFilter11();
	afx_msg void OnUpdateFilter11(CCmdUI* pCmdUI);
	afx_msg void OnFilter12();
	afx_msg void OnUpdateFilter12(CCmdUI* pCmdUI);
	afx_msg void OnColour0();
	afx_msg void OnUpdateColour0(CCmdUI* pCmdUI);
	afx_msg void OnColour1();
	afx_msg void OnUpdateColour1(CCmdUI* pCmdUI);
	afx_msg void OnColour2();
	afx_msg void OnUpdateColour2(CCmdUI* pCmdUI);
	afx_msg void OnColour3();
	afx_msg void OnUpdateColour3(CCmdUI* pCmdUI);
	afx_msg void OnColour4();
	afx_msg void OnUpdateColour4(CCmdUI* pCmdUI);
	afx_msg void OnColour5();
	afx_msg void OnUpdateColour5(CCmdUI* pCmdUI);
	afx_msg void OnColour6();
	afx_msg void OnUpdateColour6(CCmdUI* pCmdUI);
	afx_msg void OnColour7();
	afx_msg void OnUpdateColour7(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnShiftStart();
	afx_msg void OnUpdateShiftStart(CCmdUI* pCmdUI);
	afx_msg void OnDraw28();
	afx_msg void OnUpdateDraw28(CCmdUI* pCmdUI);
	afx_msg void OnDraw29();
	afx_msg void OnUpdateDraw29(CCmdUI* pCmdUI);
	afx_msg void OnDraw30();
	afx_msg void OnUpdateDraw30(CCmdUI* pCmdUI);
	afx_msg void OnDraw31();
	afx_msg void OnUpdateDraw31(CCmdUI* pCmdUI);
	afx_msg void OnDraw32();
	afx_msg void OnUpdateDraw32(CCmdUI* pCmdUI);
	afx_msg void OnDraw33();
	afx_msg void OnUpdateDraw33(CCmdUI* pCmdUI);
	afx_msg void OnDraw34();
	afx_msg void OnUpdateDraw34(CCmdUI* pCmdUI);
	afx_msg void OnDraw35();
	afx_msg void OnUpdateDraw35(CCmdUI* pCmdUI);
	afx_msg void OnDraw36();
	afx_msg void OnUpdateDraw36(CCmdUI* pCmdUI);
	afx_msg void OnDraw37();
	afx_msg void OnUpdateDraw37(CCmdUI* pCmdUI);
	afx_msg void OnDraw38();
	afx_msg void OnUpdateDraw38(CCmdUI* pCmdUI);
	afx_msg void OnDraw39();
	afx_msg void OnUpdateDraw39(CCmdUI* pCmdUI);
	afx_msg void OnDraw40();
	afx_msg void OnUpdateDraw40(CCmdUI* pCmdUI);
	afx_msg void OnDraw41();
	afx_msg void OnUpdateDraw41(CCmdUI* pCmdUI);
	afx_msg void OnDraw42();
	afx_msg void OnUpdateDraw42(CCmdUI* pCmdUI);
	afx_msg void OnDraw43();
	afx_msg void OnUpdateDraw43(CCmdUI* pCmdUI);
	afx_msg void OnDraw44();
	afx_msg void OnUpdateDraw44(CCmdUI* pCmdUI);
	afx_msg void OnDraw45();
	afx_msg void OnUpdateDraw45(CCmdUI* pCmdUI);
	afx_msg void OnDraw46();
	afx_msg void OnUpdateDraw46(CCmdUI* pCmdUI);
	afx_msg void OnDraw47();
	afx_msg void OnUpdateDraw47(CCmdUI* pCmdUI);
	afx_msg void OnDraw48();
	afx_msg void OnUpdateDraw48(CCmdUI* pCmdUI);
	afx_msg void OnDraw49();
	afx_msg void OnUpdateDraw49(CCmdUI* pCmdUI);
	afx_msg void OnDraw50();
	afx_msg void OnUpdateDraw50(CCmdUI* pCmdUI);
	afx_msg void OnFilter13();
	afx_msg void OnUpdateFilter13(CCmdUI* pCmdUI);
	afx_msg void OnFilter14();
	afx_msg void OnUpdateFilter14(CCmdUI* pCmdUI);
	afx_msg void OnFilter15();
	afx_msg void OnUpdateFilter15(CCmdUI* pCmdUI);
	afx_msg void OnFilter16();
	afx_msg void OnFilter17();
	afx_msg void OnUpdateFilter17(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilter16(CCmdUI* pCmdUI);
	afx_msg void OnFilter18();
	afx_msg void OnUpdateFilter18(CCmdUI* pCmdUI);
	afx_msg void OnFilter30();
	afx_msg void OnUpdateFilter30(CCmdUI* pCmdUI);
	afx_msg void OnFilter31();
	afx_msg void OnUpdateFilter31(CCmdUI* pCmdUI);
	afx_msg void OnFilter32();
	afx_msg void OnUpdateFilter32(CCmdUI* pCmdUI);
	afx_msg void OnFilter33();
	afx_msg void OnUpdateFilter33(CCmdUI* pCmdUI);
	afx_msg void OnFilter34();
	afx_msg void OnUpdateFilter34(CCmdUI* pCmdUI);
	afx_msg void OnFilter35();
	afx_msg void OnUpdateFilter35(CCmdUI* pCmdUI);
	afx_msg void OnFilter36();
	afx_msg void OnUpdateFilter36(CCmdUI* pCmdUI);
	afx_msg void OnFilter37();
	afx_msg void OnUpdateFilter37(CCmdUI* pCmdUI);
	afx_msg void OnFilter38();
	afx_msg void OnUpdateFilter38(CCmdUI* pCmdUI);
	afx_msg void OnFilter39();
	afx_msg void OnUpdateFilter39(CCmdUI* pCmdUI);
	afx_msg void OnFilter40();
	afx_msg void OnUpdateFilter40(CCmdUI* pCmdUI);
	afx_msg void OnFilter41();
	afx_msg void OnUpdateFilter41(CCmdUI* pCmdUI);
	afx_msg void OnFilter42();
	afx_msg void OnUpdateFilter42(CCmdUI* pCmdUI);
	afx_msg void OnFilter43();
	afx_msg void OnUpdateFilter43(CCmdUI* pCmdUI);
	afx_msg void OnFilter44();
	afx_msg void OnUpdateFilter44(CCmdUI* pCmdUI);
	afx_msg void OnFilter45();
	afx_msg void OnUpdateFilter45(CCmdUI* pCmdUI);
	afx_msg void OnFilter46();
	afx_msg void OnUpdateFilter46(CCmdUI* pCmdUI);
	afx_msg void OnFilter47();
	afx_msg void OnUpdateFilter47(CCmdUI* pCmdUI);
	afx_msg void OnFilter48();
	afx_msg void OnUpdateFilter48(CCmdUI* pCmdUI);
	afx_msg void OnFilter49();
	afx_msg void OnUpdateFilter49(CCmdUI* pCmdUI);
	afx_msg void OnFilter50();
	afx_msg void OnUpdateFilter50(CCmdUI* pCmdUI);
	afx_msg void OnFilter51();
	afx_msg void OnUpdateFilter51(CCmdUI* pCmdUI);
	afx_msg void OnFilter52();
	afx_msg void OnUpdateFilter52(CCmdUI* pCmdUI);
	afx_msg void OnFilter53();
	afx_msg void OnUpdateFilter53(CCmdUI* pCmdUI);
	afx_msg void OnDraw51();
	afx_msg void OnUpdateDraw51(CCmdUI* pCmdUI);
	afx_msg void OnDraw52();
	afx_msg void OnUpdateDraw52(CCmdUI* pCmdUI);
	afx_msg void OnDraw53();
	afx_msg void OnUpdateDraw53(CCmdUI* pCmdUI);
	afx_msg void OnDraw54();
	afx_msg void OnUpdateDraw54(CCmdUI* pCmdUI);
	afx_msg void OnDraw55();
	afx_msg void OnUpdateDraw55(CCmdUI* pCmdUI);
	afx_msg void OnDraw56();
	afx_msg void OnUpdateDraw56(CCmdUI* pCmdUI);
	afx_msg void OnDraw57();
	afx_msg void OnUpdateDraw57(CCmdUI* pCmdUI);
	afx_msg void OnDraw58();
	afx_msg void OnUpdateDraw58(CCmdUI* pCmdUI);
	afx_msg void OnDraw59();
	afx_msg void OnUpdateDraw59(CCmdUI* pCmdUI);
	afx_msg void OnDraw60();
	afx_msg void OnUpdateDraw60(CCmdUI* pCmdUI);
	afx_msg void OnOptions1();
	afx_msg void OnUpdateOptions1(CCmdUI* pCmdUI);
	afx_msg void OnOptions10();
	afx_msg void OnUpdateOptions10(CCmdUI* pCmdUI);
	afx_msg void OnOptions2();
	afx_msg void OnUpdateOptions2(CCmdUI* pCmdUI);
	afx_msg void OnOptions3();
	afx_msg void OnUpdateOptions3(CCmdUI* pCmdUI);
	afx_msg void OnOptions4();
	afx_msg void OnUpdateOptions4(CCmdUI* pCmdUI);
	afx_msg void OnOptions5();
	afx_msg void OnUpdateOptions5(CCmdUI* pCmdUI);
	afx_msg void OnOptions6();
	afx_msg void OnUpdateOptions6(CCmdUI* pCmdUI);
	afx_msg void OnOptions7();
	afx_msg void OnUpdateOptions7(CCmdUI* pCmdUI);
	afx_msg void OnOptions8();
	afx_msg void OnUpdateOptions8(CCmdUI* pCmdUI);
	afx_msg void OnOptions9();
	afx_msg void OnUpdateOptions9(CCmdUI* pCmdUI);
	afx_msg void OnDraw61();
	afx_msg void OnUpdateDraw61(CCmdUI* pCmdUI);
	afx_msg void OnDraw62();
	afx_msg void OnUpdateDraw62(CCmdUI* pCmdUI);
	afx_msg void OnDraw63();
	afx_msg void OnUpdateDraw63(CCmdUI* pCmdUI);
	afx_msg void OnDraw64();
	afx_msg void OnUpdateDraw64(CCmdUI* pCmdUI);
	afx_msg void OnColour8();
	afx_msg void OnUpdateColour8(CCmdUI* pCmdUI);
	afx_msg void OnColour9();
	afx_msg void OnUpdateColour9(CCmdUI* pCmdUI);
	afx_msg void OnColour10();
	afx_msg void OnUpdateColour10(CCmdUI* pCmdUI);
	afx_msg void OnColour11();
	afx_msg void OnUpdateColour11(CCmdUI* pCmdUI);
	afx_msg void OnColour12();
	afx_msg void OnUpdateColour12(CCmdUI* pCmdUI);
	afx_msg void OnFilter54();
	afx_msg void OnUpdateFilter54(CCmdUI* pCmdUI);
	afx_msg void OnFilter55();
	afx_msg void OnUpdateFilter55(CCmdUI* pCmdUI);
	afx_msg void OnFilter56();
	afx_msg void OnUpdateFilter56(CCmdUI* pCmdUI);
	afx_msg void OnColour13();
	afx_msg void OnUpdateColour13(CCmdUI* pCmdUI);
	afx_msg void OnColour14();
	afx_msg void OnUpdateColour14(CCmdUI* pCmdUI);
	afx_msg void OnDraw65();
	afx_msg void OnUpdateDraw65(CCmdUI* pCmdUI);
	afx_msg void OnDraw66();
	afx_msg void OnUpdateDraw66(CCmdUI* pCmdUI);
	afx_msg void OnDraw67();
	afx_msg void OnUpdateDraw67(CCmdUI* pCmdUI);
	afx_msg void OnDraw68();
	afx_msg void OnUpdateDraw68(CCmdUI* pCmdUI);
	afx_msg void OnDraw69();
	afx_msg void OnUpdateDraw69(CCmdUI* pCmdUI);
	afx_msg void OnDraw70();
	afx_msg void OnUpdateDraw70(CCmdUI* pCmdUI);
	afx_msg void OnDraw71();
	afx_msg void OnUpdateDraw71(CCmdUI* pCmdUI);
	afx_msg void OnDraw72();
	afx_msg void OnUpdateDraw72(CCmdUI* pCmdUI);
	afx_msg void OnDraw73();
	afx_msg void OnUpdateDraw73(CCmdUI* pCmdUI);
	afx_msg void OnDraw74();
	afx_msg void OnUpdateDraw74(CCmdUI* pCmdUI);
	afx_msg void OnDraw75();
	afx_msg void OnUpdateDraw75(CCmdUI* pCmdUI);
	afx_msg void OnDraw76();
	afx_msg void OnUpdateDraw76(CCmdUI* pCmdUI);
	afx_msg void OnDraw77();
	afx_msg void OnUpdateDraw77(CCmdUI* pCmdUI);
	afx_msg void OnDraw78();
	afx_msg void OnUpdateDraw78(CCmdUI* pCmdUI);
	afx_msg void OnDraw79();
	afx_msg void OnUpdateDraw79(CCmdUI* pCmdUI);
	afx_msg void OnDraw80();
	afx_msg void OnUpdateDraw80(CCmdUI* pCmdUI);
	afx_msg void OnDraw81();
	afx_msg void OnUpdateDraw81(CCmdUI* pCmdUI);
	afx_msg void OnDraw82();
	afx_msg void OnUpdateDraw82(CCmdUI* pCmdUI);
	afx_msg void OnDraw83();
	afx_msg void OnUpdateDraw83(CCmdUI* pCmdUI);
	afx_msg void OnDraw84();
	afx_msg void OnUpdateDraw84(CCmdUI* pCmdUI);
	afx_msg void OnDraw85();
	afx_msg void OnUpdateDraw85(CCmdUI* pCmdUI);
	afx_msg void OnDraw86();
	afx_msg void OnUpdateDraw86(CCmdUI* pCmdUI);
	afx_msg void OnDraw87();
	afx_msg void OnUpdateDraw87(CCmdUI* pCmdUI);
	afx_msg void OnDraw88();
	afx_msg void OnUpdateDraw88(CCmdUI* pCmdUI);
	afx_msg void OnDraw89();
	afx_msg void OnUpdateDraw89(CCmdUI* pCmdUI);
	afx_msg void OnDraw90();
	afx_msg void OnUpdateDraw90(CCmdUI* pCmdUI);
	afx_msg void OnDraw91();
	afx_msg void OnUpdateDraw91(CCmdUI* pCmdUI);
	afx_msg void OnDraw92();
	afx_msg void OnUpdateDraw92(CCmdUI* pCmdUI);
	afx_msg void OnDraw93();
	afx_msg void OnUpdateDraw93(CCmdUI* pCmdUI);
	afx_msg void OnDrawMsetmethod();
	afx_msg void OnUpdateDrawMsetmethod(CCmdUI* pCmdUI);
	afx_msg void OnFileLoadcolors();
	afx_msg void OnFileSavecolors();
	afx_msg void OnDraw94();
	afx_msg void OnUpdateDraw94(CCmdUI* pCmdUI);
	afx_msg void OnDraw95();
	afx_msg void OnUpdateDraw95(CCmdUI* pCmdUI);
	afx_msg void OnDraw96();
	afx_msg void OnUpdateDraw96(CCmdUI* pCmdUI);
	afx_msg void OnDraw97();
	afx_msg void OnUpdateDraw97(CCmdUI* pCmdUI);
	afx_msg void OnDraw98();
	afx_msg void OnUpdateDraw98(CCmdUI* pCmdUI);
	afx_msg void OnDraw99();
	afx_msg void OnUpdateDraw99(CCmdUI* pCmdUI);
	afx_msg void OnDraw100();
	afx_msg void OnUpdateDraw100(CCmdUI* pCmdUI);
	afx_msg void OnDraw101();
	afx_msg void OnUpdateDraw101(CCmdUI* pCmdUI);
	afx_msg void OnDraw102();
	afx_msg void OnUpdateDraw102(CCmdUI* pCmdUI);
	afx_msg void OnDraw103();
	afx_msg void OnUpdateDraw103(CCmdUI* pCmdUI);
	afx_msg void OnDraw104();
	afx_msg void OnUpdateDraw104(CCmdUI* pCmdUI);
	afx_msg void OnDraw105();
	afx_msg void OnUpdateDraw105(CCmdUI* pCmdUI);
	afx_msg void OnDraw106();
	afx_msg void OnUpdateDraw106(CCmdUI* pCmdUI);
	afx_msg void OnDraw107();
	afx_msg void OnUpdateDraw107(CCmdUI* pCmdUI);
	afx_msg void OnDraw108();
	afx_msg void OnUpdateDraw108(CCmdUI* pCmdUI);
	afx_msg void OnDraw109();
	afx_msg void OnUpdateDraw109(CCmdUI* pCmdUI);
	afx_msg void OnDraw110();
	afx_msg void OnUpdateDraw110(CCmdUI* pCmdUI);
	afx_msg void OnFilter357();
	afx_msg void OnUpdateFilter357(CCmdUI* pCmdUI);
	afx_msg void OnFilter358();
	afx_msg void OnUpdateFilter358(CCmdUI* pCmdUI);
	afx_msg void OnFilter359();
	afx_msg void OnUpdateFilter359(CCmdUI* pCmdUI);
	afx_msg void OnFilter360();
	afx_msg void OnUpdateFilter360(CCmdUI* pCmdUI);
	afx_msg void OnFilter61();
	afx_msg void OnUpdateFilter61(CCmdUI* pCmdUI);
	afx_msg void OnFilter62();
	afx_msg void OnUpdateFilter62(CCmdUI* pCmdUI);
	afx_msg void OnFilter63();
	afx_msg void OnUpdateFilter63(CCmdUI* pCmdUI);
	afx_msg void OnFilter64();
	afx_msg void OnUpdateFilter64(CCmdUI* pCmdUI);
	afx_msg void OnFilter65();
	afx_msg void OnUpdateFilter65(CCmdUI* pCmdUI);
	afx_msg void OnFilter66();
	afx_msg void OnUpdateFilter66(CCmdUI* pCmdUI);
	afx_msg void OnFilter67();
	afx_msg void OnUpdateFilter67(CCmdUI* pCmdUI);
	afx_msg void OnFilter68();
	afx_msg void OnUpdateFilter68(CCmdUI* pCmdUI);
	afx_msg void OnDraw111();
	afx_msg void OnUpdateDraw111(CCmdUI* pCmdUI);
	afx_msg void OnFilePrintscaling();
	afx_msg void OnColour15();
	afx_msg void OnUpdateColour15(CCmdUI* pCmdUI);
	afx_msg void OnColour16();
	afx_msg void OnUpdateColour16(CCmdUI* pCmdUI);
	afx_msg void OnColour17();
	afx_msg void OnUpdateColour17(CCmdUI* pCmdUI);
	afx_msg void OnColour18();
	afx_msg void OnUpdateColour18(CCmdUI* pCmdUI);
	afx_msg void OnDraw112();
	afx_msg void OnUpdateDraw112(CCmdUI* pCmdUI);
	afx_msg void OnDraw113();
	afx_msg void OnUpdateDraw113(CCmdUI* pCmdUI);
	afx_msg void OnDraw114();
	afx_msg void OnUpdateDraw114(CCmdUI* pCmdUI);
	afx_msg void OnDraw115();
	afx_msg void OnUpdateDraw115(CCmdUI* pCmdUI);
	afx_msg void OnDraw116();
	afx_msg void OnUpdateDraw116(CCmdUI* pCmdUI);
	afx_msg void OnDrawBiomorph4();
	afx_msg void OnUpdateDrawBiomorph4(CCmdUI* pCmdUI);
	afx_msg void OnDrawBiomorph5();
	afx_msg void OnUpdateDrawBiomorph5(CCmdUI* pCmdUI);
	afx_msg void OnDrawBiomorph6();
	afx_msg void OnUpdateDrawBiomorph6(CCmdUI* pCmdUI);
	afx_msg void OnDrawFset();
	afx_msg void OnUpdateDrawFset(CCmdUI* pCmdUI);
	afx_msg void OnColour19();
	afx_msg void OnUpdateColour19(CCmdUI* pCmdUI);
	afx_msg void OnColour20();
	afx_msg void OnUpdateColour20(CCmdUI* pCmdUI);
	afx_msg void OnColour21();
	afx_msg void OnUpdateColour21(CCmdUI* pCmdUI);
	afx_msg void OnColour22();
	afx_msg void OnUpdateColour22(CCmdUI* pCmdUI);
	afx_msg void OnViewStretchtofit();
	afx_msg void OnUpdateViewStretchtofit(CCmdUI* pCmdUI);
	afx_msg void OnFilter69();
	afx_msg void OnUpdateFilter69(CCmdUI* pCmdUI);
	afx_msg void OnDraw120();
	afx_msg void OnUpdateDraw120(CCmdUI* pCmdUI);
	afx_msg void OnDraw121();
	afx_msg void OnUpdateDraw121(CCmdUI* pCmdUI);
	afx_msg void OnDraw122();
	afx_msg void OnUpdateDraw122(CCmdUI* pCmdUI);
	afx_msg void OnDraw123();
	afx_msg void OnUpdateDraw123(CCmdUI* pCmdUI);
	afx_msg void OnDrawLatoofdlg();
	afx_msg void OnDrawAffinetransformation();
	afx_msg void OnDrawRepeat();
	afx_msg void OnImageBackgroundcolor();
	afx_msg void OnDraw117();
	afx_msg void OnUpdateDraw117(CCmdUI* pCmdUI);
	afx_msg void OnDraw124();
	afx_msg void OnUpdateDraw124(CCmdUI* pCmdUI);
	afx_msg void OnDraw118();
	afx_msg void OnUpdateDraw118(CCmdUI* pCmdUI);
	afx_msg void OnDraw119();
	afx_msg void OnUpdateDraw119(CCmdUI* pCmdUI);
	afx_msg void OnDraw125();
	afx_msg void OnUpdateDraw125(CCmdUI* pCmdUI);
	afx_msg void OnDraw126();
	afx_msg void OnUpdateDraw126(CCmdUI* pCmdUI);
	afx_msg void OnDraw127();
	afx_msg void OnUpdateDraw127(CCmdUI* pCmdUI);
	afx_msg void OnDraw128();
	afx_msg void OnUpdateDraw128(CCmdUI* pCmdUI);
	afx_msg void OnDraw129();
	afx_msg void OnUpdateDraw129(CCmdUI* pCmdUI);
	afx_msg void OnDraw130();
	afx_msg void OnUpdateDraw130(CCmdUI* pCmdUI);
	afx_msg void OnDraw131();
	afx_msg void OnUpdateDraw131(CCmdUI* pCmdUI);
	afx_msg void OnAttractorsXy();
	afx_msg void OnUpdateAttractorsXy(CCmdUI* pCmdUI);
	afx_msg void OnAttractorsXz();
	afx_msg void OnUpdateAttractorsXz(CCmdUI* pCmdUI);
	afx_msg void OnAttractorsYz();
	afx_msg void OnUpdateAttractorsYz(CCmdUI* pCmdUI);
	afx_msg void OnDraw133();
	afx_msg void OnUpdateDraw133(CCmdUI* pCmdUI);
	afx_msg void OnDraw134();
	afx_msg void OnUpdateDraw134(CCmdUI* pCmdUI);
	afx_msg void OnDraw135();
	afx_msg void OnUpdateDraw135(CCmdUI* pCmdUI);
	afx_msg void OnDraw136();
	afx_msg void OnUpdateDraw136(CCmdUI* pCmdUI);
	afx_msg void OnDraw137();
	afx_msg void OnUpdateDraw137(CCmdUI* pCmdUI);
	afx_msg void OnDraw138();
	afx_msg void OnUpdateDraw138(CCmdUI* pCmdUI);
	afx_msg void OnDrawQuaternionparameters();
	afx_msg void OnUpdateDrawAffinetransformation(CCmdUI* pCmdUI);
	afx_msg void OnDrawUnique();
	afx_msg void OnDraw140();
	afx_msg void OnUpdateDraw140(CCmdUI* pCmdUI);
	afx_msg void OnFilter70();
	afx_msg void OnUpdateFilter70(CCmdUI* pCmdUI);
	afx_msg void OnFilter71();
	afx_msg void OnUpdateFilter71(CCmdUI* pCmdUI);
	afx_msg void OnImageClear();
	afx_msg void OnDraw141();
	afx_msg void OnUpdateDraw141(CCmdUI* pCmdUI);
	afx_msg void OnDraw142();
	afx_msg void OnUpdateDraw142(CCmdUI* pCmdUI);
	afx_msg void OnDraw143();
	afx_msg void OnUpdateDraw143(CCmdUI* pCmdUI);
	afx_msg void OnDraw144();
	afx_msg void OnUpdateDraw144(CCmdUI* pCmdUI);
	afx_msg void OnDraw145();
	afx_msg void OnUpdateDraw145(CCmdUI* pCmdUI);
	afx_msg void OnFdimensionVariatei();
	afx_msg void OnUpdateFdimensionVariatei(CCmdUI* pCmdUI);
	afx_msg void OnImageAspectratio();
	afx_msg void OnUpdateImageAspectratio(CCmdUI* pCmdUI);
	afx_msg void OnFilter3Nothingbutstrands();
	afx_msg void OnUpdateFilter3Nothingbutstrands(CCmdUI* pCmdUI);
	afx_msg void OnDraw146();
	afx_msg void OnUpdateDraw146(CCmdUI* pCmdUI);
	afx_msg void OnColour23();
	afx_msg void OnUpdateColour23(CCmdUI* pCmdUI);
	afx_msg void OnColour24();
	afx_msg void OnUpdateColour24(CCmdUI* pCmdUI);
	afx_msg void OnColour25();
	afx_msg void OnUpdateColour25(CCmdUI* pCmdUI);
	afx_msg void OnColour26();
	afx_msg void OnUpdateColour26(CCmdUI* pCmdUI);
	afx_msg void OnColour27();
	afx_msg void OnUpdateColour27(CCmdUI* pCmdUI);
	afx_msg void OnColour28();
	afx_msg void OnUpdateColour28(CCmdUI* pCmdUI);
	afx_msg void OnColour29();
	afx_msg void OnUpdateColour29(CCmdUI* pCmdUI);
	afx_msg void OnColour30();
	afx_msg void OnUpdateColour30(CCmdUI* pCmdUI);
	afx_msg void OnColour31();
	afx_msg void OnUpdateColour31(CCmdUI* pCmdUI);
	afx_msg void OnColour32();
	afx_msg void OnUpdateColour32(CCmdUI* pCmdUI);
	afx_msg void OnColour33();
	afx_msg void OnUpdateColour33(CCmdUI* pCmdUI);
	afx_msg void OnFilter72();
	afx_msg void OnUpdateFilter72(CCmdUI* pCmdUI);
	afx_msg void OnColour34();
	afx_msg void OnUpdateColour34(CCmdUI* pCmdUI);
	afx_msg void OnColour35();
	afx_msg void OnUpdateColour35(CCmdUI* pCmdUI);
	afx_msg void OnColour36();
	afx_msg void OnUpdateColour36(CCmdUI* pCmdUI);
	afx_msg void OnColour37();
	afx_msg void OnUpdateColour37(CCmdUI* pCmdUI);
	afx_msg void OnFilter73();
	afx_msg void OnUpdateFilter73(CCmdUI* pCmdUI);
	afx_msg void OnFilter74();
	afx_msg void OnUpdateFilter74(CCmdUI* pCmdUI);
	afx_msg void OnColour38();
	afx_msg void OnUpdateColour38(CCmdUI* pCmdUI);
	afx_msg void OnColour39();
	afx_msg void OnUpdateColour39(CCmdUI* pCmdUI);
	afx_msg void OnFilter75();
	afx_msg void OnUpdateFilter75(CCmdUI* pCmdUI);
	afx_msg void OnFilter76();
	afx_msg void OnUpdateFilter76(CCmdUI* pCmdUI);
	afx_msg void OnDraw150();
	afx_msg void OnUpdateDraw150(CCmdUI* pCmdUI);
	afx_msg void OnDraw151();
	afx_msg void OnUpdateDraw151(CCmdUI* pCmdUI);
	afx_msg void OnDraw152();
	afx_msg void OnUpdateDraw152(CCmdUI* pCmdUI);
	afx_msg void OnDraw153();
	afx_msg void OnUpdateDraw153(CCmdUI* pCmdUI);
	afx_msg void OnDraw154();
	afx_msg void OnUpdateDraw154(CCmdUI* pCmdUI);
	afx_msg void OnDraw155();
	afx_msg void OnUpdateDraw155(CCmdUI* pCmdUI);
	afx_msg void OnFilter77();
	afx_msg void OnUpdateFilter77(CCmdUI* pCmdUI);
	afx_msg void OnFilter78();
	afx_msg void OnUpdateFilter78(CCmdUI* pCmdUI);
	afx_msg void OnFilter79();
	afx_msg void OnUpdateFilter79(CCmdUI* pCmdUI);
	afx_msg void OnFilter80();
	afx_msg void OnUpdateFilter80(CCmdUI* pCmdUI);
	afx_msg void OnFilter81();
	afx_msg void OnUpdateFilter81(CCmdUI* pCmdUI);
	afx_msg void OnFilter82();
	afx_msg void OnUpdateFilter82(CCmdUI* pCmdUI);
	afx_msg void OnFilter83();
	afx_msg void OnUpdateFilter83(CCmdUI* pCmdUI);
	afx_msg void OnFilter84();
	afx_msg void OnUpdateFilter84(CCmdUI* pCmdUI);
	afx_msg void OnFilter85();
	afx_msg void OnUpdateFilter85(CCmdUI* pCmdUI);
	afx_msg void OnFilter86();
	afx_msg void OnUpdateFilter86(CCmdUI* pCmdUI);
	afx_msg void OnFilter87();
	afx_msg void OnUpdateFilter87(CCmdUI* pCmdUI);
	afx_msg void OnFilter88();
	afx_msg void OnUpdateFilter88(CCmdUI* pCmdUI);
	afx_msg void OnFilter89();
	afx_msg void OnUpdateFilter89(CCmdUI* pCmdUI);
	afx_msg void OnFilter90();
	afx_msg void OnUpdateFilter90(CCmdUI* pCmdUI);
	afx_msg void OnFilter91();
	afx_msg void OnUpdateFilter91(CCmdUI* pCmdUI);
	afx_msg void OnFilter92();
	afx_msg void OnUpdateFilter92(CCmdUI* pCmdUI);
	afx_msg void OnFilter93();
	afx_msg void OnUpdateFilter93(CCmdUI* pCmdUI);
	afx_msg void OnFilter94();
	afx_msg void OnUpdateFilter94(CCmdUI* pCmdUI);
	afx_msg void OnFilter95();
	afx_msg void OnUpdateFilter95(CCmdUI* pCmdUI);
	afx_msg void OnFilter96();
	afx_msg void OnUpdateFilter96(CCmdUI* pCmdUI);
	afx_msg void OnOrderRgb();
	afx_msg void OnUpdateOrderRgb(CCmdUI* pCmdUI);
	afx_msg void OnOrderRbg();
	afx_msg void OnUpdateOrderRbg(CCmdUI* pCmdUI);
	afx_msg void OnOrderGrb();
	afx_msg void OnUpdateOrderGrb(CCmdUI* pCmdUI);
	afx_msg void OnOrderGbr();
	afx_msg void OnUpdateOrderGbr(CCmdUI* pCmdUI);
	afx_msg void OnOrderBrg();
	afx_msg void OnUpdateOrderBrg(CCmdUI* pCmdUI);
	afx_msg void OnOrderBgr();
	afx_msg void OnUpdateOrderBgr(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Flarium24View.cpp
inline CFlarium24Doc* CFlarium24View::GetDocument()
   { return (CFlarium24Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
