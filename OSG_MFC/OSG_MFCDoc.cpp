// OSG_MFCDoc.cpp : COSG_MFCDoc ���ʵ��
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


// COSG_MFCDoc ����/����

COSG_MFCDoc::COSG_MFCDoc()
{
	// TODO: �ڴ����һ���Թ������

}

COSG_MFCDoc::~COSG_MFCDoc()
{
}

BOOL COSG_MFCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// COSG_MFCDoc ���л�

void COSG_MFCDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// COSG_MFCDoc ���

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


// COSG_MFCDoc ����
