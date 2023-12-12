
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
#include "CInputDlg.h"
#include "cmath"
#include "vfw.h"


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
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_SUBSAMPLING, &CImageProcess20211422View::OnGeometryZoomoutSubsampling)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_AVERAGE, &CImageProcess20211422View::OnGeometryZoomoutAverage)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_MEDIAN, &CImageProcess20211422View::OnGeometryZoomoutMedian)
	ON_COMMAND(ID_GEOMETRY_ROTATE, &CImageProcess20211422View::OnGeometryRotate)
	ON_COMMAND(ID_ROTATE_DIALOG, &CImageProcess20211422View::OnRotateDialog)
	ON_COMMAND(ID_GEOMETRY_MIRROR, &CImageProcess20211422View::OnGeometryMirror)
	ON_COMMAND(ID_GEOMETRY_UPSIDEDOWN, &CImageProcess20211422View::OnGeometryUpsidedown)
	ON_COMMAND(iD_GEOMETRY_WARPING, &CImageProcess20211422View::OnGeometryWarping)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_AVI_VIEW, &CImageProcess20211422View::OnAviView)
END_MESSAGE_MAP()

// CImageProcess20211422View 생성/소멸

CImageProcess20211422View::CImageProcess20211422View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	bAviMode = false;
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

	if (bAviMode) {
		// avi 파일 재생

		LoadAviFile(pDC);

		bAviMode = false;
		return;
	}


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
					pDC->SetPixel(x + pDoc->ImageWidth * 2 + (pDoc->inputImg2 != NULL) * pDoc->ImageWidth + 60, y, RGB(pDoc->resultImg[y][x],
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
					pDC->SetPixel(x + pDoc->ImageWidth + (pDoc->inputImg2 != NULL) * pDoc->ImageWidth + 60, y, RGB(pDoc->resultImg[y][3 * x],
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
			if (pDc->depth == 1) {
				value = pDc->inputImg[y][x] - pDc->inputImg2[y][x];
				pDc->resultImg[y][x] = max(0, value);
			}
			else {
				value = pDc->inputImg[y][3 * x] - pDc->inputImg2[y][3 * x + 0];
				pDc->resultImg[y][3 * x] = max(0, value);

				value = pDc->inputImg[y][3 * x + 1] - pDc->inputImg2[y][3 * x + 1];
				pDc->resultImg[y][3 * x + 1] = max(0, value);

				value = pDc->inputImg[y][3 * x + 2] - pDc->inputImg2[y][3 * x + 2];
				pDc->resultImg[y][3 * x + 2] = max(0, value);
			}
		}
	}
	Invalidate(FALSE);
}


void CImageProcess20211422View::LoadTwoImage()
{
	CImageProcess20211422Doc* pDc = GetDocument();
	CFile file;
	CFileDialog dlg(TRUE);

	AfxMessageBox("Select the First Image");

	if (dlg.DoModal() == IDOK) {
		file.Open(dlg.GetPathName(), CFile::modeRead); // 파일 열기
		CArchive ar(&file, CArchive::load);
		pDc->LoadImageFile(ar);
		//file.Read(inputImg, 256 * 256);
		file.Close();
	}

	AfxMessageBox("Select the Second Image");

	if (dlg.DoModal() == IDOK) {
		file.Open(dlg.GetPathName(), CFile::modeRead); // 파일 열기
		CArchive ar(&file, CArchive::load);
		pDc->LoadSecondImageFile(ar);
		//file.Read(inputImg2, 256 * 256);
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
	float xscale = 3; // 2.1
	float yscale = 2; // 1.5
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
			src_x = x / xscale;
			src_y = y / yscale;
			alpha = src_x - (int)(x / xscale);
			beta = src_y - (int)(y / yscale);
			
			Ax = min(max(x / xscale, 0), pDoc->ImageWidth - 1);
			Ay = min(max(y / yscale, 0), pDoc->ImageHeight - 1);
			Bx = min(max(Ax + 1, 0), pDoc->ImageWidth - 1);
			By = Ay;
			Cx = Ax;
			Cy = min(max(Ay + 1, 0), pDoc->ImageHeight - 1);
			Dx = min(max(Ax + 1, 0), pDoc->ImageWidth - 1);
			Dy = min(max(Ay + 1, 0), pDoc->ImageHeight - 1);

			if (pDoc->depth == 1) {
				E = (int)(pDoc->inputImg[Ay][Ax] * (1 - alpha)
					+ pDoc->inputImg[By][Bx] * alpha);
				F = (int)(pDoc->inputImg[Cy][Cx] * (1 - alpha)
					+ pDoc->inputImg[Dy][Dx] * alpha);

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


void CImageProcess20211422View::OnGeometryZoomoutSubsampling()
{
	CImageProcess20211422Doc* pDoc = GetDocument();
	int x, y, i;

	int xscale = 3;
	int yscale = 2;

	if (pDoc->gResultImg != NULL) {
		for (i = 0; i < pDoc->gImageHeight; i++) {
			if (pDoc->gResultImg[i] != NULL) {
				free(pDoc->gResultImg[i]);
			}
		}
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->ImageWidth / xscale;
	pDoc->gImageHeight = pDoc->ImageHeight / yscale;

	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));

	for (i = 0; i < pDoc->gImageHeight; i++) {
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	for (y = 0; y < pDoc->gImageHeight; y++) {
		for (x = 0; x < pDoc->gImageWidth; x++) {
			if (pDoc->depth == 1) {
				pDoc->gResultImg[y][x] = pDoc->inputImg[y * yscale][x * xscale];
			}
			else {
				pDoc->gResultImg[y][3 * x + 0] = pDoc->inputImg[y * yscale][3 * x * xscale + 0];
				pDoc->gResultImg[y][3 * x + 1] = pDoc->inputImg[y * yscale][3 * x * xscale + 1];
				pDoc->gResultImg[y][3 * x + 2] = pDoc->inputImg[y * yscale][3 * x * xscale + 2];
			}
		}
	}

	Invalidate();
}


void CImageProcess20211422View::OnGeometryZoomoutMedian()
{
	OnRegionMedianFiltering();
	CopyResultToInput();
	OnGeometryZoomoutSubsampling();
}


void CImageProcess20211422View::OnGeometryZoomoutAverage()
{
	CImageProcess20211422Doc* pDoc = GetDocument();
	int x, y, i, j;

	int sum, rsum, gsum, bsum;

	int src_x, src_y;

	int xscale = 3;
	int yscale = 2;

	if (pDoc->gResultImg != NULL) {
		for (i = 0; i < pDoc->gImageHeight; i++) {
			free(pDoc->gResultImg[i]);
		}
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->ImageWidth / xscale;
	pDoc->gImageHeight = pDoc->ImageHeight / yscale;

	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));

	for (i = 0; i < pDoc->gImageHeight; i++) {
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	for (y = 0; y < pDoc->ImageHeight; y += yscale) {
		for (x = 0; x < pDoc->ImageWidth; x += xscale) {
			sum = 0;
			rsum = 0;
			gsum = 0;
			bsum = 0;
			for (j = 0; j < yscale; j++) {
				for (i = 0; i < xscale; i++) {
					src_x = min(x + i, pDoc->ImageWidth - 1);
					src_y = min(y + j, pDoc->ImageHeight - 1);

					if (pDoc->depth == 1) {
						sum += pDoc->inputImg[src_y][src_x];
					}
					else {
						rsum += pDoc->inputImg[src_y][3 * src_x + 0];
						gsum += pDoc->inputImg[src_y][3 * src_x + 1];
						bsum += pDoc->inputImg[src_y][3 * src_x + 2];
					}
				}
			}
			if (pDoc->depth == 1) {
				pDoc->gResultImg[y / yscale][x / xscale] = sum / (xscale * yscale);
			}
			else {
				pDoc->gResultImg[y / yscale][3 * (x / xscale) + 0] = rsum / (xscale * yscale);
				pDoc->gResultImg[y / yscale][3 * (x / xscale) + 1] = gsum / (xscale * yscale);
				pDoc->gResultImg[y / yscale][3 * (x / xscale) + 2] = bsum / (xscale * yscale);
			}
		}
	}
	Invalidate();
}

#define PI 3.141592
void CImageProcess20211422View::OnGeometryRotate()
{
	CImageProcess20211422Doc* pDoc = GetDocument();

	int x, y, i, j;

	int x_source, y_source;
	
	int angle = 30;
	float radian;
	
	int Cx, Cy, Oy;

	int xdiff, ydiff;

	if (pDoc->gResultImg != NULL) {
		for (int i = 0; i < pDoc->gImageHeight; i++) {
			free(pDoc->gResultImg[i]);
		}
		free(pDoc->gResultImg);
	}

	radian = PI / 180 * angle;
	//while (radian > 2 * PI) { radian -= 2 * PI; }
	//while (radian < 0) { radian += 2 * PI; }

	pDoc->gImageWidth = abs(pDoc->ImageHeight * cos(PI / 2 - radian)) + abs(pDoc->ImageWidth * cos(radian));
	pDoc->gImageHeight = abs(pDoc->ImageHeight * cos(radian)) + abs(pDoc->ImageWidth * cos(PI / 2 - radian));

	//pDoc->gImageWidth = pDoc->ImageWidth * sin(PI + radian) + pDoc->ImageHeight * cos(radian);
	//pDoc->gImageHeight = pDoc->ImageWidth * cos(PI + radian) + pDoc->ImageHeight * sin(radian);

	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));

	for (i = 0; i < pDoc->gImageHeight; i++) {
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	Cx = pDoc->ImageWidth / 2;
	Cy = pDoc->ImageHeight / 2;

	Oy = pDoc->ImageHeight - 1;

	xdiff = (pDoc->gImageWidth - pDoc->ImageWidth) / 2;
	ydiff = (pDoc->gImageHeight - pDoc->ImageHeight) / 2;

	for (y = -ydiff; y < pDoc->gImageHeight - ydiff; y++) {
		for (x = -xdiff; x < pDoc->gImageWidth - xdiff; x++) {
			x_source = (Oy - y - Cy) * sin(radian) + (x - Cx) * cos(radian) + Cx;
			y_source = (Oy - y - Cy) * cos(radian) - (x - Cx) * sin(radian) + Cy;

			y_source = Oy - y_source;

			if (pDoc->depth == 1) {
				if (x_source < 0 || x_source > pDoc->ImageWidth - 1 || y_source < 0 || y_source > pDoc->ImageHeight - 1) {
					pDoc->gResultImg[y + ydiff][x + xdiff] = 255;
				}
				else {
					pDoc->gResultImg[y + ydiff][x + xdiff] = pDoc->inputImg[y_source][x_source];
				}
			}
			else {
				if (x_source < 0 || x_source > pDoc->ImageWidth - 1 || y_source < 0 || y_source > pDoc->ImageHeight - 1) {
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 0] = 255;
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 1] = 255;
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 2] = 255;
				}
				else {
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 0] = pDoc->inputImg[y_source][3 * x_source + 0];
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 1] = pDoc->inputImg[y_source][3 * x_source + 1];
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 2] = pDoc->inputImg[y_source][3 * x_source + 2];
				}
			}
		}
	}
	Invalidate();
}


