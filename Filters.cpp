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
	if (bFDVariate)
	{
		switch (nColorOrder)
		{
			case 0:		// rgb
				red = (int) (rj*(double)(nRed))+nRedStart;
				grn = (int) (gj*(double)(nGrn))+nGrnStart;
				blu = (int) (bj*(double)(nBlu))+nBluStart;
				break;

			case 1:		// rbg
				red = (int) (rj*(double)(nRed))+nRedStart;
				grn = (int) (bj*(double)(nGrn))+nGrnStart;
				blu = (int) (gj*(double)(nBlu))+nBluStart;
				break;

			case 2:		// grb
				red = (int) (gj*(double)(nRed))+nRedStart;
				grn = (int) (rj*(double)(nGrn))+nGrnStart;
				blu = (int) (bj*(double)(nBlu))+nBluStart;
				break;

			case 3:		// gbr
				red = (int) (gj*(double)(nRed))+nRedStart;
				grn = (int) (bj*(double)(nGrn))+nGrnStart;
				blu = (int) (rj*(double)(nBlu))+nBluStart;
				break;

			case 4:		// brg
				red = (int) (bj*(double)(nRed))+nRedStart;
				grn = (int) (rj*(double)(nGrn))+nGrnStart;
				blu = (int) (gj*(double)(nBlu))+nBluStart;
				break;

			case 5:		// bgr
				red = (int) (bj*(double)(nRed))+nRedStart;
				grn = (int) (gj*(double)(nGrn))+nGrnStart;
				blu = (int) (rj*(double)(nBlu))+nBluStart;
				break;
		}
	}	
	else
	{
		red = i*nRed+nRedStart;
		grn = i*nGrn+nGrnStart;
		blu = i*nBlu+nBluStart;
	}

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
	rj+=temp;

	// Generalized Coloring Method
	if (dzx < dzx_save
	 || dzy < dzy_save)
	{		
		//red = i*nRed+nRedStart+min;
		//grn = i*nGrn+nGrnStart+min;
		//blu = i*nBlu+nBluStart+min;
		i+=min;
		rj+=min;
	}
	else
	{
		//red = i*nRed+nRedStart+max;
		//grn = i*nGrn+nGrnStart+max;
		//blu = i*nBlu+nBluStart+max;
		i+=max;
		rj+=max;
	}

	gj = bj = rj;
	Generalized_Coloring_Method();
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
	rj+=temp;

	if (z.real() > 0)
	{
		i+=min;
		rj+=min;
	}
	else
	{
		i+=max;
		rj+=max;
	}

	gj = bj = rj;
	Generalized_Coloring_Method();
}

void CFlarium24View::Generalized_Coloring_Method3()
{
	temp = atan(fabs(z.real()/z.imag()))*10*nBay100;

	if (z.magnitude() < dBailout)
		temp = 1/atan(fabs(z.real()/z.imag()))*10*nBay100;
		
	i+=(int)temp;
	rj+=temp;

	// Generalized Coloring Method
	if (fabs(z.real()) < fabs(c.real())
	 || fabs(z.imag()) < fabs(c.imag()))
	{
		i+=min;
		rj+=min;
	}
	else
	{
		i=(i+max)*(-1);
		rj=(rj+max)*(-1);
	}

	gj = bj = rj;
	Generalized_Coloring_Method();
}

void CFlarium24View::Generalized_Coloring_Method4()
{
	z.set_real(x);
	z.set_imag(y);

	temp = atan(fabs(z.real()/z.imag()))
				-atan(fabs(z.imag()/z.real()))*10*nBay100;

	if (z.magnitude() < dBailout)
		temp = atan(1/fabs(z.real()/z.imag()))
				-atan(1/fabs(z.imag()/z.real()))*100*nBay100;
		
	i+=(int)temp;
	rj+=temp;

	// Generalized Coloring Method 4
	if (fabs(z.real()) < fabs(c.real())
	 || fabs(z.imag()) < fabs(c.imag()))
	{
		i+=min;
		rj+=min;
	}
	else
	{
		i+=max;
		i*=-1;

		rj+=max;
		rj*=-1;
	}

	gj = bj = rj;
	Generalized_Coloring_Method();
}

