﻿
// ImageProcess_20211422View.cpp: CImageProcess20211422View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProcess_20211422.h"
#endif

#include "ImageProcess_20211422Doc.h"
#include "ImageProcess_20211422View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageProcess20211422View

IMPLEMENT_DYNCREATE(CImageProcess20211422View, CScrollView)

BEGIN_MESSAGE_MAP(CImageProcess20211422View, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_COMMAND(ID_PIXEL_ADD, &CImageProcess20211422View::OnPixelAdd)
	ON_COMMAND(ID_PIXEL_SUB, &CImageProcess20211422View::OnPixelSub)
	ON_COMMAND(ID_PIXEL_DIV, &CImageProcess20211422View::OnPixelDiv)
	ON_COMMAND(ID_PIXEL_MUL, &CImageProcess20211422View::OnPixelMul)
	ON_COMMAND(ID_PIXEL_HISTO_EQ, &CImageProcess20211422View::OnPixelHistoEq)
	ON_COMMAND(ID_PIXEL_LS_CONTRAST, &CImageProcess20211422View::OnPixelLsContrast)
	ON_COMMAND(ID_PIXEL_BINARIZATION, &CImageProcess20211422View::OnPixelBinarization)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_ADD, &CImageProcess20211422View::OnPixelTwoImageAdd)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_SUB, &CImageProcess20211422View::OnPixelTwoImageSub)
	ON_COMMAND(ID_REGION_SHARPENING, &CImageProcess20211422View::OnRegionSharpening)
	ON_COMMAND(ID_REGION_SMOOTHING, &CImageProcess20211422View::OnRegionSmoothing)
	ON_COMMAND(ID_REGION_EMBOSSING, &CImageProcess20211422View::OnRegionEmbossing)
	ON_COMMAND(ID_Region_Prewitt, &CImageProcess20211422View::OnRegionPrewitt)
	ON_COMMAND(ID_REGION_ROBERTS, &CImageProcess20211422View::OnRegionRoberts)
	ON_COMMAND(ID_REGION_SOBEL, &CImageProcess20211422View::OnRegionSobel)
	ON_COMMAND(ID_REGION_AVERAGE_FILTERING, &CImageProcess20211422View::OnRegionAverageFiltering)
	ON_COMMAND(ID_REGION_MEDIAN_FILTERING, &CImageProcess20211422View::OnRegionMedianFiltering)
	ON_COMMAND(ID_MORPHOLOGY_COLOR_TO_GRAY, &CImageProcess20211422View::OnMorphologyColorToGray)
	ON_COMMAND(ID_MORPHOLOGY_BINARIZATION, &CImageProcess20211422View::OnMorphologyBinarization)
	ON_COMMAND(ID_MORPHOLOGY_EROSION, &CImageProcess20211422View::OnMorphologyErosion)
	ON_COMMAND(ID_MORPHOLOGY_DILATION, &CImageProcess20211422View::OnMorphologyDilation)
	ON_COMMAND(ID_MORPHOLOGY_OPENING, &CImageProcess20211422View::OnMorphologyOpening)
	ON_COMMAND(ID_MORPHOLOGY_CLOSING, &CImageProcess20211422View::OnMorphologyClosing)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN, &CImageProcess20211422View::OnGeometryZoomin)
	ON_COMMAND(ID_GEOMETRY_BILINEAR_INTERPOLATION, &CImageProcess20211422View::OnGeometryBilinearInterpolation)
END_MESSAGE_MAP()

// CImageProcess20211422View 생성/소멸

CImageProcess20211422View::CImageProcess20211422View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CImageProcess20211422View::~CImageProcess20211422View()
{
}

BOOL CImageProcess20211422View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.
	
	return CScrollView::PreCreateWindow(cs);
}

// CImageProcess20211422View 그리기

