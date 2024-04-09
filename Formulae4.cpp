///////////////////////////////////////////
// Formulae4.cpp 21-40

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
void CFlarium24View::Formulae4()
{  
  switch(nDistortion)
  {		
		case 21:  // Sharon03 [118]
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z=(1/z*z-c)*(z*z*z*z+c);
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
					z=(1/z*z-c)*(z*z*z*z+c);
					if (nFilter) Delta_z();
				}
			}
			else
			{
				t = cmplx(42,42);
				while ((z-t).abs() > dMIN && i++ < JMAX)
				{
					t=z;
					z=(1/z*z-c)*(z*z*z*z+c);
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();
			break;

		case 22:  // [138]
			z2=cmplx(.5,0);
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z1=z;
					z=z*z-z2*z2+c;
					z2=z1;
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
					z1=z;
					z=z*z-z2*z2+c;
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
					z=z*z-z2*z2+c;
					z2=z1;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();
			break;

		case 23:  // [140]
	    z2=z;
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z1=z;
					z=z*z*z*z+z2+c;
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
					z=z*z*z*z+z2+c;
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
					z=z*z*z*z+z2+c;
					z2=z1;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();
			break;

		case 24:  // [146]
	    z2=z;    
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z1=z;
					z=z*z*z*z+2*cn*z2*c;
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
					z=z*z*z*z+2*cn*z2*c;
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
					z=z*z*z*z+2*cn*z2*c;
					z2=z1;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();
			break;

		case 25: 
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z1=z*z*z;
					z=z-(z*z1-z)/(4*z1-z);
					z=z*c;
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
					z1=z*z*z;
					z=z-(z*z1-z)/(4*z1-z);
					z=z*c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2=z;
					z1=z*z*z;
					z=z-(z*z1-z)/(4*z1-z);
					z=z*c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();
			break;

		case 26:	// [52]
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z = ((z^3)/((z+.1)^2))+c;
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
					z = ((z^3)/((z+.1)^2))+c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				t = cmplx(42,42);
				while ((z-t).abs() > dMIN && i++ < JMAX)
				{
					t=z;
					z = ((z^3)/((z+.1)^2))+c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();
			break;

		case 27:  // [163]
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z=z*z*(cn+z)/(cn+z+c)+c;  
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
					z=z*z*(cn+z)/(cn+z+c)+c;  
					if (nFilter) Delta_z();
				}
			}
			else
			{
				t = cmplx(42,42);
				while ((z-t).abs() > dMIN && i++ < JMAX)
				{
					t=z;
					z=z*z*(cn+z)/(cn+z+c)+c;  
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();
			break;

		case 28:   // Nova Multi-Fract
			if (jul == 1)
				c = cmplx(cx, cy);				

			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z=z*z+c;  
					if (nFilter) Delta_z();
				}

				c=z;
				z+=1;
				i = 0;
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
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN &&
					z.squares() < dBailout &&
					i++ < JMAX)
				{
					z2=z;
					z=z*z+c;  
					if (nFilter) Delta_z();
				}

				c=z;
				z+=1;
				i = 0;
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;		
	    		z = z - (z*z*z-1)/(3*z*z) + c;
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
					if (nFilter) Delta_z();
				}

				c=z;
				z+=1;
				i = 0;
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;		
	    		z = z - (z*z*z-1)/(3*z*z) + c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 29: 
			z2 = cmplx(42,42);
			c = (z*z*z-1)/(3*z*z);
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z -= (z*z*z-1)/(3*z*z)*c;
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
					z -= (z*z*z-1)/(3*z*z)*c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;	
					z -= (z*z*z-1)/(3*z*z)*c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 30: 
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z -= (z*z*z-1)/(3*z*z)*c;
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
					z -= (z*z*z-1)/(3*z*z)*c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;	
					z -= (z*z*z-1)/(3*z*z)*c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 31: 
			//t=c;
			//a=t;			
			//b=2*t*t*t-2*t;
			//aa3=a*a*3;
			//a2=a+a;

			t=(c*c*c-1)/(3*c*c);			
			a=t;
			b=2*t*t*t-2*t;
			aa3=a*a*3;

			if (jul == 0)
				z=-a;

			z2 = cmplx(42,42);
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
				while ((z-z2).abs() > dMIN &&
					z.squares() < dBailout &&
					i++ < JMAX)
				{
					z2 = z;	
					z = z*z*z-aa3*z+b;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;	
					z = z*z*z-aa3*z+b;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 32: // 3rd Order Nova in a M-Set
			z+=1;
      for (i = 0; i < JMAX && z.squares() < dBailout ; i++)
			{
				z2=z;
				z1 = z*z;
	    	z = z - (z*z1-1)/(3*z1) + c;
        if (nFilter) Delta_z();
			}
			if (nFilter) Filter_Complete();
			break;

		case 33: // Newton method in the Mandelbrot style
			if (jul == 1)
				c = cmplx(cx, cy);				

      for (i = 0; i < JMAX && z.squares() < dBailout ; i++)
			{
				z2=z;
				z1 = z*z;
	    	z = z - (z*z1-1)/(3*z1);
        if (nFilter) Delta_z();
			}
			if (nFilter) Filter_Complete();
			break;

		case 34: 
							// Sharon14 {
							// c = z = 1/pixel:
							// z = sqr(z * sin(z * z) / 2) + c
							// |z| <= 4;
							// }
			
			//z2 = cmplx(42,42);
			//while ((z-z2).abs() > dMIN && i++ < JMAX)
      for (i = 0; i < JMAX && z.squares() < dBailout ; i++)
			{
				z2=z;
				z1	= z*(z*z).csin()/2;
				z		= z1*z1 + c;
			 	if (nFilter) Delta_z();
			}
			if (nFilter) Filter_Complete();			
			break;

		case 35: 
			z2 = cmplx(42,42);
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z=c*(z.csin());
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
					z=c*(z.csin());
					if (nFilter) Delta_z();
				}
			}
			else
			{
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;	
					z=c*(z.csin());
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 36: 
			z2 = cmplx(42,42);
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z=(c*z).csin();
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
					z=(c*z).csin();
					if (nFilter) Delta_z();
				}
			}
			else
			{
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;	
					z=(c*z).csin();
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 37: 
			z2 = cmplx(42,42);
			z=(z*z*z-1)/(3*z*z);
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
				  z = c*(z.csin() + z.ccos()); // Eq 36 OK !!!!!!
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
				  z = c*(z.csin() + z.ccos()); // Eq 36 OK !!!!!!
					if (nFilter) Delta_z();
				}
			}
			else
			{
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;	
				  z = c*(z.csin() + z.ccos()); // Eq 36 OK !!!!!!
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 38: 
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					// Variation real        
					z = z*z+c;
					if (nFilter) Delta_z();
					z.set_real(z.real()*z.real());
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
					// Variation real        
					z = z*z+c;
					if (nFilter) Delta_z();
					z.set_real(z.real()*z.real());
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;	
					// Variation real        
					z = z*z+c;
					if (nFilter) Delta_z();
					z.set_real(z.real()*z.real());
				}
			}
			if (nFilter) Filter_Complete();								
			break;

		case 39: 
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z = z*z + c;   // 29.) Spider		// OK
					c = c/2 + z;		 // 29.) Spider			
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
					z = z*z + c;   // 29.) Spider		// OK
					c = c/2 + z;		 // 29.) Spider			
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;	
					z = z*z + c;   // 29.) Spider		// OK
					c = c/2 + z;		 // 29.) Spider			
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 40: 
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z1 = z*z*z*z;
					z = c*z1/4*z1 + z; // 96.) 
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
					z1 = z*z*z*z;
					z = c*z1/4*z1 + z; // 96.) 
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;	
					z1 = z*z*z*z;
					z = c*z1/4*z1 + z; // 96.) 
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;


	}
}

