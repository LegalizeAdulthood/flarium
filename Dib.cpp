// dib.cpp : implementation file
//

#include "stdafx.h"
#include "Flarium24.h"
#include "dib.h"

#define DIB_HEADER_MARKER   ((WORD) ('M' << 8) | 'B')

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDIB

CDIB::CDIB()
{
	m_hDrawDib = NULL;
	m_pDIB = NULL;
}

CDIB::~CDIB()
{
	Close();

	if (m_pDIB)
	{
#ifdef _WIN32
		delete m_pDIB;
#else
		GlobalFreePtr(m_pDIB);
#endif
	}
}


/////////////////////////////////////////////////////////////////////////////
// CDIB message handlers

void CDIB::Draw(CDC* pDC, CSize screen, BOOL bStretchToFit,
								double PrtScale, long lOffCenter)
{
	ASSERT(IsValid());

	cxDIB = ((BITMAPINFOHEADER*) m_pDIB)->biWidth; 
	cyDIB = ((BITMAPINFOHEADER*) m_pDIB)->biHeight;

	// Calculate the coordinates to center the object
	if (screen.cx > cxDIB)
		Orig_X = screen.cx/2 - cxDIB/2;
	else
		Orig_X = 0;

	if (screen.cy > cyDIB)
		Orig_Y = screen.cy/2 - cyDIB/2;
	else
		Orig_Y = 0;

	if (Orig_X == 0 && Orig_Y == 0)
	{
		nWidth	= -1;		// Display actual size
		nHeight = -1;
	}		

	if (bStretchToFit)
	{
		Orig_X = (int) lOffCenter/2;
		Orig_Y = (int) lOffCenter/2;
		nWidth	= screen.cx - (int) lOffCenter;    // Stretch to screen size
		nHeight = screen.cy - (int) lOffCenter;
	}
	else
	{
		nWidth	= -1;    // Don't stretch
		nHeight = -1;
	}

	if (pDC->IsPrinting() && !bStretchToFit)
	{
		// Calculate the coordinates to center the object
		if (screen.cx >= ((double) cxDIB * PrtScale))
		{
			Orig_X = (int) ((double) screen.cx/2 - 
									((double) cxDIB * PrtScale)/2);
		}
		else
		{
			Orig_X = 0;
			//wsprintf(cstr, "Image Clipped, X printer = %d, X file = %d",
			//	screen.cx, (int) ((double) cxDIB * PrtScale));
			//AfxMessageBox(cstr);
		}
			
		if (screen.cy >= ((double) cyDIB * PrtScale))
		{
			Orig_Y = (int) ((double) screen.cy/2 - 
		 							((double) cyDIB * PrtScale)/2);
		}
		else
		{
			Orig_Y = 0;
			//wsprintf(cstr, "Image Clipped, Y printer = %d, Y file = %d",
			//	screen.cy, (int) ((double) cyDIB * PrtScale)); 
			//AfxMessageBox(cstr);
			
		}

		CRect rcDest;

	  rcDest.left  	= Orig_X ;
  	rcDest.top   	= Orig_Y ;
    rcDest.right 	= (int) ((double) Orig_X +
     											((double) cxDIB * PrtScale)-1);
    rcDest.bottom	= (int) ((double) Orig_Y +
     											((double) cyDIB * PrtScale)-1);

		nWidth  = rcDest.Width();
		nHeight = rcDest.Height();
	}

	DrawDibDraw (m_hDrawDib, pDC->GetSafeHdc(),
		Orig_X,			// dest left
		Orig_Y,			// dest top
		nWidth,	  		//nWidth,  ("-1" for 1 to 1)
		nHeight,			//nHeight, ("-1" for 1 to 1)
		(BITMAPINFOHEADER*) m_pDIB,
		(LPVOID) GetBits(),
		0, 			// source left
		0,			// source top
		((BITMAPINFOHEADER*) m_pDIB)->biWidth,
		((BITMAPINFOHEADER*) m_pDIB)->biHeight,
		0);
}

CSize CDIB::GetSize()
{
	return CSize( ((BITMAPINFOHEADER*) m_pDIB)->biWidth,
		((BITMAPINFOHEADER*) m_pDIB)->biHeight);
}

void CDIB::Close()
{
	if (m_hDrawDib != NULL)
	{
		DrawDibClose(m_hDrawDib);
		m_hDrawDib = NULL;
	}		
}

