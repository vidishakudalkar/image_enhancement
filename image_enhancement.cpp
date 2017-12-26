// kingimageView.cpp : implementation of the CKingimageView class
//

#include "stdafx.h"
#include "kingimage.h"
#include <iostream>
#include "kingimageDoc.h"
#include "kingimageView.h"
#include <fstream>
#include <vector>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
using namespace std;
/////////////////////////////////////////////////////////////////////////////
// CKingimageView

IMPLEMENT_DYNCREATE(CKingimageView, CScrollView)

BEGIN_MESSAGE_MAP(CKingimageView, CScrollView)
	//{{AFX_MSG_MAP(CKingimageView)
	ON_WM_MOUSEMOVE()
	
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
	ON_COMMAND(ID_NEGATIVEIMAGE, &CKingimageView::OnNegativeimage)
	ON_COMMAND(ID_HISTOGRAMEQUALIZATION, &CKingimageView::OnHistogramequalization)
	ON_COMMAND(ID_REGIONDETECTION, &CKingimageView::OnRegiondetection)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKingimageView construction/destruction
int get_Threshold(int[], int, int);
CKingimageView::CKingimageView()
{
	// TODO: add construction code here

}

CKingimageView::~CKingimageView()
{
}

BOOL CKingimageView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CKingimageView drawing

void CKingimageView::OnDraw(CDC* pDC)
{
	CKingimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
//	pDC->SetStretchBltMode(COLORONCOLOR);
//	int x,y,bytes;
	if (pDoc->imagetype==PCX)
		(pDoc->_pcx)->draw(pDC);
	if (pDoc->imagetype==BMP)
		(pDoc->_bmp)->draw(pDC);
	if (pDoc->imagetype==GIF)
		(pDoc->_gif)->draw(pDC);
	if (pDoc->imagetype==JPG)
		(pDoc->_jpg)->draw(pDC);

}

/////////////////////////////////////////////////////////////////////////////
// CKingimageView printing

BOOL CKingimageView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CKingimageView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CKingimageView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CKingimageView diagnostics

#ifdef _DEBUG
void CKingimageView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CKingimageView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CKingimageDoc* CKingimageView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKingimageDoc)));
	return (CKingimageDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CKingimageView message handlers



void CKingimageView::OnInitialUpdate() 
{
	CScrollView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	CSize totalSize=CSize(::GetSystemMetrics(SM_CXSCREEN),
		                  ::GetSystemMetrics(SM_CYSCREEN));
	CSize pageSize=CSize(totalSize.cx/2,totalSize.cy/2);
	CSize lineSize=CSize(totalSize.cx/10,totalSize.cy/10);

	SetScrollSizes(MM_TEXT,totalSize,pageSize,lineSize);
}

void CKingimageView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CScrollView::OnMouseMove(nFlags, point);
}



void CKingimageView::OnNegativeimage()
{
	// TODO: Add your command handler code here
	CKingimageDoc* pDoc = GetDocument();


	int iBitPerPixel = pDoc->_bmp->bitsperpixel;
	int iWidth = pDoc->_bmp->width;
	int iHeight = pDoc->_bmp->height;
	BYTE *pImg = pDoc->_bmp->point;

	int Wp = iWidth;
	if (iBitPerPixel == 8)  ////Grey scale 8 bits image
	{
		int r = iWidth % 4;
		int p = (4 - r) % 4;
		Wp = iWidth + p;
	}
	else if (iBitPerPixel == 24)	// RGB image
	{
		int r = (3 * iWidth) % 4;
		int p = (4 - r) % 4;
		Wp = 3 * iWidth + p;
	}

	if (iBitPerPixel == 8)  ////Grey scale 8 bits image
	{
		for (int i = 0; i<iHeight; i++)
			for (int j = 0; j<iWidth; j++)
			{
				pImg[i*Wp + j] = 255 - pImg[i*Wp + j];
			}
	}
	else if (iBitPerPixel == 24)  ////True color 24bits image
	{
		for (int i = 0; i<iHeight; i++)
			for (int j = 0; j<iWidth; j++)
			{
				pImg[i*Wp + j * 3] = 255 - pImg[i*Wp + j * 3];      //B
			    pImg[i*Wp+j*3+1] = 255 - pImg[i*Wp + j * 3 + 1];      //G
				pImg[i*Wp + j * 3 + 2] = 255 - pImg[i*Wp + j * 3 + 2];      //R 
			}
	}

	////redraw the screen
	OnDraw(GetDC());
}




void CKingimageView::OnHistogramequalization()
{
	// TODO: Add your command handler code here

	CKingimageDoc* pDoc = GetDocument();


	int iBitPerPixel = pDoc->_bmp->bitsperpixel;
	int iWidth = pDoc->_bmp->width;
	int iHeight = pDoc->_bmp->height;
	BYTE *pImg = pDoc->_bmp->point;

	

	int Wp = iWidth;
	if (iBitPerPixel == 8)  ////Grey scale 8 bits image
	{
		int r = iWidth % 4;
		int p = (4 - r) % 4;
		Wp = iWidth + p;
	}
	else if (iBitPerPixel == 24)	// RGB image
	{
		int r = (3 * iWidth) % 4;
		int p = (4 - r) % 4;
		Wp = 3 * iWidth + p;
	}


	if (iBitPerPixel == 24)  ////True color 24bits image
	{
		float cdf[256] = { 0 };
		float probfreq[256] = { 0 };
		int freq_values[256] = { 0 };
		float tp = 0;
		int mean = 0;
		int mean_equalized = 0;
		int finalval[256] = { 0 };

		for (int i = 0; i < iHeight; i++)
			for (int j = 0; j < iWidth; j++)
			{
				mean = (int(pImg[i*Wp + j * 3]) + int(pImg[i*Wp + j * 3 + 1]) + int(pImg[i*Wp + j * 3 + 2])) / 3;
				freq_values[mean]++;
			}



		for (int x = 0; x <= 255; x++)
			tp = tp + freq_values[x];

		for (int x = 0; x <= 255; x++)
			probfreq[x] = float(freq_values[x] / tp);

		for (int x = 0; x <= 255; x++)
			cdf[x] = probfreq[x] + cdf[x - 1];

		for (int x = 0; x <= 255; x++)
			finalval[x] = cdf[x] * 255;

		for (int i = 0; i < iHeight; i++)
			for (int j = 0; j < iWidth; j++)
			{
				pImg[i*Wp + j * 3] = finalval[(pImg[i*Wp + j * 3])];
				pImg[i*Wp + j * 3 + 1] = finalval[(pImg[i*Wp + j * 3 + 1])];
				pImg[i*Wp + j * 3 + 2] = finalval[(pImg[i*Wp + j * 3 + 2])];
			}

		for (int i = 0; i < iHeight; i++)
			for (int j = 0; j < iWidth; j++)
			{
				mean_equalized = (int(pImg[i*Wp + j * 3]) + int(pImg[i*Wp + j * 3 + 1]) + int(pImg[i*Wp + j * 3 + 2])) / 3;
				freq_values[mean_equalized]++;
			}

	}
	
	////redraw the screen
	OnDraw(GetDC());

}
