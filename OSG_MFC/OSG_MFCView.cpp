// OSG_MFCView.cpp : COSG_MFCView ���ʵ��
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// COSG_MFCView ����/����

COSG_MFCView::COSG_MFCView()
{
	// TODO: �ڴ˴���ӹ������

}

COSG_MFCView::~COSG_MFCView()
{
}

BOOL COSG_MFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// COSG_MFCView ����

void COSG_MFCView::OnDraw(CDC* /*pDC*/)
{
	COSG_MFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// COSG_MFCView ��ӡ

BOOL COSG_MFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void COSG_MFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void COSG_MFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// COSG_MFCView ���

#ifdef _DEBUG
void COSG_MFCView::AssertValid() const
{
	CView::AssertValid();
}

void COSG_MFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COSG_MFCDoc* COSG_MFCView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COSG_MFCDoc)));
	return (COSG_MFCDoc*)m_pDocument;
}
#endif //_DEBUG


// COSG_MFCView ��Ϣ�������

int COSG_MFCView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	mOSG = new cOSG(m_hWnd);
	return 0;
}

void COSG_MFCView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û��� 
	mOSG ->InitOSG("Modle/JoeDirt/JoeDirt.flt");
	mThreadHandle = (HANDLE)_beginthread(&cOSG::Render,0,mOSG);
} 