void CImageProcess20211422View::OnDraw(CDC* pDC)
{
	CImageProcess20211422Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.	
	//pDC->TextOutA(120, 100, _T("asdf"));
	//pDC->Draw3dRect(10, 10, 100, 200, 0, 0);


	if (pDoc->depth == 1) {
		if (pDoc->inputImg != NULL) {
			for (int y = 0; y < pDoc->ImageHeight; y++) {
				for (int x = 0; x < pDoc->ImageWidth; x++) {
					pDC->SetPixel(x, y, RGB(pDoc->inputImg[y][x],
						pDoc->inputImg[y][x],
						pDoc->inputImg[y][x]));
				}
			}
		}

		if (pDoc->inputImg2 != NULL) {
			for (int y = 0; y < pDoc->ImageHeight; y++) {
				for (int x = 0; x < pDoc->ImageWidth; x++) {
					pDC->SetPixel(x + pDoc->ImageWidth + 30, y, RGB(pDoc->inputImg2[y][x],
						pDoc->inputImg2[y][x],
						pDoc->inputImg2[y][x]));
				}
			}
		}

		if (pDoc->resultImg != NULL) {
			for (int y = 0; y < pDoc->ImageHeight; y++) {
				for (int x = 0; x < pDoc->ImageWidth; x++) {
					pDC->SetPixel(x + pDoc->ImageWidth * 2 + 60, y, RGB(pDoc->resultImg[y][x],
						pDoc->resultImg[y][x],
						pDoc->resultImg[y][x]));
				}
			}
		}

		if (pDoc->gResultImg != NULL) {
			for (int y = 0; y < pDoc->gImageHeight; y++) {
				for (int x = 0; x < pDoc->gImageWidth; x++) {
					pDC->SetPixel(x +  30, y + pDoc->ImageHeight + 30, RGB(pDoc->gResultImg[y][x],
						pDoc->gResultImg[y][x],
						pDoc->gResultImg[y][x]));
				}
			}
		}
	}
	else {
		if (pDoc->inputImg != NULL) {
			for (int y = 0; y < pDoc->ImageHeight; y++) {
				for (int x = 0; x < pDoc->ImageWidth; x++) {
					pDC->SetPixel(x, y, RGB(pDoc->inputImg[y][3 * x],
						pDoc->inputImg[y][3 * x + 1],
						pDoc->inputImg[y][3 * x + 2]));
				}
			}
		}

		if (pDoc->inputImg2 != NULL) {
			for (int y = 0; y < pDoc->ImageHeight; y++) {
				for (int x = 0; x < pDoc->ImageWidth; x++) {
					pDC->SetPixel(x + pDoc->ImageWidth + 30, y, RGB(pDoc->inputImg2[y][3 * x],
						pDoc->inputImg2[y][3 * x + 1],
						pDoc->inputImg2[y][3 * x + 2]));
				}
			}
		}

		if (pDoc->resultImg != NULL) {
			for (int y = 0; y < pDoc->ImageHeight; y++) {
				for (int x = 0; x < pDoc->ImageWidth; x++) {
					pDC->SetPixel(x + pDoc->ImageWidth + 30, y, RGB(pDoc->resultImg[y][3 * x],
						pDoc->resultImg[y][3 * x + 1],
						pDoc->resultImg[y][3 * x + 2]));
				}
			}
		}

		if (pDoc->gResultImg != NULL) {
			for (int y = 0; y < pDoc->gImageHeight; y++) {
				for (int x = 0; x < pDoc->gImageWidth; x++) {
					pDC->SetPixel(x + 30, y + pDoc->ImageHeight + 30, RGB(pDoc->gResultImg[y][3 * x],
						pDoc->gResultImg[y][3 * x + 1],
						pDoc->gResultImg[y][3 * x + 2]));
				}
			}
		}
	}
}

void CImageProcess20211422View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = 2048;
	sizeTotal.cy = 1024;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CImageProcess20211422View 인쇄

BOOL CImageProcess20211422View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImageProcess20211422View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImageProcess20211422View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CImageProcess20211422View 진단

#ifdef _DEBUG
void CImageProcess20211422View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageProcess20211422View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageProcess20211422Doc* CImageProcess20211422View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProcess20211422Doc)));
	return (CImageProcess20211422Doc*)m_pDocument;
}
#endif //_DEBUG


// CImageProcess20211422View 메시지 처리기



int CImageProcess20211422View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


void CImageProcess20211422View::OnPixelAdd()
{
	CImageProcess20211422Doc* pDoc;

	pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->PixelAdd();
	Invalidate(FALSE);
}


void CImageProcess20211422View::OnPixelSub()
{
	CImageProcess20211422Doc* pDoc;

	pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->PixelSub();
	Invalidate(FALSE);
}


void CImageProcess20211422View::OnPixelDiv()
{
	CImageProcess20211422Doc* pDoc;

	pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->PixelDiv();
	Invalidate(FALSE);
}


void CImageProcess20211422View::OnPixelMul()
{
	CImageProcess20211422Doc* pDoc;

	pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->PixelMul();
	Invalidate(FALSE);
}


void CImageProcess20211422View::OnPixelHistoEq()
{
	CImageProcess20211422Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->PixelHistoEq();
	Invalidate(FALSE);
}


void CImageProcess20211422View::OnPixelLsContrast()
{
	CImageProcess20211422Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->PixelLsContrast();
	Invalidate(FALSE);
}


