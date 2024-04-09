// Filters.cpp

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

void CFlarium24View::Delta_z(double dzx, double dzy)
{
	switch(nFilter)
	{
		case 1:	  
			if (fabs(dzx) < z.squares() || fabs(dzy) < z.squares())
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
				dzx_save += z.squares();
			}
			if (dzy < c.imag()+dStrands && dzy > c.imag()-dStrands)
			{
				dzy_save += z.squares();
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
				dzx_save += z.squares();
				dzy_save += z.squares();
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
			if (fabs(dzx) < z.squares() || fabs(dzy) < z.squares())
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
				dzx_save += z.squares();
			}
			if (dzy < c.imag()+dStrands && dzy > c.imag()-dStrands)
			{
				dzy_save += z.squares();
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
				dzx_save += z.squares();
				dzy_save += z.squares();
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
//			if (fabs(dzx) < dStrands || fabs(dzy) < dStrands)
//				b_MAX = TRUE;
			if (fabs(dzx) < dStrands || fabs(dzy) < dStrands)
			{
				zz	= z;
				zz2 = z2;
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
//			if (fabs(dzx) < dStrands || fabs(dzy) < dStrands)
//			{
//				zz	= z;
//				zz2 = z2;
//				z		= cmplx(42,42);
//				z2	= cmplx(42,42);
//			}			
			break;

		case 156:
			if (fabs(dzx) < fabs(c.real())+dStrands && 
					fabs(dzx) > fabs(c.real())-dStrands)
			{
				zz	= z;
				zz2 = z2;
				z		= cmplx(42,42);
				z2	= cmplx(42,42);
			}			
			if (fabs(dzy) < fabs(c.imag())+dStrands &&
					fabs(dzy) > fabs(c.imag())-dStrands)
			{
				zz	= z;
				zz2 = z2;
				z		= cmplx(42,42);
				z2	= cmplx(42,42);
			}			
			break;

		case 157:
			if (z.squares() <= dStrands_HI && z.squares() > dStrands_LO)    
			{
				zz	= z;
				zz2 = z2;
				z		= cmplx(42,42);
				z2	= cmplx(42,42);
			}			
			break;

		case 158:
			if (z.squares() <= dStrands_HI && z.squares() > dStrands_LO)    
			{
				zz	= z;
				zz2 = z2;
				z		= cmplx(42,42);
				z2	= cmplx(42,42);
			}			
			break;

		case 159:
			if (fabs(z.squares() - z2.squares()) < dStrands_HI &&
					fabs(z.squares() - z2.squares()) > dStrands_LO) 
			{
				zz	= z;
				zz2 = z2;
				z		= cmplx(42,42);
				z2	= cmplx(42,42);
			}			
			break;

		case 160:
			if (fabs(1/z.squares() - 1/z2.squares()) < dStrands_HI &&
					fabs(1/z.squares() - 1/z2.squares()) > dStrands_LO) 
			{
				zz	= z;
				zz2 = z2;
				z		= cmplx(42,42);
				z2	= cmplx(42,42);
			}			
			break;

////////////////////////////////

		case 161:
		case 165:
			zz	= z;
			zz2 = z2;
			if (z.squares() <= dStrands_HI &&
				z.squares() > dStrands_LO)    
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
			if (z.squares() <= dStrands_HI &&
				z.squares() > dStrands_LO)    
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
			if (fabs(z.squares() - z2.squares()) < dStrands_HI &&
					fabs(z.squares() - z2.squares()) > dStrands_LO) 
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
			if (fabs(1/z.squares() - 1/z2.squares()) < dStrands_HI &&
					fabs(1/z.squares() - 1/z2.squares()) > dStrands_LO) 
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

void CFlarium24View::Filter_Complete()
{	
	int NMAX_Save = NMAX;
	
	switch(nFilter)
	{
		case 1:	
			i += (int) rr;			
			break;

		case 2:
			i += (int)(rr*10*nBay100);
			break;

		case 3:
			rr = dzx_save+dzy_save;
			i += (int)(rr*nBay100);
			break;

		case 4:
			//rr = atan(fabs(dzx_save/dzy_save));
			rr = dzx_save+dzy_save;
			i += (int)(rr*nBay100);
			break;

		case 5:
			if (dzx_save > dzy_save)
				rr = fabs(dzx_save)*nBay100;
			else
				rr = fabs(dzy_save)*nBay100;
			i += (int)(rr*nBay100);
			break;

		case 6:
			i+=(int)(log(dzx_save*dzx_save+dzy_save*dzy_save)*10);
			break;

		case 7:
			i+=(int)(sin(fabs(dzx_save)*fabs(dzy_save))*10);
			break;

		case 8:
			i+=(int)(sin(fabs(dzx_save)/fabs(dzy_save))*10);
			break;

		case 9:
			if (z.squares() < dBailout)
			{
				i += (int)(1/fabs(sin(dzx_save / dzy_save)));
			}
			else
			{
				i += (int)fabs(sin(dzx_save / dzy_save));
			}
			break;

		case 10:
			if (z.squares() < dBailout)
			{
				i += (int)(1/fabs(atan(dzx_save / dzy_save)));
			}
			else
			{
				i += (int)fabs(atan(dzx_save / dzy_save));
			}
			break;

		case 11:
			if (z.squares() > dBailout)
			{
				i += (int)(1/fabs(dzx_save * dzy_save));
			}
			else
			{
				i += (int)fabs(dzx_save * dzy_save);
			}

			break;

		case 12:
			dzx = z.real();
			dzy = z.imag();
			i = i * (int)((atan(fabs(dzx*dzx/dzy*dzy)))*10*nBay100);
			break;

		case 13:
			dzx=fabs(atan(z.real()/z.imag()));
			dzy=fabs(atan(dzx_save/dzy_save));
			i=(int)((dzx+dzy)*100);
			break;

		case 14:  // Fractal Dimension
			break;

		case 15:  // Standard Deviation
			break;

		case 16:
			i += jrw;
			i = abs(i);

			dzx=fabs(atan(z.real()/z.imag()));
			dzy=fabs(atan(dzx_save/dzy_save));
			i+=(int)((dzx+dzy)*100);
			//i=(int)((dzx+dzy)*100);
			break;

		case 17:	
			i += jrw;
			i = abs(i);
			return;

		case 18:
			i += jrw;	
			i = abs(i);
			return;
		
		case 130:
			//i = i3;
			//i = (int) ((sin(fabs(1 + x_rmax - x_rmin)) * sin(fabs(1 + y_rmax - y_rmin))) * 40);
			i += (int) (atan(fabs(x_rmax * x_rmin)/fabs(y_rmax * y_rmin)) * 40);

			return;			

		case 131:
			if (i >= NMAX-1)
				i += i3;
			else
				i += (int)rr;
			return;

		case 132:
			i += i3;
			return;

		case 133:
			if (rr != 0 && i3 != 0)
				i += (int)(fabs(dzy_save - dzx_save) + fabs(rr + i3));
			else
				if (rr != 0)
					i += (int)(fabs(dzy_save - dzx_save) + fabs(rr));
			else
				if (i3 != 0)
					i += (int)fabs(dzy_save - dzx_save) + i3;
			else
				i += (int)fabs(dzy_save - dzx_save);
			return;

		case 134:
			rr = (double) ((int)rr%(NMAX/2));
			if ((int)(z.real()*2)%2 == 0 || (int)(z.imag()*2)%2 == 0)
				i += (int)rr;
			else
				i += (int)rr + (NMAX/2);
			return;

		case 135:
			rr = (double) ((int)rr%(NMAX/2));
			if ((int)(z.real()*2)%2 == 0 || (int)(z.imag()*2)%2 == 0)
				i += (int)rr;
			else
				i += (int)rr + (NMAX/2);
			return;

		case 136:
			i += (int)rr;
			return;

		case 137:
			i += (int)rr;
			return;

		case 138:
			i += (int)rr;
			return;

		case 139:
			i += (int)(atan(dzx_save/dzy_save) * 80); 
			return;

		case 140:
			i += (int)(rr + atan(fabs(dzx_save/dzy_save)) * 30); 
			return;

		case 141:
			//i += (int)(rr); 
			i += (int)rr;
			
			//i = (int)(rr + atan(fabs(dzx_save/dzy_save)) * 30); 

//			i = (int)(rr + atan(fabs(dzx_save/dzy_save)) * 70); 
//			i = i%(NMAX/2);
//			if ((int)rr%2 == 1)
//				i += (NMAX/2);
			return;

		case 142:
			i += (int)(rr + atan(fabs(dzx_save/dzy_save)) * 50); 
			return;

		case 143:
			i += (int)(rr/3 + atan(fabs(dzx_save/dzy_save)) * 30); 
			if ((int)atan(fabs(dzx_save/dzy_save))%2 == 0 && i < (NMAX/2))
				i += (NMAX/2);
			return;

		case 144:
			i += (int) (atan(fabs(z.imag()/z.real())) * 13 + (rr * 10));
				
      return;

		case 145:
//			if (rr > 1)	
//				i = (int) (atan(fabs(z.imag()/z.real())) * nBay100 * 1
//					* (rr * nBay1000 * 1));
      
//				i = (int) (atan(fabs(z.imag()/z.real())) * nBay100 * 1
//					+ (rr * nBay1000 * 5));
						
//			if (rr > 1)	
//				i += (int) (rr * nBay100 * 10 *
//					(atan(fabs(z.imag()/z.real())) * nBay100));
//			else
//       i = 0;	

			if (rr >= 1)	
				i += (int) (atan(fabs(z.imag()/z.real())) * nBay100 * 5
					+ (rr * nBay1000 * 5));
			else
        i = 0;      
            
      return;

		case 146:
			i += (int)rr; 
			return;

		case 147:
			i += (int)(rr + atan(fabs(dzx_save/dzy_save)) * (10+nBay1000)); 
			return;

		case 148:
			i += (int) rr;			
			return;

		case 149:
			i += (int)(rr*10*nBay100);
			return;

		case 150:
			rr = dzx_save+dzy_save;
			i += (int)(rr*nBay100);
			return;

		case 151:
			rr = dzx_save+dzy_save;
			i += (int)(rr*nBay100);
			return;

		case 152:
			if (dzx_save > dzy_save)
				rr = fabs(dzx_save)*nBay100;
			else
				rr = fabs(dzy_save)*nBay100;
			i += (int)(rr*nBay100);		
			return;

		case 153:
			i += (int)(rr*nBay100);
			return;		

		case 154:
			z = zz;
			z2 = zz2;
									
			dzx = fabs(z.real());
			dzy = fabs(z.imag());

			//dzx_save = fabs(z2.real());
			//dzy_save = fabs(z2.imag());

			temp = 0;
			if (dzx < dStrands || dzy < dStrands) 
			{
				if (dzx < dStrands && dzx != 0)
					temp = fabs(dStrands-dzx)*10000*nBay100;

				if (dzy < dStrands && dzy != 0)
					temp += fabs(dStrands-dzy)*10000*nBay100;

				rr=(int)i;
				rr=rr+(int)temp;
				i=(int)rr;

			}
			break;

		case 155:
			z = zz;
			z2 = zz2;

			dzx = fabs(z.real());
			dzy = fabs(z.imag());

			//dzx_save = fabs(z2.real());
			//dzy_save = fabs(z2.imag());

			temp = 0;
			if ((fabs(dzx) <= dStrands_HI && fabs(dzx) > dStrands_LO) ||
				  (fabs(dzy) <= dStrands_HI && fabs(dzy) > dStrands_LO))        
			{
				if ((fabs(dzx) <= dStrands_HI && fabs(dzx) > dStrands_LO) && dzx != 0)
					temp = fabs(dStrands_HI-dzx)*10000*nBay100;

				if ((fabs(dzy) <= dStrands_HI && fabs(dzy) > dStrands_LO) && dzy != 0)
					temp += fabs(dStrands_HI-dzy)*10000*nBay100;

				rr=(int)i;
				rr=rr+(int)temp;
				i=(int)rr;

			}
			break;

		case 156:
			z = zz;
			z2 = zz2;

			dzx = fabs(z.real());
			dzy = fabs(z.imag());

			dzx_save = fabs(c.real());
			dzy_save = fabs(c.imag());

			temp = 0;
			if ((dzx < dzx_save+dStrands && dzx > dzx_save-dStrands) ||
				  (dzy < dzy_save+dStrands && dzy > dzy_save-dStrands))        
			{
				if ((dzx < dzx_save+dStrands && dzx > dzx_save-dStrands) && dzx != 0)
					temp = fabs(dzx_save+dStrands-dzx)*10000*nBay100;

				if ((dzy < dzy_save+dStrands && dzy > dzy_save-dStrands) && dzy != 0)
					temp += fabs(dzy_save+dStrands-dzy)*10000*nBay100;

				rr=(int)i;
				rr=rr+(int)temp;
				i=(int)rr;

			}
			break;

		case 157:
			z = zz;
			z2 = zz2;
			if (z.squares() <= dStrands_HI && z.squares() > dStrands_LO)    
			{
				i = (int) (fabs(c.squares() - z.squares())*20000*nBay100);
				if (z.squares() > z2.squares())
					i+=NMAX/2;
			}
			break;

		case 158:
			z = zz;
			z2 = zz2;
			if (z.squares() <= dStrands_HI && z.squares() > dStrands_LO)    
			{
				i = (int) (fabs(c.squares() - z.squares())*20000*nBay100);				
				rr = fabs((z2.squares() - z.squares())*1000*nBay100);
				i += (int) rr;
			}
			break;
		
		case 159:
			z = zz;
			z2 = zz2;
			if (fabs(z.squares() - z2.squares()) < dStrands_HI &&
					fabs(z.squares() - z2.squares()) > dStrands_LO) 
			{
				i += (int) (fabs(c.squares() - z.squares() + z2.squares())*1000*nBay100);				
			}			
			break;

		case 160:
			z = zz;
			z2 = zz2;
			if (fabs(1/z.squares() - 1/z2.squares()) < dStrands_HI &&
					fabs(1/z.squares() - 1/z2.squares()) > dStrands_LO) 
			{
				i += (int) (fabs(1/z.squares() - 1/z2.squares())*1000*nBay100);				
			}			
			break;

////////////////////////////////////////////

		case 161:
		case 165:
			z = zz;
			z2 = zz2;
			if (z.squares() <= dStrands_HI &&
				z.squares() > dStrands_LO)    
			{
				ntemp = i;
				i = (int) (fabs(c.squares() - z.squares())*4000*nBay100);
				if (z.squares() > z2.squares())
					i+=NMAX/2;
				if (nFilter == 165)
					i += ntemp*(int)(8*nBay1000);
				if (nFilter == 161)
				{
					if ((int)(z.real()*10)%2 == 0)
						i += ntemp*(int)(8*nBay1000);
					else
						i -= ntemp*(int)(8*nBay1000);
					if ((int)(z.imag()*10)%2 == 0)
						i += ntemp*(int)(8*nBay1000);
					else
						i -= ntemp*(int)(8*nBay1000);
				}									
			}
			else
				i=0;
			break;

		case 162:
		case 166:
			z = zz;
			z2 = zz2;
			if (z.squares() <= dStrands_HI &&
				z.squares() > dStrands_LO)    
			{
				ntemp = i;

				i = (int) (fabs(c.squares() - z.squares())*2000*nBay100);				
				rr = fabs((z2.squares() - z.squares())*100*nBay100);
				i += (int) rr;
				if (nFilter == 166)
					i += ntemp*(int)(8*nBay1000);
				if (nFilter == 162)
				{
					//if (ntemp%2 == 0)
					if ((int)(z.real()*10)%2 == 0)
						i += ntemp*(int)(8*nBay1000);
					else
						i -= ntemp*(int)(8*nBay1000);
					if ((int)(z.imag()*10)%2 == 0)
						i += ntemp*(int)(8*nBay1000);
					else
						i -= ntemp*(int)(8*nBay1000);
				}						
			}
			else
				i=0;
			break;
		
		case 163:
		case 167:
			z = zz;
			z2 = zz2;
			if (fabs(z.squares() - z2.squares()) < dStrands_HI &&
				fabs(z.squares() - z2.squares()) > dStrands_LO) 
			{
				ntemp = i;
				i += (int) (fabs(c.squares() - z.squares() + z2.squares())*2000*nBay100);				
				if (nFilter == 167)
					i += ntemp*(int)(8*nBay1000);
				if (nFilter == 163)
				{
					//if (ntemp%2 == 0)
					if ((int)(z.real()*10)%2 == 0)
						i += ntemp*(int)(8*nBay1000);
					else
						i -= ntemp*(int)(8*nBay1000);
					if ((int)(z.imag()*10)%2 == 0)
						i += ntemp*(int)(8*nBay1000);
					else
						i -= ntemp*(int)(8*nBay1000);
				}						
			}			
			else
				i=0;
			break;

		case 164:
		case 168:
			z = zz;
			z2 = zz2;
			if (fabs(1/z.squares() - 1/z2.squares()) < dStrands_HI &&
				fabs(1/z.squares() - 1/z2.squares()) > dStrands_LO) 
			{
				ntemp = i;
				i += (int) (fabs(1/z.squares() - 1/z2.squares())*2000*nBay100);				
				if (nFilter == 168)
					i += ntemp*(int)(8*nBay1000);
				if (nFilter == 164)
				{
					//if (ntemp%2 == 0)
					if ((int)(z.real()*10)%2 == 0)
						i += ntemp*(int)(8*nBay1000);
					else
						i -= ntemp*(int)(8*nBay1000);
					if ((int)(z.imag()*10)%2 == 0)
						i += ntemp*(int)(8*nBay1000);
					else
						i -= ntemp*(int)(8*nBay1000);
				}						
			}			
			else
				i=0;
			break;

		default:
			break;
	}

//////////////
	if (bMFilter && (nFilter == 14 || nFilter == 15))
	{
		//if (i >= NMAX)
			//i = NMAX - 1;

		NMAX = i;

		// Set up to Calculate the Fractal Dimension
		if (i <= NMAX)
		{
			// Finish out the array with the last value
			for (i2 = i ; i2<NMAX ; i2++)
			{
				pXTemp[i2] = z.real();
				pYTemp[i2] = z.imag();
			}
		}
		
		// Initialize the mean with zero
		x_mean = 0;
		y_mean = 0;

		// Initialize the range	with the first value
		x_rmin = pXTemp[0];	// x range min
		x_rmax = pXTemp[0];	// x range max
		y_rmin = pYTemp[0];	// y range min
		y_rmax = pYTemp[0];	// y range max

		switch(nFilter)
		{
			case 14:			// Fractal Dimension
				if (i < 3)
				{
					NMAX = NMAX_Save;
					return;
				}

				//if (bQuickMode)
				//{
				//	iQuickAbort = NMAX;
				//	JMAX = NMAX = i;
				//}
				
				for (i2 = 0 ; i2<NMAX ; i2++)
				{
					// Get sum x and y
					x_mean += pXTemp[i2];											
					y_mean += pYTemp[i2];

					// Get min x
					if (pXTemp[i2] < x_rmin)
						x_rmin = pXTemp[i2];

					// Get max x
					if (pXTemp[i2] > x_rmax)
						x_rmax = pXTemp[i2];

					// Get min y
					if (pYTemp[i2] < y_rmin)
						y_rmin = pYTemp[i2];

					// Get max y
					if (pYTemp[i2] > y_rmax)
						y_rmax = pYTemp[i2];
				}

				x_mean = x_mean / NMAX;
				y_mean = y_mean / NMAX;

				x_std = 0;
				y_std = 0;

				for (i2 = 0 ; i2<NMAX ; i2++)
				{
					x_std = x_std + (pXTemp[i2] - x_mean)*(pXTemp[i2] - x_mean); 
					y_std = y_std + (pYTemp[i2] - y_mean)*(pYTemp[i2] - y_mean); 
				}

				x_std = sqrt(x_std / (NMAX-1));		// Standard Deviation x
				y_std = sqrt(y_std / (NMAX-1));		// Standard Deviation y

				// Initialize complex variables
				cx_std = cmplx(x_std, 0);	// Complex Standard deviation	x
				cy_std = cmplx(y_std, 0);	// Complex Standard deviation	y

				cFDx = cmplx (1, 0);				// Complex Fractal Dimension x
				cFDy = cmplx (1, 0);				// Complex Fractal Dimension y

				cRng_x = cmplx (x_rmax - x_rmin, 0);	// Complex Range x
				cRng_y = cmplx (y_rmax - y_rmin, 0);	// Complex Range y

				cNMAX = cmplx (NMAX, 0); 
				
				//////////////////////////////////////////////////////////////
				// Fractal Dimension Equation ...
				// Ju = Upper Jaenisch coefficient 
				// Initialize Ju=1;
				// Iterate Ju = [log(R/S*N*J]/[log(1/N)] until abs(Ju+1)-Ju < .0001.
				// if ( 0  <= J <= .5,) D(j) = 1/(1-Ju)
				// if (.5  <=	J <= 1.0) D(j) = 1/Ju.
				///////////////////////////////////////////////////////////////

				//////////////////////////////////////////////////////////////
				// Real
				////////////////////////////////////////////////////////////				
				dm = 99;
				da = 0;
				nDIter_x = 0;
				denominator = log((double)(1.0/(double)NMAX));
				//while (fabs(da - dm) > .0001 && nDIter_x++ < NMAX-2)
				while (fabs(da - dm) > .0001 && nDIter_x++ < 10000)
				{
					// Calculate Fractal Dimension (real)
					da = dm;
					cFDx = (cRng_x/(cx_std*cNMAX*cFDx)).clog()/denominator;
					dm = cFDx.real();
					if (nDIter_x == 1)
						dFDx_0 = 2.0 - dm;
				}

				dFDx = cFDx.real();

				if (dFDx <= .5)
					dFDx = 1 / (1 - dFDx);
				else
					dFDx = 1 / dFDx;

				////////////////////////////////////////////////////////////				
				// Imaginary
				////////////////////////////////////////////////////////////				
				dm = 99;
				da = 0;
				nDIter_y = 0;
				denominator = log((double)(1.0/(double)NMAX));
				//while (fabs(da - dm) > .0001 && nDIter_y++ < NMAX-2)
				while (fabs(da - dm) > .0001 && nDIter_y++ < 10000)
				{
					// Calculate Fractal Dimension (real)
					da = dm;
					cFDy = (cRng_y/(cy_std*cNMAX*cFDy)).clog()/denominator;
					dm = cFDy.real();
					if (nDIter_y == 1)
						dFDy_0 = 2.0 - dm;
				}

				dFDy = cFDy.real();

				if (dFDy <= .5)
					dFDy = 1 / (1 - dFDy);
				else
					dFDy = 1 / dFDy;
				////////////////////////////////////////////////////////////				
				
				////////////////////////////////////////////////////////////
				// Apply Fractal Dimension to a color
				
				switch (nFDOption)
				{
//					case 0:
//						// Addition
//						jrw = (int) ((dFDx+dFDy) * 100 * nBay100);
//						break;
				
					case 1:
						// Fractal Dimension Real Initial (FD_0)
						jrw = (int) (dFDx_0 * 200.0 * nBay100);
						break;
				
					case 2:
						// Fractal Dimension Imginary	Initial (FD_0)
						jrw = (int) (dFDy_0 * 200.0 * nBay100);
						break;
				
					case 3:
						// (FD_0) Addition
						jrw = (int) ((dFDx_0+dFDy_0) * 200 * nBay100);
						break;

					case 4:	
						// (FD_0) Sum of Squares
						jrw = (int) ((dFDx_0*dFDx_0+dFDy_0*dFDy_0) * 200 * nBay100);
						break;

					case 5:
						// (FD_0) Multiplication
						jrw = (int) (dFDx_0 * dFDy_0 * 200 * nBay100);
						break;
					
					case 6:
						// Fractal Dimension Real
						jrw = (int) (dFDx * 200.0 * nBay100);
						break;
				
					case 7:
						// Fractal Dimension Imginary
						jrw = (int) (dFDy * 200.0 * nBay100);
						break;
				
					case 8:
						// FD Addition
						jrw = (int) ((dFDx+dFDy) * 200 * nBay100);
						break;

					case 9:	
						// FD Sum of Squares
						jrw = (int) ((dFDx*dFDx+dFDy*dFDy) * 200 * nBay100);
						break;

					case 10:
						// FD Multiplication
						jrw = (int) (dFDx * dFDy * 200 * nBay100);
						break;
									
					default:
						AfxMessageBox("FD Error");
						break;
				}				

				i += abs(jrw);

				NMAX = NMAX_Save;
				return;

				break;

			default:			// Standard deviation by default
				for (i2 = 0 ; i2<i ; i2++)
				{
					// Get sum x and y
					x_mean += pXTemp[i2];											
					y_mean += pYTemp[i2];

					// Get min x
					if (pXTemp[i2] < x_rmin)
						x_rmin = pXTemp[i2];

					// Get max x
					if (pXTemp[i2] > x_rmax)
						x_rmax = pXTemp[i2];

					// Get min y
					if (pYTemp[i2] < y_rmin)
						y_rmin = pYTemp[i2];

					// Get max y
					if (pYTemp[i2] > y_rmax)
						y_rmax = pYTemp[i2];
				}

				if (i != 0)
				{
					x_mean = x_mean / (double)i;
					y_mean = y_mean / (double)i;
				}

				x_std = 0;
				y_std = 0;

				for (i2 = 0 ; i2<i ; i2++)
				{
					x_std = x_std + (pXTemp[i2] - x_mean)*(pXTemp[i2] - x_mean); 
					y_std = y_std + (pYTemp[i2] - y_mean)*(pYTemp[i2] - y_mean); 
				}
								
				if (i>1)
				{
					x_std = (x_std / (i-1));
					y_std = (y_std / (i-1));
				}
				else
				{
					x_std = 0;
					y_std = 0;
				}

				if (x_std == 0 && y_std == 0)
					jrw = 0;
				else
					jrw = (int) (log((x_std + y_std)/2) * 30 * nBay100); // 10

				i += abs(jrw);
										
				NMAX = NMAX_Save;
				return;
		}
	}
}

/////////////////////////////////////////////////
void CFlarium24View::Apply_The_Color()
{  				
	if ((red & 0x1FF) > 0xFF) 
    red = red ^ 0xFF;    // Invert the color

  if ((grn & 0x1FF) > 0xFF) 
   grn = grn ^ 0xFF;    // Invert the color
      
  if ((blu & 0x1FF) > 0xFF) 
    blu = blu ^ 0xFF;    // Invert the color
}

void CFlarium24View::Generalized_Coloring_Method()
{
	// Generalized Coloring Method
	
	// Generalized Coloring Method
	red = i*nRed+nRedStart;
	grn = i*nGrn+nGrnStart;
	blu = i*nBlu+nBluStart;

  Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method1()
{	
	temp=0;

	dzx = fabs(z.real());
	dzy = fabs(z.imag());

	dzx_save = fabs(c.real());
	dzy_save = fabs(c.imag());

	if (dzx_save > dzx)		
		temp += (dzx_save-dzx)*10*nBay100;
	else
		temp += (dzx-dzx_save)*10*nBay100;
		
	if (dzy_save > dzy)		
		temp += (dzy_save-dzy)*10*nBay100;
	else
		temp += (dzy-dzy_save)*10*nBay100;

	i+=(int)temp;

	// Generalized Coloring Method
	if (dzx < dzx_save
	 || dzy < dzy_save)
	{		
		//red = i*nRed+nRedStart+min;
		//grn = i*nGrn+nGrnStart+min;
		//blu = i*nBlu+nBluStart+min;
		i+=min;
	}
	else
	{
		//red = i*nRed+nRedStart+max;
		//grn = i*nGrn+nGrnStart+max;
		//blu = i*nBlu+nBluStart+max;
		i+=max;
	}

	red = i*nRed+nRedStart;
	grn = i*nGrn+nGrnStart;
	blu = i*nBlu+nBluStart;

	Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method2()
{
	temp=0;

	dzx = fabs(z.real());
	dzy = fabs(z.imag());

	dzx_save = fabs(c.real());
	dzy_save = fabs(c.imag());

	if (dzx_save > dzx)		
		temp += (dzx_save-dzx)*10*nBay100;
	else
		temp += (dzx-dzx_save)*10*nBay100;
		
	if (dzy_save > dzy)		
		temp += (dzy_save-dzy)*10*nBay100;
	else
		temp += (dzy-dzy_save)*10*nBay100;
		
	i+=(int)temp;

	if (z.real() > 0)
	{
		//red = i*nRed+nRedStart+min;
		//grn = i*nGrn+nGrnStart+min;
		//blu = i*nBlu+nBluStart+min;
		i+=min;
	}
	else
	{
		//red = i*nRed+nRedStart+max;
		//grn = i*nGrn+nGrnStart+max;
		//blu = i*nBlu+nBluStart+max;
		i+=max;
	}

	red = i*nRed+nRedStart;
	grn = i*nGrn+nGrnStart;
	blu = i*nBlu+nBluStart;

	Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method3()
{
	temp = atan(fabs(z.real()/z.imag()))*10*nBay100;

	if (z.squares() < dBailout)
		temp = 1/atan(fabs(z.real()/z.imag()))*10*nBay100;
		
	i+=(int)temp;

	// Generalized Coloring Method
	if (fabs(z.real()) < fabs(c.real())
	 || fabs(z.imag()) < fabs(c.imag()))
	{
		//red = i*nRed+nRedStart+min;
		//grn = i*nGrn+nGrnStart+min;
		//blu = i*nBlu+nBluStart+min;
		i+=min;
	}
	else
	{
		//red = -i*nGrn+nRedStart+max;
		//grn = -i*nBlu+nGrnStart+max;
		//blu = -i*nRed+nBluStart+max;
		i=(i+max)*(-1);
	}

	red = i*nRed+nRedStart;
	grn = i*nGrn+nGrnStart;
	blu = i*nBlu+nBluStart;

	Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method4()
{
	z.set_real(x);
	z.set_imag(y);

	temp = atan(fabs(z.real()/z.imag()))
				-atan(fabs(z.imag()/z.real()))*10*nBay100;

	if (z.squares() < dBailout)
		temp = atan(1/fabs(z.real()/z.imag()))
				-atan(1/fabs(z.imag()/z.real()))*100*nBay100;
		
	i+=(int)temp;

	// Generalized Coloring Method 4
	if (fabs(z.real()) < fabs(c.real())
	 || fabs(z.imag()) < fabs(c.imag()))
	{
		//red = i*nRed+nRedStart+min;
		//grn = i*nGrn+nGrnStart+min;
		//blu = i*nBlu+nBluStart+min;
		i+=min;
	}
	else
	{
		//red = -i*nGrn+nRedStart+max;
		//grn = -i*nBlu+nGrnStart+max;
		//blu = -i*nRed+nBluStart+max;
		i+=max;
		i*=-1;
	}

	red = i*nRed+nRedStart;
	grn = i*nGrn+nGrnStart;
	blu = i*nBlu+nBluStart;

	Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method5()
{
	dzx = fabs(z.real());
	dzy = fabs(z.imag());

	dzx_save = fabs(c.real());
	dzy_save = fabs(c.imag());

	temp = atan(fabs(dzx/dzy))
				-atan(fabs(dzy/dzx))*10*nBay100;
	
	if (z.squares() < dBailout)
		temp = atan(1/fabs(dzx/dzy))
					+atan(1/fabs(dzy/dzx))*100*nBay100;		
	
	i+=(int)temp;

	if ((int)z.real() % 2 == 0)
	{
		//red = i*nRed+nRedStart+min;
		//grn = i*nGrn+nGrnStart+min;
		//blu = i*nBlu+nBluStart+min;
		i+=min;
	}
	else
	{
		//red = i*nRed+nRedStart+max;
		//grn = i*nGrn+nGrnStart+max;
		//blu = i*nBlu+nBluStart+max;
		i+=max;
	}
	
	red = i*nRed+nRedStart;
	grn = i*nGrn+nGrnStart;
	blu = i*nBlu+nBluStart;

	Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method6()
{
	dzx = fabs(z.real());
	dzy = fabs(z.imag());

	dzx_save = fabs(c.real());
	dzy_save = fabs(c.imag());

	temp = atan(fabs(dzx/dzy))*10*nBay100;
	
	i+=(int)temp;

	if (z.real()*z.imag() > c.real()*c.imag())
	{
		//red = i*nRed+nRedStart+min;
		//grn = i*nGrn+nGrnStart+min;
		//blu = i*nBlu+nBluStart+min;
		i+=min;
	}
	else
	{
		//red = i*nRed+nRedStart+max;
		//grn = i*nGrn+nGrnStart+max;
		//blu = i*nBlu+nBluStart+max;
		i+=max;
	}

	red = i*nRed+nRedStart;
	grn = i*nGrn+nGrnStart;
	blu = i*nBlu+nBluStart;

	Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method7()
{
	dzx = fabs(z.real());
	dzy = fabs(z.imag());

	dzx_save = fabs(c.real());
	dzy_save = fabs(c.imag());

	temp = 0;
	if ((int)(z.squares()*10) % 2 == 0)
		temp = sin(fabs(dzx*dzy*dzx_save*dzy_save))*10*nBay100;
	else
		temp = cos(fabs(dzx*dzy*dzx_save*dzy_save))*10*nBay100;

	if (z.squares() < dBailout)
	{
		if ((int)(z.squares()*10) % 2 == 0)
			temp = sin(1/fabs(dzx*dzy*dzx_save*dzy_save))*10*nBay100;
		else
			temp = cos(1/fabs(dzx*dzy*dzx_save*dzy_save))*10*nBay100;
	}
		
	i=i+(int)temp;

	if (dzx > dzx_save && dzy > dzy_save)
	{
		//red = i*nRed+nRedStart+min;
		//grn = i*nGrn+nGrnStart+min;
		//blu = i*nBlu+nBluStart+min;
		i+=min;
	}
	else
	{
		//red = i*nRed+nRedStart+max;
		//grn = i*nGrn+nGrnStart+max;
		//blu = i*nBlu+nBluStart+max;
		i+=max;
	}

	red = i*nRed+nRedStart;
	grn = i*nGrn+nGrnStart;
	blu = i*nBlu+nBluStart;

	Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method8()
{
	dzx = fabs(z.real());
	dzy = fabs(z.imag());

	//dzx_save = fabs(z2.real());
	//dzy_save = fabs(z2.imag());

	temp = 0;
	if (dzx < dStrands || dzy < dStrands) 
	{
		if (dzx < dStrands && dzx != 0)
			temp = fabs(dStrands-dzx)*20000*nBay100;

		if (dzy < dStrands && dzy != 0)
			temp += fabs(dStrands-dzy)*20000*nBay100;

		rr=(int)i;
		rr=rr+(int)temp;
		i=(int)rr;

	}

	// Generalized Coloring Method
	red = i*nRed+nRedStart;
	grn = i*nGrn+nGrnStart;
	blu = i*nBlu+nBluStart;
	
	Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method9()
{
	dzx = fabs(z.real());
	dzy = fabs(z.imag());

	//dzx_save = fabs(z2.real());
	//dzy_save = fabs(z2.imag());

	temp = sin(1/fabs((dzx)/(dzy)))*500*nBay100;
	
	rr=(int)i;
	rr=rr+(int)temp;
	i=(int)rr;

	// Generalized Coloring Method
	red = i*nRed+nRedStart;
	grn = i*nGrn+nGrnStart;
	blu = i*nBlu+nBluStart;
	
	Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method10()
{
	dzx = fabs(z.real());
	dzy = fabs(z.imag());

	dzx_save = fabs(c.real());
	dzy_save = fabs(c.imag());

	temp=z.squares()*cos(fabs(dzx*dzx/dzy*dzy))*1000*nBay100;
	
	rr=(int)i;
	rr=rr+(int)temp;
	i=(int)rr;

	if ((int)z.squares() % 2 == 0)
	{
		//red = i*nRed+nRedStart+min;
		//grn = i*nGrn+nGrnStart+min;
		//blu = i*nBlu+nBluStart+min;
		i+=min;
	}
	else
	{
		//red = i*nRed+nRedStart+max;
		//grn = i*nGrn+nGrnStart+max;
		//blu = i*nBlu+nBluStart+max;
		i+=max;
	}

	red = i*nRed+nRedStart;
	grn = i*nGrn+nGrnStart;
	blu = i*nBlu+nBluStart;

	Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method11()
{
	dzx = fabs(z.real());
	dzy = fabs(z.imag());

	dzx_save = fabs(c.real());
	dzy_save = fabs(c.imag());

	temp=sin(fabs(dzx*dzx/dzx_save*dzx_save-
		dzy*dzy/dzy_save*dzy_save)*10)*100*nBay100;
	
	rr=(int)i;
	rr=rr+(int)temp;
	i=(int)rr;

	if ((int)z.squares() % 2 == 0)
	{
		//red = i*nRed+nRedStart+min;
		//grn = i*nGrn+nGrnStart+min;
		//blu = i*nBlu+nBluStart+min;
		i+=min;
	}
	else
	{
		//red = i*nRed+nRedStart+max;
		//grn = i*nGrn+nGrnStart+max;
		//blu = i*nBlu+nBluStart+max;
		i+=max;
	}

	red = i*nRed+nRedStart;
	grn = i*nGrn+nGrnStart;
	blu = i*nBlu+nBluStart;

	Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method12()
{
	dzx = fabs(z.real());
	dzy = fabs(z.imag());

	dzx_save = fabs(c.real());
	dzy_save = fabs(c.imag());

	temp=cos(fabs(dzx*dzy/dzx_save*dzy_save)*10)*100*nBay100;
	
	rr=(int)i;
	rr=rr+(int)temp;
	i=(int)rr;

	if ((int)z.squares() % 2 == 0)
	{
		//red = i*nRed+nRedStart+min;
		//grn = i*nGrn+nGrnStart+min;
		//blu = i*nBlu+nBluStart+min;
		i+=min;
	}
	else
	{
		//red = i*nRed+nRedStart+max;
		//grn = i*nGrn+nGrnStart+max;
		//blu = i*nBlu+nBluStart+max;
		i+=max;
	}

	red = i*nRed+nRedStart;
	grn = i*nGrn+nGrnStart;
	blu = i*nBlu+nBluStart;

	Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method13()
{
	if (c.squares() < dBailout)
		temp = (atan(1/fabs(c.real()/c.imag()))
				-atan(1/fabs(c.imag()/c.real())))*100*nBay100;
	else
		temp = 0;
		
	i+=(int)temp;

	red = i*nRed+nRedStart+min;
	grn = i*nGrn+nGrnStart+min;
	blu = i*nBlu+nBluStart+min;

	Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method14()
{
	z.set_real(x);
	z.set_imag(y);

	//dzx = fabs(z.real());
	//dzy = fabs(z.imag());

	//temp = atan(fabs(z.real()/z.imag()))
	//			-atan(fabs(z.imag()/z.real()))*20*nBay100;

	temp = 0;
	if (z.squares() < dBailout)
		temp = atan(fabs(z.real()/z.imag()))*200*nBay100;
//	temp = atan(1/fabs(z.real()/z.imag()))
//				-atan(1/fabs(z.imag()/z.real()))*20*nBay100;
		
	i+=(int)temp;
		
	red = i*nRed+nRedStart;
	grn = i*nGrn+nGrnStart;
	blu = i*nBlu+nBluStart;

	Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method15()
{	

	temp = atan(fabs(c.real()/c.imag())) *
				 atan(fabs(z.real()/z.imag()));

	i+=(int)(temp*200*nBay100);

	red = i*nRed+nRedStart;
	grn = i*nGrn+nGrnStart;
	blu = i*nBlu+nBluStart;

	Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method16()
{
	temp = atan(fabs(z2.real()/z2.imag())) *
				 atan(fabs(z.real()/z.imag()));

	i+=(int)(temp*200*nBay100);
		
	red = i*nRed+nRedStart;
	grn = i*nGrn+nGrnStart;
	blu = i*nBlu+nBluStart;

	Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method17()
{
	temp = atan(fabs(z2.real()/z2.imag())) -
				 atan(fabs(z.real()/z.imag()));

	i+=(int)(temp*200*nBay100);
		
	red = i*nRed+nRedStart;
	grn = i*nGrn+nGrnStart;
	blu = i*nBlu+nBluStart;

	Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method18()
{
	temp = atan(fabs(z2.real()/z2.imag())) +
				 atan(fabs(z.real()/z.imag()));

	i+=(int)(temp*200*nBay100);
		
	red = i*nRed+nRedStart;
	grn = i*nGrn+nGrnStart;
	blu = i*nBlu+nBluStart;

	Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method19()
{
	c.set_real(x);
	c.set_imag(y);

	// Squares
	x_size = (rn*2) / (double) NMAX;
	y_size = (rn*2) / (double) NMAX;

	i += (int) (((fabs(c.real() / x_size) + 
		            fabs(c.imag() / y_size)))*nBay100);
		
	red = i*nRed+nRedStart;
	grn = i*nGrn+nGrnStart;
	blu = i*nBlu+nBluStart;

	Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method20()
{
	c.set_real(x);
	c.set_imag(y);

	// Circles
	x_size = (rn*2) / (double) NMAX;
	y_size = (rn*2) / (double) NMAX;
	
	c.set_real(fabs(c.real() / x_size));
	c.set_imag(fabs(c.imag() / y_size));	
//	z = c;
	
	z.set_real(fabs(z.real() / x_size));
	z.set_imag(fabs(z.imag() / y_size));	
	//z = c;

	i += (int) ((sqrt(z.real()*z.real()+z.imag()*z.imag()))*nBay100);
	i += (int) ((sqrt(c.real()*c.real()+c.imag()*c.imag()))*nBay100);
		
	red = i*nRed+nRedStart;
	grn = i*nGrn+nGrnStart;
	blu = i*nBlu+nBluStart;

	Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method21()
{
	c.set_real(x);
	c.set_imag(y);

	// Radial

//	deg = x_y_to_degrees(c.real(), c.imag());

	//deg = x_y_to_degrees(z.real(), z.imag());
	deg = x_y_to_degrees(c.real(), c.imag());

	temp = ((double) NMAX)/(90*rn);
	i += (int) (temp * deg * nBay100);
		
	red = i*nRed+nRedStart;
	grn = i*nGrn+nGrnStart;
	blu = i*nBlu+nBluStart;

	Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method22()
{
	c.set_real(x);
	c.set_imag(y);

	// Squares
	x_size = (rn*2) / (double) NMAX;
	y_size = (rn*2) / (double) NMAX;

	i += (int) (((fabs(c.real() / x_size) + 
		            fabs(c.imag() / y_size))));
	
	if (((int)(fabs(z.real())*nBay1000)%2) == 0)
	{
		ntemp = (int)(fabs(z.real())*10)%2; 
		i += (int)((fabs(z.real())*10-(double)ntemp)*100*nBay100);
	}

	if (((int)(fabs(z.imag())*10*nBay1000)%2) == 0)
	{
		ntemp = (int)(fabs(z.imag())*10)%2; 
		i += (int)((fabs(z.imag())*10-(double)ntemp)*100*nBay100);
	}

	red = i*nRed+nRedStart;
	grn = i*nGrn+nGrnStart;
	blu = i*nBlu+nBluStart;

	Apply_The_Color();
}


///////////////////////////////////////////////
///////////////////////////////////////////////

void CFlarium24View::OnColour0() 
{
	nColorMethod = 0;
	//bColorChange = TRUE;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour0(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 0)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	//pCmdUI->Enable(bInitialized);
}

void CFlarium24View::OnColour1() 
{
	nColorMethod = 1;
	//bColorChange = TRUE;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour1(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 1)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	//pCmdUI->Enable(bInitialized);
}

void CFlarium24View::OnColour2() 
{
	nColorMethod = 2;
	//bColorChange = TRUE;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour2(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 2)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	//pCmdUI->Enable(bInitialized);
}

void CFlarium24View::OnColour3() 
{
	nColorMethod = 3;
	//bColorChange = TRUE;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour3(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 3)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	//pCmdUI->Enable(bInitialized);
}

void CFlarium24View::OnColour4() 
{
	nColorMethod = 4;
	//bColorChange = TRUE;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour4(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 4)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	//pCmdUI->Enable(bInitialized);
}

void CFlarium24View::OnColour5() 
{
	nColorMethod = 5;
	//bColorChange = TRUE;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour5(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 5)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	//pCmdUI->Enable(bInitialized);
}

void CFlarium24View::OnColour6() 
{
	nColorMethod = 6;
	//bColorChange = TRUE;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour6(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 6)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	//pCmdUI->Enable(bInitialized);
}

void CFlarium24View::OnColour7() 
{
	nColorMethod = 7;
	//bColorChange = TRUE;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour7(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 7)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	//pCmdUI->Enable(bInitialized);
}

void CFlarium24View::OnColour8() 
{
	nColorMethod = 8;
	//bColorChange = TRUE;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour8(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 8)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	//pCmdUI->Enable(bInitialized);
}

void CFlarium24View::OnColour9() 
{
	nColorMethod = 9;
	//bColorChange = TRUE;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour9(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 9)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	//pCmdUI->Enable(bInitialized);
}

void CFlarium24View::OnColour10() 
{
	nColorMethod = 10;
	//bColorChange = TRUE;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour10(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 10)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	//pCmdUI->Enable(bInitialized);
}

void CFlarium24View::OnColour11() 
{
	nColorMethod = 11;
	//bColorChange = TRUE;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour11(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 11)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	//pCmdUI->Enable(bInitialized);
}

void CFlarium24View::OnColour12() 
{
	nColorMethod = 12;
	//bColorChange = TRUE;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour12(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 12)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	//pCmdUI->Enable(bInitialized);
}

void CFlarium24View::OnColour13() 
{
	nColorMethod = 13;
	//bColorChange = TRUE;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour13(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 13)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	//pCmdUI->Enable(bInitialized);
}

void CFlarium24View::OnColour14() 
{
	nColorMethod = 14;
	//bColorChange = TRUE;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour14(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 14)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	//pCmdUI->Enable(bInitialized);
}

void CFlarium24View::OnColour15() 
{
	nColorMethod = 15;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour15(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 15)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	//pCmdUI->Enable(bInitialized);
}

void CFlarium24View::OnColour16() 
{
	nColorMethod = 16;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour16(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 16)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	//pCmdUI->Enable(bInitialized);
}

void CFlarium24View::OnColour17() 
{
	nColorMethod = 17;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour17(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 17)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	//pCmdUI->Enable(bInitialized);
}

void CFlarium24View::OnColour18() 
{
	nColorMethod = 18;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour18(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 18)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	//pCmdUI->Enable(bInitialized);
}

void CFlarium24View::OnColour19() 
{
	COneNum rw;
	rw.m_RW1_n = rn;

	if (rw.DoModal() == IDOK)
		rn = rw.m_RW1_n;
	else
		return;
	
	nColorMethod = 19;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour19(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 19)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnColour20() 
{
	COneNum rw;
	rw.m_RW1_n = rn;

	if (rw.DoModal() == IDOK)
		rn = rw.m_RW1_n;
	else
		return;

	nColorMethod = 20;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour20(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 20)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnColour21() 
{
	COneNum rw;
	rw.m_RW1_n = rn;

	if (rw.DoModal() == IDOK)
		rn = rw.m_RW1_n;
	else
		return;

	nColorMethod = 21;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour21(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 21)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnColour22() 
{
	COneNum rw;
	rw.m_RW1_n = rn;

	if (rw.DoModal() == IDOK)
		rn = rw.m_RW1_n;
	else
		return;

	nColorMethod = 22;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour22(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 22)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

////////////////////////////////////////
////////////////////////////////////////

void CFlarium24View::OnFilter0none() 
{
	nFilter = 0;	
	bMFilter = FALSE;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter0none(CCmdUI* pCmdUI) 
{
	if (nFilter == 0)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter1() 
{
	nFilter = 1;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter1(CCmdUI* pCmdUI) 
{
	if (nFilter == 1)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter2() 
{
	nFilter = 2;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter2(CCmdUI* pCmdUI) 
{
	if (nFilter == 2)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter3() 
{
	nFilter = 3;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter3(CCmdUI* pCmdUI) 
{
	if (nFilter == 3)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter4() 
{
	nFilter = 4;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter4(CCmdUI* pCmdUI) 
{
	if (nFilter == 4)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter5() 
{
	nFilter = 5;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter5(CCmdUI* pCmdUI) 
{
	if (nFilter == 5)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter6() 
{
	nFilter = 6;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter6(CCmdUI* pCmdUI) 
{
	if (nFilter == 6)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter7() 
{
	nFilter = 7;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter7(CCmdUI* pCmdUI) 
{
	if (nFilter == 7)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter8() 
{
	nFilter = 8;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter8(CCmdUI* pCmdUI) 
{
	if (nFilter == 8)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter9() 
{
	nFilter = 9;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter9(CCmdUI* pCmdUI) 
{
	if (nFilter == 9)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter10() 
{
	nFilter = 10;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter10(CCmdUI* pCmdUI) 
{
	if (nFilter == 10)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter11() 
{
	nFilter = 11;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter11(CCmdUI* pCmdUI) 
{
	if (nFilter == 11)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter12() 
{
	nFilter = 12;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter12(CCmdUI* pCmdUI) 
{
	if (nFilter == 12)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter13() 
{
	nFilter = 13;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter13(CCmdUI* pCmdUI) 
{
	if (nFilter == 13)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter14() 
{
	// Turn off Fractal Dimension calculation (if it is on)
	nFDOption = 0;
	if (nFilter == 14)
	{
		bMFilter = FALSE;
		nFilter = 0;
	}
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter14(CCmdUI* pCmdUI) 
{
	if (nFilter == 14 && bMFilter && nFDOption == 0)	
		pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter15() 
{
	// Monster Filter, Standard Deviation
//	if (bMFilter) 
//	{
//		bMFilter = FALSE;
//		nFilter = 0;
//		bDraw = TRUE;
//		bLaunch = FALSE;
//	}
//	else
//	{
		// Create X and Y Temp Arrays for Multi-Fractals
		bMFilter = TRUE;
		nFilter = 15;
		bDraw = TRUE;
		bLaunch = FALSE;
//	}
}

void CFlarium24View::OnUpdateFilter15(CCmdUI* pCmdUI) 
{
	if (bMFilter && nFilter == 15)	
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter16() 
{
	nFilter = 16;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter16(CCmdUI* pCmdUI) 
{
	if (nFilter == 16)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter17() 
{
	nFilter = 17;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter17(CCmdUI* pCmdUI) 
{
	if (nFilter == 17)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter18() 
{
	nFilter = 18;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter18(CCmdUI* pCmdUI) 
{
	if (nFilter == 18)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

/////////////////////////////////////////////////
// Category two filters
///////////////////////////////////////////

void CFlarium24View::OnFilter30() 
{
	nFilter = 130;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter30(CCmdUI* pCmdUI) 
{
	if (nFilter == 130)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter31() 
{
	nFilter = 131;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter31(CCmdUI* pCmdUI) 
{
	if (nFilter == 131)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter32() 
{
	nFilter = 132;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter32(CCmdUI* pCmdUI) 
{
	if (nFilter == 132)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter33() 
{
	nFilter = 133;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter33(CCmdUI* pCmdUI) 
{
	if (nFilter == 133)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter34() 
{
	nFilter = 134;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter34(CCmdUI* pCmdUI) 
{
	if (nFilter == 134)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter35() 
{
	nFilter = 135;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter35(CCmdUI* pCmdUI) 
{
	if (nFilter == 135)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter36() 
{
	nFilter = 136;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter36(CCmdUI* pCmdUI) 
{
	if (nFilter == 136)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter37() 
{
	nFilter = 137;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter37(CCmdUI* pCmdUI) 
{
	if (nFilter == 137)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter38() 
{
	nFilter = 138;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter38(CCmdUI* pCmdUI) 
{
	if (nFilter == 138)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter39() 
{
	nFilter = 139;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter39(CCmdUI* pCmdUI) 
{
	if (nFilter == 139)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter40() 
{
	nFilter = 140;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter40(CCmdUI* pCmdUI) 
{
	if (nFilter == 140)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter41() 
{
	nFilter = 141;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter41(CCmdUI* pCmdUI) 
{
	if (nFilter == 141)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter42() 
{
	nFilter = 142;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter42(CCmdUI* pCmdUI) 
{
	if (nFilter == 142)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter43() 
{
	nFilter = 143;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter43(CCmdUI* pCmdUI) 
{
	if (nFilter == 143)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter44() 
{
	nFilter = 144;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter44(CCmdUI* pCmdUI) 
{
	if (nFilter == 144)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter45() 
{
	nFilter = 145;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter45(CCmdUI* pCmdUI) 
{
	if (nFilter == 145)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter46() 
{
	nFilter = 146;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter46(CCmdUI* pCmdUI) 
{
	if (nFilter == 146)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter47() 
{
	nFilter = 147;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter47(CCmdUI* pCmdUI) 
{
	if (nFilter == 147)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter48() 
{
	nFilter = 148;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter48(CCmdUI* pCmdUI) 
{
	if (nFilter == 148)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter49() 
{
	nFilter = 149;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter49(CCmdUI* pCmdUI) 
{
	if (nFilter == 149)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter50() 
{
	nFilter = 150;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter50(CCmdUI* pCmdUI) 
{
	if (nFilter == 150)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter51() 
{
	nFilter = 151;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter51(CCmdUI* pCmdUI) 
{
	if (nFilter == 151)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter52() 
{
	nFilter = 152;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter52(CCmdUI* pCmdUI) 
{
	if (nFilter == 152)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter53() 
{
	nFilter = 153;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter53(CCmdUI* pCmdUI) 
{
	if (nFilter == 153)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter54() 
{
	nFilter = 154;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter54(CCmdUI* pCmdUI) 
{
	if (nFilter == 154)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter55() 
{
	nFilter = 155;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter55(CCmdUI* pCmdUI) 
{
	if (nFilter == 155)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter56() 
{
	nFilter = 156;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter56(CCmdUI* pCmdUI) 
{
	if (nFilter == 156)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}


void CFlarium24View::OnFilter357() 
{
	nFilter = 157;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter357(CCmdUI* pCmdUI) 
{
	if (nFilter == 157)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter358() 
{
	nFilter = 158;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter358(CCmdUI* pCmdUI) 
{
	if (nFilter == 158)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter359() 
{
	nFilter = 159;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter359(CCmdUI* pCmdUI) 
{
	if (nFilter == 159)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter360() 
{
	nFilter = 160;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter360(CCmdUI* pCmdUI) 
{
	if (nFilter == 160)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}


void CFlarium24View::OnFilter61() 
{
	nFilter = 161;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter61(CCmdUI* pCmdUI) 
{
	if (nFilter == 161)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter62() 
{
	nFilter = 162;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter62(CCmdUI* pCmdUI) 
{
	if (nFilter == 162)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter63() 
{
	nFilter = 163;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter63(CCmdUI* pCmdUI) 
{
	if (nFilter == 163)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter64() 
{
	nFilter = 164;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter64(CCmdUI* pCmdUI) 
{
	if (nFilter == 164)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter65() 
{
	nFilter = 165;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter65(CCmdUI* pCmdUI) 
{
	if (nFilter == 165)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter66() 
{
	nFilter = 166;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter66(CCmdUI* pCmdUI) 
{
	if (nFilter == 166)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter67() 
{
	nFilter = 167;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter67(CCmdUI* pCmdUI) 
{
	if (nFilter == 167)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter68() 
{
	nFilter = 168;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter68(CCmdUI* pCmdUI) 
{
	if (nFilter == 168)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter69() 
{
	CClouds cloud;

	cloud.m_Top			= dCloud_top;
	cloud.m_Bottom	= dCloud_bottom;
	cloud.m_Left    = dCloud_left;	
	cloud.m_Right		= dCloud_right;	

	if (cloud.DoModal() == IDOK)
	{
		dCloud_top      = cloud.m_Top;
		dCloud_bottom		= cloud.m_Bottom;
		dCloud_left			= cloud.m_Left;	
		dCloud_right		= cloud.m_Right;			
	}
	else
		return;

	nFilter = 169;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter69(CCmdUI* pCmdUI) 
{
	if (nFilter == 169)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter70() 
{
	nFilter = 170;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter70(CCmdUI* pCmdUI) 
{
	if (nFilter == 170)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter71() 
{
	nFilter = 171;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter71(CCmdUI* pCmdUI) 
{
	if (nFilter == 171)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

//////////////////////////////////////////////////
////////////////////////////////////////////////////////
// Fractal Dimension Options
////////////////////////////////////////////////////////

void CFlarium24View::OnOptions1() 
{
	// Fractal Dimension
	nFDOption = 1;
	bMFilter = TRUE;
	nFilter = 14;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateOptions1(CCmdUI* pCmdUI) 
{
	if (nFilter == 14 && bMFilter && nFDOption == 1)	
		pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnOptions2() 
{
	// Fractal Dimension
	nFDOption = 2;
	bMFilter = TRUE;
	nFilter = 14;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateOptions2(CCmdUI* pCmdUI) 
{
	if (nFilter == 14 && bMFilter && nFDOption == 2)	
		pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnOptions3() 
{
	// Fractal Dimension
	nFDOption = 3;
	bMFilter = TRUE;
	nFilter = 14;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateOptions3(CCmdUI* pCmdUI) 
{
	if (nFilter == 14 && bMFilter && nFDOption == 3)	
		pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnOptions4() 
{
	// Fractal Dimension
	nFDOption = 4;
	bMFilter = TRUE;
	nFilter = 14;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateOptions4(CCmdUI* pCmdUI) 
{
	if (nFilter == 14 && bMFilter && nFDOption == 4)	
		pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnOptions5() 
{
	// Fractal Dimension
	nFDOption = 5;
	bMFilter = TRUE;
	nFilter = 14;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateOptions5(CCmdUI* pCmdUI) 
{
	if (nFilter == 14 && bMFilter && nFDOption == 5)	
		pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnOptions6() 
{
	// Fractal Dimension
	nFDOption = 6;
	bMFilter = TRUE;
	nFilter = 14;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateOptions6(CCmdUI* pCmdUI) 
{
	if (nFilter == 14 && bMFilter && nFDOption == 6)	
		pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnOptions7() 
{
	// Fractal Dimension
	nFDOption = 7;
	bMFilter = TRUE;
	nFilter = 14;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateOptions7(CCmdUI* pCmdUI) 
{
	if (nFilter == 14 && bMFilter && nFDOption == 7)	
		pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnOptions8() 
{
	// Fractal Dimension
	nFDOption = 8;
	bMFilter = TRUE;
	nFilter = 14;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateOptions8(CCmdUI* pCmdUI) 
{
	if (nFilter == 14 && bMFilter && nFDOption == 8)	
		pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnOptions9() 
{
	// Fractal Dimension
	nFDOption = 9;
	bMFilter = TRUE;
	nFilter = 14;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateOptions9(CCmdUI* pCmdUI) 
{
	if (nFilter == 14 && bMFilter && nFDOption == 9)	
		pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnOptions10() 
{
	// Fractal Dimension
	nFDOption = 10;
	bMFilter = TRUE;
	nFilter = 14;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateOptions10(CCmdUI* pCmdUI) 
{
	if (nFilter == 14 && bMFilter && nFDOption == 10)	
		pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

