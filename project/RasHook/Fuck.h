// Fuck.h : Fuck DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "FuckDlg.h"

// CFuckApp
// �йش���ʵ�ֵ���Ϣ������� Fuck.cpp
//

class CFuckApp : public CWinApp
{
public:
	CFuckApp();
	~CFuckApp();
// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
public:
	virtual int ExitInstance();


	GdiplusStartupInput m_gdiplusStartupInput;
	ULONG_PTR m_gdiplusToken;


};
