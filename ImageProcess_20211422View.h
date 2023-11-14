
// ImageProcess_20211422View.h: CImageProcess20211422View 클래스의 인터페이스
//

#pragma once


class CImageProcess20211422View : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CImageProcess20211422View() noexcept;
	DECLARE_DYNCREATE(CImageProcess20211422View)

// 특성입니다.
public:
	CImageProcess20211422Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CImageProcess20211422View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPixelAdd();
	afx_msg void OnPixelSub();
	afx_msg void OnPixelDiv();
	afx_msg void OnPixelMul();
	afx_msg void OnPixelHistoEq();
	afx_msg void OnPixelLsContrast();
	afx_msg void OnPixelBinarization();
	afx_msg void OnPixelTwoImageAdd();
	afx_msg void OnPixelTwoImageSub();
	void LoadTwoImage();
	afx_msg void OnRegionSharpening();
	void convolve(unsigned char** inImg, unsigned char** outImg, int cols, int rows, float mask[3][3] , int bias, int depth);
	afx_msg void OnRegionSmoothing();
	afx_msg void OnRegionEmbossing();
	afx_msg void OnRegionPrewitt();
	afx_msg void OnRegionRoberts();
	afx_msg void OnRegionSobel();
	afx_msg void OnRegionAverageFiltering();
	afx_msg void OnRegionMedianFiltering();
	afx_msg void OnMorphologyColorToGray();
	afx_msg void OnMorphologyBinarization();
	afx_msg void OnMorphologyErosion();
	afx_msg void OnMorphologyDilation();
	afx_msg void OnMorphologyOpening();
	void CopyResultToInput();
	afx_msg void OnMorphologyClosing();
	afx_msg void OnGeometryZoomin();
	afx_msg void OnGeometryBilinearInterpolation();
	afx_msg void OnGeometryZoomoutSubsampling();
	afx_msg void OnGeometryZoomoutAverage();
	afx_msg void OnGeometryZoomoutMedian();
	afx_msg void OnGeometryRotate();
};

#ifndef _DEBUG  // ImageProcess_20211422View.cpp의 디버그 버전
inline CImageProcess20211422Doc* CImageProcess20211422View::GetDocument() const
   { return reinterpret_cast<CImageProcess20211422Doc*>(m_pDocument); }
#endif

