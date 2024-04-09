///////////////////////////////////////////
// Formulae7.cpp  101-117

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
void CFlarium24View::Formulae7()
{  
	switch (nDistortion)
	{
    case 101:
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
          z1=z*z;    // 101
 		      z=(z-(z*z1-1)/(3*z1-z))*c;
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
          z1=z*z;    // 101
 		      z=(z-(z*z1-1)/(3*z1-z))*c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2=z;	
          z1=z*z;    // 101
 		      z=(z-(z*z1-1)/(3*z1-z))*c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

    case 102:
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
          z1=z*z*z;   // 102
		      z=(z-(z*z1-1)/(4*z1-z))*c;
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
          z1=z*z*z;   // 102
		      z=(z-(z*z1-1)/(4*z1-z))*c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2=z;	
          z1=z*z*z;   // 102
		      z=(z-(z*z1-1)/(4*z1-z))*c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

    case 103:
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
          z1=z*z*z;   // 103
		      z=(z-(z*z1-1)/(3*z1-z))*c;
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
          z1=z*z*z;   // 103
		      z=(z-(z*z1-1)/(3*z1-z))*c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2=z;	
          z1=z*z*z;   // 103
		      z=(z-(z*z1-1)/(3*z1-z))*c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

    case 104:
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
          z1=z*z*z;   // 104
		      z=(z-(z*z1-z-1)/(3*z1-z))*c;
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
          z1=z*z*z;   // 104
		      z=(z-(z*z1-z-1)/(3*z1-z))*c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2=z;	
          z1=z*z*z;   // 104
		      z=(z-(z*z1-z-1)/(3*z1-z))*c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

    case 105:
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
      		z=c*(z-(z*z*z-z)/(3*z*z-1));  // 105
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
      		z=c*(z-(z*z*z-z)/(3*z*z-1));  // 105
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2=z;	
      		z=c*(z-(z*z*z-z)/(3*z*z-1));  // 105
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

    case 106:
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
          z1=z*z*z;   // Sort of Good one
      		z=((1-z-z1*z)/(z-(4*z1))-z)*c;  // 106
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
          z1=z*z*z;   // Sort of Good one
      		z=((1-z-z1*z)/(z-(4*z1))-z)*c;  // 106
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2=z;	
          z1=z*z*z;   // Sort of Good one
      		z=((1-z-z1*z)/(z-(4*z1))-z)*c;  // 106
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;
  
    case 107:
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
          z1=z*z*z;   // 
		      z=((z-z1*z)/(z-(3*z1))-z)*c;  // 107
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
          z1=z*z*z;   // 
		      z=((z-z1*z)/(z-(3*z1))-z)*c;  // 107
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2=z;	
          z1=z*z*z;   // 
		      z=((z-z1*z)/(z-(3*z1))-z)*c;  // 107
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;
  
    case 108:
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
          z1=z*z*z;   // 
		      z=((z-z1)/(z-(3*z1))-z)*c;  // 108
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
          z1=z*z*z;   // 
		      z=((z-z1)/(z-(3*z1))-z)*c;  // 108
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2=z;	
          z1=z*z*z;   // 
		      z=((z-z1)/(z-(3*z1))-z)*c;  // 108
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;
  
    case 109:
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
          z1=z*z;   // 
		      z=((z1*z-1)/(2*z1-1)-z)*c;  // 109
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
          z1=z*z;   // 
		      z=((z1*z-1)/(2*z1-1)-z)*c;  // 109
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2=z;	
          z1=z*z;   // 
		      z=((z1*z-1)/(2*z1-1)-z)*c;  // 109
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;
  
    case 110:
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
          z1=z*z;
		      z=((z*z1-z-1)/(3*z*z1-1)-z)*c; // 2nd Order M-Set 110
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
		      z=((z*z1-z-1)/(3*z*z1-1)-z)*c; // 2nd Order M-Set 110
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
		      z=((z*z1-z-1)/(3*z*z1-1)-z)*c; // 2nd Order M-Set 110
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

///////////////
		case 111:	// Alden's Ray sine distortion variation
			// Sharon14 {
			// c = z = 1/pixel:
			// z = sqr(z * sin(z * z) / 2) + c
			// |z| <= 4;
			// }			

			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z1	= z*(z*z).csin_error()/2;
					z		= z1*z1 + c;
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
					z1	= z*(z*z).csin_error()/2;
					z		= z1*z1 + c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				//for (i = 0; i < JMAX && z.squares() < dBailout ; i++)
				{
					z2	= z;
					z1	= z*(z*z).csin_error()/2;
					z		= z1*z1 + c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;
			
///////////////

		case 112: // Dragon curve variation
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z=z*z*c+z*c;
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
					z=z*z*c+z*c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				//for (i = 0; i < JMAX && z.squares() < dBailout ; i++)
				{
					z2	= z;
					z=z*z*c+z*c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 113: // Dragon curve variation
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z=z*z*z*c+z*c;
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
					z=z*z*z*c+z*c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2	= z;
					z=z*z*z*c+z*c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 114: // Dragon curve variation
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
			 		z=z*z*z*c*c+z*c;
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
			 		z=z*z*z*c*c+z*c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2	= z;
			 		z=z*z*z*c*c+z*c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 115: // Dragon curve variation
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z=z*z*z*z*c*c+z*c;
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
					z=z*z*z*z*c*c+z*c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN &&
					i++ < JMAX)
				{
					z2	= z;
					z=z*z*z*z*c*c+z*c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 116: // Dragon curve variation
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z=z*z*z*z*z*c+z*c;
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
					z=z*z*z*z*z*c+z*c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2	= z;
					z=z*z*z*z*z*c+z*c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 117: // Newton Variation X
			if (jul == 0)
				z=cmplx(0,0);

			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z = z-(z*z*z-z*c-1)/(3*z*z+c-1);					
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
					z = z-(z*z*z-z*c-1)/(3*z*z+c-1);					
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2	= z;
					z = z-(z*z*z-z*c-1)/(3*z*z+c-1);					
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

	}
}

