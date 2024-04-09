///////////////////////////////////////////
// Formulae2.cpp  61-80

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
void CFlarium24View::Formulae2()
{  
  switch(nDistortion)
  {
		case 61: 
			z2 = cmplx(42,42);
			c=c+(c/pi);
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z = z*z*z*z+c;
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
					z = z*z*z*z+c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;	
					z = z*z*z*z+c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 62: 
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z=z*z*(1+z)/(1+z+c)+c;  
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
					z2 = z;	
					z=z*z*(1+z)/(1+z+c)+c;  
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;	
					z=z*z*(1+z)/(1+z+c)+c;  
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 63: 
			z2 = cmplx(42,42);
			t=z;
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z1=z;
					z=z*z*z*z+t/2+c;
					t=z1;
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
					z2=z;
					z1=z;
					z=z*z*z*z+t/2+c;
					t=z1;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2=z;
					z1=z;
					z=z*z*z*z+t/2+c;
					t=z1;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 64:
			z2 = cmplx(42,42);
			t=z;
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z1=z;
					z=z*z*z*z+c.real()*c.imag()*t/2+c;
					t=z1;
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
					z1=z;
					z=z*z*z*z+c.real()*c.imag()*t/2+c;
					t=z1;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;	
					z1=z;
					z=z*z*z*z+c.real()*c.imag()*t/2+c;
					t=z1;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 65:
			z2 = cmplx(42,42);
			z=1/z;
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z1=z*z*z;
					z=z-(z*z1-z)/(4*z1-1);
					z=z*z*c;
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
									
					z1=z*z*z;
					z=z-(z*z1-z)/(4*z1-1);
					z=z*z*c;

					if (nFilter) Delta_z();
				}
			}
			else
			{
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;	
									
					z1=z*z*z;
					z=z-(z*z1-z)/(4*z1-1);
					z=z*z*c;

					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 66:
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z=z-(z*z-1)/(2*z);
					z=z*z*c;
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
					z2 = z;	
					//z1=z*z;
					//z=z1-(z*z1-1)/(6*z1);
					//z=z*z+c;
					//z = z-z*z*c-(z*z*z-1)/(3*z);
					z=z-(z*z-1)/(2*z);
					z=z*z*c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;	
					//z1=z*z;
					//z=z1-(z*z1-1)/(6*z1);
					//z=z*z+c;
					//z = z-z*z*c-(z*z*z-1)/(3*z);
					z=z-(z*z-1)/(2*z);
					z=z*z*c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 67:
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z1=z*z;
					z=z-(z*z1-1)/(3*z1);
					z=z*z*c;
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
					z2 = z;	
					z1=z*z;
					z=z-(z*z1-1)/(3*z1);
					z=z*z*c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;	
					z1=z*z;
					z=z-(z*z1-1)/(3*z1);
					z=z*z*c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 68:
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z1=z*z*z;
					z=z-(z*z1-1)/(4*z1);
					z=z*z*c;
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
					z2 = z;	
					z1=z*z*z;
					z=z-(z*z1-1)/(4*z1);
					z=z*z*c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;	
					z1=z*z*z;
					z=z-(z*z1-1)/(4*z1);
					z=z*z*c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 69:
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z1=z*z*z*z;
					z=z-(z*z1-1)/(5*z1);
					z=z*z*c;
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
					z2 = z;	
					//z=(z*z-1)/(2*z);
					//z=z*z+c;

					z1=z*z*z*z;
					z=z-(z*z1-1)/(5*z1);
					z=z*z*c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;	
					//z=(z*z-1)/(2*z);
					//z=z*z+c;

					z1=z*z*z*z;
					z=z-(z*z1-1)/(5*z1);
					z=z*z*c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 70:
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z=z-(z*z*z*z*c-z+c)/(4*z*z*z*c);
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
					z2 = z;	
					z=z-(z*z*z*z*c-z+c)/(4*z*z*z*c);
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;	
					z=z-(z*z*z*z*c-z+c)/(4*z*z*z*c);
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 71:
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z=z-(z*z*z-z+c)/(3*z*z);
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
					z2 = z;	
					z=z-(z*z*z-z+c)/(3*z*z);
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;	
					z=z-(z*z*z-z+c)/(3*z*z);
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 72:
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z=z-(z*z*z*c-z*c-1)/(3*z*z*c);
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
					z2 = z;	
					z=z-(z*z*z*c-z*c-1)/(3*z*z*c);
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN &&
					i++ < JMAX)
				{
					z2 = z;	
					z=z-(z*z*z*c-z*c-1)/(3*z*z*c);
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 73:
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z=z-(z*z*z*c-z*z*c-1)/(3*z*z*c);
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
					z2 = z;	
					z=z-(z*z*z*c-z*z*c-1)/(3*z*z*c);
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;	
					z=z-(z*z*z*c-z*z*c-1)/(3*z*z*c);
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 74:
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z=z-(z*z*z*c-1)/(3*z*z*c);
					z=z*z*c+c;
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
					z2 = z;	
					z=z-(z*z*z*c-1)/(3*z*z*c);
					z=z*z*c+c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;	
					z=z-(z*z*z*c-1)/(3*z*z*c);
					z=z*z*c+c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 75:
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z=z-(z*z*z*c-z-1)/(3*z*z*c-z);
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
					z2 = z;	
					z=z-(z*z*z*c-z-1)/(3*z*z*c-z);
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;	
					z=z-(z*z*z*c-z-1)/(3*z*z*c-z);
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 76:
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z=z-(z*z*z*c-z*c-1)/(3*z*z*c-z);
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
					z2 = z;	
					z=z-(z*z*z*c-z*c-1)/(3*z*z*c-z);
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;	
					z=z-(z*z*z*c-z*c-1)/(3*z*z*c-z);
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 77:
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z=z-(z*z*z*c-z*z-1)/(3*z*z*c-3*z*z-3*z);
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
					z2 = z;	
					z=z-(z*z*z*c-z*z-1)/(3*z*z*c-3*z*z-3*z);
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;	
					z=z-(z*z*z*c-z*z-1)/(3*z*z*c-3*z*z-3*z);
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 78:
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z=z-(z*z*z*c-z*z*c-1)/(3*z*z*c-z*c-z);
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
					z2 = z;	
					z=z-(z*z*z*c-z*z*c-1)/(3*z*z*c-z*c-z);
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;	
					z=z-(z*z*z*c-z*z*c-1)/(3*z*z*c-z*c-z);
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 79:
			//z2 = cmplx(42,42);
		  for (i = 0; i < JMAX && z.squares() < dBailout ; i++)
			{
				z2=z;	
				z=z*c;
				if (nFilter) Delta_z();
			}
			if (nFilter) Filter_Complete();			
			break;

		case 80:
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					//z=z-(z*z*z-1)/(3*z*z);
					//z=z*z+c;
			    z1=z*z*z;   // A correct one, finally
					z=((z*z1-1)/(1-(3*z1)))*c;  // 
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
					//z=z-(z*z*z-1)/(3*z*z);
					//z=z*z+c;
			    z1=z*z*z;   // A correct one, finally
					z=((z*z1-1)/(1-(3*z1)))*c;  // 
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2=z;	
					//z=z-(z*z*z-1)/(3*z*z);
					//z=z*z+c;
			    z1=z*z*z;   // A correct one, finally
					z=((z*z1-1)/(1-(3*z1)))*c;  // 
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

    default:
      break;

  }
}
