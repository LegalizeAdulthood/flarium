/// Pattern.cpp

#include "stdafx.h"
#include "Flarium24.h"

#include "Flarium24Doc.h"
#include "Flarium24View.h"
#include "mainfrm.h"
#include <math.h>
#include "external.h"
#include "xysize.h"
#include "nthorder.h"
#include "Two_Num.h"
#include "OneNum.h"
#include "lattoof.h"
#include "affine.h"
#include "qparams.h"


void CFlarium24View::DrawPattern()  // Step 1
{
	if (bDraw) 
	{
		bGlobalDraw = TRUE;
		if (!bAbort)
			GeneratePattern();
		if (!bLaunch || bAbort) 
		{
			// Pattern complete, restore variables
			bDraw = FALSE;
			bAbort = FALSE;
			bTracker = FALSE;
			bGlobalDraw = FALSE;

			if (dim.cx <= 1024 && dim.cy <= 1024)			
				bInitialized = TRUE;

			//bColorChange = FALSE;
			jul_save = jul;

			CFlarium24Doc* pDoc = GetDocument();
			
			szTemp = szFluFileName;						
	    if ( ! outFile.Open( szTemp, 
	   							CFile::modeRead))
		  {
				// If file does not exist, create it
				szTemp = szTemp.GetBufferSetLength(szTemp.GetLength()-3);				
				szTemp+="bmp";
				pDoc->OnSaveDocument(szTemp);
			}
			else
				outFile.Close();				
						
			//if (bBorder)
			//{
				// Draw a border in the bitmap
			//	DrawBorder();				
			//}			
      
			//////////////////////////////////////////////////
			if (nFilter == 169) // count the dots filter
			{	
				CWaitCursor cursor;	// this will automatically display a wait cursor
				for (py = 0; py < dim.cy ; py++)
				{
					for (px = 0; px < dim.cx ; px++)
					{
						//ntemp = mIter_Data[px + py*pDoc->m_sizeDoc.cx];

						i = lpDots[px + py*dim.cx];							
	
						if (dim.cx <= 1024 && dim.cy <= 1024)
						{
							//mIter_Data[px + py*pDoc->m_sizeDoc.cx] = i; // ????
							//nIter_Data[px + py*pDoc->m_sizeDoc.cx] = i;

							rIter_Data[px + py*pDoc->m_sizeDoc.cx] = i;
							gIter_Data[px + py*pDoc->m_sizeDoc.cx] = i;
							bIter_Data[px + py*pDoc->m_sizeDoc.cx] = i;						
						
						}

						rj = (double) i;
						gj = (double) i;
						bj = (double) i;
						Generalized_Coloring_Method();
						
						//if (!::WriteBit(pDoc->hdib, pDoc->m_sizeDoc,
						//			px, py, (DWORD)RGB(red, grn, blu)))
						if (!pDoc->m_dib.SetPixel(px, py, RGB(red, grn, blu)))
						{
							AfxMessageBox("Error writing to DIB");  
							Row = RowMax;
							Col = ColMax;
							px = dim.cx;
							py = dim.cy;
							bAbort = TRUE;
							bDraw = FALSE;
							bLaunch = FALSE;
						}              												
					}			
				}
			}
      Invalidate(FALSE);
		}
	}
	else
		bGlobalDraw = FALSE;
}

void CFlarium24View::adjust_coords()
{

	Radius_x = 2/dMagnification;
	Radius_y = 2/dMagnification;
	
	if (jul == 0 || jul_save == 1)
	{
		CRMAX = CRMID + Radius_x;
		CRMIN = CRMID - Radius_x;
		CIMAX = CIMID + Radius_y;
		CIMIN = CIMID - Radius_y;
	}
	else
	{
		CRMAX = 2;
		CRMIN = -2;
		CIMAX = 2;
		CIMIN = -2;
	}
  	
	rx_ratio = (double) dim.cx/(double) (dim.cy);
  ry_ratio = (double) dim.cy/(double) (dim.cx);

  rx_ratio = rx_ratio + (1-rx_ratio)/2;
  ry_ratio = ry_ratio + (1-ry_ratio)/2;

  CRMAX = CRMAX + (Radius_x * (rx_ratio) - Radius_x);
  CRMIN = CRMIN - (Radius_x * (rx_ratio) - Radius_x);
  CIMAX = CIMAX + (Radius_x * (ry_ratio) - Radius_y);
  CIMIN = CIMIN - (Radius_x * (ry_ratio) - Radius_y);

}

void CFlarium24View::GeneratePattern()
{
	//if (bColorChange && !bInitialized)
		//bColorChange = FALSE;
	
	if (bLaunch)
	{
		LaunchPattern(); 
   	return;
  }  

	// Initialize some variables, Initialize Drawing
	bLaunch = TRUE;
  // Fractal initialization
  ColMax = dim.cx-1;
  RowMax = dim.cy-1;

	if (jul == 1)
	{
		CRMIN = CRMIN_JUL; 
  	CIMIN = CIMIN_JUL;
  	CRMAX = CRMAX_JUL;
  	CIMAX = CIMAX_JUL;
	}

	adjust_coords();

//  DCR = ((CRMAX - CRMIN) / ColMax);
//  DCI = ((CIMAX - CIMIN) / RowMax);

  Col = 0;
	Row = RowMax;
  CR = CRMIN;
	  
	// Check for bMFilter
	if (bMFilter)
	{
		if (pXTemp)
			delete pXTemp;
		if (pYTemp)
			delete pYTemp;

		pXTemp = (double *) new double[NMAX+1];
		pYTemp = (double *) new double[NMAX+1];
	}			

	//////////////////////////////////////////////////
	if (hdots != NULL)
	{
		::GlobalUnlock((HGLOBAL) hdots);
		::GlobalFree((HGLOBAL) hdots);
		hdots = NULL;
	}

	if (nFilter == 169) // count the dots filter
	{	
		CWaitCursor cursor;	// this will automatically display a wait cursor
		hdots = (HGLOBAL) ::GlobalAlloc(GHND, dim.cx * dim.cy * 2);
		if (hdots == 0)
		{
			AfxMessageBox("Error Allocating Global Memory for filter 69");
			return;
		}

		// Get a pointer to the Dots memory 
		lpDots = (PUSHORT) ::GlobalLock((HGLOBAL) hdots);
		//for (i=0; i<dim.cx*dim.cy; i++)
			//lpDots[i] = 0;
	}

	///////////////////////////////////////////////////////////


	if (dim.cx <= 1024 && dim.cy <= 1024)
	{		
		bInitialized = TRUE;
		
		if (bRed)
			delete bRed;
		if (bGrn)
			delete bGrn;
		if (bBlu)
			delete bBlu;

		bRed = (BOOL*) new BOOL[dim.cx*dim.cy];
		bGrn = (BOOL*) new BOOL[dim.cx*dim.cy];
		bBlu = (BOOL*) new BOOL[dim.cx*dim.cy];

		//if (!bColorChange && dim != dim_save)
		//if (dim != dim_save)
		{
			//if (nIter_Data)
				//delete nIter_Data;
			//if (mIter_Data)
				//delete mIter_Data;

			if (rIter_Data)
				delete rIter_Data;

			if (gIter_Data)
				delete gIter_Data;

			if (bIter_Data)
				delete bIter_Data;

			//if (xData)
			//	delete xData;
			//if (yData)
			//	delete yData;
		
			//nIter_Data = (int*) new int [dim.cx*dim.cy];
			//mIter_Data = (int*) new int [dim.cx*dim.cy];

			rIter_Data = (int*) new int [dim.cx*dim.cy];
			gIter_Data = (int*) new int [dim.cx*dim.cy];
			bIter_Data = (int*) new int [dim.cx*dim.cy];

			//xData = (double*) new double [dim.cx*dim.cy];
			//yData = (double*) new double [dim.cx*dim.cy];
		
			for (i=0; i<dim.cx*dim.cy; i++)
			{
				//nIter_Data[i] = 0;
				//mIter_Data[i] = 0;

				rIter_Data[i] = 0;
				gIter_Data[i] = 0;
				bIter_Data[i] = 0;
								
				//xData[i] = 0;
				//yData[i] = 0;
			}
			dim_save = dim;
		}

		for (i=0; i<dim.cx*dim.cy; i++)
		{
			bRed[i] = TRUE;
			bGrn[i] = TRUE;
			bBlu[i] = TRUE;
		}

		bRedStart = TRUE;
		bGrnStart = TRUE;
		bBluStart = TRUE;

	}
	else
		bInitialized = FALSE;

	
	// Launch The Drawing Pattern for the first time
	LaunchPattern();

}

