//////////////////////////////////
// Equation
//

#include "stdafx.h"
#include "Flarium24.h"

#include "Flarium24Doc.h"
#include "Flarium24View.h"
#include "mainfrm.h"
#include <math.h>
#include "external.h"
#include "bgcolor.h"

void CFlarium24View::Equation()
{
	i = px;
	return;

	z2 = cmplx(42,42);
	while ((z-z2).abs() > dMIN && i++ < JMAX) 
	//	&& (fabs(z.real()) > dStrands && fabs(z.imag()) > dStrands))
	//for (i = 0; i < JMAX && 
		//fabs(z.real()*z.imag()*2) < dBailout; i++)
	{
		z = z*z+c;
		if (nFilter) Delta_z();
	}
	if (nFilter) Filter_Complete();

}

void CFlarium24View::Equation1()
{
	//z+=1;
	//z2 = cmplx(42,42);
	//while ((z-z2).sum_of_sqrs() > dMIN && i++ < JMAX)
  for (i = 0; i < JMAX && z.abs() < dBailout ; i++)
	{
		if (nFilter) Delta_z();
	}
	if (nFilter) Filter_Complete();			
}

void CFlarium24View::Equation150()
{
	X = c.real();
	Y = c.imag();
	Z = .001;

	for(i=0; i < NMAX && z.squares() < dBailout; i++)
	{
		xnew	=  .001	+ af[1]*X*X + af[2]*Y	  + af[3]*X		+ af[4]*Z;
		ynew	=  .001	+ af[5]*Y*Y	+	af[6]*Y		+ af[7]*X		+ af[8]*Z;
		Z   	=  .001	+ af[9]*Z*Z	+	af[10]*Y	+ af[11]*X	+ af[12]*Z;
			
		X = xnew;
		Y = ynew;

		z = cmplx (X, Y);
		if (nFilter) Delta_z();
	}

	if (nFilter) Filter_Complete();
}

void CFlarium24View::Equation151() // (124) 
{
	X = c.real();
	Y = c.imag();
	Z = .001;

	//z2 = cmplx(42, 42);
	//i = 0;
	while(z.squares() < dBailout && i++ < NMAX)
	{
		xnew	= .0001 + af[1]*X  + af[4]*Y + af[7]*Z + X*Y*Z;
		ynew	= .0001 + af[2]*X  + af[5]*Y + af[8]*Z + X*Y*Z;
		Z   	= .0001 + af[3]*X  + af[6]*Y + af[9]*Z + X*Y*Z;      
		X = xnew;
		Y = ynew;

		z = cmplx (X, Y);
		if (nFilter) Delta_z();
	}

	if (nFilter) Filter_Complete();
}

void CFlarium24View::Equation152() // (126) 3D Quadratic from J. C. Sprott
{
	X = c.real();
	Y = c.imag();
	Z = .001;

	for(i=0; i < NMAX && z.squares() < dBailout; i++)
	{
		xnew = af[1] + af[2]*X + af[3]*X*X + af[4]*X*Y + af[5]*X*Z + af[6]*Y
				+ af[7]*Y*Y + af[8]*Y*Z + af[9]*Z + af[10]*Z*Z;
			
		ynew = af[11] + af[12]*X + af[13]*X*X + af[14]*X*Y + af[15]*X*Z + af[16]*Y 
				+ af[17]*Y*Y + af[18]*Y*Z + af[19]*Z + af[20]*Z*Z;

		Z = af[21] + af[22]*X + af[23]*X*X + af[24]*X*Y + af[25]*X*Z + af[26]*Y 
				+ af[27]*Y*Y + af[28]*Y*Z + af[29]*Z + af[30]*Z*Z;
			
		X = xnew;
		Y = ynew;
		z = cmplx (X, Y);
		if (nFilter) Delta_z();
	}

	if (nFilter) Filter_Complete();
}