BOOL CDIB::Open(const char* pzFileName)
{
	BITMAPFILEHEADER bmpfh;
	CFile file;
	int nHeaderSize;

	Close();

	// DrawDibOpen initializes the DrawDib library and
	// returns a handle for all DrawDib operations
	if (!(m_hDrawDib = DrawDibOpen()))
		goto bail;

	// Open and read the DIB file header
	nHeaderSize = sizeof(BITMAPFILEHEADER);

	if (!file.Open(pzFileName, CFile::modeRead | CFile::typeBinary))
		goto bail;

	if (file.Read((void *) &bmpfh, nHeaderSize) != (UINT) nHeaderSize)
		goto bail;

	// Validate the DIB file header by checking the first
	// two characters for the signature "BM"
	if (bmpfh.bfType != *((WORD*) "BM"))
		goto bail;

	// Allocate a big chunk of global memory to store the DIB
#ifdef _WIN32
	m_pDIB = (BYTE huge *) new char[bmpfh.bfSize - nHeaderSize];
#else
	m_pDIB = (BYTE huge *) GlobalAllocPtr(GMEM_MOVEABLE, 
		bmfph.bfSize - nHeaderSize);
#endif

	if (!m_pDIB)
		goto bail;

	// Read the DIB into the buffer 32K at a time using ReadHuge
	file.ReadHuge(m_pDIB, bmpfh.bfSize - nHeaderSize);

/*	
	if (((BITMAPINFOHEADER *) m_pDIB)->biSizeImage == 0)
	{
		// Whoever created this bitmap didn't set the biSizeImage
		// field.  It's easy to calculate, plus, the DrawDib functions
		// require it.
		BITMAPINFOHEADER huge * pDib = (BITMAPINFOHEADER * huge) m_pDIB;

      	pDib->biSizeImage = 
      		((((pDib->biWidth * pDib->biBitCount) + 31) & ~31) >> 3) * pDib->biHeight;
	}
*/
	file.Close();
	return TRUE;

bail:
	Close();
	return FALSE;
}

BOOL CDIB::Save(LPCTSTR pzFileName)
{
	CFile file;

	BITMAPFILEHEADER bmpfh;
	BITMAPINFOHEADER* lpDib = (BITMAPINFOHEADER *) m_pDIB;

	DWORD dwNumColors, dwColorTableSize ;
	WORD  wBitCount ;
	int nHeaderSize = sizeof(BITMAPFILEHEADER);

	ASSERT(IsValid());

	if (!file.Open(pzFileName, CFile::modeCreate |
		CFile::modeWrite ))
	{
		AfxMessageBox("Error creating file");
		return FALSE;
	}

	// The size of the color map is determined by the number of
	// RGBQUAD structures present.  It also depends on the bit-depth
	// of the DIB.

	wBitCount = lpDib->biBitCount ;

	if (lpDib->biSize >= 36)
		dwNumColors = lpDib->biClrUsed ;
	else
		dwNumColors = 0 ;

	if (dwNumColors == 0)
	{
		if (wBitCount != 24)
		    dwNumColors = 1L << wBitCount ;
		else
		    dwNumColors = 0 ;
	}

	dwColorTableSize = dwNumColors * sizeof (RGBQUAD) ;

	// Initialize BITMAPFILEHEADER
	bmpfh.bfType				= DIB_HEADER_MARKER;  // "BM";
	bmpfh.bfSize				= lpDib->biSizeImage + 
												sizeof(BITMAPINFOHEADER) +
												nHeaderSize + dwColorTableSize;
	bmpfh.bfReserved1		= 0;
	bmpfh.bfReserved2		= 0;
	bmpfh.bfOffBits			= (DWORD)sizeof(BITMAPFILEHEADER) + 
												(DWORD)sizeof(BITMAPINFOHEADER) + dwColorTableSize;

	dwOffbits = bmpfh.bfOffBits;
		
	TRY
	{
		// Write the file header
		file.Write((LPSTR) &bmpfh, nHeaderSize);

		// Write the DIB header and the bits
		file.WriteHuge(m_pDIB, bmpfh.bfSize - nHeaderSize);
	}
	CATCH (CFileException, e)
	{
		AfxMessageBox("Error writing file");
		file.Close();
		return FALSE;
	}
	END_CATCH

	file.Close();

	return TRUE;
}