void CFlarium24View::Generalized_Coloring_Method5()
{
	dzx = fabs(z.real());
	dzy = fabs(z.imag());

	dzx_save = fabs(c.real());
	dzy_save = fabs(c.imag());

	temp = atan(fabs(dzx/dzy))
				-atan(fabs(dzy/dzx))*10*nBay100;
	
	if (z.magnitude() < dBailout)
		temp = atan(1/fabs(dzx/dzy))
					+atan(1/fabs(dzy/dzx))*100*nBay100;		
	
	i+=(int)temp;
	rj+=temp;

	if ((int)z.real() % 2 == 0)
	{
		i+=min;
		rj+=min;
	}
	else
	{
		i+=max;
		rj+=max;
	}
	
	gj = bj = rj;
	Generalized_Coloring_Method();
}

void CFlarium24View::Generalized_Coloring_Method6()
{
	dzx = fabs(z.real());
	dzy = fabs(z.imag());

	dzx_save = fabs(c.real());
	dzy_save = fabs(c.imag());

	temp = atan(fabs(dzx/dzy))*10*nBay100;
	
	i+=(int)temp;
	rj+=temp;

	if (z.real()*z.imag() > c.real()*c.imag())
	{
		i+=min;
		rj+=min;
	}
	else
	{
		i+=max;
		rj+=max;
	}

	gj = bj = rj;
	Generalized_Coloring_Method();
}

void CFlarium24View::Generalized_Coloring_Method7()
{
	dzx = fabs(z.real());
	dzy = fabs(z.imag());

	dzx_save = fabs(c.real());
	dzy_save = fabs(c.imag());

	temp = 0;
	if ((int)(z.magnitude()*10) % 2 == 0)
		temp = sin(fabs(dzx*dzy*dzx_save*dzy_save))*10*nBay100;
	else
		temp = cos(fabs(dzx*dzy*dzx_save*dzy_save))*10*nBay100;

	if (z.magnitude() < dBailout)
	{
		if ((int)(z.magnitude()*10) % 2 == 0)
			temp = sin(1/fabs(dzx*dzy*dzx_save*dzy_save))*10*nBay100;
		else
			temp = cos(1/fabs(dzx*dzy*dzx_save*dzy_save))*10*nBay100;
	}
		
	i=i+(int)temp;
	rj+=temp;

	if (dzx > dzx_save && dzy > dzy_save)
	{
		i+=min;
		rj+=min;
	}
	else
	{
		i+=max;
		rj+=max;
	}

	gj = bj = rj;
	Generalized_Coloring_Method();
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

		rj+=temp;
	}

	gj = bj = rj;
	Generalized_Coloring_Method();
}

void CFlarium24View::Generalized_Coloring_Method9()
{
	dzx = fabs(z.real());
	dzy = fabs(z.imag());

	temp = sin(1/fabs((dzx)/(dzy)))*500*nBay100;
	
	rr=(int)i;
	rr=rr+(int)temp;
	i=(int)rr;

	rj+=temp;

	gj = bj = rj;
	Generalized_Coloring_Method();
}

void CFlarium24View::Generalized_Coloring_Method10()
{
	dzx = fabs(z.real());
	dzy = fabs(z.imag());

	dzx_save = fabs(c.real());
	dzy_save = fabs(c.imag());

	temp=z.magnitude()*cos(fabs(dzx*dzx/dzy*dzy))*1000*nBay100;
	
	rr=(int)i;
	rr=rr+(int)temp;
	i=(int)rr;

	rj+=temp;

	if ((int)z.magnitude() % 2 == 0)
	{
		i+=min;
		rj+=min;
	}
	else
	{
		i+=max;
		rj+=max;
	}

	gj = bj = rj;
	Generalized_Coloring_Method();
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

	rj+=temp;

	if ((int)z.magnitude() % 2 == 0)
	{
		i+=min;
		rj+=min;
	}
	else
	{
		i+=max;
		rj+=max;
	}

	gj = bj = rj;
	Generalized_Coloring_Method();
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

	rj+=temp;

	if ((int)z.magnitude() % 2 == 0)
	{
		i+=min;
		rj+=min;
	}
	else
	{
		i+=max;
		rj+=max;
	}

	gj = bj = rj;
	Generalized_Coloring_Method();
}

void CFlarium24View::Generalized_Coloring_Method13()
{
	if (c.magnitude() < dBailout)
		temp = (atan(1/fabs(c.real()/c.imag()))
				-atan(1/fabs(c.imag()/c.real())))*100*nBay100;
	else
		temp = 0;
		
	i+=(int)temp;
	rj+=temp;

	gj = bj = rj;
	Generalized_Coloring_Method();
}