void CFlarium24View::Equation153() // 127
{
	X = c.real();
	Y = c.imag();
	Z = .001;

	for(i=0; i < NMAX && z.squares() < dBailout; i++)
	{
		xnew	= .001 + af[1]*X + af[2]*Y + af[3]*Z + af[4]*(X*X+Y*Y+Z*Z);  // 127
		ynew	= .001 + af[5]*X + af[6]*Y + af[7]*Z + af[8]*(X*X+Y*Y+Z*Z);
 		Z			= .001 + af[9]*X + af[10]*Y + af[11]*Z + af[12]*(X*X+Y*Y+Z*Z);			

		X = xnew;
		Y = ynew;

		z = cmplx (X, Y);
		if (nFilter) Delta_z();
	}

	if (nFilter) Filter_Complete();
}

void CFlarium24View::Equation154() // 128
{
	X = c.real();
	Y = c.imag();
	Z = .001;

	for(i=0; i < NMAX && z.squares() < dBailout; i++)
	{
		xnew	= af[1] + af[2]*X*Y		+ af[3]*Y*Z		+ af[4]*Z*X;  // 128
		ynew	= af[5] + af[6]*X*Y		+ af[7]*Y*Z		+ af[8]*Z*X;
		Z			= af[9] + af[10]*X*Y	+ af[11]*Y*Z	+ af[12]*Z*X;			

		X = xnew;
		Y = ynew;

		z = cmplx (X, Y);
		if (nFilter) Delta_z();
	}

	if (nFilter) Filter_Complete();
}

void CFlarium24View::Equation155()  // 129
{
	X = c.real();
	Y = c.imag();
	Z = .001;

	for(i=0; i < NMAX && z.squares() < dBailout; i++)
	{
		xnew	= .001 + sin(af[1]*X)		+ af[2]*sin(af[3]*Y)		+ af[4]*sin(af[5]*Z);
		ynew	= .001 + sin(af[6]*X)		+ af[7]*sin(af[8]*Y)		+ af[9]*sin(af[10]*Z);
		Z   	= .001 + sin(af[11]*X)	+ af[12]*sin(af[13]*Y)	+ af[14]*sin(af[15]*Z);

		X = xnew;
		Y = ynew;

		z = cmplx (X, Y);
		if (nFilter) Delta_z();
	}

	if (nFilter) Filter_Complete();
}

void CFlarium24View::PlotDotAt()
{
  CFlarium24Doc* pDoc = GetDocument();
	if (x < CRMAX && x > CRMIN && y < CIMAX && y > CIMIN)
	{
		nx = (int) ((x-CRMIN)*xinc);
		ny = (int) ((y-CIMIN)*yinc);

		if (nx >= 0 &&
				nx <  dim.cx &&
				ny >= 0 &&
				ny < dim.cy)
			lpDots[nx + ny*dim.cx] += (int)nBay100; 
	}
}

void CFlarium24View::PlotDotAt_3D()
{
  CFlarium24Doc* pDoc = GetDocument();
	switch (nDimension)
	{
		case 0:  // XY dimension		
			if (X < CRMAX && X > CRMIN && Y < CIMAX && Y > CIMIN)
			{
				nx = (int) ((X-CRMIN)*xinc);
				ny = (int) ((Y-CIMIN)*yinc);

				if (nx >= 0 &&
					nx <  dim.cx &&
					ny >= 0 &&
					ny < dim.cy)
				{										
					if (lpDots[nx + ny*dim.cx] < (int) (Z*300*nBay100) ||
						lpDots[nx + ny*dim.cx] == 0)
					{
						if (nDistortion == 131) // Lorenz
							lpDots[nx + ny*dim.cx] = (int) (Z*10*nBay100); 
						else
							lpDots[nx + ny*dim.cx] = (int) (Z*300*nBay100); 
					}
				}
			}
			break;

		case 1:  // XZ dimension		
			if (X < CRMAX && X > CRMIN && Z < CIMAX && Z > CIMIN)
			{
				nx = (int) ((X-CRMIN)*xinc);
				ny = (int) ((Z-CIMIN)*yinc);

				if (nx >= 0 &&
					nx <  dim.cx &&
					ny >= 0 &&
					ny < dim.cy)

				{
					if (lpDots[nx + ny*dim.cx] < (int) (Y*300*nBay100) ||
						lpDots[nx + ny*dim.cx] == 0)
					{
						if (nDistortion == 131) // Lorenz
							lpDots[nx + ny*dim.cx] = (int) (Y*10*nBay100); 
						else
							lpDots[nx + ny*dim.cx] = (int) (Y*300*nBay100); 
					}
				}
			}
			break;
	
		case 2:  // YZ dimension		
			if (Y < CRMAX && Y > CRMIN && Z < CIMAX && Z > CIMIN)
			{
				nx = (int) ((Y-CRMIN)*xinc);
				ny = (int) ((Z-CIMIN)*yinc);

				if (nx >= 0 &&
					nx <  dim.cx &&
					ny >= 0 &&
					ny < dim.cy)

				{
					if (lpDots[nx + ny*dim.cx] < (int) (X*300*nBay100) ||
						lpDots[nx + ny*dim.cx] == 0)
					{
						if (nDistortion == 131) // Lorenz
							lpDots[nx + ny*dim.cx] = (int) (X*10*nBay100); 
						else
							lpDots[nx + ny*dim.cx] = (int) (X*300*nBay100); 
					}
				}
			}	
			break;
	}
}

