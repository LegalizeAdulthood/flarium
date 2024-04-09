///  myfile.cpp
//
//  Source file for Device-Independent Bitmap (DIB) API.  Provides
//  the following functions:
//
//  SaveDIB()           - Saves the specified dib in a file
//  ReadDIBFile()       - Loads a DIB from a file
//
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1995 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include <math.h>
#include <io.h>
#include <direct.h>
#include "dibapi.h"

/*
 * Dib Header Marker - used in writing DIBs to files
 */
#define DIB_HEADER_MARKER   ((WORD) ('M' << 8) | 'B')

#ifdef _MAC
#define SWAPWORD(x) MAKEWORD(HIBYTE(x), LOBYTE(x))
#define SWAPLONG(x) MAKELONG(SWAPWORD(HIWORD(x)), SWAPWORD(LOWORD(x)))
void ByteSwapHeader(BITMAPFILEHEADER* bmiHeader);
void ByteSwapInfo(LPSTR lpHeader, BOOL fWin30Header);
#endif

/*************************************************************************
 *
 * SaveDIB()
 *
 * Saves the specified DIB into the specified CFile.  The CFile
 * is opened and closed by the caller.
 *
 * Parameters:
 *
 * HDIB hDib - Handle to the dib to save
 *
 * CFile& file - open CFile used to save DIB
 *
 * Return value: TRUE if successful, else FALSE or CFileException
 *
 *************************************************************************/


BOOL WINAPI SaveDIB(HDIB hDib, CFile& file)
{
	BITMAPFILEHEADER bmfHdr; // Header for Bitmap file
	LPBITMAPINFOHEADER lpBI;   // Pointer to DIB info structure
	DWORD dwDIBSize;

	if (hDib == NULL)
		return FALSE;

	/*
	 * Get a pointer to the DIB memory, the first of which contains
	 * a BITMAPINFO structure
	 */
	lpBI = (LPBITMAPINFOHEADER) ::GlobalLock((HGLOBAL) hDib);
	if (lpBI == NULL)
		return FALSE;

	if (!IS_WIN30_DIB(lpBI))
	{
		::GlobalUnlock((HGLOBAL) hDib);
		return FALSE;       // It's an other-style DIB (save not supported)
	}

	/*
	 * Fill in the fields of the file header
	 */

	/* Fill in file type (first 2 bytes must be "BM" for a bitmap) */
	bmfHdr.bfType = DIB_HEADER_MARKER;  // "BM"

	// Calculating the size of the DIB is a bit tricky (if we want to
	// do it right).  The easiest way to do this is to call GlobalSize()
	// on our global handle, but since the size of our global memory may have
	// been padded a few bytes, we may end up writing out a few too
	// many bytes to the file (which may cause problems with some apps).
	//
	// So, instead let's calculate the size manually (if we can)
	//
	// First, find size of header plus size of color table.  Since the
	// first DWORD in both BITMAPINFOHEADER and BITMAPCOREHEADER conains
	// the size of the structure, let's use this.

	dwDIBSize = *(LPDWORD)lpBI + ::PaletteSize((LPSTR)lpBI);  // Partial Calculation

	// Now calculate the size of the image

	if ((lpBI->biCompression == BI_RLE8) || (lpBI->biCompression == BI_RLE4))
	{
		// It's an RLE bitmap, we can't calculate size, so trust the
		// biSizeImage field

		dwDIBSize += lpBI->biSizeImage;
	}
	else
	{
		DWORD dwBmBitsSize;  // Size of Bitmap Bits only

		// It's not RLE, so size is Width (DWORD aligned) * Height

		dwBmBitsSize = WIDTHBYTES((lpBI->biWidth)*((DWORD)lpBI->biBitCount)) * lpBI->biHeight;

		dwDIBSize += dwBmBitsSize;

		// Now, since we have calculated the correct size, why don't we
		// fill in the biSizeImage field (this will fix any .BMP files which
		// have this field incorrect).

		lpBI->biSizeImage = dwBmBitsSize;
	}


	// Calculate the file size by adding the DIB size to sizeof(BITMAPFILEHEADER)

	bmfHdr.bfSize = dwDIBSize + sizeof(BITMAPFILEHEADER);
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;

	/*
	 * Now, calculate the offset the actual bitmap bits will be in
	 * the file -- It's the Bitmap file header plus the DIB header,
	 * plus the size of the color table.
	 */
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + lpBI->biSize
											  + PaletteSize((LPSTR)lpBI);
#ifdef _MAC
	ByteSwapHeader(&bmfHdr);

	// First swap the size field
	*((LPDWORD)lpBI) = SWAPLONG(*((LPDWORD)lpBI));

	// Now swap the rest of the structure (we don't save < Win30 files)
	ByteSwapInfo((LPSTR)lpBI, TRUE);
#endif

	TRY
	{
		// Write the file header
		file.Write((LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER));
		//
		// Write the DIB header and the bits
		//
		file.WriteHuge(lpBI, dwDIBSize);
	}
	CATCH (CFileException, e)
	{
#ifdef _MAC
		// Swap everything back
		*((LPDWORD)lpBI) = SWAPLONG(*((LPDWORD)lpBI));
		ByteSwapInfo((LPSTR)lpBI, TRUE);
#endif
		::GlobalUnlock((HGLOBAL) hDib);
		THROW_LAST();
	}
	END_CATCH

#ifdef _MAC
	// Swap everything back
	*((LPDWORD)lpBI) = SWAPLONG(*((LPDWORD)lpBI));
	ByteSwapInfo((LPSTR)lpBI, TRUE);
#endif

	::GlobalUnlock((HGLOBAL) hDib);
	return TRUE;
}