void CFlarium24View::Generalized_Coloring_Method14()
{
	z.set_real(x);
	z.set_imag(y);

	temp = 0;
	if (z.magnitude() < dBailout)
		temp = atan(fabs(z.real()/z.imag()))*200*nBay100;
		
	i+=(int)temp;
	rj+=temp;
		
	gj = bj = rj;
	Generalized_Coloring_Method();
}

void CFlarium24View::Generalized_Coloring_Method15()
{	
	temp = atan(fabs(c.real()/c.imag())) *
				 atan(fabs(z.real()/z.imag()));

	i+=(int)(temp*200*nBay100);
	rj+=(temp*200*nBay100);

	gj = bj = rj;
	Generalized_Coloring_Method();
}

void CFlarium24View::Generalized_Coloring_Method16()
{
	temp = atan(fabs(z2.real()/z2.imag())) *
				 atan(fabs(z.real()/z.imag()));

	i+=(int)(temp*200*nBay100);		
	rj+=(temp*200*nBay100);
		
	gj = bj = rj;
	Generalized_Coloring_Method();
}

void CFlarium24View::Generalized_Coloring_Method17()
{
	temp = atan(fabs(z2.real()/z2.imag())) -
				 atan(fabs(z.real()/z.imag()));

	i+=(int)(temp*200*nBay100);
	rj+=(temp*200*nBay100);
		
	gj = bj = rj;
	Generalized_Coloring_Method();
}

void CFlarium24View::Generalized_Coloring_Method18()
{
	temp = atan(fabs(z2.real()/z2.imag())) +
				 atan(fabs(z.real()/z.imag()));

	i+=(int)(temp*200*nBay100);
	rj+=(temp*200*nBay100);
		
	gj = bj = rj;
	Generalized_Coloring_Method();
}

void CFlarium24View::Generalized_Coloring_Method19()
{
	c.set_real(x);
	c.set_imag(y);

	// magnitude
	x_size = (rn*2) / (double) NMAX;
	y_size = (rn*2) / (double) NMAX;

	i += (int) (((fabs(c.real() / x_size) + 
		            fabs(c.imag() / y_size)))*nBay100);
		
	rj += (((fabs(c.real() / x_size) + 
		            fabs(c.imag() / y_size)))*nBay100);
		
	gj = bj = rj;
	Generalized_Coloring_Method();
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
		
	rj += ((sqrt(z.real()*z.real()+z.imag()*z.imag()))*nBay100);
	rj += ((sqrt(c.real()*c.real()+c.imag()*c.imag()))*nBay100);
		
	gj = bj = rj;
	Generalized_Coloring_Method();
}

void CFlarium24View::Generalized_Coloring_Method21()
{
	c.set_real(x);
	c.set_imag(y);

	// Radial
	deg = x_y_to_degrees(c.real(), c.imag());

	temp = ((double) NMAX)/(90*rn);
	i += (int) (temp * deg * nBay100);		
	rj += (temp * deg * nBay100);
		
	gj = bj = rj;
	Generalized_Coloring_Method();
}

void CFlarium24View::Generalized_Coloring_Method22()
{
	c.set_real(x);
	c.set_imag(y);

	// magnitude
	x_size = (rn*2) / (double) NMAX;
	y_size = (rn*2) / (double) NMAX;

	i += (int) (((fabs(c.real() / x_size) + 
		            fabs(c.imag() / y_size))));
	
	rj += (((fabs(c.real() / x_size) + 
		            fabs(c.imag() / y_size))));

	if (((int)(fabs(z.real())*nBay1000)%2) == 0)
	{
		ntemp = (int)(fabs(z.real())*10)%2; 
		i += (int)((fabs(z.real())*10-(double)ntemp)*100*nBay100);
		rj += ((fabs(z.real())*10-(double)ntemp)*100*nBay100);
	}

	if (((int)(fabs(z.imag())*10*nBay1000)%2) == 0)
	{
		ntemp = (int)(fabs(z.imag())*10)%2; 
		i += (int)((fabs(z.imag())*10-(double)ntemp)*100*nBay100);
		rj += ((fabs(z.imag())*10-(double)ntemp)*100*nBay100);
	}

	gj = bj = rj;
	Generalized_Coloring_Method();
}

