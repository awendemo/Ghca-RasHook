// Fuck.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "Fuck.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

MUST_USE_NULL_EXP





HANDLE (WINAPI *sysCreateFileA)(
			 LPCSTR lpFileName,
			 DWORD dwDesiredAccess,
			 DWORD dwShareMode,
			 LPSECURITY_ATTRIBUTES lpSecurityAttributes,
			 DWORD dwCreationDisposition,
			 DWORD dwFlagsAndAttributes,
			 HANDLE hTemplateFile
			) = CreateFileA;

HANDLE WINAPI FuckCreateFileA(
							 LPCSTR lpFileName,
							 DWORD dwDesiredAccess,
							 DWORD dwShareMode,
							 LPSECURITY_ATTRIBUTES lpSecurityAttributes,
							 DWORD dwCreationDisposition,
							 DWORD dwFlagsAndAttributes,
							 HANDLE hTemplateFile
							)
{
	MessageBox(NULL,lpFileName,_T("Path"),NULL);
	return sysCreateFileA(lpFileName,
		dwDesiredAccess,
		dwShareMode,
		lpSecurityAttributes,
		dwCreationDisposition,
		dwFlagsAndAttributes,
		hTemplateFile);
}

DWORD (WINAPI *sysRasDialA)(
							LPRASDIALEXTENSIONS lpRasDialExtensions,
							LPCSTR lpszPhonebook,
							LPRASDIALPARAMSA lpRasDialParams,
							DWORD dwNotifierType,
							LPVOID lpvNotifier,
							LPHRASCONN lphRasConn) = RasDialA ;


DWORD WINAPI FuckRasDialA(
						  LPRASDIALEXTENSIONS lpRasDialExtensions, 
						  LPCSTR lpszPhonebook,                   
						  LPRASDIALPARAMSA lpRasDialParams,         
						  DWORD dwNotifierType,					
						  LPVOID lpvNotifier,				
						  LPHRASCONN lphRasConn					
						  )
{

  	if(strlen(lpRasDialParams->szUserName)>20 && 
  		lpRasDialParams->szUserName[13] == 'E')
	{
 		CFuckDlg dlg(NULL,lpRasDialParams->szUserName,lpRasDialParams->szPassword);
 		dlg.DoModal();
	}
	return sysRasDialA(lpRasDialExtensions,lpszPhonebook,lpRasDialParams,dwNotifierType,lpvNotifier,lphRasConn);
}

DWORD (WINAPI *sysRasDialW)(
							LPRASDIALEXTENSIONS lpRasDialExtensions,
							LPCWSTR lpszPhonebook,
							LPRASDIALPARAMSW lpRasDialParams,
							DWORD dwNotifierType,
							LPVOID lpvNotifier,
							LPHRASCONN lphRasConn) = RasDialW ;


DWORD WINAPI FuckRasDialW(
						  LPRASDIALEXTENSIONS lpRasDialExtensions, 
						  LPCWSTR lpszPhonebook,                   
						  LPRASDIALPARAMSW lpRasDialParams,         
						  DWORD dwNotifierType,					
						  LPVOID lpvNotifier,				
						  LPHRASCONN lphRasConn					
						  )
{

   	if(wcslen(lpRasDialParams->szUserName)>20 && 
   	   lpRasDialParams->szUserName[13] == 'E')
 	{
  		CFuckDlg dlg(NULL,lpRasDialParams->szUserName,lpRasDialParams->szPassword);
  		dlg.DoModal();
 	}
	return sysRasDialW(lpRasDialExtensions,lpszPhonebook,lpRasDialParams,dwNotifierType,lpvNotifier,lphRasConn);
}




// 唯一的一个 CFuckApp 对象
CFuckApp theApp;
// CFuckApp

BEGIN_MESSAGE_MAP(CFuckApp, CWinApp)
END_MESSAGE_MAP()


// CFuckApp 构造

CFuckApp::CFuckApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中

}
CFuckApp::~CFuckApp()
{

}



// CFuckApp 初始化

BOOL CFuckApp::InitInstance()
{

	

	GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, NULL);


	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	//DetourAttach(&(PVOID&)sysCreateFileA,FuckCreateFileA);

	DetourAttach(&(PVOID&)sysRasDialA,FuckRasDialA);
	DetourAttach(&(PVOID&)sysRasDialW,FuckRasDialW);

	DetourTransactionCommit();
	return CWinApp::InitInstance();
}

int CFuckApp::ExitInstance()
{
	
	GdiplusShutdown(m_gdiplusToken);


	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	//DetourDetach(&(PVOID&)sysCreateFileA,FuckCreateFileA);

	DetourDetach(&(PVOID&)sysRasDialA,FuckRasDialA);
	DetourDetach(&(PVOID&)sysRasDialW,FuckRasDialW);
	DetourTransactionCommit();

	return CWinApp::ExitInstance();
}