void CImageProcess20211422View::OnPixelBinarization()
{
	CImageProcess20211422Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->PixelBinarization();
	Invalidate(FALSE);
}


void CImageProcess20211422View::OnPixelTwoImageAdd()
{
	CImageProcess20211422Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->PixelTwoImageAdd();
	Invalidate(FALSE);
}


void CImageProcess20211422View::OnPixelTwoImageSub()
{
	CImageProcess20211422Doc* pDc = GetDocument();
	int value;
	int x, y;

	LoadTwoImage();

	for (y = 0; y < pDc->ImageHeight; y++) {
		for (x = 0; x < pDc->ImageWidth; x++) {
			value = pDc->inputImg[y][3 * x] - pDc->inputImg2[y][3 * x];
			pDc->resultImg[y][3 * x] = 255 * (value > 64);

			value = pDc->inputImg[y][3 * x + 1] - pDc->inputImg2[y][3 * x + 1];
			pDc->resultImg[y][3 * x + 1] = 255 * (value > 64);

			value = pDc->inputImg[y][3 * x + 2] - pDc->inputImg2[y][3 * x + 2];
			pDc->resultImg[y][3 * x + 2] = 255 * (value > 64);
		}
	}
	Invalidate(FALSE);
}


void CImageProcess20211422View::LoadTwoImage()
{
	CImageProcess20211422Doc* pDc = GetDocument();
	CFileDialog dlg(TRUE);
	CFile file;

	AfxMessageBox("Select the First Image");

	if (dlg.DoModal() == IDOK) {

		file.Open(dlg.GetPathName(), CFile::modeRead); // 파일 열기

		CArchive ar(&file, CArchive::load);
		pDc->LoadImageFile(ar);

		file.Close();
	}

	if (dlg.DoModal() == IDOK) {

		file.Open(dlg.GetPathName(), CFile::modeRead); // 파일 열기

		CArchive ar(&file, CArchive::load);
		pDc->LoadImageFile(ar);

		file.Close();
	}
}


void CImageProcess20211422View::OnRegionSharpening()
{
	CImageProcess20211422Doc* pDoc = GetDocument();

	float kernel[3][3] = { { 0, -1, 0 }, { -1, 5, -1 }, { 0, -1, 0 } };

	convolve(pDoc->inputImg, pDoc->resultImg, pDoc->ImageWidth, pDoc->ImageHeight, kernel, 0, pDoc->depth);

	Invalidate();
}


void CImageProcess20211422View::convolve(unsigned char** inImg, unsigned char** outImg, int cols, int rows, float mask[3][3], int bias, int depth)
{
	
	int x, y;
	int i, j;
	int sum, rsum, gsum, bsum;

	for (y = 1; y < rows - 1; y++) {
		for (x = 1; x < cols - 1; x++) {
			if (depth == 1) {
				sum = 0;
				for (j = 0; j < 3; j++) {
					for (i = 0; i < 3; i++) {
						sum += (inImg[y + j - 1][x + i - 1] * mask[j][i]);
					}
				}

				sum += bias;

				if (sum > 255) { sum = 255; }
				else if (sum < 0) { sum = 0; }

				outImg[y][x] = sum;
			}
			else {
				rsum = 0;
				gsum = 0;
				bsum = 0;
				for (j = 0; j < 3; j++) {
					for (i = 0; i < 3; i++) {
						rsum += (inImg[y + j - 1][3 * (x + i - 1)] * mask[j][i]);
						gsum += (inImg[y + j - 1][3 * (x + i - 1) + 1] * mask[j][i]);
						bsum += (inImg[y + j - 1][3 * (x + i - 1) + 2] * mask[j][i]);
					}
				}

				rsum += bias;
				gsum += bias;
				bsum += bias;

				if (rsum > 255) { rsum = 255; }
				else if (rsum < 0) { rsum = 0; }

				if (gsum > 255) { gsum = 255; }
				else if (gsum < 0) { gsum = 0; }

				if (bsum > 255) { bsum = 255; }
				else if (bsum < 0) { bsum = 0; }

				outImg[y][3 * x] = rsum;
				outImg[y][3 * x + 1] = gsum;
				outImg[y][3 * x + 2] = bsum;
			}
		}
	}
}


void CImageProcess20211422View::OnRegionSmoothing()
{
	CImageProcess20211422Doc* pDoc = GetDocument();

	float kernel[3][3] = { { 1 / 9.0f, 1 / 9.0f, 1 / 9.0f }, { 1 / 9.0f, 1 / 9.0f, 1 / 9.0f }, { 1 / 9.0f, 1 / 9.0f, 1 / 9.0f } };

	convolve(pDoc->inputImg, pDoc->resultImg, pDoc->ImageWidth, pDoc->ImageHeight, kernel, 0, pDoc->depth);

	Invalidate();
}