void CFlarium24View::Latoocarfian()
{
	::SetCursor(mWait);
	OnViewBackground();
      			
	x_save = mx;
  y_save = my;

	for (ri=0; ri<latoof_count; ri++)
	{
		AdvanceXY();
				
		mx_save = mxx;
		my_save = myy;

		x = mxx; 
		y = myy;
		PlotDotAt();
				
		mx = mxx;
		my = myy;
	}

  mx = x_save;
  my = y_save;

	Complete_the_Dots();
	Terminate();
}

void CFlarium24View::AdvanceXY()
{
	switch (nDistortion)
	{
		case 120: // Latoocarfian
			mxx = sin(my*mb) + mc*sin(mx*mb);
			myy = sin(mx*ma) + md*sin(my*ma);
			break;

		case 121:	// Latoocarfian Mutation Alpha
			mxx = sin(my*mb) + sin(mx*mb)*sin(mx*mb) 
					+ sin(mx*mb)*sin(mx*mb)*sin(mx*mb);
			
			myy = sin(mx*ma) + sin(my*ma)*sin(my*ma) 
				  + sin(my*mc)*sin(my*mc)*sin(my*mc);
			break;

		case 122:	// Chaotic Iterated Map
			xnew = af[1] + x * (af[2] + af[3] * x + af[4] * y) + y * (af[5] + af[6] * y);
			y = af[7] + x * (af[8] + af[9] * x + af[10] * y) + y * (af[11] + af[12] * y);
			x = xnew;

			//xnew = af[1] + af[2]*x + af[3]*x*x + af[4] *x*y + af[5] *y + af[6]*y*y;
			//y		 = af[7] + af[8]*x + af[9]*x*x + af[10]*x*y + af[11]*y + af[12]*y*y;
			//x		 = xnew;			
			
			break;	

		case 123:  // Iterated Function System
			xnew = af[1 + j] * x + af[2 + j] * y + af[5 + j];
			y = af[3 + j] * x + af[4 + j] * y + af[6 + j];
			x = xnew;
			break;

		case 124: 
			/////////////////////////////////////////////////////////////////////
			// 3D Quadratic from J. C. Sprott
			//Xn+1 = a1 + a2Xn + a3Xn2 + a4XnYn + a5XnZn + a6Yn 
			//+ a7Yn2 + a8YnZn + a9Zn + a10Zn2 

			//Yn+1 = a11 + a12Xn + a13Xn2 + a14XnYn + a15XnZn + a16Yn 
			//+ a17Yn2 + a18YnZn + a19Zn + a20Zn2 

			//Zn+1 = a21 + a22Xn + a23Xn2 + a24XnYn + a25XnZn + a26Yn 
			//+ a27Yn2 + a28YnZn + a29Zn + a30Zn2 

//			xnew = af[1] + af[2]*X + af[3]*X*X + af[4]*X*Y + af[5]*X*Z + af[6]*Y
//				+ af[7]*Y*Y + af[8]*Y*Z + af[9]*Z + af[10]*Z*Z;
//			
//			ynew = af[11] + af[12]*X + af[13]*X*X + af[14]*X*Y + af[15]*X*Z + af[16]*Y 
//				+ af[17]*Y*Y + af[18]*Y*Z + af[19]*Z + af[20]*Z*Z;
//
//			Z = af[21] + af[22]*X + af[23]*X*X + af[24]*X*Y + af[25]*X*Z + af[26]*Y 
//				+ af[27]*Y*Y + af[28]*Y*Z + af[29]*Z + af[30]*Z*Z;
//			
//			X = xnew;
//			Y = ynew;
			

//			xnew	= af[1] + af[2]*X + af[3]*Y + af[4]*Z;  // 127
//			ynew	= af[5] + af[6]*X + af[7]*Y + af[8]*Z;
// 			Z			= af[9] + af[10]*X + af[11]*Y + af[12]*Z;			
			

//			xnew	= af[1] + af[2]*X*Y		+ af[3]*Y*Z		+ af[4]*Z*X;  // 128
//			ynew	= af[5] + af[6]*X*Y		+ af[7]*Y*Z		+ af[8]*Z*X;
//			Z			= af[9] + af[10]*X*Y	+ af[11]*Y*Z	+ af[12]*Z*X;			
			

			//mxx = sin(my*mb) + mc*sin(mx*mb);
			//myy = sin(mx*ma) + md*sin(my*ma);

//			xnew	= cos(af[1]*X) + af[2]*cos(af[3]*Y) + af[4]*cos(af[5]*Z);		// 129
//			ynew	= cos(af[6]*X) + af[7]*cos(af[8]*Y) + af[9]*cos(af[10]*Z);
//			Z   	= cos(af[11]*X) + af[12]*cos(af[13]*Y) + af[14]*cos(af[15]*Z);
			
//			xnew	= af[1]*X		+ af[2]		+ af[3]*Y		+ af[4]*X		+ af[5]*Z;   // 130
//			ynew	= af[6]*Y		+ af[7]		+	af[8]*Y		+ af[9]*X		+ af[10]*Z;
//			Z   	= af[11]*Z	+ af[12]	+	af[13]*Y	+ af[14]*X	+ af[15]*Z;
			
//			xnew	= af[1]*X*X		+ af[2]		+ af[3]*Y		+ af[4]*X		+ af[5]*Z;	// 130
//			ynew	= af[6]*Y*Y		+ af[7]		+	af[8]*Y		+ af[9]*X		+ af[10]*Z;
//			Z   	= af[11]*Z*Z	+ af[12]	+	af[13]*Y	+ af[14]*X	+ af[15]*Z;

			xnew	= .0001 + af[1]*X  + af[4]*Y + af[7]*Z + X*Y*Z;
			ynew	= .0001 + af[2]*X  + af[5]*Y + af[8]*Z + X*Y*Z;
			Z   	= .0001 + af[3]*X  + af[6]*Y + af[9]*Z + X*Y*Z;      

//			xnew	= af[1+j] + af[2+j]*X  + af[3+j]*Y + af[4+j]*Z;
//			ynew	= af[5+j] + af[6+j]*X  + af[7+j]*Y + af[8+j]*Z;
//			Z   	= af[9+j] + af[10+j]*X  + af[11+j]*Y + af[12+j]*Z;      

//			xnew = af[1 + j]*X + af[2 + j]* Y + af[5 + j] + Z;
//			ynew = af[3 + j]*X + af[4 + j]* Y + af[6 + j] + Z;
//			Z    = 

			X = xnew;
			Y = ynew;
						
			break;

		case 126:
			/////////////////////////////////////////////////////////////////////
			// 3D Quadratic from J. C. Sprott
			//Xn+1 = a1 + a2Xn + a3Xn2 + a4XnYn + a5XnZn + a6Yn 
			//+ a7Yn2 + a8YnZn + a9Zn + a10Zn2 

			//Yn+1 = a11 + a12Xn + a13Xn2 + a14XnYn + a15XnZn + a16Yn 
			//+ a17Yn2 + a18YnZn + a19Zn + a20Zn2 

			//Zn+1 = a21 + a22Xn + a23Xn2 + a24XnYn + a25XnZn + a26Yn 
			//+ a27Yn2 + a28YnZn + a29Zn + a30Zn2 

			xnew = af[1] + af[2]*X + af[3]*X*X + af[4]*X*Y + af[5]*X*Z + af[6]*Y
				+ af[7]*Y*Y + af[8]*Y*Z + af[9]*Z + af[10]*Z*Z;
			
			ynew = af[11] + af[12]*X + af[13]*X*X + af[14]*X*Y + af[15]*X*Z + af[16]*Y 
				+ af[17]*Y*Y + af[18]*Y*Z + af[19]*Z + af[20]*Z*Z;

			Z = af[21] + af[22]*X + af[23]*X*X + af[24]*X*Y + af[25]*X*Z + af[26]*Y 
				+ af[27]*Y*Y + af[28]*Y*Z + af[29]*Z + af[30]*Z*Z;
			
			X = xnew;
			Y = ynew;

			break;

		case 127:
			xnew	= .001 + af[1]*X + af[2]*Y + af[3]*Z + af[4]*(X*X+Y*Y+Z*Z);  // 127
			ynew	= .001 + af[5]*X + af[6]*Y + af[7]*Z + af[8]*(X*X+Y*Y+Z*Z);
 			Z			= .001 + af[9]*X + af[10]*Y + af[11]*Z + af[12]*(X*X+Y*Y+Z*Z);			

			X = xnew;
			Y = ynew;

			break;

		case 128:
			xnew	= af[1] + af[2]*X*Y		+ af[3]*Y*Z		+ af[4]*Z*X;  // 128
			ynew	= af[5] + af[6]*X*Y		+ af[7]*Y*Z		+ af[8]*Z*X;
			Z			= af[9] + af[10]*X*Y	+ af[11]*Y*Z	+ af[12]*Z*X;			

			X = xnew;
			Y = ynew;

			break;

		case 129:
			//mxx = sin(my*mb) + mc*sin(mx*mb);
			//myy = sin(mx*ma) + md*sin(my*ma);

			xnew	= .001 + sin(af[1]*X)		+ af[2]*sin(af[3]*Y)		+ af[4]*sin(af[5]*Z);
			ynew	= .001 + sin(af[6]*X)		+ af[7]*sin(af[8]*Y)		+ af[9]*sin(af[10]*Z);
			Z   	= .001 + sin(af[11]*X)	+ af[12]*sin(af[13]*Y)	+ af[14]*sin(af[15]*Z);

			X = xnew;
			Y = ynew;

			break;

		case 130:
			xnew	= .001 + af[1]*X*X  + af[2]*Y		+ af[3]*X		+ af[4]*Z;
			ynew	= .001 + af[5]*Y*Y	+	af[6]*Y		+ af[7]*X		+ af[8]*Z;
			Z   	= .001 + af[9]*Z*Z	+	af[10]*Y	+ af[11]*X	+ af[12]*Z;
			
			X = xnew;
			Y = ynew;

			break;

		default:
			break;
	}	
}