void CFlarium24View::LaunchPattern()
{
	// Mandelbrot Fractal pattern
	TestPattern();
		
	//if ((Row % 32) == 0 && !bStartMovie && dim.cx <= 640 && dim.cy <= 480 && !nMatrix)
	if ((Row % 32) == 0)
	{
		//if (bStretchToFit)
		//	bStretchToFit = FALSE;
		Invalidate(FALSE);					
	}

	if ((Row % 2) == 0)
	{
		Window_Pane(Row);
	}

	//if ((Row % 100) == 0 && nMatrix)
	//{
	//	Window_Pane(Row);
	//}

	if (Row < 0 || dim.cy - Row < 0)
	{
		bDraw = FALSE;
  	bLaunch = FALSE;
				
		char cstr[81];
		wsprintf(cstr, "max iteration = %d", temp_max);
		Status_Bar(cstr);
  }	
}

void CFlarium24View::TestPattern()
{
  py = Row;
	for (px = 0; px < dim.cx ; px++)
		TestPatternSub();

	Row--;
}
				
void CFlarium24View::TestPatternSub()
{
  CFlarium24Doc* pDoc = GetDocument();

	xsquared = ysquared = 0;

	zz2 = cmplx(0,0); // Strands variables
	zz  = cmplx(0,0);

	//////////////////////////////////////////////
	// Fractal Initialization
	//

	if (nFilter == 169)
	{
		xO = dCloud_left; 
		yO = dCloud_bottom;
		xI = dCloud_right;
		yI = dCloud_top;
	}
	else
	{
		xO = CRMIN; 
		yO = CIMIN;
		xI = CRMAX;
		yI = CIMAX;
	}

	xinc = (double)dim.cx/(CRMAX-CRMIN);
	yinc = (double)dim.cy/(CIMAX-CIMIN);
		
	ldx = (xI - xO) / (double) dim.cx;    /* compute size of pixels */
  ldy = (yI - yO) / (double) dim.cy;
	
	x = xO + (double) px * ldx,  	/* start julia on pixel */
  y = yO + (double) py * ldy;
        
  if (jul == 0)    										// Start mandelbrot set on 0,0 
   	cx = x, cy = y;										// and use pixel for c.
   	//cx = x, cy = y, x = 0L, y = 0L;   // and use pixel for c.
  else if (jul_save == 0) 						// If previous was a mandelbrot
  	cx = CRMID, cy = CIMID;  					// A Julia coordinate

	if (bZeroInit && jul == 0)
	{
		x = 0; 
		y = 0;
	}
  
  xsquared = 0, ysquared = 0;

	// Check minimum and maximum valid limits
	if (cx < zerotol && cx > -zerotol)
	{
		if (cx >= 0)
			cx = zerotol;
		else
			cx = -zerotol;
	}

	if (cy < zerotol && cy > -zerotol)
	{
		if (cy >= 0)
			cy = zerotol;
		else
			cy = -zerotol;
	}
		
	if (x < zerotol && x > -zerotol)
	{
		if (x >= 0)
			x = zerotol;
		else
			x = -zerotol;
	}

	if (y < zerotol && y > -zerotol)
	{
		if (y >= 0)
			y = zerotol;
		else
			y = -zerotol;
	}
	
	// Initialize some complex variables
	z = cmplx (x, y );
	z.set_biomorph(dBiomorph);
	
	c = cmplx(cx, cy);
	c.set_biomorph(dBiomorph);
	
	z2 = cmplx(0,0);
	z2.set_biomorph(dBiomorph);

	if (jul == 0)
	{
		if (bInvertFractal)
		{
			c = 1/c;
			z = 1/z;
		}
		c *= cOrient;

	}
	else if (jul_save == 0)
	{
		if (bInvertFractal) { c = 1/c; z = 1/z; }
		c *= cOrient;
		z *= cOrient;
	}
	else
	{
		if (bInvertFractal)
			z = 1/z;
		z *= cOrient;
	}

	x =  z.real();
	y =  z.imaginary();
	cx = c.real();
	cy = c.imaginary();
				
  dStrands_HI = sqrt(cx*cx+cy*cy) + dStrands;
  dStrands_LO = sqrt(cx*cx+cy*cy) - dStrands;

	TestEquations();
}

void CFlarium24View::OnViewMandel() 
{
	GoDoFractal();
}

void CFlarium24View::OnUpdateViewMandel(CCmdUI* pCmdUI) 
{
	if (!jul) pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);	
}

//////////////////////////////////////////////////////////////////////
void CFlarium24View::GoDoFractal() 
{
	jul 		 = 0;
	jul_save = 1;
	bDraw = TRUE;
	bLaunch = FALSE;
}

////////////////////////////////////////////////////////////////

void CFlarium24View::OnDraw0() 
{
  ActiveTitle = "0.) ";
	nDistortion = 0;

  GoDoFractal();
}

void CFlarium24View::OnUpdateDraw0(CCmdUI* pCmdUI) 
{
	if (nDistortion == 0) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw1() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "1.) ";
	nDistortion = 1;

  GoDoFractal();
}

