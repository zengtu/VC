// OSG_MFCDoc.h : COSG_MFCDoc ��Ľӿ�
//


#pragma once


class COSG_MFCDoc : public CDocument
{
protected: // �������л�����
	COSG_MFCDoc();
	DECLARE_DYNCREATE(COSG_MFCDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~COSG_MFCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