void CFlarium24View::LyanpunovTest()
{			
	Lsum = 0;
	mxe = mx + 0.000001;
	mye = my;
      			
	x_save = mx;
  y_save = my;

	for (ri=0; ri<4000; ri++)
	{
		AdvanceXY();

		// Re-iterate for computing Lyanpunov exponent

		mx_save = mxx;
		my_save = myy;

		mx = mxe;
		my = mye;

		AdvanceXY();
		
		dLx = mxx - mx_save;
		dLy = myy - my_save;

		dL2 = dLx*dLx + dLy*dLy;
		df = 1e12*dL2;
		rs = 1/sqrt(df);

		mxe = mx_save + rs*(mxx - mx_save);
		mye = my_save + rs*(myy - my_save);

		mxx = mx_save;
		myy = my_save;

		Lsum = Lsum + log(df);

		L = 0.721347*Lsum/ri;

		mx = mxx;
		my = myy;
	}
  
	mx = x_save;
  my = y_save;
}

void CFlarium24View::StandardLatoof()
{
	::SetCursor(mWait);

	// ( -3 < a,b < 3 ),  (0.5 < c,d < 1.5)
	mx = 0.1;
	my = 0.1;
	
	int retries = 130;
	L = 0;
  	
	while ((L < .45 || L > .55) && retries-- > 0)
	{
		ma = rand() % 6000;
		ma = ma - 3000;
		ma = ma / 1000;
  	
		mb = rand() % 6000;
		mb = mb - 3000;
		mb = mb / 1000;
  	
		mc = rand() % 2000;
		mc = mc - 500;
		mc = mc / 1000;
  	
		md = rand() % 2000;
		md = md - 500;
		md = md / 1000;

		LyanpunovTest();
	}

	if (retries <= 0)
	{
		sprintf(cstr,"Failed Lyanpunov Test, L = %f, tries = %d",
			L, 1000 - retries);
		AfxMessageBox(cstr);
	}
			
  //bNewView = FALSE;
	GoDoFractal();
}