BYTE huge * CDIB::GetBits()
{
	// The size of the color map is determined by the number of
	// RGBQUAD structures present.  It also depends on the bit-depth
	// of the DIB.

	DWORD dwNumColors, dwColorTableSize ;
	WORD  wBitCount ;
	BITMAPINFOHEADER* huge lpDib = (BITMAPINFOHEADER *huge) m_pDIB;

	wBitCount = lpDib->biBitCount ;

	if (lpDib->biSize >= 36)
		dwNumColors = lpDib->biClrUsed ;
	else
		dwNumColors = 0 ;

	if (dwNumColors == 0)
	{
		if (wBitCount != 24)
		    dwNumColors = 1L << wBitCount ;
		else
		    dwNumColors = 0 ;
	}

	dwColorTableSize = dwNumColors * sizeof (RGBQUAD) ;

	return m_pDIB + lpDib->biSize + dwColorTableSize ;
}

BOOL CDIB::CreateDIB(DWORD cx, DWORD cy)
{
	//BITMAPFILEHEADER bmpfh;

	//int nHeaderSize = sizeof(BITMAPFILEHEADER);

	if (m_hDrawDib != NULL)
	{
		Close();
	}

	// DrawDibOpen initializes the DrawDib library and
	// returns a handle for all DrawDib operations
	if (!(m_hDrawDib = DrawDibOpen()))
		goto bail;

	// Initialize BITMAPFILEHEADER
	//bmpfh.bfType			= DIB_HEADER_MARKER;  // "BM";
	//bmpfh.bfSize			= (cx+1) * (cy+1) * 3 + sizeof(BITMAPFILEHEADER);
	//bmpfh.bfReserved1 = 0;
	//bmpfh.bfReserved2 = 0;
	//bmpfh.bfOffBits		= (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER);

	if (m_pDIB)
		delete m_pDIB;
		
	// Allocate a big chunk of global memory to store the DIB
	m_pDIB = (BYTE huge *) new char[cx*cy*3 + sizeof(BITMAPINFOHEADER)];
	//m_pDIB = (BYTE huge *) new char[cx * cy + sizeof(BITMAPINFOHEADER) + 1024];

	if (!m_pDIB)
		goto bail;

	// Initialize BITMAPINFOHEADER
	((BITMAPINFOHEADER *) m_pDIB)->biSize 						= sizeof(BITMAPINFOHEADER);
  ((BITMAPINFOHEADER *) m_pDIB)->biWidth 						= cx;
  ((BITMAPINFOHEADER *) m_pDIB)->biHeight 					= cy;
  ((BITMAPINFOHEADER *) m_pDIB)->biPlanes 					= 1;
  ((BITMAPINFOHEADER *) m_pDIB)->biBitCount 				= 24;
  ((BITMAPINFOHEADER *) m_pDIB)->biCompression			= 0;
  ((BITMAPINFOHEADER *) m_pDIB)->biSizeImage				= cx * cy * 3;  // cx * cy; //cx * cy * 3;
  ((BITMAPINFOHEADER *) m_pDIB)->biXPelsPerMeter		= 0;	// 3779
  ((BITMAPINFOHEADER *) m_pDIB)->biYPelsPerMeter		= 0;	// 3779
  ((BITMAPINFOHEADER *) m_pDIB)->biClrUsed  		    = 0;
  ((BITMAPINFOHEADER *) m_pDIB)->biClrImportant			= 0;
	
	DWORD kx, ky;
	int red, grn, blu;

	// Write something into the initial new bitmap
	for (ky = 0 ; ky < cy ; ky++)
	{
		for (kx = 0 ; kx < cx ; kx++)
		{
			red = kx;
			grn = 0;
			blu = ky;

			if ((red & 0x1FF) > 0xFF) 
				red = red ^ 0xFF;    // Invert the color

			if ((grn & 0x1FF) > 0xFF) 
				grn = grn ^ 0xFF;    // Invert the color
      
			if ((blu & 0x1FF) > 0xFF) 
				blu = blu ^ 0xFF;    // Invert the color

			if (!SetPixel(kx, ky, RGB(red, grn, blu)))
				return FALSE;
		}
	}

	return TRUE;

bail:
	Close();
	return FALSE;
}

////////////////////////////////////////////////////////////
// Setpixel will write to a single bit (similiar to Setpixel)
//

