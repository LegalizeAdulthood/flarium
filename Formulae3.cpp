///////////////////////////////////////////
// Formulae3.cpp

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

//////////////////////////////////////////////////////////////////////
void CFlarium24View::Formulae3()
{  
  switch(nDistortion)
  {
		case 118: // Sharon19
			//if (jul == 0)
				//z=cmplx(0,0);

			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
				  z = (z*z*z*z*z).csin() + c;		// Sharon 19
					if (nFilter) Delta_z();
				}
			}
			else
			if (bFSet)
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN &&
					z.squares() < dBailout &&
					i++ < JMAX)
				{
					z2	= z;
				  z = (z*z*z*z*z).csin() + c;		// Sharon 19
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2	= z;
				  z = (z*z*z*z*z).csin() + c;		// Sharon 19
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 119: // Sharon20 Sharon's Butterfly
			//if (jul == 0)
				//z=cmplx(0,0);

			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z = (z+(z*z)/.192).csin() + c; // Sharon's Butterfly (20)		
					if (nFilter) Delta_z();
				}
			}
			else
			if (bFSet)
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN &&
					z.squares() < dBailout &&
					i++ < JMAX)
				{
					z2	= z;
					z = (z+(z*z)/.192).csin() + c; // Sharon's Butterfly (20)		
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2	= z;
					z = (z+(z*z)/.192).csin() + c; // Sharon's Butterfly (20)		
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 125: // Sharon21
			//if (jul == 0)
				//z=cmplx(0,0);

			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z = z+z*z*z/4 + c;						// Sharon21		
					if (nFilter) Delta_z();
				}
			}
			else
			if (bFSet)
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN &&
					z.squares() < dBailout &&
					i++ < JMAX)
				{
					z2	= z;
					z = z+z*z*z/4 + c;						// Sharon21		
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2	= z;
					z = z+z*z*z/4 + c;						// Sharon21		
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		///////////////

		case 133:			// Quaternion Map [A1 and A3 Constant]
			rmu0 = cx;
			rmu1 = cy;
			rmu2 = qk1;
			rmu3 = qk2;

			x = x;
			u = y;
			y = qt1;
			w = qt2;

			for (i = 0; i <= JMAX && x*x+y*y+u*u+w*w < dBailout ; i++)
  		{
				temp = x+x;
				x = x*x-y*y-u*u-w*w+rmu0;
				y = temp*y+rmu1;
				u = temp*u+rmu2;
				w = temp*w+rmu3;
				z = cmplx(x, u);
				if (nFilter) Delta_z();
			}
			z = cmplx(x, u);
			if (nFilter) Filter_Complete();

			break;

		case 134:		// Quaternion Map [A0 and A1 Constant]
			rmu0 = cx;
			rmu1 = cy;
			rmu2 = qk1;
			rmu3 = qk2;

			u = x;
			w = y;
			x = qt1;
			y = qt2;

			for (i = 0; i <= JMAX && x*x+y*y+u*u+w*w < dBailout ; i++)
  		{
				temp = x+x;
				x = x*x-y*y-u*u-w*w+rmu0;
				y = temp*y+rmu1;
				u = temp*u+rmu2;
				w = temp*w+rmu3;
				z = cmplx(u, w);
				if (nFilter) Delta_z();
			}
			z = cmplx(u, w);
			if (nFilter) Filter_Complete();
		
			break;

		case 135:		// Quaternion Map [A0 and A2 Constant]
			rmu0 = cx;
			rmu1 = cy;
			rmu2 = qk1;
			rmu3 = qk2;

			y = x;
			w = y;
			x = qt1;
			u = qt2;

			for (i = 0; i <= JMAX && x*x+y*y+u*u+w*w < dBailout ; i++)
  		{
				temp = x+x;
				x = x*x-y*y-u*u-w*w+rmu0;
				y = temp*y+rmu1;
				u = temp*u+rmu2;
				w = temp*w+rmu3;
				z = cmplx(y, w);
				if (nFilter) Delta_z();
			}
			z = cmplx(y, w);
			if (nFilter) Filter_Complete();

			break;

		case 136:		// Quaternion Map [A0 and A3 Constant]
			rmu0 = cx;
			rmu1 = cy;
			rmu2 = qk1;
			rmu3 = qk2;

			y = y;
			u = x;
			x = qt1;
			w = qt2;

			for (i = 0; i <= JMAX && x*x+y*y+u*u+w*w < dBailout ; i++)
  		{
				temp = x+x;
				x = x*x-y*y-u*u-w*w+rmu0;
				y = temp*y+rmu1;
				u = temp*u+rmu2;
				w = temp*w+rmu3;
				z = cmplx(u, y);
				if (nFilter) Delta_z();
			}
			z = cmplx(u, y);
			if (nFilter) Filter_Complete();

			break;

		case 137:		// Quaternion Map [A1 and A2 Constant]
			rmu0 = cx;
			rmu1 = cy;
			rmu2 = qk1;
			rmu3 = qk2;

			x = x;
			w = y;
			y = qt1;
			u = qt2;

			for (i = 0; i <= JMAX && x*x+y*y+u*u+w*w < dBailout ; i++)
  		{
				temp = x+x;
				x = x*x-y*y-u*u-w*w+rmu0;
				y = temp*y+rmu1;
				u = temp*u+rmu2;
				w = temp*w+rmu3;
				z = cmplx(x, w);
				if (nFilter) Delta_z();
			}
			z = cmplx(x, w);
			if (nFilter) Filter_Complete();

			break;		

		case 138:		// Quaternion Map [A2 and A3 Constant]
			rmu0 = cx;
			rmu1 = cy;
			rmu2 = qk1;
			rmu3 = qk2;

			x = x;
			y = y;
			u = qt1;
			w = qt2;

			for (i = 0; i <= JMAX && x*x+y*y+u*u+w*w < dBailout ; i++)
  		{
				temp = x+x;
				x = x*x-y*y-u*u-w*w+rmu0;
				y = temp*y+rmu1;
				u = temp*u+rmu2;
				w = temp*w+rmu3;
				z = cmplx(x, y);
				if (nFilter) Delta_z();
			}
			z = cmplx(x, y);
			if (nFilter) Filter_Complete();

			break;

    case 140: // Unique Formuale  
      //int i_try = 0;      
      //ParsedExpr = ParseExpression( strFormulae, i_try );

      if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
          z = ParsedExpr->Do();    
					if (nFilter) Delta_z();
				}
			}
			else
			if (bFSet)
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN &&
					z.squares() < dBailout &&
					i++ < JMAX)
				{
					z2	= z;
          z = ParsedExpr->Do();    
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;
          z = ParsedExpr->Do();              
          if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 141: // 100
			if (jul == 0)
			{
				z.set_real(cx);
				z.set_imag(cy);
			}
			for (i = 0; i < JMAX && z.squares() < dBailout ; i++)
			{
				//z = c*z*(cn-z);

				z2 = z;
				z = z.csin() - c;
				c = (2/(z2*100));
				
				if (nFilter) Delta_z();
			}
			if (nFilter) Filter_Complete();
			break;

		case 142: // 148 Quartet
			z2 = z;
			for (i = 0; i < JMAX && z.squares() < dBailout ; i++)
			{
				z2	= z;
				z		= z*z*z*z+c;
				c		= z2;
				if (nFilter) Delta_z();
			}
			if (nFilter) Filter_Complete();
			break;

		case 143: // 153
      t=c;
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z1=z;
					z=z.csin()+z*z*z*z+c;
			    c=t+z1-z;
					if (nFilter) Delta_z();
				}
			}
			else
			if (bFSet)
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN &&
					z.squares() < dBailout &&
					i++ < JMAX)
				{
					z2	= z;
					z1=z;
					z=z.csin()+z*z*z*z+c;
			    c=t+z1-z;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2	= z;
					z1=z;
					z=z.csin()+z*z*z*z+c;
			    c=t+z1-z;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 144: // 156
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z1=z;
		      z=z*z*z*z/(1+z)+c;
			    c=z1;
					if (nFilter) Delta_z();
				}
			}
			else
			if (bFSet)
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN &&
					z.squares() < dBailout &&
					i++ < JMAX)
				{
					z2	= z;
					z1=z;
		      z=z*z*z*z/(1+z)+c;
			    c=z1;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2	= z;
					z1=z;
		      z=z*z*z*z/(1+z)+c;
			    c=z1;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 145: // 164
			// Generalized Mandelbrot 101
			z1 = z;
			//z2 = cmplx(rorder_r, rorder_i);
			z2 = cmplx(2, 0);
	    for (i = 0; i < JMAX && z.squares() < dBailout ; i++)
			{
				z=(z^z2) + c;
				if (nFilter) Delta_z();
			}

			if (i >= JMAX)
			{
				// Inside
				z = z1;
				z2 = cmplx(rorder_r, rorder_i);
				b_MAX = TRUE;
				i = 0;
				jrw=0;
				JMAX=NMAX-2;
				while (i++ < JMAX)
				{
					//z=z*z + c;
					z=(z^z2) + c;

					if (z.real() < 0)				z.set_real( -(log10(fabs(z.real()))));
					else if (z.real() > 0)	z.set_real(  log10(fabs(z.real())));
					else z.set_real(0);
					
					if (z.imag() < 0)				z.set_imag( -(log10(fabs(z.imag()))));
					else if (z.imag() > 0)	z.set_imag(  log10(fabs(z.imag())));
					else z.set_imag(0);
					
					r = z.squares();

					if (i == 0) { k1 = 1; rz = r; }
					else if (i == 1)
					{
						if (r > rz) rzflag = 1;
						else rzflag = -1;
						rz = r;
					}
					else
					if (r > rz && rzflag != 1)
					{
						jrw+=nFF;
						rzflag = 1;
					}
					else 
					if (r < rz && rzflag != -1)
					{
						jrw+=nFF;
						rzflag = -1;
					}
					rz = r;
					if (nFilter) Delta_z();
				}
				i = jrw;
				if (nFilter) Filter_Complete();
				//i = jrw % NMAX;				
			}								
			else
				if (nFilter) Filter_Complete();
			break;

		case 146: // Sharon19, unknown method
			//if (jul == 0)
				//z=cmplx(0,0);

			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
				  z = (z*z*z*z*z).unknown() + c;		// Sharon 19
					if (nFilter) Delta_z();
				}
			}
			else
			if (bFSet)
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN &&
					z.squares() < dBailout &&
					i++ < JMAX)
				{
					z2	= z;
				  z = (z*z*z*z*z).unknown() + c;		// Sharon 19
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2	= z;
				  z = (z*z*z*z*z).unknown() + c;		// Sharon 19
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

  }
}