void CFlarium24View::OnViewBackground() 
{
  CFlarium24Doc* pDoc = GetDocument();

	//////////////////////////////////////////////////
	if (hdots != NULL)
	{
		::GlobalUnlock((HGLOBAL) hdots);
		::GlobalFree((HGLOBAL) hdots);
		hdots = NULL;
	}

	CWaitCursor cursor;	// this will automatically display a wait cursor
	hdots = (HGLOBAL) ::GlobalAlloc(GHND, dim.cx * dim.cy * 2);
	if (hdots == 0)
	{
		AfxMessageBox("Error Allocating Global Memory for filter 69");
		return;
	}

	// Get a pointer to the Dots memory 
	lpDots = (PUSHORT) ::GlobalLock((HGLOBAL) hdots);

}

void CFlarium24View::Complete_the_Dots()
{
  CFlarium24Doc* pDoc = GetDocument();

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

			// Generalized Coloring Method
			if (i == 0)
			{
				red = nRedBack;
				grn = nGrnBack;
				blu = nBluBack;
			}
			else
			{	
				red = i*nRed+nRedStart+min;
				grn = i*nGrn+nGrnStart+min;
				blu = i*nBlu+nBluStart+min;
			}
	
			Apply_The_Color();
									
			//if (!::WriteBit(pDoc->hdib, pDoc->m_sizeDoc,
				//		px, py, (DWORD)RGB(red, grn, blu)))

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

void CFlarium24View::SetParams()
{
	// Set Params
	x = 0;
	y = 0;
	L = 0;
	
	// Set 12 random values 
	for (i=1; i<=30; i++)
	{
		af[i] = rand() % 3000;
		af[i] = af[i] - 1500;
		af[i] = af[i] / 1000;
	}
}

void CFlarium24View::SetParams_3D()
{
	// Set Params
	X = 0.001;
	Y = 0.001;
	Z = 0.001;
	L = 0;
	
	// Set 30 random values 
	for (i=1; i<=30; i++)
	{
		af[i] = rand() % 3000;
		af[i] = af[i] - 1500;
		af[i] = af[i] / 1000;
	}
	
	Affine_Data_Update();
}

void CFlarium24View::SubDisplay()
{
	if (n == 1)
	{
		CRMIN = -.001; 
		CIMIN = CRMIN;
		CRMAX = -CRMIN;
		CIMAX = -CIMIN;
	}
	else
	if (n > 1 && n < 100) ;
	// Do Nothing
	else
	if (n >= 100 && n < 1000)
	{
		if (x < CRMIN) CRMIN = x;
		if (x > CRMAX) CRMAX = x;
		if (y < CIMIN) CIMIN = y;
		if (y > CIMAX) CIMAX = y;
	}
	else
	//if (n == 1000)
	{
		// Do Nothing
	}
}

void CFlarium24View::SubDisplay_3D()
{
	if (n == 1)
	{
		CRMIN = -.000001; 
		CIMIN = CRMIN;
		CRMAX = -CRMIN;
		CIMAX = -CIMIN;
	}
	else
	if (n > 1 && n < 100) ;
	// Do Nothing
	else
	if (n >= 100)
	{
		switch (nDimension)		
		{		
			case 0: // XY Dimension
				if (X < CRMIN) CRMIN = X;
				if (X > CRMAX) CRMAX = X;
				if (Y < CIMIN) CIMIN = Y;
				if (Y > CIMAX) CIMAX = Y;
			break;

			case 1: // XZ Dimension
				if (X < CRMIN) CRMIN = X;
				if (X > CRMAX) CRMAX = X;
				if (Z < CIMIN) CIMIN = Z;
				if (Z > CIMAX) CIMAX = Z;
				break;

			case 2: // YZ Dimension
				if (Y < CRMIN) CRMIN = Y;
				if (Y > CRMAX) CRMAX = Y;
				if (Z < CIMIN) CIMIN = Z;
				if (Z > CIMAX) CIMAX = Z;
				break;
		}
	}
}

void CFlarium24View::TestSolution()
{
	GetLyanpunovExponent();
	if (L == 0 && n > 2) n = 0;
	if (n > 100 && L < .1) n = 0;		// Solution is not chaotic
	if (x + y > 1000000) n = 0;       // Solution is unbounded
}

void CFlarium24View::TestSolution_1()
{
	GetLyanpunovExponent();
	if (L == 0 && n > 2) n = 0;
	if (n > 100 && L > -.1) n = 0;		// Solution is not chaotic
	if (n > 100 && L < -.9) n = 0;		// Solution is not chaotic
	if (x + y > 1000000) n = 0;       // Solution is unbounded
}

void CFlarium24View::GetLyanpunovExponent()
{			
	if (n == 1)
	{
		// Initialize variables
		Lsum = 0;
		xe = x + 0.000001;
		ye = 0;
	}

	x_save = x;
	y_save = y;
	x = xe;
	y = ye;

	AdvanceXY();  // Re-Iterate equations
		
	dx = x - x_save;
	dy = y - y_save;

	if (dx == 0 && dy == 0)
	{
		L = 0;
	}
	else
	{	
	
		d2 = dx*dx + dy*dy;
		df = 100000000000*d2;
		rs = 1/sqrt(df);
		xe = x_save + rs*(x - x_save);
		x  = x_save;
		ye = y_save + rs*(y - y_save);
		y  = y_save;
		Lsum = Lsum + log(df);
		L		= 0.721348*Lsum/(double) n;
	}
}

void CFlarium24View::TestSolution_3D()
{
	GetLyanpunovExponent_3D();
	if (L == 0 && n > 2) n = 0;

//	if (n > 100 && L < .1) n = 0;		// Solution is not chaotic

	if (n > 100 && L < .03) n = 0;		// Solution is not chaotic
	if (n > 100 && L > 1) n = 0;		// Solution is not chaotic

	//if (n > 100 && L > -.1) n = 0;		// Solution is not chaotic
	//if (n > 100 && L < -.9) n = 0;		// Solution is not chaotic
	if (X + Y + Z > 1000000) n = 0;       // Solution is unbounded
}

void CFlarium24View::GetLyanpunovExponent_3D()
{			
	if (n == 1)
	{
		// Initialize variables
		Lsum = 0;
		xe = 0.001;
		ye = 0.001;
		ze = 0.001;
	}

	x_save = X;
	y_save = Y;
	z_save = Z;

	X = xe;
	Y = ye;
	Z = ze;

	AdvanceXY();  // Re-Iterate equations
		
	dx = X - x_save;
	dy = Y - y_save;
	dz = Z - z_save;

	if (dx == 0 && dy == 0 && dz == 0)
	{
		L = 0;
	}
	else
	{
		d3 = dx*dx + dy*dy + dz*dz;
		df = 100000000000*d3;
		rs = 1/sqrt(df);
		xe = x_save + rs*(X - x_save);
		X  = x_save;
		ye = y_save + rs*(Y - y_save);
		Y  = y_save;
		ze = z_save + rs*(Z - z_save);
		Z  = z_save;
		Lsum = Lsum + log(df);
		L		= 0.721348*Lsum/(double) n;
	}
}

void CFlarium24View::OnImageBackgroundcolor() 
{
	CBGColor bg;
	
	bg.m_RedBack		= nRedBack;
	bg.m_GreenBack	= nGrnBack;
	bg.m_BlueBack		= nBluBack;

	if (bg.DoModal() == IDOK)
	{
		nRedBack	= bg.m_RedBack; 		
		nGrnBack	= bg.m_GreenBack;
		nBluBack	= bg.m_BlueBack;	
		
		GoDoFractal();
	}
}

