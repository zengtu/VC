// OSG_MFCDoc.cpp : COSG_MFCDoc 类的实现
//

#include "stdafx.h"
#include "OSG_MFC.h"

#include "OSG_MFCDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COSG_MFCDoc

IMPLEMENT_DYNCREATE(COSG_MFCDoc, CDocument)

BEGIN_MESSAGE_MAP(COSG_MFCDoc, CDocument)
END_MESSAGE_MAP()


// COSG_MFCDoc 构造/析构

COSG_MFCDoc::COSG_MFCDoc()
{
	// TODO: 在此添加一次性构造代码

}

COSG_MFCDoc::~COSG_MFCDoc()
{
}

BOOL COSG_MFCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// COSG_MFCDoc 序列化

void COSG_MFCDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// COSG_MFCDoc 诊断

#ifdef _DEBUG
void COSG_MFCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COSG_MFCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// COSG_MFCDoc 命令