void CImageProcess20211422View::OnRotateDialog()
{
	CImageProcess20211422Doc* pDoc = GetDocument();

	CInputDlg inputDlg;
	inputDlg.DoModal();

	int x, y, i, j;

	int x_source, y_source;

	int angle = inputDlg.m_zoom_in_ratio;
	float radian;

	int Cx, Cy, Oy;

	int xdiff, ydiff;

	if (pDoc->gResultImg != NULL) {
		for (int i = 0; i < pDoc->gImageHeight; i++) {
			free(pDoc->gResultImg[i]);
		}
		free(pDoc->gResultImg);
	}

	radian = PI / 180 * angle;
	//while (radian > 2 * PI) { radian -= 2 * PI; }
	//while (radian < 0) { radian += 2 * PI; }

	pDoc->gImageWidth = abs(pDoc->ImageHeight * cos(PI / 2 - radian)) + abs(pDoc->ImageWidth * cos(radian));
	pDoc->gImageHeight = abs(pDoc->ImageHeight * cos(radian)) + abs(pDoc->ImageWidth * cos(PI / 2 - radian));

	//pDoc->gImageWidth = pDoc->ImageWidth * sin(PI + radian) + pDoc->ImageHeight * cos(radian);
	//pDoc->gImageHeight = pDoc->ImageWidth * cos(PI + radian) + pDoc->ImageHeight * sin(radian);

	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));

	for (i = 0; i < pDoc->gImageHeight; i++) {
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	Cx = pDoc->ImageWidth / 2;
	Cy = pDoc->ImageHeight / 2;

	Oy = pDoc->ImageHeight - 1;

	xdiff = (pDoc->gImageWidth - pDoc->ImageWidth) / 2;
	ydiff = (pDoc->gImageHeight - pDoc->ImageHeight) / 2;

	for (y = -ydiff; y < pDoc->gImageHeight - ydiff; y++) {
		for (x = -xdiff; x < pDoc->gImageWidth - xdiff; x++) {
			x_source = (Oy - y - Cy) * sin(radian) + (x - Cx) * cos(radian) + Cx;
			y_source = (Oy - y - Cy) * cos(radian) - (x - Cx) * sin(radian) + Cy;

			y_source = Oy - y_source;

			if (pDoc->depth == 1) {
				if (x_source < 0 || x_source > pDoc->ImageWidth - 1 || y_source < 0 || y_source > pDoc->ImageHeight - 1) {
					pDoc->gResultImg[y + ydiff][x + xdiff] = 255;
				}
				else {
					pDoc->gResultImg[y + ydiff][x + xdiff] = pDoc->inputImg[y_source][x_source];
				}
			}
			else {
				if (x_source < 0 || x_source > pDoc->ImageWidth - 1 || y_source < 0 || y_source > pDoc->ImageHeight - 1) {
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 0] = 255;
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 1] = 255;
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 2] = 255;
				}
				else {
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 0] = pDoc->inputImg[y_source][3 * x_source + 0];
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 1] = pDoc->inputImg[y_source][3 * x_source + 1];
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 2] = pDoc->inputImg[y_source][3 * x_source + 2];
				}
			}
		}
	}
	Invalidate();
}


