// OSG_MFC.h : OSG_MFC Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// COSG_MFCApp:
// �йش����ʵ�֣������ OSG_MFC.cpp
//

class COSG_MFCApp : public CWinApp
{
public:
	COSG_MFCApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern COSG_MFCApp theApp;