

// Computer_GraphicView.cpp : CComputer_GraphicView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
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

// CComputer_GraphicView 构造/析构

CComputer_GraphicView::CComputer_GraphicView()
{
	// TODO: 在此处添加构造代码
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
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CComputer_GraphicView 绘制

void CComputer_GraphicView::OnDraw(CDC* /*pDC*/)
{
	CComputer_GraphicDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CComputer_GraphicView 打印

BOOL CComputer_GraphicView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CComputer_GraphicView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CComputer_GraphicView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CComputer_GraphicView 诊断

#ifdef _DEBUG
void CComputer_GraphicView::AssertValid() const
{
	CView::AssertValid();
}

void CComputer_GraphicView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CComputer_GraphicDoc* CComputer_GraphicView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CComputer_GraphicDoc)));
	return (CComputer_GraphicDoc*)m_pDocument;
}
#endif //_DEBUG


// CComputer_GraphicView 消息处理程序

void CComputer_GraphicView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int xx, yy;
	char p1[20];
	CComputer_GraphicDoc *pDoc = GetDocument();
	xx = point.x;	yy = point.y;					//取出坐标信息
	sprintf(p1, "%4d", xx);						//转化为字符串
	m_wndStatusBar.SetPaneText(2,LPCTSTR( p1), TRUE);	//在第2个区域显示x坐标
	sprintf(p1, "%4d", yy);						//转化为字符串
	m_wndStatusBar.SetPaneText(3,LPCTSTR(p1), TRUE);	//在第3个区域显示y坐标
	if (Menu_ID >=1&&Menu_ID<=5) {
		CClientDC pDC(this);
		OnPrepareDC(&pDC);
		pDC.DPtoLP(&point);
		pDC.SetROP2(R2_NOT);
		if (mPointOld != point&&Press_num==1) {
			if (Menu_ID == 1) {
				pDoc->DDAline(&pDC, mPointOrign, mPointOld);//擦旧线
				pDoc->DDAline(&pDC, mPointOrign, point);//画新线
			}
			else if (Menu_ID == 2) {
				pDoc->MidLineCC(&pDC, mPointOrign, mPointOld);//擦旧线
				pDoc->MidLineCC(&pDC, mPointOrign, point);//画新线
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
				pDC.MoveTo(mPointOrign); pDC.LineTo(mPointOld);//擦旧线
			}
			pDC.MoveTo(mPointOrign);pDC.LineTo(point);//画新线
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
				pDC.MoveTo(pDoc->pointgroup[saved_number - 1]); pDC.LineTo(mPointOld);//擦旧线
				pDC.MoveTo(pDoc->pointgroup[saved_number + 1]); pDC.LineTo(mPointOld);
			}
			control = false;
		}
		pDC.MoveTo(pDoc->pointgroup[saved_number - 1]); pDC.LineTo(point);//画新线
		pDC.MoveTo(pDoc->pointgroup[saved_number + 1]); pDC.LineTo(point);//画新线
		mPointOld = point;
	}
	
	/*if (mPointOld != point) {
		pDC.MoveTo(mPointOrign); pDC.LineTo(mPointOld);//擦旧线
		pDC.MoveTo(mPointOrign);
		pDC.LineTo(point);//画新线
		mPointOld = point;
	}*/
	CView::OnMouseMove(nFlags, point);
}


void CComputer_GraphicView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CComputer_GraphicDoc *pDoc = GetDocument();
	CClientDC pDc(this);
    //DDA画线
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
		mPointOrign = point; mPointOld = point;//记录第一点
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
		mPointOrign = point; mPointOld = point;//记录第一点

	}
	if (Menu_ID == 7 && control == true) {
		CClientDC pDC(this);
		OnPrepareDC(&pDC);
		pDC.DPtoLP(&point);
		pDC.SetROP2(R2_NOT);
		if (tag == true) {
			pDoc->Bezier(&pDC, pDoc->pointgroup, Press_num);//消除旧的曲线
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
		pDC.MoveTo(mPointOrign); pDC.LineTo(mPointOld);//擦旧线
		control = true;
		pDoc->Bezier(&pDc, pDoc->pointgroup, Press_num);
		//画bezier曲线
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
	// TODO: 在此添加命令处理程序代码
	CComputer_GraphicDoc *pDoc = GetDocument();
	CClientDC dc(this);
	pDoc->Generate_Graph(&dc);
	Menu_ID = 8;
	Press_num = 0;
}