void CImageProcess20211422View::OnGeometryMirror()
{
	CImageProcess20211422Doc* pDoc = GetDocument();
	
	int x, y;

	for (y = 0; y < pDoc->ImageHeight; y++) {
		for (x = 0; x < pDoc->ImageWidth; x++) {
			if (pDoc->depth == 1) {
				pDoc->resultImg[y][x] = pDoc->inputImg[y][pDoc->ImageWidth - 1 - x];
			}
			else {
				pDoc->resultImg[y][3 * x + 0] = pDoc->inputImg[y][3 * (pDoc->ImageWidth - 1 - x) + 0];
				pDoc->resultImg[y][3 * x + 1] = pDoc->inputImg[y][3 * (pDoc->ImageWidth - 1 - x) + 1];
				pDoc->resultImg[y][3 * x + 2] = pDoc->inputImg[y][3 * (pDoc->ImageWidth - 1 - x) + 2];
			}
		}
	}
	Invalidate();
}


void CImageProcess20211422View::OnGeometryUpsidedown()
{
	CImageProcess20211422Doc* pDoc = GetDocument();

	int x, y;

	for (y = 0; y < pDoc->ImageHeight; y++) {
		for (x = 0; x < pDoc->ImageWidth; x++) {
			if (pDoc->depth == 1) {
				pDoc->resultImg[y][x] = pDoc->inputImg[pDoc->ImageHeight - 1 - y][x];
			}
			else {
				pDoc->resultImg[y][3 * x + 0] = pDoc->inputImg[pDoc->ImageHeight - 1 - y][3 * x + 0];
				pDoc->resultImg[y][3 * x + 1] = pDoc->inputImg[pDoc->ImageHeight - 1 - y][3 * x + 1];
				pDoc->resultImg[y][3 * x + 2] = pDoc->inputImg[pDoc->ImageHeight - 1 - y][3 * x + 2];
			}
		}
	}
	Invalidate();
}