void CImageProcess20211422View::OnRegionEmbossing()
{
	CImageProcess20211422Doc* pDoc = GetDocument();

	float kernel[3][3] = { { -1, 0, 0 }, { 0, 0, 0 }, { 0, 0, 1 } };

	convolve(pDoc->inputImg, pDoc->resultImg, pDoc->ImageWidth, pDoc->ImageHeight, kernel, 0, pDoc->depth);

	Invalidate();
}


void CImageProcess20211422View::OnRegionPrewitt()
{
	CImageProcess20211422Doc* pDoc = GetDocument();

	float kernel_h[3][3] = { { -1, -1, -1 }, { 0, 0, 0 }, { 1, 1, 1 } };
	float kernel_v[3][3] = { { -1, 0, 1 }, { -1, 0, 1 }, { -1, 0, 1 } };

	unsigned char** Er, ** Ec;

	Er = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));

	for (int i = 0; i < pDoc->ImageHeight; i++) {
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
	}

	convolve(pDoc->inputImg, Er, pDoc->ImageWidth, pDoc->ImageHeight, kernel_h, 128, pDoc->depth);
	convolve(pDoc->inputImg, Ec, pDoc->ImageWidth, pDoc->ImageHeight, kernel_v, 128, pDoc->depth);

	for (int y = 0; y < pDoc->ImageHeight; y++) {
		for (int x = 0; x < pDoc->ImageWidth; x++) {
			if (pDoc->depth == 1) {
				int value = min(max(sqrt((Er[y][x] - 128) * (Er[y][x] - 128) + (Ec[y][x] - 128) * (Ec[y][x] - 128)), 0), 255);
				pDoc->resultImg[y][x] = (unsigned char)value;
			}
			else {
				int value_r = sqrt((Er[y][3 * x] - 128) * (Er[y][3 * x] - 128) + (Ec[y][3 * x] - 128) * (Ec[y][3 * x] - 128));
				int value_g =sqrt((Er[y][3* x + 1] - 128) * (Er[y][3 * x + 1] - 128) + (Ec[y][3 * x + 1] - 128) * (Ec[y][3 * x + 1] - 128));
				int value_b = sqrt((Er[y][3* x + 2] - 128) * (Er[y][3 * x + 2] - 128) + (Ec[y][3 * x + 2] - 128) * (Ec[y][3 * x + 2] - 128));

				int value = min(max(sqrt(value_r * value_r + value_g * value_g + value_b * value_b), 0), 255);

				pDoc->resultImg[y][3 * x] = value;
				pDoc->resultImg[y][3 * x + 1] = value;
				pDoc->resultImg[y][3 * x + 2] = value;
			}
		}
	}

	for (int i = 0; i < pDoc->ImageHeight; i++) {
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);

	Invalidate();
}


void CImageProcess20211422View::OnRegionRoberts()
{
	CImageProcess20211422Doc* pDoc = GetDocument();

	float kernel_h[3][3] = { {},  { 1, 0 }, { 0, -1 } };
	float kernel_v[3][3] = { {},  { 0, 1 }, { -1, 0 } };

	unsigned char** Er, ** Ec;

	Er = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));

	for (int i = 0; i < pDoc->ImageHeight; i++) {
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
	}

	convolve(pDoc->inputImg, Er, pDoc->ImageWidth, pDoc->ImageHeight, kernel_h, 128, pDoc->depth);
	convolve(pDoc->inputImg, Ec, pDoc->ImageWidth, pDoc->ImageHeight, kernel_v, 128, pDoc->depth);

	for (int y = 0; y < pDoc->ImageHeight; y++) {
		for (int x = 0; x < pDoc->ImageWidth; x++) {
			if (pDoc->depth == 1) {
				int value = min(max(sqrt((Er[y][x] - 128) * (Er[y][x] - 128) + (Ec[y][x] - 128) * (Ec[y][x] - 128)), 0), 255);
				pDoc->resultImg[y][x] = (unsigned char)value;
			}
			else {
				int value_r = sqrt((Er[y][3 * x] - 128) * (Er[y][3 * x] - 128) + (Ec[y][3 * x] - 128) * (Ec[y][3 * x] - 128));
				int value_g = sqrt((Er[y][3 * x + 1] - 128) * (Er[y][3 * x + 1] - 128) + (Ec[y][3 * x + 1] - 128) * (Ec[y][3 * x + 1] - 128));
				int value_b = sqrt((Er[y][3 * x + 2] - 128) * (Er[y][3 * x + 2] - 128) + (Ec[y][3 * x + 2] - 128) * (Ec[y][3 * x + 2] - 128));

				int value = min(max(sqrt(value_r * value_r + value_g * value_g + value_b * value_b), 0), 255);

				pDoc->resultImg[y][3 * x] = value;
				pDoc->resultImg[y][3 * x + 1] = value;
				pDoc->resultImg[y][3 * x + 2] = value;
			}
		}
	}

	for (int i = 0; i < pDoc->ImageHeight; i++) {
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);

	Invalidate();
}


