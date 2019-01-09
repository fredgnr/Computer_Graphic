
// Computer_GraphicView.h : CComputer_GraphicView ��Ľӿ�
//

#pragma once


class CComputer_GraphicView : public CView
{
protected: // �������л�����
	CComputer_GraphicView();
	DECLARE_DYNCREATE(CComputer_GraphicView)

// ����
public:
	CComputer_GraphicDoc* GetDocument() const;

// ����
public:
	CPoint mPointOrign, mPointOld;
// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CComputer_GraphicView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
	//Menu_IDΪ����ִ�е��㷨������ID
	//1--DDA�㷨   2--�е㻭�߷�  3-Bresenham��Բ�㷨
	int Menu_ID;
	int Press_num;
	int saved_number;
	//Ϊ��ʱ��ʾ���ڲ���ȡ��
	bool sample;
	//����ѡ���µĿ��Ƶ�
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

#ifndef _DEBUG  // Computer_GraphicView.cpp �еĵ��԰汾
inline CComputer_GraphicDoc* CComputer_GraphicView::GetDocument() const
   { return reinterpret_cast<CComputer_GraphicDoc*>(m_pDocument); }
#endif
