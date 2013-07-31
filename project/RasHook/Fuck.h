// Fuck.h : Fuck DLL 的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "FuckDlg.h"

// CFuckApp
// 有关此类实现的信息，请参阅 Fuck.cpp
//

class CFuckApp : public CWinApp
{
public:
	CFuckApp();
	~CFuckApp();
// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
public:
	virtual int ExitInstance();


	GdiplusStartupInput m_gdiplusStartupInput;
	ULONG_PTR m_gdiplusToken;


};
