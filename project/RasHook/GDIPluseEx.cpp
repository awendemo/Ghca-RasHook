

#include "stdafx.h"
#include "GDIPluseEx.h"
#pragma warning(disable:4267) 



GDIPluseExt::GDIPluseExt()
{

}
GDIPluseExt::~GDIPluseExt()
{

}
BOOL GDIPluseExt::MakeRoundRectPath(GraphicsPath* pPath,CRect rect, int radius)
{

	pPath->StartFigure();

	REAL width = rect.Width()   - 1.5f;
	REAL height = rect.Height() - 1.0f;
	Rect r((INT)rect.left,(INT) rect.top, (INT)width, (INT)height);
	int dia = radius;

	if(dia > r.Width)      dia = r.Width;
	if(dia > r.Height)     dia = r.Height;



	// define a corner 
	Rect Corner(r.X, r.Y, dia, dia);

	// top left
	pPath->AddArc(Corner, 180, 90);                    

	if(dia == 20)
	{
		Corner.Width += 1; 
		Corner.Height += 1; 
		r.Width -=1; r.Height -= 1;
	}

	//top right
	Corner.X += (r.Width - dia - 1);
	pPath->AddArc(Corner, 270, 90);    

	// bottom right
	Corner.Y += (r.Height - dia - 1);
	pPath->AddArc(Corner,   0, 90);    

	// bottom left
	Corner.X -= (r.Width - dia - 1);
	pPath->AddArc(Corner, 90, 90);

	pPath->CloseFigure(); 
	return TRUE;
}
BOOL GDIPluseExt::ImageFromIDResource(UINT nID,LPCTSTR sTR,Image * &pImg)
{
	HINSTANCE hInst = AfxGetResourceHandle();
	HRSRC hRsrc = ::FindResource (hInst,MAKEINTRESOURCE(nID),sTR); 
	if (!hRsrc)
		return FALSE;

	//����Դ�����ڴ�
	DWORD len = SizeofResource(hInst, hRsrc);
	BYTE* lpRsrc = (BYTE*)LoadResource(hInst, hRsrc);
	if (!lpRsrc)
		return FALSE;

	//��
	HGLOBAL hMem = GlobalAlloc(GMEM_FIXED, len);
	BYTE* pmem = (BYTE*)GlobalLock(hMem);
	memcpy(pmem,lpRsrc,len);
	IStream* pstm;
	CreateStreamOnHGlobal(hMem,FALSE,&pstm);

	//����������
	pImg=Gdiplus::Image::FromStream(pstm);


	GlobalUnlock(hMem);
	GlobalFree(hMem);
	pstm->Release();
	FreeResource(lpRsrc);

	return TRUE;
}
BOOL GDIPluseExt::DrawRoundRect(Graphics&  gp,CRect rect,Color boardscolor,Color FillPathcolor,int radius)
{

	//�߿�·��
	GraphicsPath Path;
	MakeRoundRectPath(&Path,rect,radius);
	SolidBrush solidBrush(FillPathcolor);
	gp.SetSmoothingMode(SmoothingModeAntiAlias);
	gp.SetInterpolationMode(InterpolationModeHighQualityBicubic);
	gp.FillPath(&solidBrush, &Path);
	//���߿�
	for(int i=1; i < 4; ++i)
	{
		Pen pen(boardscolor, (REAL)i);
		pen.SetLineJoin(LineJoinRound);
		gp.DrawPath(&pen, &Path);
	}
	return TRUE;
}
BOOL GDIPluseExt::DrawRect(Graphics &gp,CRect rect,Color linecolor,REAL nbold)
{
	Pen solipen(linecolor,nbold);
	gp.DrawLine(&solipen,Point(rect.left,rect.top),Point(rect.left,rect.bottom));                    //��������
	gp.DrawLine(&solipen,Point(rect.left,rect.top),Point(rect.right ,rect.top));                       //ˮƽ�϶���
	gp.DrawLine(&solipen,Point(rect.right,rect.top),Point(rect.right ,rect.bottom));               //��������
	gp.DrawLine(&solipen,Point(rect.left,rect.bottom),Point(rect.right,rect.bottom));            //ˮƽ����
	return TRUE;
}
BOOL GDIPluseExt::DrawBoardsText(Graphics&  gp,PointF startpf,CString strText,CString strFont,INT nfontsize,Color textcolor,Color boardscolor)
{

	gp.SetSmoothingMode(SmoothingModeAntiAlias);
	gp.SetInterpolationMode(InterpolationModeHighQualityBicubic);

#ifdef _UNICODE

	StringFormat strformat;
	FontFamily  fontFamily(strFont);
	GraphicsPath path;
	path.AddString(strText,strText.GetLength(), &fontFamily, 
		FontStyleRegular, 
		(REAL)nfontsize,
		startpf, 
		&strformat );
	for(int i=1; i < 4; ++i)
	{
		Pen pen(boardscolor, (REAL)i);
		pen.SetLineJoin(LineJoinRound);
		gp.DrawPath(&pen, &path);
	}
	SolidBrush  textBrush(textcolor); 
	gp.FillPath(&textBrush, &path);
#else

	//�ַ�ת��
	int font_len = strFont.GetLength();
	WCHAR* pfont_w = new WCHAR[font_len];
	MultiByteToWideChar(CP_ACP,0,strFont.GetBuffer(),-1,pfont_w,font_len);
	strFont.ReleaseBuffer();
	//�ַ�ת��
	int text_len = strText.GetLength();
	WCHAR* ptext_w = new WCHAR[text_len];
	MultiByteToWideChar(CP_ACP,0,strText.GetBuffer(),-1,ptext_w,text_len);
	strText.ReleaseBuffer();


	FontFamily  fontFamily(pfont_w);

	Font font(&fontFamily, (REAL)nfontsize, FontStyleRegular, UnitPixel);

	GraphicsPath path;
	StringFormat strformat;

	path.AddString(ptext_w,wcsnlen_s(ptext_w,text_len), &fontFamily, 
		font.GetStyle(),
		font.GetSize(),
		startpf, 
		&strformat );

	for(int i=1; i < 4; ++i)
	{
		Pen pen(boardscolor,(REAL)i);
		pen.SetLineJoin(LineJoinRound);
		gp.DrawPath(&pen, &path);
	}

	SolidBrush  textBrush(textcolor); 
	gp.FillPath(&textBrush, &path);
	
	DEL_P(ptext_w);
	DEL_P(pfont_w);
#endif
	return TRUE;
}


