// OSG_MFCView.cpp : COSG_MFCView 类的实现
//

#include "stdafx.h"
#include "OSG_MFC.h"

#include "OSG_MFCDoc.h"
#include "OSG_MFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COSG_MFCView

IMPLEMENT_DYNCREATE(COSG_MFCView, CView)

BEGIN_MESSAGE_MAP(COSG_MFCView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// COSG_MFCView 构造/析构

COSG_MFCView::COSG_MFCView()
{
	// TODO: 在此处添加构造代码

}

COSG_MFCView::~COSG_MFCView()
{
}

BOOL COSG_MFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// COSG_MFCView 绘制

void COSG_MFCView::OnDraw(CDC* /*pDC*/)
{
	COSG_MFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// COSG_MFCView 打印

BOOL COSG_MFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void COSG_MFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void COSG_MFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// COSG_MFCView 诊断

#ifdef _DEBUG
void COSG_MFCView::AssertValid() const
{
	CView::AssertValid();
}

void COSG_MFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COSG_MFCDoc* COSG_MFCView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COSG_MFCDoc)));
	return (COSG_MFCDoc*)m_pDocument;
}
#endif //_DEBUG


// COSG_MFCView 消息处理程序

int COSG_MFCView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	mOSG = new cOSG(m_hWnd);
	return 0;
}

void COSG_MFCView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类 
	mOSG ->InitOSG("Modle/JoeDirt/JoeDirt.flt");
	mThreadHandle = (HANDLE)_beginthread(&cOSG::Render,0,mOSG);
} 