typedef struct {
	int Px;
	int Py;
	int Qx;
	int Qy;
} control_line;

control_line mctrl_source = { 100, 100, 150, 150 };
control_line mctrl_dest = { 100, 100, 200, 200 };

void CImageProcess20211422View::OnGeometryWarping()
{
	CImageProcess20211422Doc* pDoc = GetDocument();

	control_line source_lines[5] = {
		mctrl_source,
		{0, 0, pDoc->ImageWidth - 1, 0},
		{pDoc->ImageWidth - 1, 0, pDoc->ImageWidth - 1, pDoc->ImageHeight - 1},
		{pDoc->ImageWidth - 1, pDoc->ImageHeight - 1, 0, pDoc->ImageHeight - 1},
		{0, pDoc->ImageHeight - 1, 0, 0}
	};
	control_line dest_lines[5] = {
		mctrl_dest,
		{0, 0, pDoc->ImageWidth - 1, 0},
		{pDoc->ImageWidth - 1, 0, pDoc->ImageWidth - 1, pDoc->ImageHeight - 1},
		{pDoc->ImageWidth - 1, pDoc->ImageHeight - 1, 0, pDoc->ImageHeight - 1},
		{0, pDoc->ImageHeight - 1, 0, 0}
	};

	source_lines[0] = mctrl_source;
	dest_lines[0] = mctrl_dest;
	int x, y;

	double u;
	double h;
	double d;
	double tx, ty;
	double xp, yp;

	double weight;
	double totalWeight;
	double a = 0.001;
	double b = 2.0;
	double p = 0.75;

	int x1, x2, y1, y2;
	int src_x1, src_y1, src_x2, src_y2;
	double src_line_length, dest_line_length;

	int num_lines = 5;
	int line;
	int source_x, source_y;
	int last_row, last_col;

	last_row = pDoc->ImageHeight - 1;
	last_col = pDoc->ImageWidth - 1;

	for (y = 0; y < pDoc->ImageHeight; y++) {
		for (x = 0; x < pDoc->ImageWidth; x++) {
			totalWeight = 0.0;
			tx = 0.0;
			ty = 0.0;

			for (line = 0; line < num_lines; line++) {
				x1 = dest_lines[line].Px;
				y1 = dest_lines[line].Py;
				x2 = dest_lines[line].Qx;
				y2 = dest_lines[line].Qy;

				dest_line_length = sqrt((double)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));

				u = (double)((x - x1) * (x2 - x1) + (y - y1) * (y2 - y1)) / (double)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
				h = (double)((y - y1) * (x2 - x1) - (x - x1) * (y2 - y1)) / dest_line_length;

				if (u < 0) { d = sqrt((double)((x - x1) * (x - x1) + (y - y1) * (y - y1))); }
				else if (u > 1) { d = sqrt((double)((x - x2) * (x - x2) + (y - y2) * (y - y2))); }
				else { d = fabs(h); }

				src_x1 = source_lines[line].Px;
				src_y1 = source_lines[line].Py;
				src_x2 = source_lines[line].Qx;
				src_y2 = source_lines[line].Qy;
				src_line_length = sqrt((double)((src_x2 - src_x1) * (src_x2 - src_x1) + (src_y2 - src_y1) * (src_y2 - src_y1)));

				xp = src_x1 + u * (src_x2 - src_x1) - h * (src_y2 - src_y1) / src_line_length;
				yp = src_y1 + u * (src_y2 - src_y1) + h * (src_x2 - src_x1) / src_line_length;

				weight = pow((pow((double)(dest_line_length), p) / (a + d)), b);

				tx += (xp - x) * weight;
				ty += (yp - y) * weight;

				totalWeight += weight;
			}

			source_x = x + (int)(tx / totalWeight + 0.5);
			source_y = y + (int)(ty / totalWeight + 0.5);

			source_x = min(max(source_x, 0), last_col);
			source_y = min(max(source_y, 0), last_row);

			if (pDoc->depth == 1) {
				pDoc->resultImg[y][x] = pDoc->inputImg[source_y][source_x];
			}
			else {
				pDoc->resultImg[y][3 * x + 0] = pDoc->inputImg[source_y][3 * source_x + 0];
				pDoc->resultImg[y][3 * x + 1] = pDoc->inputImg[source_y][3 * source_x + 1];
				pDoc->resultImg[y][3 * x + 2] = pDoc->inputImg[source_y][3 * source_x + 2];
			}
		}
	}

	Invalidate();
}

