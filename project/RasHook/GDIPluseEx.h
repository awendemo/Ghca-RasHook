#pragma once
#ifndef  DEL_P
#define DEL_P(p) if (p != NULL)\
{\
	delete []p;\
	p =NULL;\
}
#endif


//GDI+ 外置功能扩展
class GDIPluseExt
{
public:
	GDIPluseExt();
	virtual ~GDIPluseExt();
public:
	static BOOL MakeRoundRectPath(GraphicsPath* pPath,CRect rect, int radius);
	static BOOL ImageFromIDResource(UINT nID,LPCTSTR sTR,Image * &pImg);
public:
	static BOOL DrawRoundRect(Graphics&  gp,CRect rect,Color boardscolor,Color FillPathcolor,int radius);
	static BOOL DrawBoardsText(Graphics&  gp,PointF startpf,CString strText,CString strFont,INT nfontsize,Color textcolor,Color boardscolor);
    static BOOL DrawRect(Graphics &gp,CRect rect,Color linecolor,REAL nbold);
public:
	static BOOL GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
	static BOOL SaveScreenToJpg(CRect rect);
public:
	static SizeF GetTextBounds(const Font& font,const StringFormat& strFormat,CString szText);
	static SizeF GetBounds(CString strText,CString strFont,INT nfontsize);	

};