void CFlarium24View::Generalized_Coloring_Method23()
{
	// Generalized Coloring Method	
	if (bFDVariate)
	{
		red = (int) (5000*nBay1000*(z.real()*z.imag())*(double)nRed+(double)nRedStart+
			rj*(double)nRed+(double)nRedStart);
		grn = (int) (5000*nBay1000*(z.real()*z.real())*(double)nGrn+(double)nGrnStart+
			rj*(double)nGrn+(double)nGrnStart);
		blu = (int) (5000*nBay1000*(z.imag()*z.imag())*(double)nBlu+(double)nBluStart+
			rj*(double)nBlu+(double)nBluStart);
	}	
	else
	{
		red = (int) (5000*nBay1000*fabs(z.real()*z.imag())*(double)nRed+(double)nRedStart+
			(double)i*(double)nRed+(double)nRedStart);
		grn = (int) (5000*nBay1000*fabs(z.real()*z.real())*(double)nGrn+(double)nGrnStart+
			(double)i*(double)nGrn+(double)nGrnStart);
		blu = (int) (5000*nBay1000*fabs(z.imag()*z.imag())*(double)nBlu+(double)nBluStart+
			(double)i*(double)nBlu+(double)nBluStart);
	}

	rj = (double) red;
	gj = (double) grn;
	bj = (double) blu;
  
	Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method24()
{
	if (bFDVariate)
	{
		red = (int) (2500*nBay1000*fabs(z.squares()-
			c.squares())*(double)nRed+(double)nRedStart+
			rj*(double)nRed+(double)nRedStart);
		grn = (int) (2500*nBay1000*fabs(z.real()*z.real()*2-
			c.squares())*(double)nGrn+(double)nGrnStart+
			rj*(double)nGrn+(double)nGrnStart);
		blu = (int) (2500*nBay1000*fabs(z.imag()*z.imag()*2-
			c.squares())*(double)nBlu+(double)nBluStart+
			rj*(double)nBlu+(double)nBluStart);
	}
	else
	{
		red = (int) (2500*nBay1000*fabs(z.squares()-
			c.squares())*(double)nRed+(double)nRedStart+
			(int)i*(double)nRed+(double)nRedStart);
		grn = (int) (2500*nBay1000*fabs(z.real()*z.real()*2-
			c.squares())*(double)nGrn+(double)nGrnStart+
			(int)i*(double)nGrn+(double)nGrnStart);
		blu = (int) (2500*nBay1000*fabs(z.imag()*z.imag()*2-
			c.squares())*(double)nBlu+(double)nBluStart+
			(int)i*(double)nBlu+(double)nBluStart);
	}

	rj = (double) red;
	gj = (double) grn;
	bj = (double) blu;

  Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method25()
{
	if (bFDVariate)
	{
		red = (int) (rj*(double)nRed+(double)nRedStart);
		grn = (int) (rj*(double)nGrn+(double)nGrnStart);
		blu = (int) (rj*(double)nBlu+(double)nBluStart);	
	}	
	else
	{
		red = i*nRed+nRedStart;
		grn = i*nGrn+nGrnStart;
		blu = i*nBlu+nBluStart;
	}
	
	red += (int) (5000*nBay1000*fabs(z.imag()*c.imag())*(double)nRed+(double)nRedStart);
	grn += (int) (5000*nBay1000*fabs(z.real()*c.real())*(double)nGrn+(double)nGrnStart);
	blu += (int) (5000*nBay1000*fabs(z.real()*z.imag())*(double)nBlu+(double)nBluStart);

	rj = (double) red;
	gj = (double) grn;
	bj = (double) blu;

	Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method26()
{
	if (bFDVariate)
	{
		red = (int) (5000*nBay1000*fabs(z.real()*z.imag()-
			c.squares())*(double)nRed+(double)nRedStart+
			rj*(double)nRed+(double)nRedStart);
		grn = (int) (5000*nBay1000*fabs(z.real()*z.real()-
			c.squares())*(double)nGrn+(double)nGrnStart+
			rj*(double)nGrn+(double)nGrnStart);
		blu = (int) (5000*nBay1000*fabs(z.imag()*z.imag()-
			c.squares())*(double)nBlu+(double)nBluStart+
			rj*(double)nBlu+(double)nBluStart);
	}
	else
	{
		red = (int) (5000*nBay1000*fabs(z.real()*z.imag()-
			c.squares())*(double)nRed+(double)nRedStart+
			(int)i*(double)nRed+(double)nRedStart);
		grn = (int) (5000*nBay1000*fabs(z.real()*z.real()-
			c.squares())*(double)nGrn+(double)nGrnStart+
			(int)i*(double)nGrn+(double)nGrnStart);
		blu = (int) (5000*nBay1000*fabs(z.imag()*z.imag()-
			c.squares())*(double)nBlu+(double)nBluStart+
			(int)i*(double)nBlu+(double)nBluStart);
	}

	rj = (double) red;
	gj = (double) grn;
	bj = (double) blu;

  Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method27()
{
	// Generalized Coloring Method	
	if (bFDVariate)
	{
		red = (int) (5000*nBay1000*fabs(z.real()*z.imag())*(double)nRed+(double)nRedStart+
			rj*(double)nRed+(double)nRedStart);
		grn = (int) (5000*nBay1000*fabs(z.real()*z.real())*(double)nGrn+(double)nGrnStart+
			rj*(double)nGrn+(double)nGrnStart);
		blu = (int) (5000*nBay1000*fabs(z.imag()*z.imag())*(double)nBlu+(double)nBluStart+
			rj*(double)nBlu+(double)nBluStart);
	}	
	else
	{
		red = (int) (5000*nBay1000*fabs(z.real()*z.imag())*(double)nRed+(double)nRedStart+
			(double)i*(double)nRed+(double)nRedStart);
		grn = (int) (5000*nBay1000*fabs(z.real()*z.real())*(double)nGrn+(double)nGrnStart+
			(double)i*(double)nGrn+(double)nGrnStart);
		blu = (int) (5000*nBay1000*fabs(z.imag()*z.imag())*(double)nBlu+(double)nBluStart+
			(double)i*(double)nBlu+(double)nBluStart);
	}

	if (j%2 == 0)
	{
		if (j%4==0)
		{
		}
		else
		{
			red = red ^ 0xFF;
		}
	}
	else
	{
		if (j%4==1)
		{
			grn = grn ^ 0xFF;
		}
		else
		{
			blu = blu ^ 0xFF;
		}
	}

	rj = (double) red;
	gj = (double) grn;
	bj = (double) blu;

  Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method28()
{
	if (bFDVariate)
	{
		red = (int) (2500*nBay1000*fabs(z.squares()-
			c.squares())*(double)nRed+(double)nRedStart+
			rj*(double)nRed+(double)nRedStart);
		grn = (int) (2500*nBay1000*fabs(z.real()*z.real()*2-
			c.squares())*(double)nGrn+(double)nGrnStart+
			rj*(double)nGrn+(double)nGrnStart);
		blu = (int) (2500*nBay1000*fabs(z.imag()*z.imag()*2-
			c.squares())*(double)nBlu+(double)nBluStart+
			rj*(double)nBlu+(double)nBluStart);
	}
	else
	{
		red = (int) (2500*nBay1000*fabs(z.squares()-
			c.squares())*(double)nRed+(double)nRedStart+
			(int)i*(double)nRed+(double)nRedStart);
		grn = (int) (2500*nBay1000*fabs(z.real()*z.real()*2-
			c.squares())*(double)nGrn+(double)nGrnStart+
			(int)i*(double)nGrn+(double)nGrnStart);
		blu = (int) (2500*nBay1000*fabs(z.imag()*z.imag()*2-
			c.squares())*(double)nBlu+(double)nBluStart+
			(int)i*(double)nBlu+(double)nBluStart);
	}

	if (red | grn | blu)
	{
		if (j%2 == 0)
		{
			if (j%4==0)
			{		
			}
			else
			{
				red = red ^ 0xFF;
			}
		}
		else
		{
			if (j%4==1)
			{
				grn = grn ^ 0xFF;
			}
			else
			{
				blu = blu ^ 0xFF;
			}
		}
	}
  
	rj = (double) red;
	gj = (double) grn;
	bj = (double) blu;

	Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method29()
{
	red = (int) (rj*(double)nRed*nBay1000+(double)nRedStart);
	grn = (int) (gj*(double)nGrn*nBay1000+(double)nGrnStart);
	blu = (int) (bj*(double)nBlu*nBay1000+(double)nBluStart);	

	rj = (double) red;
	gj = (double) grn;
	bj = (double) blu;

	Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method30()
{
	grn = (int) (rj*(double)nRed*nBay1000+(double)nRedStart);
	red = (int) (gj*(double)nGrn*nBay1000+(double)nGrnStart);
	blu = (int) (bj*(double)nBlu*nBay1000+(double)nBluStart);	

	rj = (double) red;
	gj = (double) grn;
	bj = (double) blu;

	Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method31()
{
	// Generalized Coloring Method	
	blu = (int) (5000*nBay1000*fabs(z.real()*z.imag())*(double)nRed+(double)nRedStart+
		rj*(double)nRed+(double)nRedStart);
	grn = (int) (5000*nBay1000*fabs(z.real()*z.real())*(double)nGrn+(double)nGrnStart+
		gj*(double)nGrn+(double)nGrnStart);
	red = (int) (5000*nBay1000*fabs(z.imag()*z.imag())*(double)nBlu+(double)nBluStart+
		bj*(double)nBlu+(double)nBluStart);

	rj = (double) red;
	gj = (double) grn;
	bj = (double) blu;

	Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method32()
{
	// Generalized Coloring Method	
	blu = (int) (5000*nBay1000*fabs(z.real()*z.imag())*(double)nRed+(double)nRedStart+
		rj*(double)nRed+(double)nRedStart);
	red = (int) (5000*nBay1000*fabs(z.real()*z.real())*(double)nGrn+(double)nGrnStart+
		gj*(double)nGrn+(double)nGrnStart);
	grn = (int) (5000*nBay1000*fabs(z.imag()*z.imag())*(double)nBlu+(double)nBluStart+
		bj*(double)nBlu+(double)nBluStart);

	rj = (double) red;
	gj = (double) grn;
	bj = (double) blu;

	Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method33()
{
	// Generalized Coloring Method	
	red = (int) (5000*nBay1000*fabs(z.real()*z.imag())*(double)nRed+(double)nRedStart+
		rj*(double)nRed+(double)nRedStart);
	grn = (int) (5000*nBay1000*fabs(z.real()*z.real())*(double)nGrn+(double)nGrnStart+
		gj*(double)nGrn+(double)nGrnStart);
	blu = (int) (5000*nBay1000*fabs(z.imag()*z.imag())*(double)nBlu+(double)nBluStart+
		bj*(double)nBlu+(double)nBluStart);

	rj = (double) red;
	gj = (double) grn;
	bj = (double) blu;

	Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method34()
{
	red = (int)rj*nRed+nRedStart;
	grn = (int)rj*nGrn+nGrnStart;
	blu = (int)rj*nBlu+nBluStart;
		
	if (j < JMAX)
	{
		red += (int) (nBay1000*5*(double)nRed*fabs(z.real()+z.imag())+(double)nRedStart);
		grn += (int) (nBay1000*5*(double)nGrn*fabs(z.real()+z.real())+(double)nGrnStart);
		blu += (int) (nBay1000*5*(double)nBlu*fabs(z.imag()+z.imag())+(double)nBluStart);
	}

	if (j%2 == 0)
	{
		if (j%4==0)
		{
		}
		else
		{
			red = red ^ 0xFF;
		}
	}
	else
	{
		if (j%4==1)
		{
			blu = blu ^ 0xFF;
		}
		else
		{
			grn = grn ^ 0xFF;
		}
	}
				
	rj = (double) red;
	gj = (double) grn;
	bj = (double) blu;

	Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method35()
{
	red = (int)rj*nRed+nRedStart;
	grn = (int)rj*nGrn+nGrnStart;
	blu = (int)rj*nBlu+nBluStart;

	if (j < JMAX)
	{
		red += (int) (nBay1000*5*(double)nRed*fabs(z.real()*z.imag())+(double)nRedStart);
		grn += (int) (nBay1000*5*(double)nGrn*fabs(z.real()*z.real())+(double)nGrnStart);
		blu += (int) (nBay1000*5*(double)nBlu*fabs(z.imag()*z.imag())+(double)nBluStart);
	}
	
	red+=128;
	grn+=128;
	blu+=128;

	if (j%2 == 0)
	{
		if (j%4==0)
		{
		}
		else
		{
			blu = blu ^ 0xFF;
		}
	}
	else
	{
		if (j%4==1)
		{
			red = red ^ 0xFF;
		}
		else
		{
			grn = grn ^ 0xFF;
		}
	}
					
	rj = (double) red;
	gj = (double) grn;
	bj = (double) blu;

	Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method36()
{
	red = (int) (5000*nBay1000*(cos(fabs(z.real()*z.real())))*(double)nRed+(double)nRedStart+
			rj*(double)nRed+(double)nRedStart);
	grn = (int) (5000*nBay1000*(cos(fabs(z.real()*z.imag())))*(double)nGrn+(double)nGrnStart+
			gj*(double)nGrn+(double)nGrnStart);
	blu = (int) (5000*nBay1000*(cos(z.squares()))*(double)nBlu+(double)nBluStart+
			bj*(double)nBlu+(double)nBluStart);
						
	rj = (double) red;
	gj = (double) grn;
	bj = (double) blu;

	Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method37()
{
	red = (int) (5000*nBay1000*(cos(z.squares()))*(double)nRed+(double)nRedStart+
			rj*(double)nRed+(double)nRedStart);
	grn = (int) (5000*nBay1000*(sin(fabs(z.real()*z.imag())))*(double)nGrn+(double)nGrnStart+
			gj*(double)nGrn+(double)nGrnStart);
	blu = (int) (5000*nBay1000*(cos(fabs(z.imag()*z.real())))*(double)nBlu+(double)nBluStart+
			bj*(double)nBlu+(double)nBluStart);
						
	rj = (double) red;
	gj = (double) grn;
	bj = (double) blu;

	Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method38()
{
	red = (int) (100*nBay1000*(fabs(atan(z.real()/z.imag())))*(double)nRed+(double)nRedStart+
			rj*(double)nRed+(double)nRedStart);
	grn = (int) (100*nBay1000*(fabs(atan(z.real()/z.imag())))*(double)nGrn+(double)nGrnStart+
			gj*(double)nGrn+(double)nGrnStart);
	blu = (int) (100*nBay1000*(fabs(atan(z.imag()/z.real())))*(double)nBlu+(double)nBluStart+
			bj*(double)nBlu+(double)nBluStart);
					
	rj = (double) red;
	gj = (double) grn;
	bj = (double) blu;

	Apply_The_Color();
}

void CFlarium24View::Generalized_Coloring_Method39()
{
	red = (int) (50*nBay1000*(fabs(z.real()*z.real()))*(double)nRed+(double)nRedStart+
		rj*(double)nRed+(double)nRedStart);
	grn = (int) (50*nBay1000*(fabs(z.real()*z.real()))*(double)nGrn+(double)nGrnStart+
		gj*(double)nGrn+(double)nGrnStart);
	blu = (int) (50*nBay1000*(fabs(z.imag()*z.imag()))*(double)nBlu+(double)nBluStart+
		bj*(double)nBlu+(double)nBluStart);
					
	rj = (double) red;
	gj = (double) grn;
	bj = (double) blu;

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

void CFlarium24View::OnColour23() 
{
	nColorMethod = 23;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour23(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 23)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnColour24() 
{
	nColorMethod = 24;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour24(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 24)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnColour25() 
{
	nColorMethod = 25;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour25(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 25)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnColour26() 
{
	nColorMethod = 26;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour26(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 26)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnColour27() 
{
	nColorMethod = 27;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour27(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 27)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnColour28() 
{
	nColorMethod = 28;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour28(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 28)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnColour29() 
{
	bFDVariate = TRUE;
	nColorMethod = 29;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour29(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 29)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnColour30() 
{
	bFDVariate = TRUE;
	nColorMethod = 30;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour30(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 30)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnColour31() 
{
	bFDVariate = TRUE;
	nColorMethod = 31;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour31(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 31)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnColour32() 
{
	bFDVariate = TRUE;
	nColorMethod = 32;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour32(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 32)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnColour33() 
{
	bFDVariate = TRUE;
	nColorMethod = 33;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour33(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 33)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnColour34() 
{
	bFDVariate = TRUE;
	nColorMethod = 34;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour34(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 34)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnColour35() 
{
	bFDVariate = TRUE;
	nColorMethod = 35;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour35(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 35)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnColour36() 
{
	bFDVariate = TRUE;
	nColorMethod = 36;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour36(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 36)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnColour37() 
{
	bFDVariate = TRUE;
	nColorMethod = 37;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour37(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 37)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnColour38() 
{
	bFDVariate = TRUE;
	nColorMethod = 38;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour38(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 38)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnColour39() 
{
	bFDVariate = TRUE;
	nColorMethod = 39;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateColour39(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 39)
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

void CFlarium24View::OnFilter72() 
{
	nFilter = 172;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter72(CCmdUI* pCmdUI) 
{
	if (nFilter == 172)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}


void CFlarium24View::OnFilter73() 
{
	nFilter = 173;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter73(CCmdUI* pCmdUI) 
{
	if (nFilter == 173)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter74() 
{
	nFilter = 174;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter74(CCmdUI* pCmdUI) 
{
	if (nFilter == 174)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter75() 
{
	nFilter = 175;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter75(CCmdUI* pCmdUI) 
{
	if (nFilter == 175)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter76() 
{
	nFilter = 176;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter76(CCmdUI* pCmdUI) 
{
	if (nFilter == 176)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter77() 
{
	nFilter = 177;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter77(CCmdUI* pCmdUI) 
{
	if (nFilter == 177)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter78() 
{
	nFilter = 178;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter78(CCmdUI* pCmdUI) 
{
	if (nFilter == 178)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter79() 
{
	nFilter = 179;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter79(CCmdUI* pCmdUI) 
{
	if (nFilter == 179)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter80() 
{
	nFilter = 180;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter80(CCmdUI* pCmdUI) 
{
	if (nFilter == 180)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter81() 
{
	nFilter = 181;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter81(CCmdUI* pCmdUI) 
{
	if (nFilter == 181)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter82() 
{
	nFilter = 182;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter82(CCmdUI* pCmdUI) 
{
	if (nFilter == 182)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}


void CFlarium24View::OnFilter83() 
{
	nFilter = 183;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter83(CCmdUI* pCmdUI) 
{
	if (nFilter == 183)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter84() 
{
	nFilter = 184;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter84(CCmdUI* pCmdUI) 
{
	if (nFilter == 184)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter85() 
{
	nFilter = 185;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter85(CCmdUI* pCmdUI) 
{
	if (nFilter == 185)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter86() 
{
	nFilter = 186;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter86(CCmdUI* pCmdUI) 
{
	if (nFilter == 186)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter87() 
{
	nFilter = 187;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter87(CCmdUI* pCmdUI) 
{
	if (nFilter == 187)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter88() 
{
	nFilter = 188;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter88(CCmdUI* pCmdUI) 
{
	if (nFilter == 188)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter89() 
{
	nFilter = 189;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter89(CCmdUI* pCmdUI) 
{
	if (nFilter == 189)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter90() 
{
	nFilter = 190;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter90(CCmdUI* pCmdUI) 
{
	if (nFilter == 190)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter91() 
{
	nFilter = 191;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter91(CCmdUI* pCmdUI) 
{
	if (nFilter == 191)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter92() 
{
	nFilter = 192;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter92(CCmdUI* pCmdUI) 
{
	if (nFilter == 192)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter93() 
{
	nFilter = 193;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter93(CCmdUI* pCmdUI) 
{
	if (nFilter == 193)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter94() 
{
	nFilter = 194;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter94(CCmdUI* pCmdUI) 
{
	if (nFilter == 194)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter95() 
{
	nFilter = 195;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter95(CCmdUI* pCmdUI) 
{
	if (nFilter == 195)	pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnFilter96() 
{
	nFilter = 196;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter96(CCmdUI* pCmdUI) 
{
	if (nFilter == 196)	pCmdUI->SetCheck(TRUE);
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

void CFlarium24View::OnFdimensionVariatei() 
{
	bFDVariate ^= TRUE;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFdimensionVariatei(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(bFDVariate);
}

void CFlarium24View::OnFilter3Nothingbutstrands() 
{
	bNothingButStrands ^= TRUE;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFilter3Nothingbutstrands(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(bNothingButStrands);	
}

//////////////////////

void CFlarium24View::OnOrderRgb() 
{
	nColorOrder = 0;	
	bLaunch = FALSE;
	bDraw = TRUE;
}

void CFlarium24View::OnUpdateOrderRgb(CCmdUI* pCmdUI) 
{
	if (nColorOrder == 0)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnOrderRbg() 
{
	nColorOrder = 1;	
	bLaunch = FALSE;
	bDraw = TRUE;
}

void CFlarium24View::OnUpdateOrderRbg(CCmdUI* pCmdUI) 
{
	if (nColorOrder == 1)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnOrderGrb() 
{
	nColorOrder = 2;	
	bLaunch = FALSE;
	bDraw = TRUE;
}

void CFlarium24View::OnUpdateOrderGrb(CCmdUI* pCmdUI) 
{
	if (nColorOrder == 2)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnOrderGbr() 
{
	nColorOrder = 3;	
	bLaunch = FALSE;
	bDraw = TRUE;
}

void CFlarium24View::OnUpdateOrderGbr(CCmdUI* pCmdUI) 
{
	if (nColorOrder == 3)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnOrderBrg() 
{
	nColorOrder = 4;	
	bLaunch = FALSE;
	bDraw = TRUE;
}

void CFlarium24View::OnUpdateOrderBrg(CCmdUI* pCmdUI) 
{
	if (nColorOrder == 4)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnOrderBgr() 
{
	nColorOrder = 5;	
	bLaunch = FALSE;
	bDraw = TRUE;
}

void CFlarium24View::OnUpdateOrderBgr(CCmdUI* pCmdUI) 
{
	if (nColorOrder == 5)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
