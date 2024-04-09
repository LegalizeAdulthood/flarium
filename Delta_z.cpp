// Delta_z.cpp

#include "stdafx.h"
#include "Flarium24.h"

#include "Flarium24Doc.h"
#include "Flarium24View.h"
#include "mainfrm.h"
#include <math.h>
#include "external.h"
#include "xysize.h"
#include "OneNum.h"
#include "Clouds.h"

void CFlarium24View::Delta_z()
{
	dzx = z.real();
	dzy = z.imag();
	switch(nFilter)
	{
		case 1:	  
			if (fabs(dzx) < z.magnitude() || fabs(dzy) < z.magnitude())
				rr+=nFF;
			break;

		case 2:
			if (fabs(dzx) < dStrands || fabs(dzy) < dStrands)
			{
				rr += atan(fabs(dzy/dzx))*atan(fabs(dzx/dzy))*2;
			}
			break;

		case 3:	
			if (dzx < c.real()+dStrands && dzx > c.real()-dStrands)
			{
				dzx_save += z.magnitude();
			}
			if (dzy < c.imag()+dStrands && dzy > c.imag()-dStrands)
			{
				dzy_save += z.magnitude();
			}
			
			break;

		case 4:
			if (dzx < c.real()+dStrands && dzx > c.real()-dStrands)
			{
				dzx_save += fabs(atan(dzx/dzy))*3;
				dzy_save += fabs(atan(dzy/dzx))*3;
			}
			else
			{
				dzx_save += z.magnitude();
				dzy_save += z.magnitude();
			}
			
			break;

		case 5:
			if (fabs(dzx) < dStrands || fabs(dzy) < dStrands)
			{
				dzx_save += (atan(fabs(dzx/dzy)))*3;
				dzy_save += (atan(fabs(dzy/dzx)))*3;
			}
			
			break;

		case 6:
			if (fabs(dzx) < dStrands || fabs(dzy) < dStrands)
			{
				rr += (fabs(dzx) + fabs(dzy));
			}
								
			if (dzx < c.real()+dStrands && dzx > c.real()-dStrands)
			{
				rr += (fabs(dzx) + fabs(dzy));
			}

			dzx_save = fabs(dzx);
			dzy_save = fabs(dzy);
			
			break;

		case 7:
			dzx_save += dzx;
			dzy_save += dzy;
			break;

		case 8:
			dzx_save += dzx;
			dzy_save += dzy;
			break;

		case 9:
			dzx_save += dzx;
			dzy_save += dzy;
			break;

		case 10:
			dzx_save += dzx;
			dzy_save += dzy;
			break;

		case 11:
			dzx_save += dzx;
			dzy_save += dzy;
			break;

		case 12:
			dzx_save += dzx;
			dzy_save += dzy;
			break;
	
		case 13:
			dzx_save=dzx;
			dzy_save=dzy;
			break;

		case 14:  // Fractal Dimension
			break;

		case 15:	// Standard Deviation
			break;			

		case 16:				
			//break;			

		case 17:
			if (dzx_save == 0)
			{
				bPositiveX=FALSE;
				bPositiveY=FALSE;
			}

			if (fabs(dzx) >= dzx_save)
			{
				// Count the Positive Slope Change
				if (!bPositiveX)
				{
					jrw+=nFF;
					bPositiveX = TRUE;
				}
			}
			else
			{
				// Count the Negative Slope Change
				if (bPositiveX)
				{
					jrw+=nFF;
					bPositiveX = FALSE;
				}
			}			

			if (fabs(dzy) >= dzy_save)
			{
				// Count the Positive Slope Change
				if (!bPositiveY)
				{
					jrw+=nFF;
					bPositiveY=TRUE;
				}
			}
			else
			{
				// Count The Negative Slope Change
				if (bPositiveY)
				{
					jrw+=nFF;
					bPositiveY=FALSE;
				}
			}
			
			dzx_save = fabs(dzx);
			dzy_save = fabs(dzy);

			break;

		case 18:  //
			if (dzx_save == 0)
			{
				bPositiveX=FALSE;
				bPositiveY=FALSE;
				z1 = z;
				dzx_save = 99;
				jrw = NMAX/4;
				return;

			}

			if (fabs(z.real()) >= fabs(z1.real()) || fabs(z.imag()) >= fabs(z1.imag()))
			{
				// Count the Positive Slope No Change
				if (!bPositiveX)
				{
					bPositiveX = TRUE;
					if (jrw-nFF > 0)
						jrw-=nFF;
				}
				else
				{
					if (jrw+(nFF*2) < NMAX)
						jrw+=(nFF*2);
				}
			}
			else
			{
				// Count the Negative Slope No Change
				if (bPositiveX)
				{
					bPositiveX = FALSE;
					if (jrw-nFF > 0)
						jrw-=nFF;
				}
				else
				{
					if (jrw+(nFF*2) < NMAX)
						jrw+=(nFF*2);
				}
			}			

			z1 = z;

			break;

		////////////////////////////
		// Category 2 filters
		case 130:  // 		
			if (i <= 1)
			{
				x_rmin = dzx;
				x_rmax = dzx;
				y_rmin = dzy;
				y_rmax = dzy;
			}	
			else
			{	
				if (x_rmin > dzx)
					x_rmin = dzx;
				if (x_rmax < dzx)
					x_rmax = dzx;

				if (y_rmin > dzy)
					y_rmin = dzy;
				if (y_rmax < dzy)
					y_rmax = dzy;
			}

			break;		

		case 131:
			if ((fabs(dzx) <= dStrands_HI && fabs(dzx) > dStrands_LO) || (fabs(dzy) <= dStrands_HI && fabs(dzy) > dStrands_LO))        
			{
				rr+=log(dzx*dzx+dzy*dzy)*13;  // Don't mess with this
			}	
			if (fabs(dzx) < dStrands || fabs(dzy) < dStrands)
			{
				i3++;
			}
			break;

		case 132:
			if (dzx*dzx+dzy*dzy < limit)
				i3++;
			break;

		case 133:
			if (dzx < dStrands && dzx > -dStrands)
			{
				if (dzx < 0)
					dzx = -dStrands;
				else
					dzx =  dStrands;
			}

			if (dzy < dStrands && dzy > -dStrands)
			{
				if (dzy < 0)
					dzy = -dStrands;
				else
					dzy = dStrands;
			}

			dzx_save += log(fabs(dzx));
			dzy_save += log(fabs(dzy));
			
			if ((fabs(dzx) <= dStrands_HI && fabs(dzx) > dStrands_LO) || (fabs(dzy) <= dStrands_HI && fabs(dzy) > dStrands_LO))        
			{
     		rr+=log(dzx*dzx+dzy*dzy)*13;  // Don't mess with this			
			}
			
			if (dzx*dzx+dzy*dzy < limit)
				i3++;

			break;

		case 134:
   		rr+=log(dzx*dzx+dzy*dzy)*10;		
			if (fabs(dzx) > dStrands || fabs(dzy) > dStrands)
			{
				rr+=nFF;
			}
			break;
			
		case 135:
			if (fabs(dzx) < limit || fabs(dzy) < limit)
     		rr+=log(dzx*dzx+dzy*dzy)*10;
			else
				i+=nFF;
			break;

		case 136:
			rr+=log(dzx*dzx+dzy*dzy)*10;		
			if (fabs(dzx) > limit || fabs(dzy) > limit)
				i+=nFF;
			break;

		case 137:
			if (fabs(dzx) < limit || fabs(dzy) < limit)
     		rr+=log(dzx*dzx+dzy*dzy)*10;
			else
				i+=nFF;
			break;

		case 138:
			rr+=log(dzx*dzx+dzy*dzy)*10;		
			if (fabs(1/dzx*dzy) > limit)
				i+=nFF;
			break;

		case 139:
			rr+=log(dzx*dzx+dzy*dzy)*10;		
			if (fabs(dzx) > limit || fabs(dzy) > limit)
				i+=nFF;

			dzx_save = dzx;
			dzy_save = dzy;
			break;

		case 140:
			rr+=log(dzx*dzx+dzy*dzy)*2;		
			if (fabs(dzx) > limit || fabs(dzy) > limit)
				i+=nFF;
			
			dzx_save = dzx;
			dzy_save = dzy;
			break;

		case 141:
			rr+=log(dzx*dzx+dzy*dzy)*nBay100;		
			
			dzx_save = dzx;
			dzy_save = dzy;
			
			break;

		case 142:
			rr+=log(dzx*dzx+dzy*dzy);		
			if (fabs(dzx) > limit || fabs(dzy) > limit)
				i+=nFF;
						
			dzx_save = dzx;
			dzy_save = dzy;
			break;

		case 143:
			rr+=log(dzx*dzx+dzy*dzy)*8;		
			if (fabs(dzx) > limit || fabs(dzy) > limit)
				i+=nFF;
			//i%=NMAX;
						
			dzx_save = dzx;
			dzy_save = dzy;
			break;

		case 144:
			if (fabs(dzx) < dStrands || fabs(dzy) < dStrands)
			{
				rr+=nFF;
			}

			dzx_save = dzx;
			dzy_save = dzy;
			break;

		case 145:
			if (fabs(dzx) < dStrands || fabs(dzy) < dStrands)
			{
				rr+=nFF;
			}

			dzx_save = dzx;
			dzy_save = dzy;
			break;
		
		case 146:
			rr+=log(dzx*dzx+dzy*dzy)*(1+nBay100);		
			break;

		case 147:
			rr+=log(dzx*dzx+dzy*dzy)*(1+nBay100);								
			dzx_save = dzx;
			dzy_save = dzy;			
			break;

		case 148: 
			if (fabs(dzx) < z.magnitude() || fabs(dzy) < z.magnitude())
				rr+=nFF;
			break;

		case 149:
			if (fabs(dzx) < dStrands || fabs(dzy) < dStrands)
			{
				rr += atan(fabs(dzy/dzx))*atan(fabs(dzx/dzy))*2;
			}
			break;

		case 150:
			if (dzx < c.real()+dStrands && dzx > c.real()-dStrands)
			{
				dzx_save += z.magnitude();
			}
			if (dzy < c.imag()+dStrands && dzy > c.imag()-dStrands)
			{
				dzy_save += z.magnitude();
			}
			
			break;

		case 151:
			if (dzx < c.real()+dStrands && dzx > c.real()-dStrands)
			{
				dzx_save += fabs(atan(dzx/dzy))*3;
				dzy_save += fabs(atan(dzy/dzx))*3;
			}
			else
			{
				dzx_save += z.magnitude();
				dzy_save += z.magnitude();
			}
			
			break;

		case 152:
			if (fabs(dzx) < dStrands || fabs(dzy) < dStrands)
			{
				dzx_save += (atan(fabs(dzx/dzy)))*3;
				dzy_save += (atan(fabs(dzy/dzx)))*3;
			}

			break;

		case 153:
			if (fabs(dzx) < dStrands || fabs(dzy) < dStrands)
			{
				rr += (fabs(dzx) + fabs(dzy));
			}								
			if (dzx < c.real()+dStrands && dzx > c.real()-dStrands)
			{
				rr += (fabs(dzx) + fabs(dzy));
			}
			break;

		/////////////////////////////////////////////////
		//	Begin new strands technques
		case 154:
			zz	= z;
			zz2 = z2;
			if (fabs(dzx) < dStrands || fabs(dzy) < dStrands)
			{
				z		= cmplx(42,42);
				z2	= cmplx(42,42);
			}			
			break;

		case 171:  // Part II
			zz	= z;
			zz2 = z2;
			if (fabs(dzx) < dStrands || fabs(dzy) < dStrands)
			{
				z		= cmplx(42,42);
				z2	= cmplx(42,42);
			}			
			
			break;

		case 155:
			if ((fabs(dzx) <= dStrands_HI && fabs(dzx) > dStrands_LO) ||
				(fabs(dzy) <= dStrands_HI && fabs(dzy) > dStrands_LO))        
			{
				zz	= z;
				zz2 = z2;
				z		= cmplx(42,42);
				z2	= cmplx(42,42);
			}			
			break;

		case 156:			
			zz	= z;
			zz2 = z2;
			if (fabs(dzx) < fabs(c.real())+dStrands && 
					fabs(dzx) > fabs(c.real())-dStrands)
			{
				z		= cmplx(42,42);
				z2	= cmplx(42,42);
			}			
			if (fabs(dzy) < fabs(c.imag())+dStrands &&
					fabs(dzy) > fabs(c.imag())-dStrands)
			{
				z		= cmplx(42,42);
				z2	= cmplx(42,42);
			}			
			break;

		case 157:
			zz	= z;
			zz2 = z2;
			if (z.magnitude() <= dStrands_HI && z.magnitude() > dStrands_LO)    
			{
				z		= cmplx(42,42);
				z2	= cmplx(42,42);
			}			
			break;

		case 158:
			zz	= z;
			zz2 = z2;
			if (z.magnitude() <= dStrands_HI && z.magnitude() > dStrands_LO)    
			{
				z		= cmplx(42,42);
				z2	= cmplx(42,42);
			}			
			break;

		case 159:
			if (fabs(z.magnitude() - z2.magnitude()) < dStrands_HI &&
					fabs(z.magnitude() - z2.magnitude()) > dStrands_LO) 
			{
				zz	= z;
				zz2 = z2;
				z		= cmplx(42,42);
				z2	= cmplx(42,42);
			}			
			break;

		case 160:
			zz	= z;
			zz2 = z2;
			if (fabs(1/z.magnitude() - 1/z2.magnitude()) < dStrands_HI &&
					fabs(1/z.magnitude() - 1/z2.magnitude()) > dStrands_LO) 
			{
				z		= cmplx(42,42);
				z2	= cmplx(42,42);
			}			
			break;

////////////////////////////////

		case 161:
		case 165:
			zz	= z;
			zz2 = z2;
			if (z.magnitude() <= dStrands_HI &&
				z.magnitude() > dStrands_LO)    
			{
				z		= cmplx(42,42);
				z2	= cmplx(42,42);
			}			
			else
			{
				dzx_save = z.real();
				dzy_save = z.imag();
			}			
			break;

		case 162:
		case 166:
			zz	= z;
			zz2 = z2;
			if (z.magnitude() <= dStrands_HI &&
				z.magnitude() > dStrands_LO)    
			{
				z		= cmplx(42,42);
				z2	= cmplx(42,42);
			}			
			else
			{
				dzx_save = z.real();
				dzy_save = z.imag();
			}
			break;

		case 163:
		case 167:
			zz	= z;
			zz2 = z2;
			if (fabs(z.magnitude() - z2.magnitude()) < dStrands_HI &&
					fabs(z.magnitude() - z2.magnitude()) > dStrands_LO) 
			{
				z		= cmplx(42,42);
				z2	= cmplx(42,42);
			}			
			else
			{
				dzx_save = z.real();
				dzy_save = z.imag();
			}
			break;

		case 164:
		case 168:
			zz	= z;
			zz2 = z2;
			if (fabs(1/z.magnitude() - 1/z2.magnitude()) < dStrands_HI &&
					fabs(1/z.magnitude() - 1/z2.magnitude()) > dStrands_LO) 
			{
				z		= cmplx(42,42);
				z2	= cmplx(42,42);
			}			
			else
			{
				dzx_save = z.real();
				dzy_save = z.imag();
			}
			break;

		case 169:  // Clouds method
			nx = dim.cx - 1 - (int) (((CRMAX-dzx)/(CRMAX-CRMIN))*dim.cx);
			ny = dim.cy - 1 - (int) (((CIMAX-dzy)/(CIMAX-CIMIN))*dim.cy);

			if (nx >= 0 &&
					nx <  dim.cx &&
					ny >= 0 &&
					ny < dim.cy)
				lpDots[nx + ny*dim.cx] += 1; 

			break;

		case 170:
			
			dzx_save_quick = dzx_save;
			dzy_save_quick = dzy_save;

			dzx_save = dzx;
			dzy_save = dzy;

			break;

		case 172:
			zz	= z;
			zz2 = z2;
			if (fabs(1/z.magnitude()) < dStrands_HI &&
				fabs(1/z.magnitude()) > dStrands_LO)
			{
				z		= cmplx(42,42);
				z2	= cmplx(42,42);
			}			
			else
			{
				dzx_save = z.real();
				dzy_save = z.imag();
			}
			break;

		case 173:
			zz	= z;
			zz2 = z2;
			if (fabs(dzx*dzx) < dStrands || fabs(dzy*dzy) < dStrands)
			{
				z		= cmplx(42,42);
				z2	= cmplx(42,42);
			}			
			break;

		case 174:
			zz	= z;
			zz2 = z2;
			if (fabs(dzx*dzx) < fabs(c.real())+dStrands && 
					fabs(dzx*dzx) > fabs(c.real())-dStrands)
			{
				z		= cmplx(42,42);
				z2	= cmplx(42,42);
			}			
			if (fabs(dzy*dzy) < fabs(c.imag())+dStrands &&
					fabs(dzy*dzy) > fabs(c.imag())-dStrands)
			{
				z		= cmplx(42,42);
				z2	= cmplx(42,42);
			}			
			break;

		case 175:
			zz	= z;
			zz2 = z2;
			if (z.squares() < dStrands)
			//if (fabs(dzx*dzx) < dStrands && fabs(dzy*dzy) < dStrands)
			{
				z		= cmplx(42,42);
				z2	= cmplx(42,42);
			}			
			break;

		case 176:
			zz	= z;
			zz2 = z2;
			if (fabs(dzx*dzy) < dStrands)
			//if (fabs(dzx*dzx) < dStrands && fabs(dzy*dzy) < dStrands)
			{
				z		= cmplx(42,42);
				z2	= cmplx(42,42);
			}			
			break;

		// Begin the InkBlot filters
		case 177:		// 1
		case 178:		// 2
		case 193:		// 17
			if (i == 1)
				return;

			if (fabs(z.real()) < dStrands)  // re
			{
				x_temp = dStrands - z.real();
				xi = i;
			}
				
			if (fabs(z.imag()) < dStrands) // im
			{
				y_temp = dStrands - z.imag();
				yi = i;
			}

			if (z.abs() < dStrands)  // Bubbles
			{
				temp = dStrands - z.abs();
				ii = i;
			}

			break;

		case 179: // 3
			if (i == 1)
				return;

			if (fabs(z.real()) < dStrands)  // re
			{
				x_temp = dStrands - fabs(z.real());
				xi = i;
			}
				
			if (fabs(z.imag()) < dStrands) // im
			{
				y_temp = dStrands - fabs(z.imag());
				yi = i;
			}

			if (z.abs() < dStrands)  // Bubbles
			{
				temp = dStrands - z.abs();
				ii = i;
			}
			
			break;

		case 180:
			if (i == 1)
				return;

			dzx = fabs(z.real());
			dzy = fabs(z.imag());

			if (dzx < dStrands)
			{
				xi ++;
				x_temp = dStrands - dzx;
			}
			
			if (dzy < dStrands)
			{
				yi ++;
				y_temp = dStrands - dzy;
			}

			if (z.abs() < dStrands)  // Bubbles
			{
				temp = dStrands - z.abs();
				ii = i;
			}
			
			break;
	
		case 181:	// 5
		case 182: // 6
		case 183: // 7
		case 195: // 19
			if (i == 1)
				return;

			dzx = fabs(z.real());
			dzy = fabs(z.imag());

			if (dzx < dStrands)
			{
				//x_temp1 = atan(fabs(dzx/c.real()));
				x_temp	= dStrands - dzx;
				xi = i;
			}
			
			if (dzy < dStrands)
			{
				//y_temp1 = atan(fabs(dzy/c.imag()));
				y_temp  = dStrands - dzy;
				yi = i;
			}

			if (z.abs() < dStrands)  // Bubbles
			{
				temp = dStrands - z.abs();
				ii = i;
			}
			
			break;

		case 184:		// 8
		case 186:		// 10:
			if (i == 1)
				return;
			
			dzx = fabs(z.real()*z.real());
			dzy = fabs(z.imag()*z.imag());

			if (dzx < dStrands)  
			{
				x_temp = dStrands - dzx;
				xi = i;
			}
			
			if (dzy < dStrands)
			{
				y_temp = dStrands - dzy;
				yi = i;
			}

			if (z.abs() < dStrands)  // Bubbles
			{
				temp = dStrands - z.abs();
				ii = i;
			}
			
			break;
			
		case 185:
			break;

		case 187:	// 11:
		case 190:	// 14:
		case 192:	// 16:
		case 194:	// 18:
			if (i == 1)
				return;

			dzx = fabs(z.real()*z.real());
			dzy = fabs(z.imag()*z.imag());

			if (z.abs() < dStrands*2)  // Bubbles
			{
				x_temp = dStrands*2 - z.abs();
				xi = i;
			}

			if (z.abs() < dStrands*3)  // Bubbles
			{
				y_temp = dStrands*3 - z.abs();
				yi = i;
			}

			break;
			
		case 188: // 12:
			if (i == 1)
				return;
			
			if (z.real()*z.real() < dStrands)  // re
			{
				x_temp = dStrands - z.real()*z.real();
				xi = i;
			}
				
			if (z.imag()*z.imag() < dStrands) // im
			{
				y_temp = dStrands - z.imag()*z.imag();
				yi = i;
			}

			if (z.abs() < dStrands)  // Bubbles
			{
				temp = dStrands - z.abs();
				ii = i;
			}

			break;

		case 191: // 15:
			if (i == 1)
				return;
			
			if (fabs(z.real()*z.real()) < dStrands)  // re
			{
				x_temp = dStrands - z.real()*z.real();
				xi = i;
			}
				
			if (fabs(z.imag()*z.imag()) < dStrands) // im
			{
				y_temp = dStrands - z.imag()*z.imag();
				yi = i;
			}

			if (z.abs() < dStrands)  // Bubbles
			{
				temp = dStrands - z.abs();
				ii = i;
			}

			break;

////////////////////////////////////////////

		default:
			break;
	}

	if (bMFilter) 
	{
		// Fractal Dimension or Standard Deviation
		// Make sure i is within limits
		//if (i >= NMAX || i < 0)
			//i = NMAX - 1;

		// Store the data into the temp arrays for Standard Deviation
		// and Fractal Dimension calculations
		pXTemp[i] = dzx;
		pYTemp[i] = dzy;	
	}

}
