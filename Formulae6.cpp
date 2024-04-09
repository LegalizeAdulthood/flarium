///////////////////////////////////////////
// Formulae6.cpp  81-100

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
void CFlarium24View::Formulae6()
{  
	switch (nDistortion)
	{
		case 81:	 // Squares

			x_size = (rn*2) / (double) NMAX;
			y_size = (rn*2) / (double) NMAX;
			z = c;
			i = (int) (fabs(z.real() / x_size) + fabs(z.imag() / y_size));
			if (nFilter) Delta_z();
			if (nFilter) Filter_Complete();

			break;
		
		case 82:   // Circles

			x_size = (rn*2) / (double) NMAX;
			y_size = (rn*2) / (double) NMAX;
			c.set_real(fabs(c.real() / x_size));
			c.set_imag(fabs(c.imag() / y_size));
			z = c;
			i = (int) sqrt(z.real()*z.real()+z.imag()*z.imag());

			if (nFilter) Delta_z();
			if (nFilter) Filter_Complete();
			
			break;

		case 83:	 // Radial

			deg = x_y_to_degrees(c.real(), c.imag());
			temp = ((double) NMAX)/(90*rn);
			i = (int) (temp * deg);
			z = c;

			if (nFilter) Delta_z();
			if (nFilter) Filter_Complete();
			break;

		case 84:	 // Spiral

			deg = x_y_to_degrees(c.real(), c.imag());
			temp = ((double) NMAX)/(180*rn);

			x_size = rn / (double) NMAX;
			y_size = rn / (double) NMAX;
			c.set_real(fabs(c.real() / x_size));
			c.set_imag(fabs(c.imag() / y_size));
			z = c;
						
			i = (int) (temp*deg  + sqrt(z.real()*z.real()+z.imag()*z.imag()));
			
			if (nFilter) Delta_z();
			if (nFilter) Filter_Complete();
			//z = cmplx(((temp * deg) + sqrt(z.real()*z.real()+z.imag()*z.imag())),0);

			//if (nFilter) Delta_z();
			//if (nFilter) Filter_Complete();
			break;

		case 85:
			x_size = (CRMAX-CRMIN) / (double) NMAX;
			z = c;
			i = (int) ((z.real() + CRMIN) / x_size);
			if (nFilter) Delta_z();
			if (nFilter) Filter_Complete();
			break;

		case 86:  // 153
			z2 = cmplx(42,42);
      t=c;
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z=z.csin()+z*z*z*z+c;
					c=t+z1-z;
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
					z=z.csin()+z*z*z*z+c;
					c=t+z1-z;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2=z;	
					z=z.csin()+z*z*z*z+c;
					c=t+z1-z;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 87: // 157
			z2 = cmplx(42,42);
			t = cmplx(0,0);
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z1=z;
					z=z*z*z-t*t*t+c;
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
					z=z*z*z-t*t*t+c;
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
					z=z*z*z-t*t*t+c;
					t=z1;
					if (nFilter) Delta_z();
				}	
			}
			if (nFilter) Filter_Complete();			
			break;

		case 88:  // 158
			z2 = cmplx(42,42);
			t = cmplx(0,0);
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z1=z;
					z=z*z*z*z-t*t*t*t+c;
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
					z=z*z*z*z-t*t*t*t+c;
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
					z=z*z*z*z-t*t*t*t+c;
					t=z1;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 89:  // 133
			t=(1+c).csin();
			z2 = cmplx(42,42);
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z = z*z*z*z/t+c;
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
					z = z*z*z*z/t+c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2=z;	
					z = z*z*z*z/t+c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 90:
			//Sharon15 {
			//c = z = 1/pixel:
			//z = sin(z * sin(z + z) / 2) + c
			//|z| <= 4;
			//}

			z2 = cmplx(42,42);
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z = (z*(z*z).csin()/2).csin()+c;
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
					z = (z*(z*z).csin()/2).csin()+c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2=z;	
					z = (z*(z*z).csin()/2).csin()+c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 91:
			//Sharon16 {
			//c = z = 1/pixel:
			//z = sqr(z * cos(z + z) / 2) + c
			//|z| <= 4;
			//}

			z2 = cmplx(42,42);
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z = (z*(z+z).ccos()/2);
					z = z*z+c;
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
					z = (z*(z+z).ccos()/2);
					z = z*z+c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2=z;	
					z = (z*(z+z).ccos()/2);
					z = z*z+c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 92:
			//Sharon17 {
			//c = z = 1/pixel:
			//z = sqr(z * sin(z + z) / 2) + c
			//|z| <= 4;
			//}

			z2 = cmplx(42,42);
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z = (z*(z+z).csin()/2);
					z = z*z+c;
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
					z = (z*(z+z).csin()/2);
					z = z*z+c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2=z;	
					z = (z*(z+z).csin()/2);
					z = z*z+c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 93:
			//Sharon18 {
			//c = z = 1/pixel:
			//z = sqr(z * sin(z + (z*z)) / 2) + c
			//|z| <= 4;
			//}
			
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z = (z*(z+z*z).csin()/2);
					z = z*z+c;
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
					z = (z*(z+z*z).csin()/2);
					z = z*z+c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2=z;	
					z = (z*(z+z*z).csin()/2);
					z = z*z+c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

    case 94:
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					if (nFilter) Delta_z();
          z1=z*z;
    	  	z=((z*z1-z-1)/(z1*z-1)-z)*c;   // 3rd order M-Set
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
          z1=z*z;
    	  	z=((z*z1-z-1)/(z1*z-1)-z)*c;   // 3rd order M-Set
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2=z;	
          z1=z*z;
    	  	z=((z*z1-z-1)/(z1*z-1)-z)*c;   // 3rd order M-Set
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

    case 95:
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
          z1=z*z;
		      z=((z1*z1-z1-1)/(4*z1-1)-z)*c;  // 
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
          z1=z*z;
		      z=((z1*z1-z1-1)/(4*z1-1)-z)*c;  // 
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2=z;	
          z1=z*z;
		      z=((z1*z1-z1-1)/(4*z1-1)-z)*c;  // 
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

    case 96:
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
          z1=z*z;
      		z=(z-(z*z1-1)/(3*z1-z.abs()-1))*c;
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
          z1=z*z;
      		z=(z-(z*z1-1)/(3*z1-z.abs()-1))*c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2=z;	
          z1=z*z;
      		z=(z-(z*z1-1)/(3*z1-z.abs()-1))*c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

    case 97:
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
          z1=z*z;   // 97
    	  	z=(z-(z*z1-1)/(3*z1-z-1))*c;  // Almost makes a connection
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
          z1=z*z;   // 97
    	  	z=(z-(z*z1-1)/(3*z1-z-1))*c;  // Almost makes a connection
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2=z;	
          z1=z*z;   // 97
    	  	z=(z-(z*z1-1)/(3*z1-z-1))*c;  // Almost makes a connection
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

    case 98:
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
          z1=z*z*z;   // 98
    	  	z=((z*z1-z-1)/(4*z1-z-1)-z)*c;  // Some strange curls
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
          z1=z*z*z;   // 98
    	  	z=((z*z1-z-1)/(4*z1-z-1)-z)*c;  // Some strange curls
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2=z;	
          z1=z*z*z;   // 98
    	  	z=((z*z1-z-1)/(4*z1-z-1)-z)*c;  // Some strange curls
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

    case 99:
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
          z1=z*z;   // 99
    	  	z=((z*z1-z-1)/(3*z1-1)-z)*c;  // This is definetly a good one !!
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
          z1=z*z;   // 99
    	  	z=((z*z1-z-1)/(3*z1-1)-z)*c;  // This is definetly a good one !!
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2=z;	
          z1=z*z;   // 99
    	  	z=((z*z1-z-1)/(3*z1-1)-z)*c;  // This is definetly a good one !!
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

    case 100:
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
          z1=z*z;   // 100
    	  	z=(z-(z*z1-1)/(4*z1-z-1))*c;
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
          z1=z*z;   // 100
    	  	z=(z-(z*z1-1)/(4*z1-z-1))*c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2=z;	
          z1=z*z;   // 100
    	  	z=(z-(z*z1-1)/(4*z1-z-1))*c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;


	}
}