void CImageProcess20211422View::OnRegionSobel()
{
	CImageProcess20211422Doc* pDoc = GetDocument();

	float kernel_h[3][3] = { { 1, 0, -1 }, { 2, 0, -2 }, { 1, 0, -1 } };
	float kernel_v[3][3] = { { -1, -2, -1 }, { 0, 0, 0 }, { 1, 2, 1 } };

	unsigned char** Er, ** Ec;

	Er = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));

	for (int i = 0; i < pDoc->ImageHeight; i++) {
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
	}

	convolve(pDoc->inputImg, Er, pDoc->ImageWidth, pDoc->ImageHeight, kernel_h, 128, pDoc->depth);
	convolve(pDoc->inputImg, Ec, pDoc->ImageWidth, pDoc->ImageHeight, kernel_v, 128, pDoc->depth);

	for (int y = 0; y < pDoc->ImageHeight; y++) {
		for (int x = 0; x < pDoc->ImageWidth; x++) {
			if (pDoc->depth == 1) {
				int value = min(max(sqrt((Er[y][x] - 128) * (Er[y][x] - 128) + (Ec[y][x] - 128) * (Ec[y][x] - 128)), 0), 255);
				pDoc->resultImg[y][x] = (unsigned char)value;
			}
			else {
				int value_r = sqrt((Er[y][3 * x] - 128) * (Er[y][3 * x] - 128) + (Ec[y][3 * x] - 128) * (Ec[y][3 * x] - 128));
				int value_g = sqrt((Er[y][3 * x + 1] - 128) * (Er[y][3 * x + 1] - 128) + (Ec[y][3 * x + 1] - 128) * (Ec[y][3 * x + 1] - 128));
				int value_b = sqrt((Er[y][3 * x + 2] - 128) * (Er[y][3 * x + 2] - 128) + (Ec[y][3 * x + 2] - 128) * (Ec[y][3 * x + 2] - 128));

				int value = min(max(sqrt(value_r * value_r + value_g * value_g + value_b * value_b), 0), 255);

				pDoc->resultImg[y][3 * x] = value;
				pDoc->resultImg[y][3 * x + 1] = value;
				pDoc->resultImg[y][3 * x + 2] = value;
			}
		}
	}

	for (int i = 0; i < pDoc->ImageHeight; i++) {
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);

	Invalidate();
}


void CImageProcess20211422View::OnRegionAverageFiltering()
{
	CImageProcess20211422Doc* pDoc = GetDocument();
	int x, y, xPos, yPos, i, j, sum, rSum, gSum, bSum, pixelCount;

	for (y = 0; y < pDoc->ImageHeight; y++) {
		for (x = 0; x < pDoc->ImageWidth; x++) {
			sum = 0;
			rSum = 0;
			gSum = 0;
			bSum = 0;
			pixelCount = 0;

			for (j = -2; j <= 2; j++) {
				for (i = -2; i <= 2; i++) {
					xPos = x + i;
					yPos = y + j;
					if (xPos >= 0 && xPos <= pDoc->ImageWidth - 1 && yPos >= 0 && yPos < pDoc->ImageHeight - 1) {
						if (pDoc->depth == 1) {
							sum += pDoc->inputImg[y + j][x + i];
						}
						else {
							rSum += pDoc->inputImg[y + j][3 * (x + i)];
							gSum += pDoc->inputImg[y + j][3 * (x + i) + 1];
							bSum += pDoc->inputImg[y + j][3 * (x + i) + 2];
						}
						pixelCount++;
					}
				}
			}
			if (pDoc->depth == 1) {
				pDoc->resultImg[y][x] = sum / pixelCount;
			}
			else {
				pDoc->resultImg[y][3 * x] = rSum / pixelCount;
				pDoc->resultImg[y][3 * x + 1] = gSum / pixelCount;
				pDoc->resultImg[y][3 * x + 2] = bSum / pixelCount;
			}
		}
	}
	Invalidate();
}


