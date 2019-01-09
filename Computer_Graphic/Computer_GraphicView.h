
// Computer_GraphicView.h : CComputer_GraphicView 类的接口
//

#pragma once


class CComputer_GraphicView : public CView
{
protected: // 仅从序列化创建
	CComputer_GraphicView();
	DECLARE_DYNCREATE(CComputer_GraphicView)

// 特性
public:
	CComputer_GraphicDoc* GetDocument() const;

// 操作
public:
	CPoint mPointOrign, mPointOld;
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CComputer_GraphicView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
	//Menu_ID为正在执行的算法的命令ID
	//1--DDA算法   2--中点画线法  3-Bresenham画圆算法
	int Menu_ID;
	int Press_num;
	int saved_number;
	//为真时表示正在采样取点
	bool sample;
	//正在选择新的控制点
	bool control,tag;
	afx_msg void OnDrawDdaline();
	afx_msg void OnDrawMidline();
	afx_msg void OnDrawBcircle();
	afx_msg void OnDrawMidcircle();
	afx_msg void OnDrawPncircle();
	afx_msg void OnCurveBezier();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnTransMove();
};

#ifndef _DEBUG  // Computer_GraphicView.cpp 中的调试版本
inline CComputer_GraphicDoc* CComputer_GraphicView::GetDocument() const
   { return reinterpret_cast<CComputer_GraphicDoc*>(m_pDocument); }
#endif

