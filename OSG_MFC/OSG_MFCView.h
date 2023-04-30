// OSG_MFCView.h : COSG_MFCView ��Ľӿ�
//

#include "MFC_OSG.h"

#pragma once

class COSG_MFCView : public CView
{
protected: // �������л�����
	COSG_MFCView();
	DECLARE_DYNCREATE(COSG_MFCView)

// ����
public:
	COSG_MFCDoc* GetDocument() const;

// ����
public:

	cOSG *mOSG;
	HANDLE mThreadHandle;

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
	virtual ~COSG_MFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // OSG_MFCView.cpp �еĵ��԰汾
inline COSG_MFCDoc* COSG_MFCView::GetDocument() const
   { return reinterpret_cast<COSG_MFCDoc*>(m_pDocument); }
#endif

