///////////////////////////////////////////
// Formulae.cpp

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
void CFlarium24View::TestEquations()
{
  CFlarium24Doc* pDoc = GetDocument();
	i = jrw = i3 = 0;

	xi = yi = ii = 0;
	
	rj = bj = gj = 0;
	x_temp = 0;
	y_temp = 0;	
	temp = 0;
		
	dzx_save = dzy_save = 0;
	dzx_save_quick = dzy_save_quick = 0;

	rr = rr3 = 0;
	auto_rr = NMAX;

	limit = sqrt(cx*cx+cy*cy);
	//cx_hi = 0;
	//cx_lo = 0;
	//cy_hi = 0;
	//cy_lo = 0;

	JMAX = NMAX;
	
	//if (bColorChange)
	//{
		//i = nIter_Data[px + py*pDoc->m_sizeDoc.cx];		
		//z.set_real(xData[px + py*pDoc->m_sizeDoc.cx]);
		//z.set_imag(yData[px + py*pDoc->m_sizeDoc.cx]);
	//}
	//else
	//{
	
  switch (nDistortion)
	{					
		case 0:
			Equation();
			//i = px;
      break;
      
    case 1: 			
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
	    		z = z*z + c;
					if (nFilter) Delta_z();
				}
			}
			else
			if (bFSet)
			{
				z2 = cmplx(42,42);					
				while ((z2-z).abs() > dMIN && 
					z.squares() < dBailout &&
				  i++ < JMAX)
				{
					z2=z;
					z = z*z + c;
					if (nFilter) Delta_z();
				}			
			}			
			else
			{
				z2 = cmplx(42,42);					
				while ((z2-z).abs() > dMIN && 
				  i++ < JMAX)
				{
					z2=z;
					z = z*z + c;
					if (nFilter) Delta_z();
				}			
			}			

			if (nFilter) Filter_Complete();
			break;

    case 2: 
			// Generalized Mandelbrot
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z = (z^cn)+c;
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
					z2=z;
					z = (z^cn)+c;
					if (nFilter) Delta_z();
				}
			}
			else
			{			
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2=z;
					z = (z^cn)+c;
					if (nFilter) Delta_z();
				}
			}
				
			if (nFilter) Filter_Complete();
			break;

		case 3:  // CBAP  F(z) = Z^3 - 3*(A^2)*Z + B(MOD 2)
			t=c;
			t3=3*t;
			t2=t*t;
			a=(t2+1)/t3;
			b=2*a*a*a+(t2-cmplx(2,0))/t3;
			aa3=a*a*3;

			if (jul == 0)
				z=-a;

			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z = z*z*z-aa3*z+b;
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
					z2=z;
					z = z*z*z-aa3*z+b;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2=z;
					z = z*z*z-aa3*z+b;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();
			break;

    case 4: 
			if (jul == 0)
				z = cmplx(0, 0);

			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z=z*z+c;
					temp=z.real();
					z.set_real(z.imag());
					z.set_imag(temp);
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
					z2=z;
					z=z*z+c;
					temp=z.real();
					z.set_real(z.imag());
					z.set_imag(temp);
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2=z;
					z=z*z+c;
					temp=z.real();
					z.set_real(z.imag());
					z.set_imag(temp);
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();
			break;

    case 5: 
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z = z*z*sin(z.real()) + c*z*cos(z.imag()) + c;
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
					z2=z;
					z = z*z*sin(z.real()) + c*z*cos(z.imag()) + c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2=z;
					z = z*z*sin(z.real()) + c*z*cos(z.imag()) + c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();
			break;

    case 6: 
			if (bMSet)
			{
				while (z.squares() < dBailout && i++ < JMAX)
				{
					z1=z*z;
					z=z-(z*z1-1)/3*z1;
					z=z*c;
					if (nFilter) Delta_z();
				}
			}
			else
			if (bFSet)
			{
				z2=cmplx(42,42);
				while ((z-z2).abs() > dMIN &&
					z.squares() < dBailout &&
					i++ < JMAX)
				{
					z2=z;
					z1=z*z;
					z=z-(z*z1-1)/3*z1;
					z=z*c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2=cmplx(42,42);
				while ((z2-z).abs() > dMIN && i++ < JMAX)
				{
					z2=z;
					z1=z*z;
					z=z-(z*z1-1)/3*z1;
					z=z*c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();
			break;

    case 7: 
			//if (jul == 0)
			//z = cmplx(0, 0);
			//z2 = cmplx(42,42);
			//while ((z-z2).abs() > dMIN && i++ < JMAX)
      for (i = 0; i < JMAX && z.squares() < dBailout ; i++)
			{
				//z2=z;
				z = (z*z+c)^(cn+c);
				if (nFilter) Delta_z();
			}
			if (nFilter) Filter_Complete();
			break;

    case 8: // Sharon's Star
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z = z*z*z*z+1/c; // Sharon01
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
					z2=z;
					z = z*z*z*z+1/c; // Sharon01
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2=z;
					z = z*z*z*z+1/c; // Sharon01
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();
			break;

    case 9: // 02 Sharon's Space Probe			 
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z = (z*z/2+c)*(z*z/2+c);
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
					z2=z;
					z = (z*z/2+c)*(z*z/2+c);
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2=z;
					z = (z*z/2+c)*(z*z/2+c);
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();
			break;

    case 10: // Sharon08
			t = (c/2)^2;
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z = z*z*z*z+t+c;
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
					z2=z;
					z = z*z*z*z+t+c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2=z;
					z = z*z*z*z+t+c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();
			break;

		case 11:
			t=z^(z+2);
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z = z*z*z*z+t+c;
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
					z2=z;
					z = z*z*z*z+t+c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2=z;
					z = z*z*z*z+t+c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();
			break;

		case 12:
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z = (z+z*z/2)+c;
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
					z2=z;
					z = (z+z*z/2)+c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2=z;
					z = (z+z*z/2)+c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();
			break;

		case 13:
      z2=cmplx(0,0);
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z1=z;
					z=(z*z*z*z-z2*z2*z2*z2+c)*(z*z*z*z-z2*z2*z2*z2+c);
					z2=z1;
				}
			}
			else
			if (bFSet)
			{
				t = cmplx(42,42);
				while ((z-z2).abs() > dMIN &&
					z.squares() < dBailout &&
					i++ < JMAX)
				{
					t=z;
					z1=z;
					z=(z*z*z*z-z2*z2*z2*z2+c)*(z*z*z*z-z2*z2*z2*z2+c);
					z2=z1;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				t = cmplx(42,42);
				while ((z-t).abs() > dMIN && i++ < JMAX)
				{
					t=z;
					z1=z;
					z=(z*z*z*z-z2*z2*z2*z2+c)*(z*z*z*z-z2*z2*z2*z2+c);
					z2=z1;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();
			break;

		case 14:	// 3rd Order Nova
			if (jul == 1)
				c = cmplx(cx, cy);				

			z += 1;
			z2 = cmplx(42,42);
			JMAX = NMAX-2;

			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z = z - (z*z*z-1)/(3*z*z) + c;
					if (nFilter) Delta_z();
				}
			}		
			else
			if (bFSet)
			{
				while ((z-z2).abs() > dMIN &&
					z.squares() < dBailout &&
					i++ < JMAX)
				{
					z2 = z;		
					z = z - (z*z*z-1)/(3*z*z) + c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;		
					z = z - (z*z*z-1)/(3*z*z) + c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 15:  // 4th Order Nova
			if (jul == 1)
				c = cmplx(cx, cy);				

			z += 1;
			z2 = cmplx(42,42);
			JMAX = NMAX-2;
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z = z - (z*z*z*z-1)/(4*z*z*z) + c;
					if (nFilter) Delta_z();
				}
			}		
			else
			if (bFSet)
			{
				while ((z-z2).abs() > dMIN &&
					z.squares() < dBailout &&
					i++ < JMAX)
				{
					z2 = z;		
					z = z - (z*z*z*z-1)/(4*z*z*z) + c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;		
					z = z - (z*z*z*z-1)/(4*z*z*z) + c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 16:  // 5th Order Nova
			if (jul == 1)
				c = cmplx(cx, cy);				

			z += 1;
			z2 = cmplx(42,42);
			JMAX = NMAX-2;
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z = z - (z*z*z*z*z-1)/(5*z*z*z*z) + c;
					if (nFilter) Delta_z();
				}
			}		
			else
			if (bFSet)
			{
				while ((z-z2).abs() > dMIN &&
					z.squares() < dBailout &&
					i++ < JMAX)
				{
					z2 = z;		
					z = z - (z*z*z*z*z-1)/(5*z*z*z*z) + c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;		
					z = z - (z*z*z*z*z-1)/(5*z*z*z*z) + c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 17:  // Generalized Newton
			if (jul == 1)
				z1 = cmplx(cx, cy);
			else
				z1 = cmplx(0,0);

			z2 = cmplx(42,42);
			JMAX = NMAX-2;
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z = ((cn-1)*(z^cn)+cr)/(cn*(z^(cn-1))) + z1;
					if (nFilter) Delta_z();
				}
			}		
			else
			if (bFSet)
			{
				while ((z-z2).abs() > dMIN &&
					z.squares() < dBailout &&
					i++ < JMAX)
				{
					z2 = z;		
					z = ((cn-1)*(z^cn)+cr)/(cn*(z^(cn-1))) + z1;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;		
					z = ((cn-1)*(z^cn)+cr)/(cn*(z^(cn-1))) + z1;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 18:  // 2nd Order Phoenix
			z2 = cmplx(0,0);

			if (jul == 0)
			{
				c *= cmplx(0,1);
			}
			else
			{
				c *= cmplx(0,1);	
				z *= cmplx(0,1);
			}

			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z1 = z;
					z = z*z+c.imag()+c.real()*z2;
					z2 = z1;
     			if (nFilter) Delta_z();
				}
			}
			else
			if (bFSet)
			{
				t = cmplx(42,42);
				while ((z-z2).abs() > dMIN &&
					z.squares() < dBailout &&
					i++ < JMAX)
				{
					t=z;
					z1 = z;
					z = z*z+c.imag()+c.real()*z2;
					z2 = z1;
     			if (nFilter) Delta_z();
				}
			}
			else
			{
				t = cmplx(42,42);
				while ((z-t).abs() > dMIN && i++ < JMAX)
				{
					t=z;
					z1 = z;
					z = z*z+c.imag()+c.real()*z2;
					z2 = z1;
     			if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();
			break;

		case 19:  // 3rd Order Phoenix
			z2 = cmplx(0,0);
			if (jul == 0)
			{
				c *= cmplx(0,1);
			}
			else
			{
				c *= cmplx(0,1);	
				z *= cmplx(0,1);
			}

			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z1 = z;
					z = z*z*z+c.imag()+c.real()*z2;
					z2 = z1;
     			if (nFilter) Delta_z();
				}
			}
			else
			if (bFSet)
			{
				t = cmplx(42,42);
				while ((z-z2).abs() > dMIN &&
					z.squares() < dBailout &&
					i++ < JMAX)
				{
					t=z;
					z1 = z;
					z = z*z*z+c.imag()+c.real()*z2;
					z2 = z1;
     			if (nFilter) Delta_z();
				}
			}
			else
			{
				t = cmplx(42,42);
				while ((z-t).abs() > dMIN && i++ < JMAX)
				{
					t=z;
					z1 = z;
					z = z*z*z+c.imag()+c.real()*z2;
					z2 = z1;
     			if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();
			break;

		case 20:  // 4th Order Phoenix
			z2 = cmplx(0,0);
			if (jul == 0)
			{
				c *= cmplx(0,1);
			}
			else
			{
				c *= cmplx(0,1);	
				z *= cmplx(0,1);
			}

			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z1 = z;
					z = z*z*z*z+c.imag()+c.real()*z2;
					z2 = z1;
     			if (nFilter) Delta_z();
				}
			}
			else
			if (bFSet)
			{
				t = cmplx(42,42);
				while ((z-z2).abs() > dMIN &&
					z.squares() < dBailout &&
					i++ < JMAX)
				{
					t=z;
					z1 = z;
					z = z*z*z*z+c.imag()+c.real()*z2;
					z2 = z1;
     			if (nFilter) Delta_z();
				}
			}
			else
			{
				t = cmplx(42,42);
				while ((z-t).abs() > dMIN && i++ < JMAX)
				{
					t=z;
					z1 = z;
					z = z*z*z*z+c.imag()+c.real()*z2;
					z2 = z1;
     			if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();
			break;

		case 21:
		case 22:
		case 23:
		case 24:
		case 25:
		case 26:
		case 27:
		case 28:
		case 29:
		case 30:
		case 31:
		case 32:
		case 33:
		case 34:
		case 35:
		case 36:
		case 37:
		case 38:
		case 39:
		case 40:

      Formulae4();
      break;

		case 41:
		case 42:
		case 43:
		case 44:
		case 45:
		case 46:
		case 47:
		case 48:
		case 49:
		case 50:
		case 51:
		case 52:
		case 53:
		case 54:
		case 55:
		case 56:
		case 57:
		case 58:
		case 59:
		case 60:

      Formulae5();
      break;

    //////////////////////////////////////////
    case 61:
    case 62:
    case 63:
    case 64:
    case 65:
    case 66:
    case 67:
    case 68:
    case 69:
    case 70:
    case 71:
    case 72:
    case 73:
    case 74:
    case 75:
    case 76:
    case 77:
    case 78:
    case 79:
    case 80:

      Formulae2();
      break;

    case 81:
    case 82:
    case 83:
    case 84:
    case 85:
    case 86:
    case 87:
    case 88:
    case 89:
    case 90:
    case 91:
    case 92:
    case 93:
    case 94:
    case 95:
    case 96:
    case 97:
    case 98:
    case 99:
    case 100:

      Formulae6();
      break;

    case 101:
    case 102:
    case 103:
    case 104:
    case 105:
    case 106:
    case 107:
    case 108:
    case 109:
    case 110:            
		case 111:
		case 112:
		case 113:
		case 114:
		case 115:
		case 116:
		case 117:

      Formulae7();
      break;

		case 118:
		case 119:
		case 125:
		case 133:
		case 134:
		case 135:
		case 136:
		case 137:
		case 138:
    case 140:
    case 141:
    case 142:
    case 143:
    case 144:
    case 145:
    case 146:

			Formulae3();
			break;

		case 120: // 114
			Latoocarfian();
			break;		

///////////////
		case 121: // 115
			Latoocarfian();
			break;
		
		case 122: // 116
			::SetCursor(mWait);
			OnViewBackground();
      			
			x = 0;
			y = 0;
			
			L = 0;
	
			for (ri=0; ri<latoof_count; ri++)
			{
				AdvanceXY();
				PlotDotAt();
			}

			Complete_the_Dots();
			Terminate();
			break;

		case 123:  // 117 
			::SetCursor(mWait);
			OnViewBackground();
      			
			x = 0;
			y = 0;
			L = 0;
	
			for (ri=0; ri<latoof_count; ri++)
			{
				j = 6 * (rand() % 2); 
				AdvanceXY();
				PlotDotAt();
			}

			Complete_the_Dots();
			Terminate();
			break;

		case 124: // 3d
		case 126: // 3d
		case 127: // 3d
		case 128: // 3d
		case 129: // 3d
		case 130: // 3d
			
			nPostFractal = nDistortion; // Save for formula 150
			
			::SetCursor(mWait);
			OnViewBackground();
      			
			X = 0.001;
			Y = 0;
			Z = 0;
			L = 0;
	
			for (ri=0; ri<latoof_count; ri++)
			{
				AdvanceXY();
				PlotDotAt_3D();
			}

			Complete_the_Dots();
			Terminate();
			break;		

		case 131: // Lorenz Attractor

			::SetCursor(mWait);
			OnViewBackground();

			lx = 0.6; ly=0.6; lz=0.6;

			lx_save = lx;
			ly_save = ly;
			lz_save = lz;
            
			// lorenz variables
			lx=0.6, ly=0.6, lz=0.6;
			lh=0.01;
			frac = 8.0/3.0;

			for (ri=0; ri<latoof_count; ri++)
			{
				X = lxx = lx + lh*10*(ly-lx);
				Y = lyy = ly + lh*((-lx*lz) + 28*lx-ly);
				Z = lzz = lz + lh*(lx*ly - frac*lz);

				lx = lxx; ly=lyy; lz=lzz;
            
				PlotDotAt_3D();

			}

			lx = lx_save;
			ly = ly_save;
			lz = lz_save;

			Complete_the_Dots();
			Terminate();

			break;

		case 150:
			Equation150();
			break;

		case 151:
			Equation151();
			break;

		case 152:
			Equation152();
			break;

		case 153:
			Equation153();
			break;

		case 154:
			Equation154();
			break;

		case 155:
			Equation155();
			break;

		default:
			AfxMessageBox("This equation number is under construction");
			Terminate();
				
			break;    
	}

	if (nFilter == 0)
	{
		rj  = (double) i;		
		gj  = (double) i;		
		bj  = (double) i;		
		j		= i;
	}

//	if (dim.cx <= 1024 && dim.cy <= 1024)
//	{
//		if (bFDVariate)
//			nIter_Data[px + py*pDoc->m_sizeDoc.cx] = (int)rj;
//		else
//			nIter_Data[px + py*pDoc->m_sizeDoc.cx] = i;
//	}

  switch (nColorMethod)
	{
		case 0:
			Generalized_Coloring_Method();		
			break;

		case 1:
			Generalized_Coloring_Method1();		
			break;

		case 2:
			Generalized_Coloring_Method2();		
			break;

		case 3:
			Generalized_Coloring_Method3();		
			break;
	
		case 4:
			Generalized_Coloring_Method4();		
			break;
	
		case 5:
			Generalized_Coloring_Method5();		
			break;
	
		case 6:
			Generalized_Coloring_Method6();		
			break;
	
		case 7:
			Generalized_Coloring_Method7();		
			break;

		case 8:
			Generalized_Coloring_Method8();		
			break;

		case 9:
			Generalized_Coloring_Method9();		
			break;

		case 10:
			Generalized_Coloring_Method10();		
			break;

		case 11:
			Generalized_Coloring_Method11();		
			break;

		case 12:
			Generalized_Coloring_Method12();		
			break;

		case 13:
			Generalized_Coloring_Method13();		
			break;

		case 14:
			Generalized_Coloring_Method14();		
			break;

		case 15:
			Generalized_Coloring_Method15();		
			break;

		case 16:
			Generalized_Coloring_Method16();		
			break;

		case 17:
			Generalized_Coloring_Method17();		
			break;

		case 18:
			Generalized_Coloring_Method18();		
			break;

		case 19:
			Generalized_Coloring_Method19();		
			break;

		case 20:
			Generalized_Coloring_Method20();		
			break;

		case 21:
			Generalized_Coloring_Method21();		
			break;

		case 22:
			Generalized_Coloring_Method22();		
			break;

		case 23:
			Generalized_Coloring_Method23();		
			break;

		case 24:
			Generalized_Coloring_Method24();		
			break;

		case 25:
			Generalized_Coloring_Method25();		
			break;

		case 26:
			Generalized_Coloring_Method26();		
			break;

		case 27:
			Generalized_Coloring_Method27();		
			break;

		case 28:
			Generalized_Coloring_Method28();		
			break;

		case 29:
			Generalized_Coloring_Method29();		
			break;

		case 30:
			Generalized_Coloring_Method30();		
			break;

		case 31:
			Generalized_Coloring_Method31();		
			break;

		case 32:
			Generalized_Coloring_Method32();		
			break;

		case 33:
			Generalized_Coloring_Method33();		
			break;

		case 34:
			Generalized_Coloring_Method34();		
			break;

		case 35:
			Generalized_Coloring_Method35();		
			break;

		case 36:
			Generalized_Coloring_Method36();		
			break;

		case 37:
			Generalized_Coloring_Method37();		
			break;

		case 38:
			Generalized_Coloring_Method38();		
			break;

		case 39:
			Generalized_Coloring_Method39();		
			break;

		default:
			break;
	}	
	
	if (dim.cx <= 1024 && dim.cy <= 1024)
	{
		//if (bFDVariate)
		//	mIter_Data[px + py*pDoc->m_sizeDoc.cx] = (int) rj;
		//else
		//	mIter_Data[px + py*pDoc->m_sizeDoc.cx] = i; 

		if (bFDVariate)
		{
			rIter_Data[px + py*pDoc->m_sizeDoc.cx] = (int)rj;
			gIter_Data[px + py*pDoc->m_sizeDoc.cx] = (int)gj;
			bIter_Data[px + py*pDoc->m_sizeDoc.cx] = (int)bj;
		}
		else
		{
			rIter_Data[px + py*pDoc->m_sizeDoc.cx] = i; 
			gIter_Data[px + py*pDoc->m_sizeDoc.cx] = i;
			bIter_Data[px + py*pDoc->m_sizeDoc.cx] = i;
		}		
	}		  
  if (bDraw)
  {
    //if (!::WriteBit(pDoc->hdib, pDoc->m_sizeDoc,
     // px, py, (DWORD)RGB(red, grn, blu)))

		if (red || grn || blu)
			j=0;

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

void CFlarium24View::Terminate()
{
	::SetCursor(mHCross);

	Row = RowMax;
	Col = ColMax;
	px = dim.cx-1;
	py = dim.cy-1;
	bAbort = TRUE;
}

////////////////////////////////////////////////////////////////
double CFlarium24View::x_y_to_degrees(double x_, double y_)
{
	double a;

	if (x_ >= 0 && y_ >= 0)
		a = atan(y_/x_);				// Q0
	else
	if (x_ < 0 && y_ >= 0)
		a = atan(y_/x_)+pi;			// Q1
	else
	if (x_ < 0 && y_ < 0)		
		a = atan(y_/x_)+pi;			// Q3
	else
		a = atan(y_/x_)+2*pi;		// Q4

	return a*rad;
}
