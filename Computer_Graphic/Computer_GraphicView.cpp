

// Computer_GraphicView.cpp : CComputer_GraphicView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Computer_Graphic.h"
#endif

#include "Computer_GraphicDoc.h"
#include "Computer_GraphicView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CComputer_GraphicView
extern CStatusBar m_wndStatusBar;
IMPLEMENT_DYNCREATE(CComputer_GraphicView, CView)

BEGIN_MESSAGE_MAP(CComputer_GraphicView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_DRAW_DDALINE, &CComputer_GraphicView::OnDrawDdaline)
	ON_COMMAND(ID_DRAW_MIDLINE, &CComputer_GraphicView::OnDrawMidline)
	ON_COMMAND(ID_DRAW_BCIRCLE, &CComputer_GraphicView::OnDrawBcircle)
	ON_COMMAND(ID_DRAW_MIDCIRCLE, &CComputer_GraphicView::OnDrawMidcircle)
	ON_COMMAND(ID_DRAW_PNCIRCLE, &CComputer_GraphicView::OnDrawPncircle)
	ON_COMMAND(ID_CURVE_BEZIER, &CComputer_GraphicView::OnCurveBezier)
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_TRANS_MOVE, &CComputer_GraphicView::OnTransMove)
END_MESSAGE_MAP()

// CComputer_GraphicView ����/����

CComputer_GraphicView::CComputer_GraphicView()
{
	// TODO: �ڴ˴���ӹ������
	Menu_ID = 0;
	Press_num = 0;
	saved_number = -1;
	control = false;
	tag = false;
}

CComputer_GraphicView::~CComputer_GraphicView()
{
}

BOOL CComputer_GraphicView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CComputer_GraphicView ����

void CComputer_GraphicView::OnDraw(CDC* /*pDC*/)
{
	CComputer_GraphicDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CComputer_GraphicView ��ӡ

BOOL CComputer_GraphicView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CComputer_GraphicView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CComputer_GraphicView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CComputer_GraphicView ���

#ifdef _DEBUG
void CComputer_GraphicView::AssertValid() const
{
	CView::AssertValid();
}

void CComputer_GraphicView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CComputer_GraphicDoc* CComputer_GraphicView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CComputer_GraphicDoc)));
	return (CComputer_GraphicDoc*)m_pDocument;
}
#endif //_DEBUG


// CComputer_GraphicView ��Ϣ�������

void CComputer_GraphicView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int xx, yy;
	char p1[20];
	CComputer_GraphicDoc *pDoc = GetDocument();
	xx = point.x;	yy = point.y;					//ȡ��������Ϣ
	sprintf(p1, "%4d", xx);						//ת��Ϊ�ַ���
	m_wndStatusBar.SetPaneText(2,LPCTSTR( p1), TRUE);	//�ڵ�2��������ʾx����
	sprintf(p1, "%4d", yy);						//ת��Ϊ�ַ���
	m_wndStatusBar.SetPaneText(3,LPCTSTR(p1), TRUE);	//�ڵ�3��������ʾy����
	if (Menu_ID >=1&&Menu_ID<=5) {
		CClientDC pDC(this);
		OnPrepareDC(&pDC);
		pDC.DPtoLP(&point);
		pDC.SetROP2(R2_NOT);
		if (mPointOld != point&&Press_num==1) {
			if (Menu_ID == 1) {
				pDoc->DDAline(&pDC, mPointOrign, mPointOld);//������
				pDoc->DDAline(&pDC, mPointOrign, point);//������
			}
			else if (Menu_ID == 2) {
				pDoc->MidLineCC(&pDC, mPointOrign, mPointOld);//������
				pDoc->MidLineCC(&pDC, mPointOrign, point);//������
			}
			else if (Menu_ID == 3) {
				pDoc->MidCircleCC(&pDC, mPointOrign, mPointOld);
				pDoc->MidCircleCC(&pDC, mPointOrign, point);
			}
			else if (Menu_ID == 4) {
				pDoc->BCircle(&pDC, mPointOrign, mPointOld);
				pDoc->BCircle(&pDC, mPointOrign, point);
			}
			else if (Menu_ID == 5) {
				pDoc->PNCircle(&pDC, mPointOrign, mPointOld);
				pDoc->PNCircle(&pDC, mPointOrign, point);
			}
			mPointOld = point;
		}
	}
	else if (Menu_ID == 6) {
		if (sample == true&&Press_num!=0) {
			CClientDC pDC(this);
			OnPrepareDC(&pDC);
			pDC.DPtoLP(&point);
			pDC.SetROP2(R2_NOT);
			if (mPointOld != point) {
				pDC.MoveTo(mPointOrign); pDC.LineTo(mPointOld);//������
			}
			pDC.MoveTo(mPointOrign);pDC.LineTo(point);//������
			mPointOld = point;
		}
	}
	else if (Menu_ID == 7&&saved_number!=-1) {
		CClientDC pDC(this);
		OnPrepareDC(&pDC);
		pDC.DPtoLP(&point);
		pDC.SetROP2(R2_NOT);
		if (mPointOld != point) {
			if (control == false) {
				pDC.MoveTo(pDoc->pointgroup[saved_number - 1]); pDC.LineTo(mPointOld);//������
				pDC.MoveTo(pDoc->pointgroup[saved_number + 1]); pDC.LineTo(mPointOld);
			}
			control = false;
		}
		pDC.MoveTo(pDoc->pointgroup[saved_number - 1]); pDC.LineTo(point);//������
		pDC.MoveTo(pDoc->pointgroup[saved_number + 1]); pDC.LineTo(point);//������
		mPointOld = point;
	}
	
	/*if (mPointOld != point) {
		pDC.MoveTo(mPointOrign); pDC.LineTo(mPointOld);//������
		pDC.MoveTo(mPointOrign);
		pDC.LineTo(point);//������
		mPointOld = point;
	}*/
	CView::OnMouseMove(nFlags, point);
}


void CComputer_GraphicView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CComputer_GraphicDoc *pDoc = GetDocument();
	CClientDC pDc(this);
    //DDA����
	if (Menu_ID>=1&&Menu_ID<=5){
		if (Press_num == 0) {
			pDoc->pointgroup[Press_num++] = point;
			SetCapture();
		}
		else{
			pDoc->pointgroup[Press_num] = point;
			Press_num =0;
			if (Menu_ID == 1)
				pDoc->DDAline(&pDc, pDoc->pointgroup[0], pDoc->pointgroup[1]);
			else if (Menu_ID == 2)
				pDoc->MidLineCC(&pDc, pDoc->pointgroup[0], pDoc->pointgroup[1]);
			else if (Menu_ID == 3)
				pDoc->MidCircleCC(&pDc, pDoc->pointgroup[0], pDoc->pointgroup[1]);
			else if (Menu_ID == 4)
				pDoc->BCircle(&pDc, pDoc->pointgroup[0], pDoc->pointgroup[1]);
			else if(Menu_ID==5)
				pDoc->PNCircle(&pDc, pDoc->pointgroup[0], pDoc->pointgroup[1]);
			ReleaseCapture();
		}
		mPointOrign = point; mPointOld = point;//��¼��һ��
	}
	else if (Menu_ID == 6) {
		if (sample == true) {
			pDoc->pointgroup[Press_num++] = point;
			CClientDC dc(this);
			dc.MoveTo(point.x - 5, point.y - 5);
			dc.LineTo(point.x + 5, point.y + 5);
			dc.MoveTo(point.x - 5, point.y + 5);
			dc.LineTo(point.x + 5, point.y - 5);
		}
		mPointOrign = point; mPointOld = point;//��¼��һ��

	}
	if (Menu_ID == 7 && control == true) {
		CClientDC pDC(this);
		OnPrepareDC(&pDC);
		pDC.DPtoLP(&point);
		pDC.SetROP2(R2_NOT);
		if (tag == true) {
			pDoc->Bezier(&pDC, pDoc->pointgroup, Press_num);//�����ɵ�����
			tag = false;
		}
		for (int i = 0; i < Press_num; i++) {
			if (point.x<=pDoc->pointgroup[i].x + 5 && point.x>=pDoc->pointgroup[i].x - 5 && point.y<=pDoc->pointgroup[i].y + 5 && point.y>=pDoc->pointgroup[i].y - 5)
				saved_number = i;
		}
		if (saved_number != -1) {
			Press_num++;
			for (int i = Press_num - 1; i >= saved_number; i--)
				pDoc->pointgroup[i + 1] = pDoc->pointgroup[i];
			
			if (control == true) {
				pDC.MoveTo(pDoc->pointgroup[saved_number + 1]);
				pDC.LineTo(pDoc->pointgroup[saved_number - 1]);
			}
			mPointOld = point;
			/*pDC.MoveTo(pDoc->pointgroup[saved_number + 1]);
			pDc.LineTo(point);
			pDC.MoveTo(pDoc->pointgroup[saved_number - 1]);
			pDc.LineTo(point);*/
		}
	}
	else if (Menu_ID == 8) {
		if (Press_num == 0) {
			pDoc->pointgroup[0] = point;
			Press_num++;
		}
		else {

		}
	}
	CView::OnLButtonDown(nFlags, point);
}