/*************************************************************************

  Function:  ReadDIBFile (CFile&)

   Purpose:  Reads in the specified DIB file into a global chunk of
			 memory.

   Returns:  A handle to a dib (hDIB) if successful.
			 NULL if an error occurs.

  Comments:  BITMAPFILEHEADER is stripped off of the DIB.  Everything
			 from the end of the BITMAPFILEHEADER structure on is
			 returned in the global memory handle.

*************************************************************************/


HDIB WINAPI ReadDIBFile(CFile& file)
{
	BITMAPFILEHEADER bmfHeader;
	DWORD dwBitsSize;
	HDIB hDIB;
	LPSTR pDIB;

	/*
	 * get length of DIB in bytes for use when reading
	 */

	dwBitsSize = file.GetLength();

	/*
	 * Go read the DIB file header and check if it's valid.
	 */
	if (file.Read((LPSTR)&bmfHeader, sizeof(bmfHeader)) != sizeof(bmfHeader))
		return NULL;

#ifdef _MAC
	ByteSwapHeader(&bmfHeader);
#endif
	if (bmfHeader.bfType != DIB_HEADER_MARKER)
		return NULL;

	/*
	 * Allocate memory for DIB
	 */
	hDIB = (HDIB) ::GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, dwBitsSize);
	if (hDIB == 0)
	{
		return NULL;
	}
	pDIB = (LPSTR) ::GlobalLock((HGLOBAL) hDIB);

	/*
	 * Go read the bits.
	 */
	if (file.ReadHuge(pDIB, dwBitsSize - sizeof(BITMAPFILEHEADER)) !=
		dwBitsSize - sizeof(BITMAPFILEHEADER) )
	{
		::GlobalUnlock((HGLOBAL) hDIB);
		::GlobalFree((HGLOBAL) hDIB);
		return NULL;
	}
#ifdef _MAC
	// First swap the size field
	*((LPDWORD)pDIB) = SWAPLONG(*((LPDWORD)pDIB));

	// Now swap the rest of the structure
	ByteSwapInfo(pDIB, IS_WIN30_DIB(pDIB));
#endif
	::GlobalUnlock((HGLOBAL) hDIB);
	return hDIB;
}

////////////////////////////////////////////////////////////
// WriteBit will write to a single pit (similiar to Setpixel)
//

BOOL WINAPI WriteBit (HANDLE hDIB, CSize m_sizeDoc,
                      int px, int py, DWORD Color)
{
	LPSTR    lpDIBHdr;            // Pointer to BITMAPINFOHEADER
	LPSTR    lpDIBBits;           // Pointer to DIB bits
	RGBTRIPLE * lpRGB;       // Pointer to the RGB Color Table 
  
	/* Check for valid DIB handle */
	if (hDIB == NULL)
		return FALSE;
  
  /* Lock down the DIB, and get a pointer to the beginning of the bit
	 *  buffer
	 */
	lpDIBHdr  = (LPSTR) ::GlobalLock((HGLOBAL) hDIB);
	lpDIBBits = ::FindDIBBits(lpDIBHdr);

  if (m_sizeDoc.cx > (int) ::DIBWidth(lpDIBHdr))
  {
    AfxMessageBox("Specified Width is too large");
    return FALSE;
  }    
  if (m_sizeDoc.cy > (int) ::DIBHeight(lpDIBHdr))
  {
    AfxMessageBox("Specified Height is too large");
    return FALSE;
  }    

  // Calculate the pixel location
	DWORD Pixel = px + py * m_sizeDoc.cx;
  
	lpRGB = (RGBTRIPLE *) lpDIBBits;
  
	lpRGB[Pixel].rgbtRed   = GetRValue(Color);
	lpRGB[Pixel].rgbtGreen = GetGValue(Color);
	lpRGB[Pixel].rgbtBlue  = GetBValue(Color);

	::GlobalUnlock((HGLOBAL) hDIB);

	return TRUE;
}

//////////////////////////////////////////////////////
// ApplyDibColors

BOOL WINAPI ApplyDibColors(HANDLE hDIB, int nRed, int nGrn, int nBlu,
	int nRedStart, int nGrnStart, int nBluStart, int* nIter_Data)
{
	LPSTR    lpDIBHdr;            // Pointer to BITMAPINFOHEADER
	LPSTR    lpDIBBits;           // Pointer to DIB bits
	RGBTRIPLE * lpRGB;       // Pointer to the RGB Color Table 
	
	DWORD			Pixel;
	DWORD			dwColorSize;
	
	int				red, grn, blu, i;
	//int				junk;
		
	/* Check for valid DIB handle */
	if (hDIB == NULL)
		return FALSE;
  
  /* Lock down the DIB, and get a pointer to the beginning of the bit
	 *  buffer
	 */
	lpDIBHdr  = (LPSTR) ::GlobalLock((HGLOBAL) hDIB);
	lpDIBBits = ::FindDIBBits(lpDIBHdr);

	dwColorSize = ::DIBWidth(lpDIBHdr)*::DIBHeight(lpDIBHdr);
  
	// Calculate the pixel location
	lpRGB = (RGBTRIPLE *) lpDIBBits;
  
	for (Pixel = 0; Pixel< dwColorSize; Pixel++)
	{
		i = nIter_Data[Pixel];

//		if (lpRGB[Pixel].rgbtRed		!= 0 &&
//				lpRGB[Pixel].rgbtGreen	!= 0 &&
//				lpRGB[Pixel].rgbtBlue		!= 0)
		
		if (i != 0)
		{
			red = i*nRed+nRedStart;  // Generalized Coloring Method
			grn = i*nGrn+nGrnStart;
			blu = i*nBlu+nBluStart;

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
	}

	::GlobalUnlock((HGLOBAL) hDIB);

	return TRUE;
}
