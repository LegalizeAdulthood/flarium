// Filter_Complete.cpp

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

#define BAY_INIT 2000

void CFlarium24View::Filter_Complete()
{	
	NMAX_Save = NMAX;

	rj = bj = gj = i;  // rj is used for FD Variate mode
	j = i;

	switch(nFilter)
	{
		case 1:	
			i += (int) rr;			
			rj += rr;			
			
			gj = rr*2;
			bj = rr/2;
						
			break;

		case 2:
			i += (int)(rr*10*nBay100);
			rj += (rr*10*nBay100);

			gj = rr*10*nBay100*2;
			bj = rr*10*nBay100/2;
			
			break;

		case 3:
			rr = dzx_save+dzy_save;
			i += (int)(rr*nBay100);
			rj += (rr*nBay100);

			gj = dzx_save*nBay1000;
			bj = dzy_save*nBay1000;
			
			break;

		case 4:
			//rr = atan(fabs(dzx_save/dzy_save));
			rr = dzx_save+dzy_save;
			i += (int)(rr*nBay100);
			rj += (rr*nBay100);

			gj = dzx_save*nBay1000;
			bj = dzy_save*nBay1000;
			
			break;

		case 5:
			if (dzx_save > dzy_save)
				rr = fabs(dzx_save)*nBay100;
			else
				rr = fabs(dzy_save)*nBay100;
			i += (int)(rr*nBay100);
			rj += (rr*nBay100);

			gj = fabs(dzx_save)*nBay1000;
			bj = fabs(dzy_save)*nBay1000;
			
			break;

		case 6:
			i+=(int)(log(dzx_save*dzx_save+dzy_save*dzy_save)*10);
			rj+=(log(dzx_save*dzx_save+dzy_save*dzy_save)*10);

			gj+=(log(dzx_save*dzx_save)*10); 
			bj+=(log(dzy_save*dzy_save)*10); 

			break;

		case 7:
			i+=(int)(sin(fabs(dzx_save)*fabs(dzy_save))*10);
			rj+=(sin(fabs(dzx_save)*fabs(dzy_save))*10);

			gj+=(sin(fabs(dzx_save))*10);
			bj+=(sin(fabs(dzy_save))*10);

			break;

		case 8:
			i+=(int)(sin(fabs(dzx_save)/fabs(dzy_save))*10);
			rj+=(sin(fabs(dzx_save)/fabs(dzy_save))*10);

			gj+=(cos(fabs(dzx_save)/fabs(dzy_save))*10);
			bj+=(acos(fabs(dzx_save)/fabs(dzy_save))*10);

			break;

		case 9:
			if (z.magnitude() < dBailout)
			{
				i += (int)(1/fabs(sin(dzx_save / dzy_save)));
				rj += (1/fabs(sin(dzx_save / dzy_save)));

				gj += (1/fabs(cos(dzx_save / dzy_save)));
				bj += (2/fabs(cos(dzx_save / dzy_save)));
			
			}
			else
			{
				i += (int)fabs(sin(dzx_save / dzy_save));
				rj += fabs(sin(dzx_save / dzy_save));

				gj += fabs(cos(dzx_save / dzy_save));
				bj += fabs(2*cos(dzx_save / dzy_save));
			}
			break;

		case 10:
			if (z.magnitude() < dBailout)
			{
				i += (int)(1/fabs(atan(dzx_save / dzy_save)));
				rj += (1/fabs(atan(dzx_save / dzy_save)));				
			}
			else
			{
				i += (int)fabs(atan(dzx_save / dzy_save));
				rj += fabs(atan(dzx_save / dzy_save));
			}

			gj = fabs(dzx_save*dzx_save)*500*nBay1000;
			bj = fabs(dzy_save*dzy_save)*500*nBay1000;

			break;

		case 11:
			if (z.magnitude() > dBailout)
			{
				i += (int)(1/fabs(dzx_save * dzy_save));
				rj += (1/fabs(dzx_save * dzy_save));
			}
			else
			{
				i += (int)fabs(dzx_save * dzy_save);
				rj += fabs(dzx_save * dzy_save);
			}

			gj = fabs(dzx_save*dzx_save)*500*nBay1000;
			bj = fabs(dzy_save*dzy_save)*500*nBay1000;

			break;

		case 12:
			dzx = z.real();
			dzy = z.imag();
			i = i * (int)((atan(fabs(dzx*dzx/dzy*dzy)))*10*nBay100);
			rj = rj * ((atan(fabs(dzx*dzx/dzy*dzy)))*10*nBay100);

			gj = fabs(dzx*dzx)*500*nBay1000;
			bj = fabs(dzy*dzy)*500*nBay1000;
			
			break;

		case 13:
			dzx=fabs(atan(z.real()/z.imag()));
			dzy=fabs(atan(dzx_save/dzy_save));
			i=(int)((dzx+dzy)*100);
			rj=((dzx+dzy)*100);

			gj = fabs(dzx*dzx)*500*nBay1000;
			bj = fabs(dzy*dzy)*500*nBay1000;
			
			break;

		case 14:  // Fractal Dimension
			break;

		case 15:  // Standard Deviation
			break;

		case 16:
			i += jrw;
			i = abs(i);

			rj += jrw;
			rj = fabs(rj);

			dzx=fabs(atan(z.real()/z.imag()));
			dzy=fabs(atan(dzx_save/dzy_save));
			i+=(int)((dzx+dzy)*100);

			rj+=((dzx+dzy)*100);
			gj+= fabs(dzx)*200*nBay1000;
			bj+= fabs(dzy)*200*nBay1000;

			break;

		case 17:	
			i += jrw;
			i = abs(i);
			rj += jrw;
			rj = fabs(rj);
			gj=bj=rj;

			return;

		case 18:
			i += jrw;	
			i = abs(i);
			rj += jrw;	
			rj = fabs(rj);
			gj=bj=rj;
			return;
		
		case 130:
			//i = i3;
			//i = (int) ((sin(fabs(1 + x_rmax - x_rmin)) * sin(fabs(1 + y_rmax - y_rmin))) * 40);
			i += (int) (atan(fabs(x_rmax * x_rmin)/fabs(y_rmax * y_rmin)) * 40);
			rj += (atan(fabs(x_rmax * x_rmin)/fabs(y_rmax * y_rmin)) * 40);
			gj=bj=rj;
			
			return;			

		case 131:
			if (i >= NMAX-1)
				i += i3;
			else
				i += (int)rr;

			if (rj >= NMAX-1)
				rj += i3;
			else
				rj += rr;

			gj=bj=rj;
			return;

		case 132:
			i += i3;
			rj += i3;
			gj=bj=rj;
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

			if (rr != 0 && i3 != 0)
				rj += (fabs(dzy_save - dzx_save) + fabs(rr + i3));
			else
				if (rr != 0)
					rj += (fabs(dzy_save - dzx_save) + fabs(rr));
			else
				if (i3 != 0)
					rj += fabs(dzy_save - dzx_save) + i3;
			else
				rj += fabs(dzy_save - dzx_save);

			gj=bj=rj;
			return;

		case 134:
			rr = (double) ((int)rr%(NMAX/2));
			if ((int)(z.real()*2)%2 == 0 || (int)(z.imag()*2)%2 == 0)
				i += (int)rr;
			else
				i += (int)rr + (NMAX/2);

			if ((int)(z.real()*2)%2 == 0 || (int)(z.imag()*2)%2 == 0)
				rj += rr;
			else
				rj += rr + (NMAX/2);
			
			gj=bj=rj;
			return;

		case 135:
			rr = (double) ((int)rr%(NMAX/2));
			if ((int)(z.real()*2)%2 == 0 || (int)(z.imag()*2)%2 == 0)
				i += (int)rr;
			else
				i += (int)rr + (NMAX/2);

			if ((int)(z.real()*2)%2 == 0 || (int)(z.imag()*2)%2 == 0)
				rj += rr;
			else
				rj += rr + (NMAX/2);			

			gj=bj=rj;
			return;

		case 136:
			i += (int)rr;
			rj += rr;
			gj=bj=rj;
			return;

		case 137:
			i += (int)rr;
			rj += rr;
			gj=bj=rj;
			return;

		case 138:
			i += (int)rr;
			rj += rr;
			gj=bj=rj;
			return;

		case 139:
			i += (int)(atan(dzx_save/dzy_save) * 80); 
			rj += (atan(dzx_save/dzy_save) * 80); 
			gj=bj=rj;
		 
			return;

		case 140:
			i += (int)(rr + atan(fabs(dzx_save/dzy_save)) * 30); 
			rj += (rr + atan(fabs(dzx_save/dzy_save)) * 30); 

			gj=bj=rj;
			
			return;

		case 141:
			i += (int)rr;
			rj += rr;			
			gj=bj=rj;
			return;

		case 142:
			i += (int)(rr + atan(fabs(dzx_save/dzy_save)) * 50); 
			rj += (rr + atan(fabs(dzx_save/dzy_save)) * 50); 
			gj=bj=rj;			
			return;

		case 143:
			i += (int)(rr/3 + atan(fabs(dzx_save/dzy_save)) * 30); 
			if ((int)atan(fabs(dzx_save/dzy_save))%2 == 0 && i < (NMAX/2))
				i += (NMAX/2);
			rj += (rr/3 + atan(fabs(dzx_save/dzy_save)) * 30); 
			if ((int)atan(fabs(dzx_save/dzy_save))%2 == 0 && rj < (NMAX/2))
				rj += (double) (NMAX/2);
			gj=bj=rj;			
			return;

		case 144:
			i += (int) (atan(fabs(z.imag()/z.real())) * 13 + (rr * 10));
			rj += (atan(fabs(z.imag()/z.real())) * 13 + (rr * 10));								
			gj=bj=rj;
      return;

		case 145:
			if (rr >= 1)	
				i += (int) (atan(fabs(z.imag()/z.real())) * nBay100 * 5
					+ (rr * nBay1000 * 5));
			else
        i = 0;   

			if (rr >= 1)	
				rj += (atan(fabs(z.imag()/z.real())) * nBay100 * 5
					+ (rr * nBay1000 * 5));
			else
        rj = 0;                  
			            
			gj=bj=rj;
      return;

		case 146:
			i += (int)rr; 
			rj += rr; 
			gj=bj=rj;
			return;

		case 147:
			i += (int)(rr + atan(fabs(dzx_save/dzy_save)) * (10+nBay1000)); 
			rj += (rr + atan(fabs(dzx_save/dzy_save)) * (10+nBay1000)); 
			gj=bj=rj;
			return;

		case 148:
			i += (int) rr;			
			rj += rr;			
			gj=bj=rj;
			return;

		case 149:
			i += (int)(rr*10*nBay100);
			rj += (rr*10*nBay100);
			gj=bj=rj;
			return;

		case 150:
			rr = dzx_save+dzy_save;
			i += (int)(rr*nBay100);
			rj += (rr*nBay100);
			gj=bj=rj;
			return;

		case 151:
			rr = dzx_save+dzy_save;
			i += (int)(rr*nBay100);
			rj += (rr*nBay100);
			gj=bj=rj;
			return;

		case 152:
			if (dzx_save > dzy_save)
				rr = fabs(dzx_save)*nBay100;
			else
				rr = fabs(dzy_save)*nBay100;
			i += (int)(rr*nBay100);		
			rj += (rr*nBay100);		
			gj=bj=rj;			
			return;

		case 153:
			i += (int)(rr*nBay100);
			rj += (rr*nBay100);
			gj=bj=rj;
			return;		

		case 154:
			z = zz;
			z2 = zz2;
									
			dzx = fabs(z.real());
			dzy = fabs(z.imag());

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

				rj+=temp;
				gj=bj=rj;

			}
			else
			{
				if (bNothingButStrands)
				{
					rj=0;
					gj=bj=rj;
					i=j=0;
				}
			}
			
			break;

		case 171:  // Part II
			z = zz;
			z2 = zz2;
									
			dzx = fabs(z.real());
			dzy = fabs(z.imag());

			temp = 0;
			if (dzx < dStrands || dzy < dStrands) 
			{
				if (dzx < dStrands && dzx != 0)
					temp = fabs(dStrands-dzx)*800*nBay100;

				if (dzy < dStrands && dzy != 0)
					temp += fabs(dStrands-dzy)*800*nBay100;

				rr=(int)i;
				rr=rr+(int)temp;
				i=(int)rr;

				rj+=temp;
				gj=bj=rj;
			}
			else
			{
				if (bNothingButStrands)
				{
					rj=0;
					gj=bj=rj;
					i=j=0;
				}
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

				rj+=temp;
				gj=bj=rj;
			}
			else
			{
				if (bNothingButStrands)
				{
					rj=0;
					gj=bj=rj;
					i=j=0;
				}
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

				if ((dzx < dzx_save+dStrands && dzx > dzx_save-dStrands))
					temp = fabs(dzx_save+dStrands-dzx)*10000*nBay100;

				if ((dzy < dzy_save+dStrands && dzy > dzy_save-dStrands))
					temp += fabs(dzy_save+dStrands-dzy)*10000*nBay100;

				rr=(int)i;
				rr=rr+(int)temp;
				i=(int)rr;

				rj+=temp;
				gj=bj=rj;
			}
			else
			{
				if (bNothingButStrands)
				{
					rj=0;
					gj=bj=rj;
					i=j=0;
				}
			}
			
			break;

		case 157:
			z = zz;
			z2 = zz2;
			if (z.magnitude() <= dStrands_HI && z.magnitude() > dStrands_LO)    
			{
				i = (int) (fabs(c.magnitude() - z.magnitude())*20000*nBay100);
				if (z.magnitude() > z2.magnitude())
					i+=NMAX/2;

				rj = (fabs(c.magnitude() - z.magnitude())*20000*nBay100);
				if (z.magnitude() > z2.magnitude())
					rj+=NMAX/2;
			}
			else
			{
				if (bNothingButStrands)
				{
					rj=0;
					gj=bj=rj;
					i=j=0;
				}
			}
			break;

		case 158:
			z = zz;
			z2 = zz2;
			if (z.magnitude() <= dStrands_HI && z.magnitude() > dStrands_LO)    
			{
				i = (int) (fabs(c.magnitude() - z.magnitude())*20000*nBay100);				
				rj = (fabs(c.magnitude() - z.magnitude())*20000*nBay100);				
				rr = fabs((z2.magnitude() - z.magnitude())*1000*nBay100);
				i += (int) rr;
				rj += rr;
				gj=bj=rj;
			}
			else
			{
				if (bNothingButStrands)
				{
					rj=0;
					gj=bj=rj;
					i=j=0;
				}
			}
			break;
		
		case 159:
			z = zz;
			z2 = zz2;
			if (fabs(z.magnitude() - z2.magnitude()) < dStrands_HI &&
					fabs(z.magnitude() - z2.magnitude()) > dStrands_LO) 
			{
				i += (int) (fabs(c.magnitude() - z.magnitude() + z2.magnitude())*1000*nBay100);				
				rj += (fabs(c.magnitude() - z.magnitude() + z2.magnitude())*1000*nBay100);				
			}			
			else
			{
				if (bNothingButStrands)
				{
					rj=0;
					i=j=0;
				}
			}
			gj=bj=rj;
			break;

		case 160:
			z = zz;
			z2 = zz2;
			if (fabs(1/z.magnitude() - 1/z2.magnitude()) < dStrands_HI &&
					fabs(1/z.magnitude() - 1/z2.magnitude()) > dStrands_LO) 
			{
				i += (int) (fabs(1/z.magnitude() - 1/z2.magnitude())*1000*nBay100);				
				rj += (fabs(1/z.magnitude() - 1/z2.magnitude())*1000*nBay100);				
			}			
			else
			{
				if (bNothingButStrands)
				{
					rj=0;
					i=j=0;
				}
			}
			gj=bj=rj;
			break;

////////////////////////////////////////////

		case 161:
		case 165:
			z = zz;
			z2 = zz2;
			if (z.magnitude() <= dStrands_HI &&
				z.magnitude() > dStrands_LO)    
			{
				ntemp = i;
				i = (int) (fabs(c.magnitude() - z.magnitude())*4000*nBay100);
				if (z.magnitude() > z2.magnitude())
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
				
				temp = rj;
				rj = (fabs(c.magnitude() - z.magnitude())*4000*nBay100);
				if (z.magnitude() > z2.magnitude())
					rj+=NMAX/2;
				if (nFilter == 165)
					rj += temp*(8*nBay1000);
				if (nFilter == 161)
				{
					if ((int)(z.real()*10)%2 == 0)
						rj += temp*(8*nBay1000);
					else
						rj -= temp*(8*nBay1000);
					if ((int)(z.imag()*10)%2 == 0)
						rj += temp*(8*nBay1000);
					else
						rj -= temp*(8*nBay1000);
				}									
			}
			else
			{
				if (bNothingButStrands)
				{
					rj=0;
					i=j=0;
				}
			}
			gj=bj=rj;
			break;

		case 162:
		case 166:
			z = zz;
			z2 = zz2;
			if (z.magnitude() <= dStrands_HI &&
				z.magnitude() > dStrands_LO)    
			{
				ntemp = i;

				i = (int) (fabs(c.magnitude() - z.magnitude())*2000*nBay100);				
				rr = fabs((z2.magnitude() - z.magnitude())*100*nBay100);
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

				temp = rj;

				rj = (fabs(c.magnitude() - z.magnitude())*2000*nBay100);				
				rr = fabs((z2.magnitude() - z.magnitude())*100*nBay100);
				rj += rr;
				if (nFilter == 166)
					rj += temp*(8*nBay1000);
				if (nFilter == 162)
				{
					if ((int)(z.real()*10)%2 == 0)
						rj += temp*(8*nBay1000);
					else
						rj -= ntemp*(8*nBay1000);
					if ((int)(z.imag()*10)%2 == 0)
						rj += temp*(8*nBay1000);
					else
						rj -= temp*(8*nBay1000);
				}						
			}
			else
			{
				if (bNothingButStrands)
				{
					rj=0;
					i=j=0;
				}
			gj=bj=rj;
			}

			break;
		
		case 163:
		case 167:
			z = zz;
			z2 = zz2;
			if (fabs(z.magnitude() - z2.magnitude()) < dStrands_HI &&
				fabs(z.magnitude() - z2.magnitude()) > dStrands_LO) 
			{
				ntemp = i;
				i += (int) (fabs(c.magnitude() - z.magnitude() + z2.magnitude())*2000*nBay100);				
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

				temp = rj;
				rj += (fabs(c.magnitude() - z.magnitude() + z2.magnitude())*2000*nBay100);				
				if (nFilter == 167)
					rj += temp*(8*nBay1000);
				if (nFilter == 163)
				{
					if ((int)(z.real()*10)%2 == 0)
						rj += temp*(8*nBay1000);
					else
						rj -= temp*(8*nBay1000);
					if ((int)(z.imag()*10)%2 == 0)
						rj += temp*(8*nBay1000);
					else
						rj -= temp*(8*nBay1000);
				}									
			}			
			else
			{
				if (bNothingButStrands)
				{
					rj=0;
					i=j=0;
				}
			}
			gj=bj=rj;
			break;

		case 164:
		case 168:
			z = zz;
			z2 = zz2;
			if (fabs(1/z.magnitude() - 1/z2.magnitude()) < dStrands_HI &&
				fabs(1/z.magnitude() - 1/z2.magnitude()) > dStrands_LO) 
			{
				ntemp = i;
				i += (int) (fabs(1/z.magnitude() - 1/z2.magnitude())*2000*nBay100);				
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

				temp = rj;
				rj += (fabs(1/z.magnitude() - 1/z2.magnitude())*2000*nBay100);				
				if (nFilter == 168)
					rj += temp*(8*nBay1000);
				if (nFilter == 164)
				{
					if ((int)(z.real()*10)%2 == 0)
						rj += temp*(8*nBay1000);
					else
						rj -= temp*(8*nBay1000);
					if ((int)(z.imag()*10)%2 == 0)
						rj += temp*(8*nBay1000);
					else
						rj -= ntemp*(8*nBay1000);
				}										
			}			
			else
			{
				if (bNothingButStrands)
				{
					rj=0;
					i=j=0;
				}
			}
			gj=bj=rj;
			break;

		case 170:
			if (i > 1)
			{
				i = (int) (atan(fabs(dzx_save-dzx_save_quick)/
						fabs(dzy_save-dzy_save_quick))*50*nBay100);			
			}

			if (rj > 1)
			{
				rj = (atan(fabs(dzx_save-dzx_save_quick)/
						fabs(dzy_save-dzy_save_quick))*50*nBay100);			
			}
			gj=bj=rj;
			break;

		case 172:
			z = zz;
			z2 = zz2;
			if (fabs(1/z.magnitude()) < dStrands_HI &&
				fabs(1/z.magnitude()) > dStrands_LO)
			{
				ntemp = i;
				i = (int) (fabs(1/z.magnitude() - dStrands_HI - dStrands_LO)*2000*nBay100);				
				i += ntemp*(int)(8*nBay1000);
				
				temp = rj;
				rj = (fabs(1/z.magnitude() - dStrands_HI - dStrands_LO)*2000*nBay100);				
				rj += temp*(8*nBay1000);

				gj = fabs(1/z.real()*1/z.real()*2000*nBay100);
				bj = fabs(1/z.imag()*1/z.imag()*2000*nBay100);
			}			
			else
			{
				if (bNothingButStrands)
				{
					rj=0;
					i=j=0;
				}
			}
			gj=bj=rj;
			break;

		case 173:
			z = zz;
			z2 = zz2;
									
			dzx = fabs(z.real()*z.real());
			dzy = fabs(z.imag()*z.imag());

			temp = 0;
			if (dzx < dStrands || dzy < dStrands) 
			{
				if (dzx < dStrands && dzx)
					temp = fabs(dStrands-dzx)*10000*nBay100;

				if (dzy < dStrands && dzy)
					temp += fabs(dStrands-dzy)*10000*nBay100;

				rr=(int)i;
				rr=rr+(int)temp;
				i=(int)rr;

				rj+=temp;
			}
			else
			{
				if (bNothingButStrands)
				{
					rj=0;
					i=j=0;
				}
			}
			
			gj=bj=rj;
			break;

		case 174:
			z = zz;
			z2 = zz2;

			dzx = fabs(z.real()*z.real());
			dzy = fabs(z.imag()*z.imag());

			dzx_save = fabs(c.real());
			dzy_save = fabs(c.imag());

			temp = 0;

			if ((dzx < dzx_save+dStrands && dzx > dzx_save-dStrands) ||
				  (dzy < dzy_save+dStrands && dzy > dzy_save-dStrands))        
			{

				if ((dzx < dzx_save+dStrands && dzx > dzx_save-dStrands))
					temp = fabs(dzx_save+dStrands-dzx)*10000*nBay100;

				if ((dzy < dzy_save+dStrands && dzy > dzy_save-dStrands))
					temp += fabs(dzy_save+dStrands-dzy)*10000*nBay100;

				rr=(int)i;
				rr=rr+(int)temp;
				i=(int)rr;

				rj+=temp;
			}
			else
			{
				if (bNothingButStrands)
				{
					rj=0;
					i=j=0;
				}
			}
			
			gj=bj=rj;
			break;

		case 175:
			z = zz;
			z2 = zz2;
									
			dzx = fabs(z.real()*z.real());
			dzy = fabs(z.imag()*z.imag());

			temp = 0;
			if (z.squares() < dStrands)
			//if (dzx < dStrands && dzy < dStrands) 
			{
				//if (dzx < dStrands && dzx)
					temp = fabs(dStrands-dzx)*10000*nBay100;

				//if (dzy < dStrands && dzy)
					temp += fabs(dStrands-dzy)*10000*nBay100;

				rr=(int)i;
				rr=rr+(int)temp;
				i=(int)rr;

				rj+=temp;
				gj=bj=rj;
			}
			else
			{
				if (bNothingButStrands)
				{
					rj=0;
					gj=bj=rj;
					i=j=0;
				}
			}
			
			gj=bj=rj;
			break;

		case 176:
			z = zz;
			z2 = zz2;
									
			dzx = fabs(z.real());
			dzy = fabs(z.imag());

			temp = 0;
			if (fabs(dzx*dzy) < dStrands)
			//if (dzx < dStrands && dzy < dStrands) 
			{
				//if (dzx < dStrands && dzx)
					temp = fabs(dStrands-fabs(dzx*dzy))*10000*nBay100;

				//if (dzy < dStrands && dzy)
					//temp += fabs(dStrands-dzy)*10000*nBay100;

				rr=(int)i;
				rr=rr+(int)temp;
				i=(int)rr;

				rj+=temp;
			}
			else
			{
				if (bNothingButStrands)
				{
					rj=0;
					i=j=0;
				}
			}

			gj=bj=rj;			
			break;

		case 177:  // 1
			temp   *= 2500*nBay100;
			x_temp *= 2500*nBay100;
			y_temp *= 2500*nBay100;
			
			temp1 = i;
						
			gj = temp1+x_temp;				
			bj = temp1+y_temp;	
			rj = temp1+temp;
			
			if (xi%2==0 && xi != 0)			
				gj += nBay1000;

			if (yi%2==0 && yi != 0)
				bj += nBay1000;

			if (ii%2==0 && ii != 0)
				rj += nBay1000;

			break;

		case 178:  // 2
		case 188:	 // 12
			if (ii)
				temp *= 500*nBay100;
			else
				temp = (i - log (log (z.magnitude())) / log (2))*10; 

			if (xi)
				x_temp *= 500*nBay100;
			else
				x_temp = atan(fabs(z.real())/fabs(z.imag()))*12*nBay100;
				
			if (yi)
				y_temp *= 500*nBay100;
			else
				y_temp = atan(fabs(z.imag())/fabs(z.real()))*12*nBay100;

			if (nFilter == 12)
			{
				if (i<NMAX)
					temp1 = (i - log (log (z.magnitude())) / log (2))*10; 
				else
					temp1 = i;
			}
			else
				temp1 = i;
						
			rj = x_temp;						
			bj = y_temp;
			rj += gj = temp + temp1;
			
			break;

		case 179:		// 3	
			temp   *= BAY_INIT*nBay100;
			x_temp *= BAY_INIT*nBay100;
			y_temp *= BAY_INIT*nBay100;
						
			if (i < NMAX)
				temp1 = (i - log (log (z.magnitude())) / log (2))*10; 
			else
				temp1 = i;

			rj = temp1 + nRedStart;
			gj = temp1 + nGrnStart;
			bj = temp1 + nBluStart;

			if (xi > yi)
			{
				rj += x_temp;
			}
			else
			{
				if (yi > xi)
				{
					gj += y_temp;
				}
				else
				{
					if (xi) // equal
					{
						rj += x_temp/2;
						gj += y_temp/2;
					}			
				}
			}

			if (!xi && !yi)
			{
				bj += temp;
				rj = nRedStart;
				gj = nGrnStart;
			}

			if (ii)
			{
				bj += temp;
				rj += temp;
				bj += temp;
			}

			break;

		case 180: // 4						
			x_temp *= BAY_INIT*nBay100;
			y_temp *= BAY_INIT*nBay100;
			temp   *= BAY_INIT*nBay100;

			rj = xi + x_temp;
			gj = yi + y_temp;
						
			if (i < NMAX)
				temp1 = (i - log (log (z.magnitude())) / log (2))*10; 
			else
				temp1 = i;
			
			if (xi == 0 && yi == 0)
				bj = ii + temp + temp1;

			break;					

		case 181:	// 5					
			x_temp *= BAY_INIT*nBay100;
			y_temp *= BAY_INIT*nBay100;
			temp   *= BAY_INIT*nBay100;
	
			if (xi)
			{
				rj = xi + x_temp + x_temp1*10*nBay1000;
				//bj = rj;
			}

			if (yi)
			{
				gj = yi + y_temp + y_temp1*10*nBay1000;
				//bj = gj;
			}
			
			if (i < NMAX)
				temp1 = (i - log (log (z.magnitude())) / log (2))*10; 
			else
				temp1 = i;

			if (xi == 0 && yi == 0)
				bj += ii + temp1;

			break;					

		case 182:	// 6					
			temp   *= BAY_INIT*nBay1000;
			x_temp *= BAY_INIT*nBay100;
			y_temp *= BAY_INIT*nBay100;
	
			if (xi)
			{
				if (xi%2==0)
				{
					if (xi%4==0)
						rj = xi + x_temp;
					else
						gj = rj = xi + x_temp;
						
				}
				else
				if (xi%4==1)
					gj = rj = xi + x_temp;
				else
					rj = xi + x_temp;
			}

			if (yi)
			{
				if (yi%2==0)
				{
					if (yi%4==0)
						gj += yi + y_temp;
					else
						rj += gj += yi + y_temp;
				}
				else
				if (yi%4==1)
					rj += gj += yi + y_temp;
				else
					gj += yi + y_temp;
			}

			if (xi == 0 && yi == 0)
				rj += bj += temp + ii;
			
			break;

		case 183: // 7:						
		case 184: // 8:
		case 186: // 10:
			temp   *= BAY_INIT*nBay100;
			x_temp *= BAY_INIT*nBay100;
			y_temp *= BAY_INIT*nBay100;
	
			if (xi > yi)
			{
				if (xi)
				{
					if (xi%2==0)
					{
						if (xi%4==0)
						{
							rj = bj = x_temp;
						}
						else
						{
							gj = bj = x_temp;
						}						
					}
					else
					if (xi%4==1)
						rj = bj = x_temp;
					else
						gj = bj = x_temp;
				}
			}
			else
			if (yi)
			{
				if (yi%2==0)
				{
					if (yi%4==0)
						bj = rj = y_temp;
					else
						gj = rj = y_temp;
				}
				else					
				if (yi%4==1)
					bj = rj = y_temp;
				else
					gj = rj = y_temp;					
			}
						
			if (nFilter == 8)
				gj+=i;
			else
			{
				if (i<NMAX)
					temp1 = (i - log (log (z.magnitude())) / log (2))*10; 
				else
					temp1 = i;
			}

			if (xi == 0 && yi == 0)
				rj = gj = temp1;

			//gj+=temp1*10*nBay100;

			break;	
			
		case 185: // 9:
			if (i<NMAX)
				temp = i - log (log (z.magnitude())) / log (2); 
			else
				temp = i;

			rj = gj = bj = temp*10*nBay100;

			break;

		case 187: // 11:
			temp   *= BAY_INIT*nBay100;
			x_temp *= BAY_INIT*nBay100;
			y_temp *= BAY_INIT*nBay100;

			if (i<NMAX)
				temp1 = (i - log (log (z.magnitude())) / log (2))*10; 
			else
				temp1 = 0;
			
			if (xi >= yi)
				bj = gj = x_temp;
			else
				bj = rj = y_temp;

			//rj += bj += gj += temp1; 
			
			break;

		case 189: // 13:
			temp = atan(fabs(z.real()/z.imag()))*10*nBay100;

			if (i<NMAX)
				temp1 = (i - log (log (z.magnitude())) / log (2))*10; 
			else
				temp1 = i;

			rj = gj = bj = temp + temp1;	
			break;
	
		case 190: // 14:
			temp   *= BAY_INIT*nBay1000;
			x_temp *= BAY_INIT*nBay1000;
			y_temp *= BAY_INIT*nBay1000;

			if (i<NMAX)
				temp1 = (i - log (log (z.magnitude())) / log (2))*10; 
			else
				temp1 = 0;
			
			if (xi >= yi)
				bj = gj = x_temp;
			else
				bj = rj = y_temp;

			if (xi == 0 && yi == 0)
				rj += bj += gj += temp1; 
			
			break;
	
		case 191: // 15:
			temp   *= 2500*nBay100;
			x_temp *= 2500*nBay100;
			y_temp *= 2500*nBay100;
			
			if (nFilter == 15)
			{
				if (i<NMAX)
					temp1 = (i - log (log (z.magnitude())) / log (2))*10; 
				else
					temp1 = i;
			}
			else
				temp1 = i;
						
			if (xi)
				gj = x_temp;			
	
			if (yi)	
				bj = y_temp;
	
			rj = gj += bj += temp1+temp;
			
			if (xi%2==0 && xi != 0)			
				gj += nBay1000;

			if (yi%2==0 && yi != 0)
				bj += nBay1000;

			if (ii%2==0 && ii != 0)
				rj += nBay1000;

			if (nFilter == 4 && xi == 0 && yi == 0)
			{
				x_temp = y_temp = temp = atan(fabs(c.real()-z.real())/fabs(c.imag()-z.imag()))*5*nBay100;

				if (i<NMAX)
					temp1 = (i - log (log (z.magnitude())) / log (2))*10; 
				else
					temp1 = i;
				
				rj += temp1+temp;
				gj += temp1+temp;			
				bj += temp1+y_temp;
			}		

			break;

		case 192: // 16:
			temp   *= BAY_INIT*nBay1000;
			x_temp *= BAY_INIT*nBay1000;
			y_temp *= BAY_INIT*nBay1000;

			if (i<NMAX)
				temp1 = (i - log (log (z.magnitude())) / log (2))*10; 
			else
				temp1 = 0;
			
			if (xi >= yi)
			{
				if (xi%2==0)
				{
					if (xi%4==0)
						bj = rj = x_temp;
					else
						gj = rj = x_temp;
				}
				else					
				if (xi%4==1)
					bj = rj = x_temp;
				else
					gj = rj = x_temp;					
			}
			else
			{
				if (yi%2==0)
				{
					if (yi%4==0)
						rj = bj = y_temp;
					else
						gj = bj = y_temp;
				}
				else					
				if (yi%4==1)
					rj = bj = y_temp;
				else
					gj = bj = y_temp;					
			}

			if (xi == 0 && yi == 0)
				rj += bj += gj += temp1; 
			
			break;

		case 193: // 17:
			if (ii)
				temp *= 2500*nBay100;
			else
				temp = atan(fabs(c.real()-z.real())/fabs(c.imag()-z.imag()))*12*nBay100;

			if (xi)
				x_temp *= 2500*nBay100;
			else
				x_temp = atan(fabs(z.real())/fabs(z.imag()))*12*nBay100;
				
			if (yi)
				y_temp *= 2500*nBay100;
			else
				y_temp = atan(fabs(z.imag())/fabs(z.real()))*12*nBay100;

			rj += (double)i+temp;
			gj += (double)i+x_temp;			
			bj += (double)i+y_temp;
			
			if (ii%2==0 && ii != 0)
				rj += nBay1000;

			if (xi%2==0 && xi != 0)			
				gj += nBay1000;

			if (yi%2==0 && yi != 0)
				bj += nBay1000;

			break;

		case 194: // 18:  // dual bubbles mod 1
		case 195: // 19:
			temp   *= BAY_INIT*nBay1000;
			x_temp *= BAY_INIT*nBay1000;
			y_temp *= BAY_INIT*nBay1000;

			if (i<NMAX)
				temp1 = (i - log (log (z.magnitude())) / log (2))*10; 
			else
				temp1 = 0;
			
			if (xi >= yi)
			{				
				switch (xi%4)
				{				
				case 0:
					bj = gj = x_temp;
					break;
				case 1:
					bj = rj = x_temp;
					break;
				case 2:
					rj = bj = x_temp;
					break;
				case 3:
					rj = gj = x_temp;
					break;					
				}
			}
			else
			{
				switch (yi%4)
				{				
				case 0:
					rj = bj = y_temp;
					break;
				case 1:
					rj = gj = y_temp;
					break;
				case 2:
					gj = rj = y_temp;
					break;
				case 3:
					gj = bj = y_temp;
					break;					
				}
			}

			if (xi == 0 && yi == 0)
				rj += bj += gj += 128 + temp1; 
				//rj += bj += gj += temp1; 
			
			break;

		case 196: // 20:						
			z.set_real((z.real()-c.real()));
			z.set_imag((z.imag()-c.imag()));					

			bj = (log(log(z.abs()))*50*nBay100);
			if (i%2==0)
				rj = bj;
			if (i%4==0)
				gj = bj;
			break;

		default:
			break;
	}

//////////////
	if (bMFilter && (nFilter == 14 || nFilter == 15))
	{
		FDimension();
	}
}