CPoint mpos_st, mpos_end;

void CImageProcess20211422View::OnLButtonDown(UINT nFlags, CPoint point)
{
	mpos_st = point;

	CScrollView::OnLButtonDown(nFlags, point);
}

void CImageProcess20211422View::OnLButtonUp(UINT nFlags, CPoint point)
{
	mpos_end = point;

	CDC* pDC = GetDC();
	CPen rpen;
	rpen.CreatePen(PS_SOLID, 0, RGB(255, 0, 0));
	pDC->SelectObject(rpen);

	pDC->MoveTo(mpos_st);
	pDC->LineTo(mpos_end);

	ReleaseDC(pDC);

	int Ax, Ay, Bx, By;
	Ax = mpos_st.x;
	Ay = mpos_st.y;
	Bx = mpos_end.x;
	By = mpos_end.y;

	if (Ax < Bx) { mctrl_source.Px = Ax - (Bx - Ax) / 2; }
	else { mctrl_source.Px = Ax + (Ax - Bx) / 2; }

	if (Ay < By) { mctrl_source.Py = Ay - (By - Ay) / 2; }
	else { mctrl_source.Py = Ay + (Ay - By) / 2; }

	mctrl_dest.Px = mctrl_source.Px;
	mctrl_dest.Py = mctrl_source.Py;

	mctrl_source.Qx = mpos_st.x;
	mctrl_source.Qy = mpos_st.y;
	mctrl_dest.Qx = mpos_end.x;
	mctrl_dest.Qy = mpos_end.y;

	CScrollView::OnLButtonUp(nFlags, point);
}