void CImageProcess20211422View::OnRegionMedianFiltering()
{
	CImageProcess20211422Doc* pDoc = GetDocument();
	int x, y;
	int i, j, temp;

	if (pDoc->depth == 1) {
		int n[9];

		for (y = 1; y < pDoc->ImageHeight - 1; y++) {
			for (x = 1; x < pDoc->ImageWidth - 1; x++) {

				n[0] = pDoc->inputImg[y - 1][x - 1];
				n[1] = pDoc->inputImg[y - 1][x];
				n[2] = pDoc->inputImg[y - 1][x + 1];
				n[3] = pDoc->inputImg[y][x - 1];
				n[4] = pDoc->inputImg[y][x];
				n[5] = pDoc->inputImg[y][x + 1];
				n[6] = pDoc->inputImg[y + 1][x - 1];
				n[7] = pDoc->inputImg[y + 1][x];
				n[8] = pDoc->inputImg[y + 1][x + 1];

				// 버블 정렬
				for (i = 8; i > 0; i--) {
					for (j = 0; j < i; j++) {
						if (n[j] > n[j + 1]) {
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
					}
				}

				pDoc->resultImg[y][x] = n[4];
			}
		}
	}
	else {
		int n[9][3];

		for (y = 1; y < pDoc->ImageHeight - 1; y++) {
			for (x = 1; x < pDoc->ImageWidth - 1; x++) {
				for (i = 0; i < 3; i++) {
					n[0][i] = pDoc->inputImg[y - 1][3 * (x - 1) + i];
					n[1][i] = pDoc->inputImg[y - 1][3 * (x)+i];
					n[2][i] = pDoc->inputImg[y - 1][3 * (x + 1) + i];
					n[3][i] = pDoc->inputImg[y][3 * (x - 1) + i];
					n[4][i] = pDoc->inputImg[y][3 * (x)+i];
					n[5][i] = pDoc->inputImg[y][3 * (x + 1) + i];
					n[6][i] = pDoc->inputImg[y + 1][3 * (x - 1) + i];
					n[7][i] = pDoc->inputImg[y + 1][3 * (x)+i];
					n[8][i] = pDoc->inputImg[y + 1][3 * (x + 1) + i];
				}

				// 버블 정렬
				for (int k = 0; k < 3; k++) {
					for (i = 8; i > 0; i--) {
						for (j = 0; j < i; j++) {
							if (n[j][k] > n[j + 1][k]) {
								temp = n[j + 1][k];
								n[j + 1][k] = n[j][k];
								n[j][k] = temp;
							}
						}
					}
				}

				pDoc->resultImg[y][3 * x] = n[4][0];
				pDoc->resultImg[y][3 * x + 1] = n[4][1];
				pDoc->resultImg[y][3 * x + 2] = n[4][2];
			}
		}
	}

	Invalidate();
}


void CImageProcess20211422View::OnMorphologyColorToGray()
{
	CImageProcess20211422Doc* pDoc = GetDocument();
	if (pDoc->depth == 1) { return; }

	int x, y;
	int gray;

	for (y = 0; y < pDoc->ImageHeight; y++) {
		for (x = 0; x < pDoc->ImageWidth; x++) {
			gray = (pDoc->inputImg[y][3 * x + 0] + pDoc->inputImg[y][3 * x + 1] + pDoc->inputImg[y][3 * x + 2]) / 3;
			pDoc->inputImg[y][3 * x + 0] = gray;
			pDoc->inputImg[y][3 * x + 1] = gray;
			pDoc->inputImg[y][3 * x + 2] = gray;
		}
	}

	Invalidate();
}


void CImageProcess20211422View::OnMorphologyBinarization()
{
	
	CImageProcess20211422Doc* pDoc = GetDocument();

	int x, y;
	int gray, threshold = 100;

	for (y = 0; y < pDoc->ImageHeight; y++) {
		for (x = 0; x < pDoc->ImageWidth; x++) {

			if (pDoc->depth == 1) {

				if (pDoc->inputImg[y][x] > threshold) { pDoc->inputImg[y][x] = 255; }
				else { pDoc->inputImg[y][x] = 0; }

			}
			else {

				if ((pDoc->inputImg[y][3 * x + 0] + pDoc->inputImg[y][3 * x + 1] + pDoc->inputImg[y][3 * x + 2]) / 3 > threshold) {
					pDoc->inputImg[y][3 * x + 0] = 255;
					pDoc->inputImg[y][3 * x + 1] = 255;
					pDoc->inputImg[y][3 * x + 2] = 255;
				}
				else {
					pDoc->inputImg[y][3 * x + 0] = 0;
					pDoc->inputImg[y][3 * x + 1] = 0;
					pDoc->inputImg[y][3 * x + 2] = 0;
				}

			}
		}
	}

	Invalidate();
}


void CImageProcess20211422View::OnMorphologyErosion()
{
	
	CImageProcess20211422Doc* pDoc = GetDocument();

	int x, y, i, j;
	int min = 255;
	int rmin = 255, gmin = 255, bmin = 255;

	for (y = 1; y < pDoc->ImageHeight - 1; y++) {
		for (x = 1; x < pDoc->ImageWidth - 1; x++) {

			min = rmin = gmin = bmin = 255;
			for (j = -1; j <= 1; j++) {
				for (i = -1; i <= 1; i++) {

					if (pDoc->depth == 1) {
						if (pDoc->inputImg[y + j][x + i] < min) {
							min = pDoc->inputImg[y + j][x + i];
						}
					}
					else {
						if (pDoc->inputImg[y + j][3 * (x + i) + 0] < rmin) {
							rmin = pDoc->inputImg[y + j][3 * (x + i) + 0];
						}
						if (pDoc->inputImg[y + j][3 * (x + i) + 1] < gmin) {
							gmin = pDoc->inputImg[y + j][3 * (x + i) + 1];
						}
						if (pDoc->inputImg[y + j][3 * (x + i) + 2] < bmin) {
							bmin = pDoc->inputImg[y + j][3 * (x + i) + 2];
						}
					}

				}
			}
			if (pDoc->depth == 1) { pDoc->resultImg[y][x] = min; }
			else {
				pDoc->resultImg[y][3 * x + 0] = rmin;
				pDoc->resultImg[y][3 * x + 1] = gmin;
				pDoc->resultImg[y][3 * x + 2] = bmin;
			}

		}
	}

	Invalidate();
}


void CImageProcess20211422View::OnMorphologyDilation()
{
	CImageProcess20211422Doc* pDoc = GetDocument();

	int x, y, i, j;
	int max = 0;
	int rmax = 0, gmax = 0, bmax = 0;

	for (y = 1; y < pDoc->ImageHeight - 1; y++) {
		for (x = 1; x < pDoc->ImageWidth - 1; x++) {

			max = rmax = gmax = bmax = 0;
			for (j = -1; j <= 1; j++) {
				for (i = -1; i <= 1; i++) {

					if (pDoc->depth == 1) {
						if (pDoc->inputImg[y + j][x + i] > max) {
							max = pDoc->inputImg[y + j][x + i];
						}
					}
					else {
						if (pDoc->inputImg[y + j][3 * (x + i) + 0] > rmax) {
							rmax = pDoc->inputImg[y + j][3 * (x + i) + 0];
						}
						if (pDoc->inputImg[y + j][3 * (x + i) + 1] > gmax) {
							gmax = pDoc->inputImg[y + j][3 * (x + i) + 1];
						}
						if (pDoc->inputImg[y + j][3 * (x + i) + 2] > bmax) {
							bmax = pDoc->inputImg[y + j][3 * (x + i) + 2];
						}
					}

				}
			}
			if (pDoc->depth == 1) { pDoc->resultImg[y][x] = max; }
			else {
				pDoc->resultImg[y][3 * x + 0] = rmax;
				pDoc->resultImg[y][3 * x + 1] = gmax;
				pDoc->resultImg[y][3 * x + 2] = bmax;
			}
			
		}
	}

	Invalidate();
}


void CImageProcess20211422View::OnMorphologyOpening()
{
	OnMorphologyErosion();
	CopyResultToInput();
	OnMorphologyErosion();
	CopyResultToInput();
	OnMorphologyErosion();
	CopyResultToInput();

	OnMorphologyDilation();
	CopyResultToInput();
	OnMorphologyDilation();
	CopyResultToInput();
	OnMorphologyDilation();
}


void CImageProcess20211422View::CopyResultToInput()
{
	CImageProcess20211422Doc *pDoc = GetDocument();
	int x, y;

	for (y = 0; y < pDoc->ImageHeight; y++) {
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++) {
			pDoc->inputImg[y][x] = pDoc->resultImg[y][x];
		}
	}
}


