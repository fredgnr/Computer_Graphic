
// Computer_GraphicDoc.h : CComputer_GraphicDoc 类的接口
//


#pragma once

class CComputer_GraphicDoc : public CDocument
{
protected: // 仅从序列化创建
	CComputer_GraphicDoc();
	DECLARE_DYNCREATE(CComputer_GraphicDoc)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CComputer_GraphicDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

public:
	
	CPoint pointgroup[1000];
	void MidCircleCC(CClientDC *pDc, CPoint center, CPoint point_r);
	void DDAline(CClientDC * pDc, CPoint startp, CPoint endp);
	void MidLineCC(CClientDC *pDc, CPoint startp, CPoint endp);
	void BCircle(CClientDC *pDc, CPoint startp, CPoint endp);
	void PNCircle(CClientDC *pDc, CPoint startp, CPoint endp);
	void Bezier(CClientDC *pDc, CPoint *pointgroup, int Point_num);
	CPoint group[100];
	int group_num;
	void Generate_Graph(CClientDC *pDc);
	void Draw_Graph(CClientDC *pDc);
};