void CImageProcess20211422View::OnAviView()
{
	CFileDialog dlg(true, ".", 0, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "AVI파일(*.avi)|*.avi|모든파일|*.*|");

	if (dlg.DoModal() == IDOK) {
		AVIFileName = dlg.GetPathName();
		bAviMode = true;
		Invalidate();
	}
}


void CImageProcess20211422View::LoadAviFile(CDC* pDC)
{
	PAVIFILE pavi;
	AVIFILEINFO fi;
	int stm;
	PAVISTREAM pstm = NULL;
	AVISTREAMINFO si;
	PGETFRAME pfrm = NULL;
	int frame;
	LPBITMAPINFOHEADER pbmpih;
	unsigned char* image;
	int x, y;

	AVIFileInit();
	AVIFileOpen(&pavi, AVIFileName, OF_READ | OF_SHARE_DENY_NONE, NULL);
	AVIFileInfo(pavi, &fi, sizeof(AVIFILEINFO));

	for (stm = 0; stm < fi.dwStreams; stm++) {
		AVIFileGetStream(pavi, &pstm, 0, stm);
		AVIStreamInfo(pstm, &si, sizeof(si));

		if (si.fccType == streamtypeVIDEO) {
			pfrm = AVIStreamGetFrameOpen(pstm, NULL);

			for (frame = 0; frame < si.dwLength; frame++) {
				pbmpih = (LPBITMAPINFOHEADER)AVIStreamGetFrame(pfrm, frame);
				if (!pbmpih) { continue; }
				image = (unsigned char*)((LPSTR)pbmpih + (WORD)pbmpih->biSize);

				/*
				for (y = 0; y < fi.dwHeight; y++) {
					for(x = 0; x < fi.dwWidth; x++) {
						pDC->SetPixel(x, fi.dwHeight - y - 1,
							RGB(
								image[(y * fi.dwWidth + x) * 3 + 2],
								image[(y * fi.dwWidth + x) * 3 + 1],
								image[(y * fi.dwWidth + x) * 3 + 0]));
					}
				}
				*/
				SetDIBitsToDevice(pDC->GetSafeHdc(),
					0, 0, fi.dwWidth, fi.dwHeight,
					0, 0, 0, fi.dwWidth,
					image, (BITMAPINFO*)pbmpih, DIB_RGB_COLORS);
				Sleep(30);

			}
		}
	}

	AVIStreamGetFrameClose(pfrm);
	AVIStreamRelease(pstm);
	AVIFileRelease(pavi);
	AVIFileExit();

}
