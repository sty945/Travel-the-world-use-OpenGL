// OpenGL.h: interface for the OpenGL class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPENGL_H__4ABB930E_0EDC_42DC_B2E1_11D6B417B2D2__INCLUDED_)
#define AFX_OPENGL_H__4ABB930E_0EDC_42DC_B2E1_11D6B417B2D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "bsipic.h"

class OpenGL  
{
public:
	OpenGL();
	virtual ~OpenGL();
	bsipic  *m_bsipic;	// 定义bsipic类变量
	HDC		hDC;		// GDI设备描述表
	HGLRC	hRC;		// 永久着色描述表
	BOOL	SetupPixelFormat(HDC hDC);
	void	init(int Width, int Height);
	void	Render();
	void	CleanUp();
	void    play();

};

#endif // !defined(AFX_OPENGL_H__4ABB930E_0EDC_42DC_B2E1_11D6B417B2D2__INCLUDED_)
