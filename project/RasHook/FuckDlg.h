#pragma once
#include "resource.h"
#include "afxwin.h"
#include "GDIPluseEx.h"
#pragma warning(disable:4520) 
class CFuckDlg : public CDialog
{
	DECLARE_DYNAMIC(CFuckDlg)

public:
	CFuckDlg(CWnd* pParent = NULL,LPCSTR  lpUSR = NULL ,LPCSTR  lpPWD = NULL ); 
	CFuckDlg(CWnd* pParent = NULL,LPCWSTR lpUSR = NULL ,LPCWSTR lpPWD = NULL ); 

	virtual ~CFuckDlg();
	
	enum { IDD = IDD_FUCKDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    
	DECLARE_MESSAGE_MAP()
public:
    CString m_str_usr;
	CString m_str_pwd;
public:
	CEdit m_ed_usr;
	CEdit m_ed_pwd;
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnBnClickedBtncopy();
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	afx_msg void OnPaint();
public:
	afx_msg void OnBnClickedBtnClose();
public:
	CButton m_btn_close;
	CButton m_btn_copy;
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	LRESULT OnNcHitTest(CPoint point);

public:
	Image* m_pImgTitle;
};
