// OSG_MFC.h : OSG_MFC 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// COSG_MFCApp:
// 有关此类的实现，请参阅 OSG_MFC.cpp
//

class COSG_MFCApp : public CWinApp
{
public:
	COSG_MFCApp();


// 重写
public:
	virtual BOOL InitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern COSG_MFCApp theApp;