// bmpתjpg
BOOL GDIPluseExt::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{

	UINT num= 0;
	UINT size= 0;

	ImageCodecInfo* pImageCodecInfo = NULL;

	GetImageEncodersSize(&num, &size);
	if(size== 0)
	{
		return FALSE;
	}
	pImageCodecInfo= (ImageCodecInfo*)(malloc(size));
	if(pImageCodecInfo== NULL)
	{
		return FALSE;
	}

	GetImageEncoders(num, size, pImageCodecInfo);

	for(UINT j=0; j< num; ++j)
	{
		if(wcscmp(pImageCodecInfo[j].MimeType, format)== 0)
		{
			*pClsid= pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;
		}
	} 
	free(pImageCodecInfo);
	return FALSE;
}

BOOL GDIPluseExt::SaveScreenToJpg(CRect rect)
{
	// �õ���ĻDC
	HWND hDeskWnd = ::GetDesktopWindow();                        //�����Ļ��HWND. 
	CDC *pDestDC = CDC::FromHandle(::GetDC(hDeskWnd));           //��ȡ��ǰ������ĻDC
	int Width = rect.Width();                                    //��
	int Height = rect.Height();                                  //��

	// ��������Ļ���ݵ�Bitmap 
	CBitmap memBitmap;   
	memBitmap.CreateCompatibleBitmap(pDestDC, Width, Height);

	// ������Ļ���ڴ�DC
	CDC memDC;     
	memDC.CreateCompatibleDC(pDestDC);

	// ������Bitmap��ʽѡ���ڴ�DC
	memDC.SelectObject(&memBitmap);

	// ����ĻDC����copy���ڴ�DC
	memDC.BitBlt(0, 0, Width, Height, pDestDC, 0, 0, SRCCOPY); 

	// ���λͼ��Ϣ
	BITMAP bmpInfo;
	memBitmap.GetBitmap(&bmpInfo);

	// ����BITMAPINFO
	BITMAPINFO m_BITMAPINFO;
	memset(&m_BITMAPINFO, 0, sizeof(BITMAPINFO));
	m_BITMAPINFO.bmiHeader.biSize     = sizeof(BITMAPINFOHEADER);
	m_BITMAPINFO.bmiHeader.biPlanes     = 1;
	m_BITMAPINFO.bmiHeader.biBitCount    = bmpInfo.bmBitsPixel;
	m_BITMAPINFO.bmiHeader.biCompression   = BI_RGB;
	m_BITMAPINFO.bmiHeader.biWidth     = bmpInfo.bmWidth;
	m_BITMAPINFO.bmiHeader.biHeight     = bmpInfo.bmHeight;

	// ��ȡλͼ����
	BYTE * pBuffer = new BYTE[bmpInfo.bmWidthBytes * bmpInfo.bmHeight];
	GetDIBits(memDC.m_hDC, (HBITMAP) memBitmap.m_hObject, 0, Height, pBuffer,
		(LPBITMAPINFO) &m_BITMAPINFO, DIB_RGB_COLORS);

	// ����λͼ
	Bitmap *pSrcBmp = Bitmap::FromBITMAPINFO(&m_BITMAPINFO, (void*)pBuffer);

	// �����jpg�ļ�
	CLSID encoderClsid;
	GetEncoderClsid(L"image/jpeg", &encoderClsid);
	pSrcBmp-> Save(L"destop.jpg", &encoderClsid);

	// �ͷ��ڴ�
	delete pSrcBmp;
	delete pBuffer;
	AfxGetMainWnd()->ReleaseDC(pDestDC);
	return TRUE;
}
SizeF GDIPluseExt::GetTextBounds(const Font& font,const StringFormat& strFormat,CString szText)
{
#ifndef _UNICODE
	//�ַ�ת��
	int str_len = szText.GetLength();
	WCHAR* pstr_w = new WCHAR[str_len];
	MultiByteToWideChar(CP_ACP,0,szText.GetBuffer(),-1,pstr_w,str_len);
	szText.ReleaseBuffer();
	
	GraphicsPath graphicsPathObj;
	FontFamily fontfamily;
	font.GetFamily(&fontfamily);
	graphicsPathObj.AddString(pstr_w,-1,&fontfamily,font.GetStyle(),font.GetSize(),PointF(0,0),&strFormat);
	DEL_P(pstr_w);
#else
	
	GraphicsPath graphicsPathObj;
	FontFamily fontfamily;
	font.GetFamily(&fontfamily);
	graphicsPathObj.AddString(szText,-1,&fontfamily,font.GetStyle(),font.GetSize(),PointF(0,0),&strFormat);


#endif
	
	
	RectF rcBound;
	// ��ȡ�߽緶Χ
	graphicsPathObj.GetBounds(&rcBound);
	// �����ı��Ŀ��
	return SizeF(rcBound.Width,rcBound.Height);
}
SizeF GDIPluseExt::GetBounds(CString strText,CString strFont,INT nfontsize)
{
	StringFormat strformat;
	GraphicsPath path;

#ifdef _UNICODE


	FontFamily  fontFamily(strFont);
	path.AddString(strText,strText.GetLength(), &fontFamily, 
		FontStyleRegular, 
		(REAL)nfontsize,
		PointF(0,0), 
		&strformat );

#else

	//�ַ�ת��
	int font_len = strFont.GetLength();
	WCHAR* pfont_w = new WCHAR[font_len];
	MultiByteToWideChar(CP_ACP,0,strFont.GetBuffer(),-1,pfont_w,font_len);
	strFont.ReleaseBuffer();
	//�ַ�ת��
	int text_len = strText.GetLength();
	WCHAR* ptext_w = new WCHAR[text_len];
	MultiByteToWideChar(CP_ACP,0,strText.GetBuffer(),-1,ptext_w,text_len);
	strText.ReleaseBuffer();


	FontFamily  fontFamily(pfont_w);

	Font font(&fontFamily, (REAL)nfontsize, FontStyleRegular, UnitPixel);


	path.AddString(ptext_w,wcsnlen_s(ptext_w,text_len), &fontFamily, 
		font.GetStyle(),
		font.GetSize(),
		PointF(0,0), 
		&strformat );


	DEL_P(ptext_w);
	DEL_P(pfont_w);
#endif

	RectF rcBound;
	// ��ȡ�߽緶Χ
	path.GetBounds(&rcBound);
	TRACE("Round_Size:%d\r\n",rcBound.Width);

	// �����ı��Ŀ��
	return SizeF(rcBound.Width,rcBound.Height);
}