void CFlarium24View::OnUpdateDraw1(CCmdUI* pCmdUI) 
{
	if (nDistortion == 1) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw2() 
{
	CNthOrder real_order;
	real_order.m_RealNthOrder				= rorder_r;
	real_order.m_ImaginaryNthOrder	= rorder_i;
	if (real_order.DoModal() == IDOK)
	{
		rorder_r = real_order.m_RealNthOrder;	
		rorder_i = real_order.m_ImaginaryNthOrder;	
		cn = cmplx (rorder_r, rorder_i);
	}
	else
	{
		return;
	}  	

	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "2) Nth Order Mandelbrot [Generalized]";
	nDistortion = 2;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw2(CCmdUI* pCmdUI) 
{
	if (nDistortion == 2) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw3() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "3.) ";
	nDistortion = 3;

  GoDoFractal();
}

void CFlarium24View::OnUpdateDraw3(CCmdUI* pCmdUI) 
{
	if (nDistortion == 3) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw4() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "4.) ";
	nDistortion = 4;
  GoDoFractal();
}

void CFlarium24View::OnUpdateDraw4(CCmdUI* pCmdUI) 
{
	if (nDistortion == 4) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw5() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "5.) ";
	nDistortion = 5;

  GoDoFractal();
}

void CFlarium24View::OnUpdateDraw5(CCmdUI* pCmdUI) 
{
	if (nDistortion == 5) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw6() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "6.) ";
	nDistortion = 6;

  GoDoFractal();
}

void CFlarium24View::OnUpdateDraw6(CCmdUI* pCmdUI) 
{
	if (nDistortion == 6) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw7() 
{
	CNthOrder real_order;
	real_order.m_RealNthOrder				= rorder_r;
	real_order.m_ImaginaryNthOrder	= rorder_i;
	if (real_order.DoModal() == IDOK)
	{
		rorder_r = real_order.m_RealNthOrder;	
		rorder_i = real_order.m_ImaginaryNthOrder;	
		cn = cmplx (rorder_r, rorder_i);
	}
	else
	{
		return;
	}  	

	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "7) ";
	nDistortion = 7;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw7(CCmdUI* pCmdUI) 
{
	if (nDistortion == 7) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw8() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "8.) ";
	nDistortion = 8;

  GoDoFractal();
}

void CFlarium24View::OnUpdateDraw8(CCmdUI* pCmdUI) 
{
	if (nDistortion == 8) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw9() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "9) ";
	nDistortion = 9;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw9(CCmdUI* pCmdUI) 
{
	if (nDistortion == 9) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw10() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "10) ";
	nDistortion = 10;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw10(CCmdUI* pCmdUI) 
{
	if (nDistortion == 10) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw11() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "11) ";
	nDistortion = 11;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw11(CCmdUI* pCmdUI) 
{
	if (nDistortion == 11) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw12() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "12) ";
	nDistortion = 12;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw12(CCmdUI* pCmdUI) 
{
	if (nDistortion == 12) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw13() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "13.) ";
	nDistortion = 13;

  GoDoFractal();
}

void CFlarium24View::OnUpdateDraw13(CCmdUI* pCmdUI) 
{
	if (nDistortion == 13) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw14() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "14.) ";
	nDistortion = 14;

  GoDoFractal();
}

void CFlarium24View::OnUpdateDraw14(CCmdUI* pCmdUI) 
{
	if (nDistortion == 14) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw15() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "15.) ";
	nDistortion = 15;

  GoDoFractal();
}

void CFlarium24View::OnUpdateDraw15(CCmdUI* pCmdUI) 
{
	if (nDistortion == 15) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw16() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "16.) ";
	nDistortion = 16;

  GoDoFractal();
}

void CFlarium24View::OnUpdateDraw16(CCmdUI* pCmdUI) 
{
	if (nDistortion == 16) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw17() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	jul      = 0;
	jul_save = 1;

	bZeroInit = FALSE;

	nDistortion = 17;
	ActiveTitle = "17.) F(z) = ((cn-1)*(z^cn)+cm)/(cn*(z^(cn-1))); [Newton Raphson]";

	CTwo_Num two;

	two.m_cn_real = cn.real();
	two.m_cn_imag = cn.imag();

	two.m_cr_real = cr.real();
	two.m_cr_imag = cr.imag();

	if (two.DoModal() == IDOK)
	{
		cn.set_real(two.m_cn_real);
		cn.set_imag(two.m_cn_imag);
		rorder_r = cn.real();
		rorder_i = cn.imag();

		cr.set_real(two.m_cr_real);
		cr.set_imag(two.m_cr_imag);

		GoDoFractal();
	}
}

void CFlarium24View::OnUpdateDraw17(CCmdUI* pCmdUI) 
{
	if (nDistortion == 17) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw18() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "18.) ";
	nDistortion = 18;

  GoDoFractal();
}

void CFlarium24View::OnUpdateDraw18(CCmdUI* pCmdUI) 
{
	if (nDistortion == 18) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw19() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "19.) ";
	nDistortion = 19;

  GoDoFractal();
}

void CFlarium24View::OnUpdateDraw19(CCmdUI* pCmdUI) 
{
	if (nDistortion == 19) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw20() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "20.) ";
	nDistortion = 20;

  GoDoFractal();
}

void CFlarium24View::OnUpdateDraw20(CCmdUI* pCmdUI) 
{
	if (nDistortion == 20) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw21() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "21.) ";
	nDistortion = 21;

  GoDoFractal();
}

void CFlarium24View::OnUpdateDraw21(CCmdUI* pCmdUI) 
{
	if (nDistortion == 21) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw22() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "22.) ";
	nDistortion = 22;

  GoDoFractal();
}

void CFlarium24View::OnUpdateDraw22(CCmdUI* pCmdUI) 
{
	if (nDistortion == 22) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw23() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "23.) ";
	nDistortion = 23;

  GoDoFractal();
}

void CFlarium24View::OnUpdateDraw23(CCmdUI* pCmdUI) 
{
	if (nDistortion == 23) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw24() 
{
	CNthOrder real_order;
	real_order.m_RealNthOrder				= rorder_r;
	real_order.m_ImaginaryNthOrder	= rorder_i;
	if (real_order.DoModal() == IDOK)
	{
		rorder_r = real_order.m_RealNthOrder;	
		rorder_i = real_order.m_ImaginaryNthOrder;	
		cn = cmplx (rorder_r, rorder_i);
	}
	else
	{
		return;
	}  	

	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "24) ";
	nDistortion = 24;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw24(CCmdUI* pCmdUI) 
{
	if (nDistortion == 24) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw25() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "25.) ";
	nDistortion = 25;

  GoDoFractal();
}

void CFlarium24View::OnUpdateDraw25(CCmdUI* pCmdUI) 
{
	if (nDistortion == 25) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw26() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "26) ";
	nDistortion = 26;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw26(CCmdUI* pCmdUI) 
{
	if (nDistortion == 26) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw27() 
{
	CNthOrder real_order;
	real_order.m_RealNthOrder				= rorder_r;
	real_order.m_ImaginaryNthOrder	= rorder_i;
	if (real_order.DoModal() == IDOK)
	{
		rorder_r = real_order.m_RealNthOrder;	
		rorder_i = real_order.m_ImaginaryNthOrder;	
		cn = cmplx (rorder_r, rorder_i);
	}
	else
	{
		return;
	}  	

	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "27) ";
	nDistortion = 27;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw27(CCmdUI* pCmdUI) 
{
	if (nDistortion == 27) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw28() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "28) ";
	nDistortion = 28;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw28(CCmdUI* pCmdUI) 
{
	if (nDistortion == 28) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw29() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "29) ";
	nDistortion = 29;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw29(CCmdUI* pCmdUI) 
{
	if (nDistortion == 29) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw30() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "30) ";
	nDistortion = 30;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw30(CCmdUI* pCmdUI) 
{
	if (nDistortion == 30) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}


void CFlarium24View::OnDraw31() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "31) ";
	nDistortion = 31;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw31(CCmdUI* pCmdUI) 
{
	if (nDistortion == 31) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw32() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "32) ";
	nDistortion = 32;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw32(CCmdUI* pCmdUI) 
{
	if (nDistortion == 32) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw33() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "33) ";
	nDistortion = 33;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw33(CCmdUI* pCmdUI) 
{
	if (nDistortion == 33) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw34() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "34) ";
	nDistortion = 34;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw34(CCmdUI* pCmdUI) 
{
	if (nDistortion == 34) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}


void CFlarium24View::OnDraw35() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "35) ";
	nDistortion = 35;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw35(CCmdUI* pCmdUI) 
{
	if (nDistortion == 35) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw36() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "36) ";
	nDistortion = 36;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw36(CCmdUI* pCmdUI) 
{
	if (nDistortion == 36) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw37() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "37) ";
	nDistortion = 37;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw37(CCmdUI* pCmdUI) 
{
	if (nDistortion == 37) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw38() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "38) ";
	nDistortion = 38;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw38(CCmdUI* pCmdUI) 
{
	if (nDistortion == 38) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw39() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "39) ";
	nDistortion = 39;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw39(CCmdUI* pCmdUI) 
{
	if (nDistortion == 39) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw40() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "40) ";
	nDistortion = 40;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw40(CCmdUI* pCmdUI) 
{
	if (nDistortion == 40) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}


void CFlarium24View::OnDraw41() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "41) ";
	nDistortion = 41;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw41(CCmdUI* pCmdUI) 
{
	if (nDistortion == 41) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw42() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "42) ";
	nDistortion = 42;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw42(CCmdUI* pCmdUI) 
{
	if (nDistortion == 42) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw43() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "43) ";
	nDistortion = 43;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw43(CCmdUI* pCmdUI) 
{
	if (nDistortion == 43) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw44() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "44) ";
	nDistortion = 44;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw44(CCmdUI* pCmdUI) 
{
	if (nDistortion == 44) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw45() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "45) ";
	nDistortion = 45;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw45(CCmdUI* pCmdUI) 
{
	if (nDistortion == 45) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}


void CFlarium24View::OnDraw46() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "46) ";
	nDistortion = 46;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw46(CCmdUI* pCmdUI) 
{
	if (nDistortion == 46) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw47() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "47) ";
	nDistortion = 47;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw47(CCmdUI* pCmdUI) 
{
	if (nDistortion == 47) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw48() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "48) ";
	nDistortion = 48;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw48(CCmdUI* pCmdUI) 
{
	if (nDistortion == 48) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw49() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "49) ";
	nDistortion = 49;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw49(CCmdUI* pCmdUI) 
{
	if (nDistortion == 49) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw50() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "50) ";
	nDistortion = 50;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw50(CCmdUI* pCmdUI) 
{
	if (nDistortion == 50) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw51() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "51) ";
	nDistortion = 51;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw51(CCmdUI* pCmdUI) 
{
	if (nDistortion == 51) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw52() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "52) ";
	nDistortion = 52;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw52(CCmdUI* pCmdUI) 
{
	if (nDistortion == 52) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw53() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "53) ";
	nDistortion = 53;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw53(CCmdUI* pCmdUI) 
{
	if (nDistortion == 53) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw54() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "54) ";
	nDistortion = 54;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw54(CCmdUI* pCmdUI) 
{
	if (nDistortion == 54) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw55() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "55) ";
	nDistortion = 55;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw55(CCmdUI* pCmdUI) 
{
	if (nDistortion == 55) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw56() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "56) ";
	nDistortion = 56;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw56(CCmdUI* pCmdUI) 
{
	if (nDistortion == 56) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw57() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "57) ";
	nDistortion = 57;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw57(CCmdUI* pCmdUI) 
{
	if (nDistortion == 57) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw58() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "58) ";
	nDistortion = 58;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw58(CCmdUI* pCmdUI) 
{
	if (nDistortion == 58) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw59() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "59) ";
	nDistortion = 59;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw59(CCmdUI* pCmdUI) 
{
	if (nDistortion == 59) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw60() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "60) ";
	nDistortion = 60;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw60(CCmdUI* pCmdUI) 
{
	if (nDistortion == 60) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}


void CFlarium24View::OnDraw61() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "61) ";
	nDistortion = 61;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw61(CCmdUI* pCmdUI) 
{
	if (nDistortion == 61) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw62() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "62) ";
	nDistortion = 62;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw62(CCmdUI* pCmdUI) 
{
	if (nDistortion == 62) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw63() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "63) ";
	nDistortion = 63;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw63(CCmdUI* pCmdUI) 
{
	if (nDistortion == 63) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw64() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "64) ";
	nDistortion = 64;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw64(CCmdUI* pCmdUI) 
{
	if (nDistortion == 64) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw65() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "65) ";
	nDistortion = 65;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw65(CCmdUI* pCmdUI) 
{
	if (nDistortion == 65) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw66() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "66) ";
	nDistortion = 66;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw66(CCmdUI* pCmdUI) 
{
	if (nDistortion == 66) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw67() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "67) ";
	nDistortion = 67;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw67(CCmdUI* pCmdUI) 
{
	if (nDistortion == 67) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw68() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "68) ";
	nDistortion = 68;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw68(CCmdUI* pCmdUI) 
{
	if (nDistortion == 68) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw69() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "69) ";
	nDistortion = 69;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw69(CCmdUI* pCmdUI) 
{
	if (nDistortion == 69) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw70() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "70) ";
	nDistortion = 70;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw70(CCmdUI* pCmdUI) 
{
	if (nDistortion == 70) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw71() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "71) ";
	nDistortion = 71;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw71(CCmdUI* pCmdUI) 
{
	if (nDistortion == 71) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw72() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "72) ";
	nDistortion = 72;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw72(CCmdUI* pCmdUI) 
{
	if (nDistortion == 72) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw73() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "73) ";
	nDistortion = 73;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw73(CCmdUI* pCmdUI) 
{
	if (nDistortion == 73) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw74() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "74) ";
	nDistortion = 74;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw74(CCmdUI* pCmdUI) 
{
	if (nDistortion == 74) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw75() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "75) ";
	nDistortion = 75;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw75(CCmdUI* pCmdUI) 
{
	if (nDistortion == 75) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw76() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "76) ";
	nDistortion = 76;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw76(CCmdUI* pCmdUI) 
{
	if (nDistortion == 76) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw77() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "77) ";
	nDistortion = 77;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw77(CCmdUI* pCmdUI) 
{
	if (nDistortion == 77) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw78() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "78) ";
	nDistortion = 78;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw78(CCmdUI* pCmdUI) 
{
	if (nDistortion == 78) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw79() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "79) ";
	nDistortion = 79;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw79(CCmdUI* pCmdUI) 
{
	if (nDistortion == 79) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw80() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "80) ";
	nDistortion = 80;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw80(CCmdUI* pCmdUI) 
{
	if (nDistortion == 80) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw81() 
{
	COneNum rw;
	rw.m_RW1_n = rn;

	if (rw.DoModal() == IDOK)
	{
		rn = rw.m_RW1_n;
		GoDoFractal();
	}
	else
		return;

	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "81) ";
	nDistortion = 81;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw81(CCmdUI* pCmdUI) 
{
	if (nDistortion == 81) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw82() 
{
	COneNum rw;
	rw.m_RW1_n = rn;

	if (rw.DoModal() == IDOK)
	{
		rn = rw.m_RW1_n;
		GoDoFractal();
	}
	else
		return;

	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "82) ";
	nDistortion = 82;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw82(CCmdUI* pCmdUI) 
{
	if (nDistortion == 82) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw83() 
{
	COneNum rw;
	rw.m_RW1_n = rn;

	if (rw.DoModal() == IDOK)
	{
		rn = rw.m_RW1_n;
		GoDoFractal();
	}
	else
		return;

	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "83) ";
	nDistortion = 83;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw83(CCmdUI* pCmdUI) 
{
	if (nDistortion == 83) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw84() 
{
	COneNum rw;
	rw.m_RW1_n = rn;

	if (rw.DoModal() == IDOK)
	{
		rn = rw.m_RW1_n;
		GoDoFractal();
	}
	else
		return;

	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "84) ";
	nDistortion = 84;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw84(CCmdUI* pCmdUI) 
{
	if (nDistortion == 84) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw85() 
{
	COneNum rw;
	rw.m_RW1_n = rn;

	if (rw.DoModal() == IDOK)
	{
		rn = rw.m_RW1_n;
		GoDoFractal();
	}
	else
		return;

	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "85) ";
	nDistortion = 85;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw85(CCmdUI* pCmdUI) 
{
	if (nDistortion == 85) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}


void CFlarium24View::OnDraw86() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "86) ";
	nDistortion = 86;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw86(CCmdUI* pCmdUI) 
{
	if (nDistortion == 86) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw87() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "87) ";
	nDistortion = 87;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw87(CCmdUI* pCmdUI) 
{
	if (nDistortion == 87) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw88() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "88) ";
	nDistortion = 88;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw88(CCmdUI* pCmdUI) 
{
	if (nDistortion == 88) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw89() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "89) ";
	nDistortion = 89;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw89(CCmdUI* pCmdUI) 
{
	if (nDistortion == 89) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw90() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "90) ";
	nDistortion = 90;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw90(CCmdUI* pCmdUI) 
{
	if (nDistortion == 90) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw91() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "91) ";
	nDistortion = 91;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw91(CCmdUI* pCmdUI) 
{
	if (nDistortion == 91) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw92() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "92) ";
	nDistortion = 92;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw92(CCmdUI* pCmdUI) 
{
	if (nDistortion == 92) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw93() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "93) ";
	nDistortion = 93;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw93(CCmdUI* pCmdUI) 
{
	if (nDistortion == 93) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}


void CFlarium24View::OnDraw94() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "94) ";
	nDistortion = 94;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw94(CCmdUI* pCmdUI) 
{
	if (nDistortion == 94) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw95() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "95) ";
	nDistortion = 95;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw95(CCmdUI* pCmdUI) 
{
	if (nDistortion == 95) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw96() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "96) ";
	nDistortion = 96;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw96(CCmdUI* pCmdUI) 
{
	if (nDistortion == 96) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw97() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "97) ";
	nDistortion = 97;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw97(CCmdUI* pCmdUI) 
{
	if (nDistortion == 97) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw98() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "98) ";
	nDistortion = 98;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw98(CCmdUI* pCmdUI) 
{
	if (nDistortion == 98) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw99() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "99) ";
	nDistortion = 99;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw99(CCmdUI* pCmdUI) 
{
	if (nDistortion == 99) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw100() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "100) ";
	nDistortion = 100;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw100(CCmdUI* pCmdUI) 
{
	if (nDistortion == 100) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw101() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "101) ";
	nDistortion = 101;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw101(CCmdUI* pCmdUI) 
{
	if (nDistortion == 101) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw102() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "102) ";
	nDistortion = 102;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw102(CCmdUI* pCmdUI) 
{
	if (nDistortion == 102) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw103() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "103) ";
	nDistortion = 103;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw103(CCmdUI* pCmdUI) 
{
	if (nDistortion == 103) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw104() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "104) ";
	nDistortion = 104;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw104(CCmdUI* pCmdUI) 
{
	if (nDistortion == 104) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw105() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "105) ";
	nDistortion = 105;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw105(CCmdUI* pCmdUI) 
{
	if (nDistortion == 105) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw106() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "106) ";
	nDistortion = 106;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw106(CCmdUI* pCmdUI) 
{
	if (nDistortion == 106) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw107() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "107) ";
	nDistortion = 107;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw107(CCmdUI* pCmdUI) 
{
	if (nDistortion == 107) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw108() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "108) ";
	nDistortion = 108;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw108(CCmdUI* pCmdUI) 
{
	if (nDistortion == 108) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw109() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "109) ";
	nDistortion = 109;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw109(CCmdUI* pCmdUI) 
{
	if (nDistortion == 109) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw110() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "110) ";
	nDistortion = 110;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw110(CCmdUI* pCmdUI) 
{
	if (nDistortion == 110) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw111() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "111) ";
	nDistortion = 111;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw111(CCmdUI* pCmdUI) 
{
	if (nDistortion == 111) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw112() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "112) ";
	nDistortion = 112;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw112(CCmdUI* pCmdUI) 
{
	if (nDistortion == 112) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw113() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "113) ";
	nDistortion = 113;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw113(CCmdUI* pCmdUI) 
{
	if (nDistortion == 113) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw114() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "114) ";
	nDistortion = 114;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw114(CCmdUI* pCmdUI) 
{
	if (nDistortion == 114) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw115() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "115) ";
	nDistortion = 115;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw115(CCmdUI* pCmdUI) 
{
	if (nDistortion == 115) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw116() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "116) ";
	nDistortion = 116;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw116(CCmdUI* pCmdUI) 
{
	if (nDistortion == 116) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw117() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "117) ";
	nDistortion = 117;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw117(CCmdUI* pCmdUI) 
{
	if (nDistortion == 117) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw118() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "118) ";
	nDistortion = 118;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw118(CCmdUI* pCmdUI) 
{
	if (nDistortion == 118) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw119() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "119) ";
	nDistortion = 119;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw119(CCmdUI* pCmdUI) 
{
	if (nDistortion == 119) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw125() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "125) ";
	nDistortion = 125;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw125(CCmdUI* pCmdUI) 
{
	if (nDistortion == 125) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

/////////////////////////////////////////////
// Attractors
//

void CFlarium24View::OnAttractorsXy() 
{
	nDimension = 0;
	if (nDistortion == 131)
		OnDrawRepeat(); // Lorenz;
	else
		GoDoFractal();
}

void CFlarium24View::OnUpdateAttractorsXy(CCmdUI* pCmdUI) 
{
	if (nDimension == 0)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnAttractorsXz() 
{
	nDimension = 1;	
	if (nDistortion == 131)
		OnDrawRepeat(); // Lorenz;
	else
		GoDoFractal();
}

void CFlarium24View::OnUpdateAttractorsXz(CCmdUI* pCmdUI) 
{	
	if (nDimension == 1)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnAttractorsYz() 
{
	nDimension = 2;	
	if (nDistortion == 131)
		OnDrawRepeat(); // Lorenz;
	else
		GoDoFractal();
}

void CFlarium24View::OnUpdateAttractorsYz(CCmdUI* pCmdUI) 
{
	if (nDimension == 2)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDrawRepeat() 
{
	switch (nDistortion)
	{
		case 120:
			OnDraw120();
			break;

		case 121:
			OnDraw121();
			break;

		case 122:
			OnDraw122();
			break;

		case 123:
			OnDraw123();
			break;

		case 124:
			OnDraw124();
			break;

		case 126:
			OnDraw126();
			break;

		case 127:
			OnDraw127();
			break;

		case 128:
			OnDraw128();
			break;

		case 129:
			OnDraw129();
			break;

		case 130:
			OnDraw130();
			break;

		case 131:
			OnDraw131();
			break;

		default:
			bDraw = TRUE;
			bLaunch = FALSE;
			break;
	}
}

void CFlarium24View::OnDrawLatoofdlg() 
{
  CLattoof cl;
  cl.m_mx = mx;
  cl.m_my = my;
  cl.m_ma = ma;
  cl.m_mb = mb;
  cl.m_mc = mc;
  cl.m_md = md;

  cl.m_Count = latoof_count;
	cl.m_Formulae = nDistortion;

  cl.m_Top    = CIMAX;
  cl.m_Left   = CRMIN;
  cl.m_Bottom = CIMIN;
  cl.m_Right  = CRMAX;

  if (cl.DoModal() == IDOK)
  {
    mx = cl.m_mx;
    my = cl.m_my;
    ma = cl.m_ma;
    mb = cl.m_mb;
    mc = cl.m_mc;
    md = cl.m_md;

    latoof_count = cl.m_Count;
		nDistortion = cl.m_Formulae;

    CIMAX = cl.m_Top;
    CRMIN = cl.m_Left;
    CIMIN = cl.m_Bottom;
    CRMAX = cl.m_Right;
  
    //bNewView = FALSE;

		GoDoFractal();
  }  
}

void CFlarium24View::OnDraw120() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "120.) Latoocarfian";
  nDistortion = 120;
	StandardLatoof();
}

void CFlarium24View::OnUpdateDraw120(CCmdUI* pCmdUI) 
{
	if (nDistortion == 120) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw121() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "121.) Latoocarfian Variant Alpha";
  nDistortion = 121;
	StandardLatoof();
}

void CFlarium24View::OnUpdateDraw121(CCmdUI* pCmdUI) 
{
	if (nDistortion == 121) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDrawAffinetransformation() 
{
	//CAffine ifs;
	if (m_pAffineView->GetSafeHwnd() == 0)
	{
		// Create the non-modal dialog
		bAffine = TRUE;

		m_pAffineView->Create();
		m_pAffineView->ShowWindow(SW_SHOW);

		Affine_Data_Update();
	}
	else
	{
		bAffine = FALSE;
		m_pAffineView->DestroyWindow();
	}	
}

void CFlarium24View::Affine_Data_Update()
{
	if (m_pAffineView->GetSafeHwnd() != 0)
	{
		m_pAffineView->m_A01 = af[1];
		m_pAffineView->m_A02 = af[2];
		m_pAffineView->m_A03 = af[3];
		m_pAffineView->m_A04 = af[4];
		m_pAffineView->m_A05 = af[5];
		m_pAffineView->m_A06 = af[6];
		m_pAffineView->m_A07 = af[7];
		m_pAffineView->m_A08 = af[8];
		m_pAffineView->m_A09 = af[9];

		m_pAffineView->m_A10 = af[10];
		m_pAffineView->m_A11 = af[11];
		m_pAffineView->m_A12 = af[12];
		m_pAffineView->m_A13 = af[13];
		m_pAffineView->m_A14 = af[14];
		m_pAffineView->m_A15 = af[15];
		m_pAffineView->m_A16 = af[16];
		m_pAffineView->m_A17 = af[17];
		m_pAffineView->m_A18 = af[18];
		m_pAffineView->m_A19 = af[19];

		m_pAffineView->m_A20 = af[20];
		m_pAffineView->m_A21 = af[21];
		m_pAffineView->m_A22 = af[22];
		m_pAffineView->m_A23 = af[23];
		m_pAffineView->m_A24 = af[24];
		m_pAffineView->m_A25 = af[25];
		m_pAffineView->m_A26 = af[26];
		m_pAffineView->m_A27 = af[27];
		m_pAffineView->m_A28 = af[28];
		m_pAffineView->m_A29 = af[29];
		m_pAffineView->m_A30 = af[30];

		m_pAffineView->m_Counts = latoof_count;
		m_pAffineView->m_Formulae = nDistortion;

		m_pAffineView->UpdateData(FALSE);

	}
}

void CFlarium24View::OnUpdateDrawAffinetransformation(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(bAffine);	
}

long CFlarium24View::OnApply_AffineView(UINT wParam, LONG lParam)
{	
	CFlarium24Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (wParam == ID_DLGCLOSE)
	{
		bAffine = FALSE;
		m_pAffineView->DestroyWindow();
	}	
	else
	{		
		m_pAffineView->UpdateData(TRUE);

		af[1] = m_pAffineView->m_A01;
		af[2] = m_pAffineView->m_A02;
		af[3] = m_pAffineView->m_A03;
		af[4] = m_pAffineView->m_A04;
		af[5] = m_pAffineView->m_A05;
		af[6] = m_pAffineView->m_A06;
		af[7] = m_pAffineView->m_A07;
		af[8] = m_pAffineView->m_A08;
		af[9] = m_pAffineView->m_A09;
		af[10] = m_pAffineView->m_A10;

		af[11] = m_pAffineView->m_A11;
		af[12] = m_pAffineView->m_A12;
		af[13] = m_pAffineView->m_A13;
		af[14] = m_pAffineView->m_A14;
		af[15] = m_pAffineView->m_A15;
		af[16] = m_pAffineView->m_A16;
		af[17] = m_pAffineView->m_A17;
		af[18] = m_pAffineView->m_A18;
		af[19] = m_pAffineView->m_A19;
		af[20] = m_pAffineView->m_A20;

		af[21] = m_pAffineView->m_A21;
		af[22] = m_pAffineView->m_A22;
		af[23] = m_pAffineView->m_A23;
		af[24] = m_pAffineView->m_A24;
		af[25] = m_pAffineView->m_A25;
		af[26] = m_pAffineView->m_A26;
		af[27] = m_pAffineView->m_A27;
		af[28] = m_pAffineView->m_A28;
		af[29] = m_pAffineView->m_A29;
		af[30] = m_pAffineView->m_A30;

		latoof_count = m_pAffineView->m_Counts;
		nDistortion  = m_pAffineView->m_Formulae;

		//GoDoFractal();
		bDraw = TRUE;
		bLaunch = FALSE;

	}
	return 0L;
}

///////////////////////////////////
void CFlarium24View::OnDraw122() 
{
  nDistortion = 122;  // 116
	::SetCursor(mWait);
		
	NMAX = 1000;
	n = 0;
	while (n < NMAX)
	{
		if (n == 0)
			SetParams();
		AdvanceXY();
		SubDisplay();	
		n++;
		TestSolution();
	}
		
	char cstr[81];
	sprintf(cstr,"122.) Chaotic Iterated Map, L = %f", L);
	ActiveTitle = cstr;
	
	//bNewView = FALSE;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw122(CCmdUI* pCmdUI) 
{
	if (nDistortion == 122) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw123() // 117
{
  nDistortion = 123;  // 117
	::SetCursor(mWait);
		
	NMAX = 1000;
	n = 0;
	while (n < NMAX)
	{
		if (n == 0)
			SetParams();
		j = 6 * (rand() % 2); 
		AdvanceXY();
		SubDisplay();	
		n++;
		TestSolution_1();
	}
		
	char cstr[81];
	sprintf(cstr,"123.) Iterated Function System, L = %f", L);
	ActiveTitle = cstr;
	
	//bNewView = FALSE;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw123(CCmdUI* pCmdUI) 
{
	if (nDistortion == 123) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::Attractor_3D()
{
	int retries = 1000000;
	::SetCursor(mWait);

	NMAX = 1000;
	n = 0;
	while (n < NMAX && retries-- > 0)
	{
		if (n == 0)
			SetParams_3D(); // zero, and seed vars
		AdvanceXY();
		SubDisplay_3D();	
		n++;
		TestSolution_3D();
	}

	if (retries <= 0)
	{
		AfxMessageBox("Failed Lyanpunov Test, timed out");
	}
	else
	if (L == 0)
	{
		AfxMessageBox("Failed Lyanpunov Test, L = 0");
	}
	else
	{		
		char cstr[81];
		sprintf(cstr,"%d.) 3D Chaotic Iterated Map, L = %f", 
			nDistortion, L);
		ActiveTitle = cstr;
	
		GoDoFractal();
	}
}

void CFlarium24View::OnDraw124() 
{
  nDistortion = 124; 
	int retries = 1000000;
	::SetCursor(mWait);

	NMAX = 1000;
	n = 0;
	while (n < NMAX && retries-- > 0)
	{
		if (n == 0)
			SetParams_3D(); // zero, and seed vars
		AdvanceXY();
		SubDisplay_3D();	
		n++;
		TestSolution_3D();
	}

	if (retries <= 0)
	{
		AfxMessageBox("Failed Lyanpunov Test, timed out");
	}
	else
	if (L == 0)
	{
		AfxMessageBox("Failed Lyanpunov Test, L = 0");
	}
	else
	{		
		char cstr[81];
		sprintf(cstr,"%d.) 3D Chaotic Iterated Map, L = %f", 
			nDistortion, L);
		ActiveTitle = cstr;
	
		GoDoFractal();
	}
}

void CFlarium24View::OnUpdateDraw124(CCmdUI* pCmdUI) 
{
	if (nDistortion == 124) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw126() 
{
  nDistortion = 126; 
	Attractor_3D();	
}

void CFlarium24View::OnUpdateDraw126(CCmdUI* pCmdUI) 
{
	if (nDistortion == 126) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw127() 
{
  nDistortion = 127; 
	Attractor_3D();	
}

void CFlarium24View::OnUpdateDraw127(CCmdUI* pCmdUI) 
{
	if (nDistortion == 127) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw128() 
{
  nDistortion = 128; 
	Attractor_3D();	
}

void CFlarium24View::OnUpdateDraw128(CCmdUI* pCmdUI) 
{
	if (nDistortion == 128) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw129() 
{
  nDistortion = 129; 
	Attractor_3D();	
}

void CFlarium24View::OnUpdateDraw129(CCmdUI* pCmdUI) 
{
	if (nDistortion == 129) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw130() 
{
  nDistortion = 130; 
	Attractor_3D();	
}

void CFlarium24View::OnUpdateDraw130(CCmdUI* pCmdUI) 
{
	if (nDistortion == 130) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw131() 
{
	ActiveTitle = "131) Lorenz Attractor ";
	nDistortion = 131;

	lx = 0.6; ly=0.6; lz=0.6;

	lx_save = lx;
	ly_save = ly;
	lz_save = lz;
            
	// lorenz variables
	lx=0.6, ly=0.6, lz=0.6;
	lh=0.01;
	frac = 8.0/3.0;

	for (n=0; n<latoof_count; n++)
	{
		if (n == 0)
			SetParams_3D();
		
		X = lxx = lx + lh*10*(ly-lx);
		Y = lyy = ly + lh*((-lx*lz) + 28*lx-ly);
		Z = lzz = lz + lh*(lx*ly - frac*lz);

		lx = lxx; ly=lyy; lz=lzz;
            
		SubDisplay_3D();	
	}

	lx = lx_save;
	ly = ly_save;
	lz = lz_save;
	
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw131(CCmdUI* pCmdUI) 
{
	if (nDistortion == 131) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

////////////////////////////////////////////
// Quaternions
//

void CFlarium24View::OnDrawQuaternionparameters() 
{
	CQparams qp;

	qp.m_qk1 = qk1;
	qp.m_qk2 = qk2;
	qp.m_qt1 = qt1;
	qp.m_qt2 = qt2;
	if (qp.DoModal() == IDOK)
	{
		qk1 = qp.m_qk1;
		qk2 = qp.m_qk2;
		qt1 = qp.m_qt1;
		qt2 = qp.m_qt2;

		GoDoFractal();
	}
}

void CFlarium24View::OnDraw133() // 74
{
	CQparams qp;

	qp.m_qk1 = qk1;
	qp.m_qk2 = qk2;
	qp.m_qt1 = qt1;
	qp.m_qt2 = qt2;
	if (qp.DoModal() == IDOK)
	{
		qk1 = qp.m_qk1;
		qk2 = qp.m_qk2;
		qt1 = qp.m_qt1;
		qt2 = qp.m_qt2;
	}
	else
	{
		return;
	}	

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	jul      = 0;
	jul_save = 1;

	nDistortion = 133;
	ActiveTitle = "133.) Quaternion Map [A1 and A3 Constant]";

	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw133(CCmdUI* pCmdUI) 
{
	if (nDistortion == 133) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw134() // 75
{
	CQparams qp;

	qp.m_qk1 = qk1;
	qp.m_qk2 = qk2;
	qp.m_qt1 = qt1;
	qp.m_qt2 = qt2;
	if (qp.DoModal() == IDOK)
	{
		qk1 = qp.m_qk1;
		qk2 = qp.m_qk2;
		qt1 = qp.m_qt1;
		qt2 = qp.m_qt2;
	}
	else
	{
		return;
	}	
		
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	jul      = 0;
	jul_save = 1;

	nDistortion = 134;
	ActiveTitle = "134.) Quaternion Map [A0 and A1 Constant]";

	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw134(CCmdUI* pCmdUI) 
{
	if (nDistortion == 134) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw135() // 76
{
	CQparams qp;

	qp.m_qk1 = qk1;
	qp.m_qk2 = qk2;
	qp.m_qt1 = qt1;
	qp.m_qt2 = qt2;
	if (qp.DoModal() == IDOK)
	{
		qk1 = qp.m_qk1;
		qk2 = qp.m_qk2;
		qt1 = qp.m_qt1;
		qt2 = qp.m_qt2;
	}
	else
	{
		return;
	}	

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	jul      = 0;
	jul_save = 1;

	nDistortion = 135;
	ActiveTitle = "135.) Quaternion Map [A0 and A2 Constant]";

	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw135(CCmdUI* pCmdUI) 
{
	if (nDistortion == 135) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw136() 
{
	CQparams qp;

	qp.m_qk1 = qk1;
	qp.m_qk2 = qk2;
	qp.m_qt1 = qt1;
	qp.m_qt2 = qt2;
	if (qp.DoModal() == IDOK)
	{
		qk1 = qp.m_qk1;
		qk2 = qp.m_qk2;
		qt1 = qp.m_qt1;
		qt2 = qp.m_qt2;
	}
	else
	{
		return;
	}	

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	jul      = 0;
	jul_save = 1;

	nDistortion = 136;
	ActiveTitle = "136.) Quaternion Map [A0 and A3 Constant]";

	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw136(CCmdUI* pCmdUI) 
{
	if (nDistortion == 136) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw137() // 78
{
	CQparams qp;

	qp.m_qk1 = qk1;
	qp.m_qk2 = qk2;
	qp.m_qt1 = qt1;
	qp.m_qt2 = qt2;
	if (qp.DoModal() == IDOK)
	{
		qk1 = qp.m_qk1;
		qk2 = qp.m_qk2;
		qt1 = qp.m_qt1;
		qt2 = qp.m_qt2;
	}
	else
	{
		return;
	}	

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	jul      = 0;
	jul_save = 1;

	nDistortion = 137;
	ActiveTitle = "137.) Quaternion Map [A1 and A2 Constant]";

	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw137(CCmdUI* pCmdUI) 
{
	if (nDistortion == 137) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw138() // 79
{
	CQparams qp;

	qp.m_qk1 = qk1;
	qp.m_qk2 = qk2;
	qp.m_qt1 = qt1;
	qp.m_qt2 = qt2;
	if (qp.DoModal() == IDOK)
	{
		qk1 = qp.m_qk1;
		qk2 = qp.m_qk2;
		qt1 = qp.m_qt1;
		qt2 = qp.m_qt2;
	}
	else
	{
		return;
	}	

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	jul      = 0;
	jul_save = 1;

	nDistortion = 138;
	ActiveTitle = "138.) Quaternion Map [A2 and A3 Constant]";

	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw138(CCmdUI* pCmdUI) 
{
	if (nDistortion == 138) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

///////////////////////////////////////////////
void CFlarium24View::OnDraw141() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "141) ";
	nDistortion = 141;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw141(CCmdUI* pCmdUI) 
{
	if (nDistortion == 141) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw142() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "142) ";
	nDistortion = 142;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw142(CCmdUI* pCmdUI) 
{
	if (nDistortion == 142) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw143() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "143) ";
	nDistortion = 143;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw143(CCmdUI* pCmdUI) 
{
	if (nDistortion == 143) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw144() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "144) ";
	nDistortion = 144;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw144(CCmdUI* pCmdUI) 
{
	if (nDistortion == 144) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw145() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "145) ";
	nDistortion = 145;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw145(CCmdUI* pCmdUI) 
{
	if (nDistortion == 145) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw146() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "146) ";
	nDistortion = 146;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw146(CCmdUI* pCmdUI) 
{
	if (nDistortion == 146) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw150() 
{
	if (nPostFractal != 130)
		AfxMessageBox("Previous formula should be 130");
	
	NMAX		= 128;
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "150) ";
	nDistortion = 150;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw150(CCmdUI* pCmdUI) 
{
	if (nDistortion == 150) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw151() 
{
	if (nPostFractal != 124)
		AfxMessageBox("Previous formula should be 124");

	NMAX		= 128;
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "151) ";
	nDistortion = 151;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw151(CCmdUI* pCmdUI) 
{
	if (nDistortion == 151) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw152() 
{
	if (nPostFractal != 126)
		AfxMessageBox("Previous formula should be 126");

	NMAX		= 128;
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "152) ";
	nDistortion = 152;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw152(CCmdUI* pCmdUI) 
{
	if (nDistortion == 152) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw153() 
{
	if (nPostFractal != 127)
		AfxMessageBox("Previous formula should be 127");

	NMAX		= 128;
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "153) ";
	nDistortion = 153;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw153(CCmdUI* pCmdUI) 
{
	if (nDistortion == 153) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw154() 
{
	if (nPostFractal != 128)
		AfxMessageBox("Previous formula should be 128");

	NMAX		= 128;
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "154) ";
	nDistortion = 154;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw154(CCmdUI* pCmdUI) 
{
	if (nDistortion == 154) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnDraw155() 
{
	if (nPostFractal != 129)
		AfxMessageBox("Previous formula should be 129");

	NMAX		= 128;
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "155) ";
	nDistortion = 155;
	GoDoFractal();
}

void CFlarium24View::OnUpdateDraw155(CCmdUI* pCmdUI) 
{
	if (nDistortion == 155) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}