BOOL CDIB::SetPixel (DWORD px, DWORD py, COLORREF Color)
//BOOL CDIB::SetPixel (DWORD px, DWORD py, BYTE Color)
{
	char cstr[81];
	ASSERT(IsValid());

	BYTE huge *lpDIBBits;           // Pointer to DIB bits
	
	RGBTRIPLE huge * lpRGB;       // Pointer to the RGB Color Table 

	DWORD cxDIB = ((BITMAPINFOHEADER*) m_pDIB)->biWidth; 
	DWORD	cyDIB = ((BITMAPINFOHEADER*) m_pDIB)->biHeight;

	if (px >= (DWORD)cxDIB || px < 0)
	{
		wsprintf(cstr,"Error, X Pixel = %ld, out of range", px);
		AfxMessageBox(cstr);
		return FALSE;
	}

	if (py >= (DWORD)cyDIB || py < 0)
	{
		wsprintf(cstr,"Error, Y Pixel = %ld, out of range", py);
		AfxMessageBox(cstr);
		return FALSE;
	}
	
  lpDIBBits = GetBits();
  lpRGB = (RGBTRIPLE huge *) lpDIBBits;
  
	//DWORD Pixel = (DWORD) (((DWORD) (dim.cy - 1 - py)
	//	 																	* (DWORD) dim.cx) + (DWORD) px);

 	DWORD Pixel = px + py * cxDIB;

	//lpDIBBits[Pixel] = Color;
		
	lpRGB[Pixel].rgbtRed   = GetRValue(Color);	 
  lpRGB[Pixel].rgbtGreen = GetGValue(Color);
  lpRGB[Pixel].rgbtBlue  = GetBValue(Color);

 	return TRUE;
}

//////////////////////////////////////////////////////
// ApplyDibColors

//BOOL CDIB::ApplyDibColors(int nRed, int nGrn, int nBlu,
//	int nRedStart, int nGrnStart, int nBluStart, int* nIter_Data)

BOOL CDIB::ApplyDibColors(int nRed, int nGrn, int nBlu,
	int nRedStart, int nGrnStart, int nBluStart,
	int* rIter_Data, int* gIter_Data, int* bIter_Data,
	int nColorOrder)
{
	//char cstr[81];
	ASSERT(IsValid());

	BYTE huge *lpDIBBits;           // Pointer to DIB bits
	
	RGBTRIPLE huge * lpRGB;       // Pointer to the RGB Color Table 

	DWORD cxDIB = ((BITMAPINFOHEADER*) m_pDIB)->biWidth; 
	DWORD	cyDIB = ((BITMAPINFOHEADER*) m_pDIB)->biHeight;
	
  lpDIBBits = GetBits();
  lpRGB = (RGBTRIPLE huge *) lpDIBBits;
  
 	DWORD Pixel, dwColorSize;
	CSize colorsize = GetSize();
	int red, grn, blu;
	dwColorSize = (DWORD) (colorsize.cx * colorsize.cy);

	//lpDIBBits[Pixel] = Color;

	for (Pixel = 0; Pixel< dwColorSize; Pixel++)
	{
		//i = nIter_Data[Pixel];

		rj = (double)rIter_Data[Pixel];
		gj = (double)gIter_Data[Pixel];
		bj = (double)bIter_Data[Pixel];


//		if (lpRGB[Pixel].rgbtRed		!= 0 &&
//				lpRGB[Pixel].rgbtGreen	!= 0 &&
//				lpRGB[Pixel].rgbtBlue		!= 0)
		
		//	red = i*nRed+nRedStart;  // Generalized Coloring Method
		//	grn = i*nGrn+nGrnStart;
		//	blu = i*nBlu+nBluStart;


		switch (nColorOrder)
		{
			case 0:		// rgb
				//red = (int) (rj*(double)nRed+(double)nRedStart);
				//grn = (int) (gj*(double)nGrn+(double)nGrnStart);
				//blu = (int) (bj*(double)nBlu+(double)nBluStart);	

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

		if ((red & 0x1FF) > 0xFF) 
			red = red ^ 0xFF;    // Invert the color

		if ((grn & 0x1FF) > 0xFF) 
			grn = grn ^ 0xFF;    // Invert the color
      
		if ((blu & 0x1FF) > 0xFF) 
			blu = blu ^ 0xFF;    // Invert the color

		lpRGB[Pixel].rgbtRed		= (BYTE) red;
		lpRGB[Pixel].rgbtGreen	= (BYTE) grn;
		lpRGB[Pixel].rgbtBlue		= (BYTE) blu;

	}

	return TRUE;
}
