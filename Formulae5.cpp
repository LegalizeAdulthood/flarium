///////////////////////////////////////////
// Formulae5.cpp  41-60

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
void CFlarium24View::Formulae5()
{  
	switch (nDistortion)
	{
		case 41: 
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z = c*(z*z*z*z).csin();		
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
					z = c*(z*z*z*z).csin();		
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;	
					z = c*(z*z*z*z).csin();		
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 42: 			
			if (jul == 0)
				z=cmplx(0, 0);

			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z = z-((z*z*z)+(c-1)*z-c)/(3*(z*z)+c-1);					
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
					//z = z-((z*z*z)+(c-1)*z-c)/(3*(z*z)+c-1);					
					z = z-((z*z*z)+(c-1)*z-c)/(3*(z*z)+c-1);					
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;	
					//z = z-((z*z*z)+(c-1)*z-c)/(3*(z*z)+c-1);					
					z = z-((z*z*z)+(c-1)*z-c)/(3*(z*z)+c-1);					
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 43: 
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z = z*z*z*z + (z*c).csin() + c;
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
					z = z*z*z*z + (z*c).csin() + c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;	
					z = z*z*z*z + (z*c).csin() + c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 44: 
			z=(z*z*z*z-z)/(4*z*z*z);
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z=c*z.csin();
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
					z=c*z.csin();
					if (nFilter) Delta_z();
				}
			}
			else
			{
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;	
					z=c*z.csin();
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 45: 
			z=(z*z*z*z-1)/(4*z*z*z);
			z2 = cmplx(42,42);
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z=c*z.csin();
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
					z=c*z.csin();
					if (nFilter) Delta_z();
				}
			}
			else
			{
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;	
					z=c*z.csin();
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 46: 
			// Sharon14 {
			// c = z = 1/pixel:
			// z = sqr(z * sin(z * z) / 2) + c
			// |z| <= 4;
			// }
			
			// Sharon 14 in the Newton method
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z1	= ((z*z).csin())*z/2;
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
					z1	= z*(z*z).csin()/2;
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
					z1	= z*(z*z).csin()/2;
					z		= z1*z1 + c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 47: 
			z+=1;
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z1=z*z*z;
					z=z-(z*z1-z)/((4*z1)-1)+c;
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
					z=z-(z*z1-z)/((4*z1)-1)+c;
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
					z=z-(z*z1-z)/((4*z1)-1)+c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 48: 
			z+=1;
			z2 = cmplx(42,42);
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z1=z*z*z;
					z=z-(z*z1-z)/((4*z1)-z)+c;
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
					z1=z*z*z;
					z=z-(z*z1-z)/((4*z1)-z)+c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;	
					z1=z*z*z;
					z=z-(z*z1-z)/((4*z1)-z)+c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 49: 
			z=(z*z*z*z-z)/((4*z*z*z)-z);
			z2 = cmplx(42,42);
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z=c*z.csin();
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
					z=c*z.csin();
					if (nFilter) Delta_z();
				}
			}
			else
			{
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2=z;
					z=c*z.csin();
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 50: 
		  for (i = 0; i < JMAX && z.squares() < dBailout ; i++)
			{
				z2=z;
				z = z*z*z*z+1/c; // Sharon01 - Sharon's Star
				if (nFilter) Delta_z();
			}
			if (nFilter) Filter_Complete();			
			break;

		case 51: 
		  for (i = 0; i < JMAX && z.squares() < dBailout ; i++)
			{
				z2=z;
				z = (z*z/2+c)*(z*z/2+c);  // Space Probe M-Set
				if (nFilter) Delta_z();
			}
			if (nFilter) Filter_Complete();			
			break;

		case 52: 
			//z2 = cmplx(42,42);
			//while ((z-z2).abs() > dMIN && i++ < JMAX)
			t = (c/2)^2;
		  for (i = 0; i < JMAX && z.squares() < dBailout ; i++)
			{
				z2=z;
				z = z*z*z*z+t+c;  // Sharon08
				if (nFilter) Delta_z();
			}
			if (nFilter) Filter_Complete();			
			break;

		case 53: 
			//z2 = cmplx(42,42);
			//while ((z-z2).abs() > dMIN && i++ < JMAX)
		  for (i = 0; i < JMAX && z.squares() < dBailout ; i++)
			{
				z2=z;
				z = (z+z*z/2)+c;
				if (nFilter) Delta_z();
			}
			if (nFilter) Filter_Complete();			
			break;

		case 54: 
			//z2 = cmplx(42,42);
			//while ((z-z2).abs() > dMIN && i++ < JMAX)
		  for (i = 0; i < JMAX && z.squares() < dBailout ; i++)
			{
				z2=z;
				z = z*z*c+c; 
				if (nFilter) Delta_z();
			}
			if (nFilter) Filter_Complete();			
			break;

		case 55: 
			//z2 = cmplx(42,42);
			//while ((z-z2).abs() > dMIN && i++ < JMAX)
		  for (i = 0; i < JMAX && z.squares() < dBailout ; i++)
			{
				z2=z;
				z = (z*z).csin()*z*z*c+c; 
				if (nFilter) Delta_z();
			}
			if (nFilter) Filter_Complete();			
			break;

		case 56: 
			//z2 = cmplx(42,42);
			//while ((z-z2).abs() > dMIN && i++ < JMAX)
		  for (i = 0; i < JMAX && z.squares() < dBailout ; i++)
			{
				z2=z;
				z = (z*z+c)/(z*z-c); 
				if (nFilter) Delta_z();
			}
			if (nFilter) Filter_Complete();			
			break;

		case 57: 
			z+=1;
			z2 = cmplx(42,42);
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z1=z*z*z*z;
					z=z-(z*z1-z)/((5*z1)-z)+c;
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
					z1=z*z*z*z;
					z=z-(z*z1-z)/((5*z1)-z)+c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;	
					z1=z*z*z*z;
					z=z-(z*z1-z)/((5*z1)-z)+c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 58: 
			z+=1;
			z2 = cmplx(42,42);
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z1=z*z;
					z=z-(z*z1-z)/((3*z1)-z)+c;
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
					z1=z*z;
					z=z-(z*z1-z)/((3*z1)-z)+c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;	
					z1=z*z;
					z=z-(z*z1-z)/((3*z1)-z)+c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;
		
		case 59: 
			z+=1;
			z2 = cmplx(42,42);
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z1=z*z;
					z=z-(z*z1-z)/((3*z1)-1)+c;
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
					z1=z*z;
					z=z-(z*z1-z)/((3*z1)-1)+c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;	
					z1=z*z;
					z=z-(z*z1-z)/((3*z1)-1)+c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

		case 60: 
			z+=1;
			z2 = cmplx(42,42);
			if (bMSet)
			{
				while (z.squares() < dBailout &&
					  i++ < JMAX)
				{
					z1=z*z*z*z;
					z=z-(z*z1-z)/((5*z1)-1)+c;
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
					z1=z*z*z*z;
					z=z-(z*z1-z)/((5*z1)-1)+c;
					if (nFilter) Delta_z();
				}
			}
			else
			{
				while ((z-z2).abs() > dMIN && i++ < JMAX)
				{
					z2 = z;	
					z1=z*z*z*z;
					z=z-(z*z1-z)/((5*z1)-1)+c;
					if (nFilter) Delta_z();
				}
			}
			if (nFilter) Filter_Complete();			
			break;

	}
}