void CComputer_GraphicView::OnDrawDdaline()
{
	Menu_ID = 1, Press_num = 0;
}


void CComputer_GraphicView::OnDrawMidline()
{
	Menu_ID = 2, Press_num = 0;
}

void CComputer_GraphicView::OnDrawMidcircle()
{
	Menu_ID = 3, Press_num = 0;
}

void CComputer_GraphicView::OnDrawBcircle()
{
	Menu_ID = 4, Press_num = 0;
}

void CComputer_GraphicView::OnDrawPncircle()
{
	Menu_ID = 5, Press_num = 0;

}


void CComputer_GraphicView::OnCurveBezier()
{
	Menu_ID = 6, Press_num = 0;
	sample = true;
}


void CComputer_GraphicView::OnRButtonDown(UINT nFlags, CPoint point)
{
	CComputer_GraphicDoc *pDoc = GetDocument();
	CClientDC pDc(this);
	if (Menu_ID == 6) {
		sample = false;
		CClientDC pDC(this);
		OnPrepareDC(&pDC);
		pDC.DPtoLP(&point);
		pDC.SetROP2(R2_NOT);
		pDC.MoveTo(mPointOrign); pDC.LineTo(mPointOld);//������
		control = true;
		pDoc->Bezier(&pDc, pDoc->pointgroup, Press_num);
		//��bezier����
		Menu_ID = 7;
		tag = true;
	}
	else if (Menu_ID == 7 && saved_number != -1) {
		
		control = true;
		pDoc->pointgroup[saved_number] = point;
		pDc.MoveTo(point.x + 5, point.y + 5);
		pDc.LineTo(point.x - 5, point.y - 5);
		pDc.MoveTo(point.x - 5, point.y + 5);
		pDc.LineTo(point.x + 5, point.y - 5);
		saved_number = -1;
	}
	CView::OnRButtonDown(nFlags, point);
}


void CComputer_GraphicView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (Menu_ID == 7) {
		CComputer_GraphicDoc *pDoc = GetDocument();
		CClientDC pDC(this);
		CPen newpen(PS_SOLID, 1, RGB(255, 0, 0)),*oldpen;
		oldpen = pDC.SelectObject(&newpen);
		pDoc->Bezier(&pDC, pDoc->pointgroup, Press_num);
		pDC.SelectObject(oldpen);
	}
	CView::OnLButtonDblClk(nFlags, point);
}


void CComputer_GraphicView::OnTransMove()
{
	// TODO: �ڴ���������������
	CComputer_GraphicDoc *pDoc = GetDocument();
	CClientDC dc(this);
	pDoc->Generate_Graph(&dc);
	Menu_ID = 8;
	Press_num = 0;
}