void CImageProcess20211422View::OnMorphologyClosing()
{
	OnMorphologyDilation();
	CopyResultToInput();
	OnMorphologyDilation();
	CopyResultToInput();
	OnMorphologyDilation();

	OnMorphologyErosion();
	CopyResultToInput();
	OnMorphologyErosion();
	CopyResultToInput();
	OnMorphologyErosion();
	CopyResultToInput();
}


void CImageProcess20211422View::OnGeometryZoomin()
{
	CImageProcess20211422Doc* pDoc = GetDocument();
	int xscale = 3;
	int yscale = 2;

	if (pDoc->gResultImg != NULL) {
		for (int i = 0; i < pDoc->gImageHeight; i++) {
			free(pDoc->gResultImg[i]);
		}
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->ImageWidth * xscale;
	pDoc->gImageHeight = pDoc->ImageHeight * yscale;

	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));

	for (int i = 0; i < pDoc->gImageHeight; i++) {
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	for (int y = 0; y < pDoc->gImageHeight; y++) {
		for (int x = 0; x < pDoc->gImageWidth; x++) {
			if (pDoc->depth == 1) {
				pDoc->gResultImg[y][x] = pDoc->inputImg[y / yscale][x / xscale];
			}
			else {
				pDoc->gResultImg[y][3 * x + 0] = pDoc->inputImg[y / yscale][3 * (x / xscale) + 0];
				pDoc->gResultImg[y][3 * x + 1] = pDoc->inputImg[y / yscale][3 * (x / xscale) + 1];
				pDoc->gResultImg[y][3 * x + 2] = pDoc->inputImg[y / yscale][3 * (x / xscale) + 2];
			}
		}
	}

	Invalidate();
}


