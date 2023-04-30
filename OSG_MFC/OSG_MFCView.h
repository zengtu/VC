// OSG_MFCView.h : COSG_MFCView 类的接口
//

#include "MFC_OSG.h"

#pragma once

class COSG_MFCView : public CView
{
protected: // 仅从序列化创建
	COSG_MFCView();
	DECLARE_DYNCREATE(COSG_MFCView)

// 属性
public:
	COSG_MFCDoc* GetDocument() const;

// 操作
public:

	cOSG *mOSG;
	HANDLE mThreadHandle;

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
	virtual ~COSG_MFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // OSG_MFCView.cpp 中的调试版本
inline COSG_MFCDoc* COSG_MFCView::GetDocument() const
   { return reinterpret_cast<COSG_MFCDoc*>(m_pDocument); }
#endif

