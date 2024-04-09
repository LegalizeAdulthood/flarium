// dib.h : header file
//

#include <vfw.h>

#ifdef _WIN32
#define huge
#endif

class CDIB : public CObject
{
// Construction
public:
	CDIB();

// Attributes
public:
	BYTE huge* GetBits();
	BOOL IsValid() { return (m_hDrawDib != NULL); }
	CSize GetSize();

	HDRAWDIB m_hDrawDib;

	int nWidth;
	int nHeight;
	int Orig_X, Orig_Y;
	int cxDIB, cyDIB;

	double rj, gj, bj;
	
	DWORD dwOffbits;

	// Convolution Kernal Array	variables
	//BYTE RK[9], GK[9], BK[9];
	//BYTE  R[9],  G[9],  B[9];				// Temporary color value arrays

	double C[9];
	double CK[9];		// Temporary color value array

	DWORD dwPixel[9];								// Pixel locations array

// Operations
public:
	BOOL Open(const char* pzFileName);
	void Close();
	BOOL Save(LPCTSTR pzFileName);
	void Draw(CDC* pDC, CSize dim, BOOL bStretchToFit, double PrtScale, long lOffCenter);
	//BOOL CreateDIB_Temp(DWORD cx, DWORD cy);
	BOOL CreateDIB(DWORD cx, DWORD cy);
	BOOL SetPixel (DWORD Xpix, DWORD Ypix, COLORREF Color);
	//BOOL SetPixelTemp (DWORD Xpix, DWORD Ypix, COLORREF Color);
	//BOOL SetPixel (DWORD Xpix, DWORD Ypix, BYTE Color);

//BOOL ApplyDibColors(int nRed, int nGrn, int nBlu,
//									  int nRedStart, int nGrnStart, int nBluStart,
//									  int* nIter_Data);

BOOL ApplyDibColors(int nRed, int nGrn, int nBlu,
									  int nRedStart, int nGrnStart, int nBluStart,
									  int* rIter_Data, int* gIter_Data, int* bIter_Data,
										int nColorOrder);

// Implementation
public:
	virtual ~CDIB();

protected:

	BYTE huge* m_pDIB;
};