void CImageProcess20211422View::OnGeometryBilinearInterpolation()
{
	CImageProcess20211422Doc* pDoc = GetDocument();
	float xscale = 2.1;
	float yscale = 1.5;
	float src_x, src_y;
	float alpha, beta;
	int E, F;
	int Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;

	if (pDoc->gResultImg != NULL) {
		for (int i = 0; i < pDoc->gImageHeight; i++) {
			free(pDoc->gResultImg[i]);
		}
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->ImageWidth * xscale + 0.5;
	pDoc->gImageHeight = pDoc->ImageHeight * yscale + 0.5;

	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));

	for (int i = 0; i < pDoc->gImageHeight; i++) {
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	for (int y = 0; y < pDoc->gImageHeight; y++) {
		for (int x = 0; x < pDoc->gImageWidth; x++) {
			src_x = x / (float)xscale;
			src_y = y / (float)yscale;
			alpha = src_x - x / xscale;
			beta = src_y - y / yscale;

			Ax = min(x / xscale, pDoc->ImageWidth - 1);
			Ay = min(y / yscale, pDoc->ImageWidth - 1);
			Bx = min(Ax + 1, pDoc->ImageWidth - 1);
			By = Ay;
			Cx = Ax;
			Cy = min(Ay + 1, pDoc->ImageWidth - 1);
			Dx = min(Ax + 1, pDoc->ImageWidth - 1);
			Dy = min(Ay + 1, pDoc->ImageWidth - 1);

			if (pDoc->depth == 1) {
				E = (int)(pDoc->inputImg[Ay][Ax] * (1 - alpha) + pDoc->inputImg[By][Bx] * alpha);
				F = (int)(pDoc->inputImg[Cy][Cx] * (1 - alpha) + pDoc->inputImg[Dy][Dx] * alpha);

				pDoc->gResultImg[y][x] = (unsigned char)(E * (1 - beta) + F * beta);
			}
			else {
				E = (int)(pDoc->inputImg[Ay][3 * Ax + 0] * (1 - alpha) + pDoc->inputImg[By][3 * Bx + 0] * alpha);
				F = (int)(pDoc->inputImg[Cy][3 * Cx + 0] * (1 - alpha) + pDoc->inputImg[Dy][3 * Dx + 0] * alpha);

				pDoc->gResultImg[y][3 * x + 0] = (unsigned char)(E * (1 - beta) + F * beta);

				E = (int)(pDoc->inputImg[Ay][3 * Ax + 1] * (1 - alpha) + pDoc->inputImg[By][3 * Bx + 1] * alpha);
				F = (int)(pDoc->inputImg[Cy][3 * Cx + 1] * (1 - alpha) + pDoc->inputImg[Dy][3 * Dx + 1] * alpha);

				pDoc->gResultImg[y][3 * x + 1] = (unsigned char)(E * (1 - beta) + F * beta);

				E = (int)(pDoc->inputImg[Ay][3 * Ax + 2] * (1 - alpha) + pDoc->inputImg[By][3 * Bx + 2] * alpha);
				F = (int)(pDoc->inputImg[Cy][3 * Cx + 2] * (1 - alpha) + pDoc->inputImg[Dy][3 * Dx + 2] * alpha);

				pDoc->gResultImg[y][3 * x + 2] = (unsigned char)(E * (1 - beta) + F * beta);
			}
		}
	}

	Invalidate();
}