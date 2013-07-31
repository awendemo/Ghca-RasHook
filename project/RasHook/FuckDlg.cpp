#include "stdafx.h"
#include "Fuck.h"
#include "FuckDlg.h"



IMPLEMENT_DYNAMIC(CFuckDlg, CDialog)

CFuckDlg::CFuckDlg(CWnd* pParent,LPCSTR  lpUSR,LPCSTR  lpPWD)
	: CDialog(CFuckDlg::IDD, pParent)
{
	m_str_usr = lpUSR;
	m_str_pwd = lpPWD;
	m_pImgTitle = NULL;
}
CFuckDlg::CFuckDlg(CWnd* pParent,LPCWSTR  lpUSR,LPCWSTR  lpPWD)
	: CDialog(CFuckDlg::IDD, pParent)
{
	m_str_usr = lpUSR;
	m_str_pwd = lpPWD;
	m_pImgTitle = NULL;
}

CFuckDlg::~CFuckDlg()
{
	DEL_P(m_pImgTitle);
}

void CFuckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDUSR, m_ed_usr);
	DDX_Control(pDX, IDC_EDPWD, m_ed_pwd);
	DDX_Control(pDX, IDC_BTN_CLOSE, m_btn_close);
	DDX_Control(pDX, IDC_BTNCOPY, m_btn_copy);
}


BEGIN_MESSAGE_MAP(CFuckDlg, CDialog)
	ON_BN_CLICKED(IDC_BTNCOPY, &CFuckDlg::OnBnClickedBtncopy)
	ON_WM_ERASEBKGND()
	ON_WM_NCHITTEST()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CFuckDlg::OnBnClickedBtnClose)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()



BOOL CFuckDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_ed_usr.SetWindowText(m_str_usr);
	m_ed_pwd.SetWindowText(m_str_pwd);


	

	GDIPluseExt::ImageFromIDResource(IDR_PNG_TITLE,_T("PNG"),m_pImgTitle);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void CFuckDlg::OnBnClickedBtncopy()
{

	CString strUSR;
	m_ed_usr.GetWindowText(strUSR);
	if(OpenClipboard())
	{
		HANDLE hclip;
		char *buffer;
		EmptyClipboard();
		hclip = GlobalAlloc(GMEM_MOVEABLE,strUSR.GetLength()+1);
		buffer = (char*)GlobalLock(hclip);
		strcpy_s(buffer,strUSR.GetLength()+1,strUSR.GetBuffer());
		strUSR.ReleaseBuffer();
		GlobalUnlock(hclip);
		SetClipboardData(CF_TEXT,hclip);
		CloseClipboard();
		return;
	}
	return;
}

void CFuckDlg::OnBnClickedBtnClose()
{
	EndDialog(1);
}
BOOL CFuckDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return TRUE;//CDialog::OnEraseBkgnd(pDC);
}
LRESULT CFuckDlg::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//return CDialog::OnNcHitTest(point);
	LRESULT nHitTest = CDialog :: OnNcHitTest (point);
	return (nHitTest == HTCLIENT)? HTCAPTION: nHitTest;
}
void CFuckDlg::OnPaint()
{

	CPaintDC dc(this);
	Graphics gp(dc.m_hDC);
	CRect ClientRect;
	GetClientRect(&ClientRect);

	Bitmap CacheImage(ClientRect.Width(),ClientRect.Height());
	Graphics gpbuf(&CacheImage);
	gpbuf.Clear(Color::Black);
	gpbuf.SetSmoothingMode(SmoothingModeAntiAlias);
	gpbuf.SetInterpolationMode(InterpolationModeHighQualityBicubic);

	if (m_pImgTitle != NULL)
		gpbuf.DrawImage(m_pImgTitle,0,15,m_pImgTitle->GetWidth(),m_pImgTitle->GetHeight());

	ClientRect -= ClientRect.TopLeft();
	GDIPluseExt gdipluseExt;

	//程序边框
	gdipluseExt.DrawRoundRect(gpbuf,CRect(ClientRect.left , ClientRect.top , ClientRect.right+2, ClientRect.bottom+1),Color(48,0,0,0),Color(0,192,192,192),1);
	gdipluseExt.DrawRect(gpbuf,CRect(ClientRect.left+1, ClientRect.top+1, ClientRect.right-2, ClientRect.bottom-2),Color(255,192,192,192),1);

	gp.DrawImage(&CacheImage,0,0);


}

HBRUSH CFuckDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性

 	switch(pWnd->GetDlgCtrlID())
 	{
 	case IDC_STATIC:
 		pDC->SetBkMode(TRANSPARENT);  
 		pDC->SetTextColor(RGB(255,255,255));
 		return   (HBRUSH)::GetStockObject(NULL_BRUSH); 
 		break;
	case IDC_BTNCOPY:case IDC_BTN_CLOSE:
 		pDC->SetBkMode(TRANSPARENT);  
 		return (HBRUSH)::GetStockObject(BLACK_BRUSH); 
 		break;
 	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
