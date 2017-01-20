// OpenGL.cpp: implementation of the OpenGL class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OpenGL.h"
#include "bsipic.h"

float r;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

OpenGL::OpenGL()
{
	
}

OpenGL::~OpenGL()
{
	
}

BOOL OpenGL::SetupPixelFormat(HDC hDC0)
{
	int nPixelFormat;					  // 象素点格式
	hDC=hDC0;
	PIXELFORMATDESCRIPTOR pfd = 
	{ 
		sizeof(PIXELFORMATDESCRIPTOR),    // pfd结构的大小 
			1,                                // 版本号 
			PFD_DRAW_TO_WINDOW |              // 支持在窗口中绘图 
			PFD_SUPPORT_OPENGL |              // 支持 OpenGL 
			PFD_DOUBLEBUFFER,                 // 双缓存模式 
			PFD_TYPE_RGBA,                    // RGBA 颜色模式 
			16,                               // 24 位颜色深度 
			0, 0, 0, 0, 0, 0,                 // 忽略颜色位 
			0,                                // 没有非透明度缓存 
			0,                                // 忽略移位位 
			0,                                // 无累加缓存 
			0, 0, 0, 0,                       // 忽略累加位 
			16,                               // 32 位深度缓存     
			0,                                // 无模板缓存 
			0,                                // 无辅助缓存 
			PFD_MAIN_PLANE,                   // 主层 
			0,                                // 保留 
			0, 0, 0                           // 忽略层,可见性和损毁掩模 
	}; 
	if (!(nPixelFormat = ChoosePixelFormat(hDC, &pfd)))
	{ 
		MessageBox(NULL,"没找到合适的显示模式","Error",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}
	SetPixelFormat(hDC,nPixelFormat,&pfd);//设置当前设备的像素点格式
	hRC = wglCreateContext(hDC);          //获取渲染描述句柄
	wglMakeCurrent(hDC, hRC);             //激活渲染描述句柄
	m_bsipic = new bsipic();
	m_bsipic->light0();
	return TRUE;
}

void OpenGL::init(int Width, int Height)
{	
	glViewport(0,0,Width,Height);			// 设置OpenGL视口大小。	
	glMatrixMode(GL_PROJECTION);			// 设置当前矩阵为投影矩阵。
	glLoadIdentity();						// 重置当前指定的矩阵为单位矩阵
	gluPerspective							// 设置透视图
		( 55.0f,							// 透视角设置为 45 度
		(GLfloat)Width/(GLfloat)Height,	// 窗口的宽与高比
		1.0f,								// 视野透视深度:近点1.0f
		3000.0f							// 视野透视深度:始点0.1f远点1000.0f
		);
	// 这和照象机很类似，第一个参数设置镜头广角度，第二个参数是长宽比，后面是远近剪切。
	glMatrixMode(GL_MODELVIEW);				// 设置当前矩阵为模型视图矩阵
	glLoadIdentity();						// 重置当前指定的矩阵为单位矩阵
	//====================================================
}
void OpenGL::Render()//OpenGL图形处理
{	
	if(m_bsipic==NULL) return;
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);			 // 设置刷新背景色
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);// 刷新背景
	glLoadIdentity();								 // 重置当前的模型观察矩阵
    m_bsipic->DisplayScene();
	m_bsipic->DrawGround();
	m_bsipic->CreateSkyBox(3,6,3,6);				 // 显示天
	//play();
	srand(100);//产生树的固定随机数种子
	for(int i=0;i<300;i++)						//树的数量			
	{
		float x= RAND_COORD((MAP_W-1)*MAP_SCALE);	//位置x
		float z= RAND_COORD((MAP_W-1)*MAP_SCALE);	//位置z
		float size=4.0f+rand()%4;					//大小2-4随机
		float h=-size/10;							//深浅
		int   cactus=rand()%4+11;					//树形随机4种  
		//m_bsipic->ShowTree(x,z,size,h,cactus);	//显示平面树
		m_bsipic->ShowTree(x,z,size,h,cactus);	//显示树

	}
	glFlush();										 // 更新窗口
	SwapBuffers(hDC);								 // 切换缓冲区
	//r+=1;if(r>360) r=0;
}
void OpenGL::CleanUp()//清除OpenGL
{	 
	wglMakeCurrent(hDC, NULL);                       //清除OpenGL
	wglDeleteContext(hRC);                           //清除OpenGL
}

/*
void OpenGL::play()
{
	glPushMatrix(); 
	glPointSize(4);										//点的大小
	glTranslatef (-5, 4,-13);glRotatef(r,1.0,1.0,1.0);	//整体旋转
	glColor3f(1.0f, 0.0f, 0.0f);
	m_bsipic.Point();		//画点
	glPopMatrix();
	
	glPushMatrix(); 
	glTranslatef ( 0, 4,-13);glRotatef(r,1.0,1.0,1.0); //整体旋转
	glColor3f(0.0f, 1.0f, 0.0f);m_bsipic.Line();		//画线
	glPopMatrix();
	glPushMatrix();
	glTranslatef ( 5, 4,-13);glRotatef(r,1.0,1.0,1.0); //整体旋转
	glColor3f(0.0f, 0.0f, 1.0f);m_bsipic.Triangle();	//画面
	glPopMatrix();
	glPushMatrix();
	glTranslatef (-5, 0,-13);glRotatef(r,1.0,1.0,1.0); //整体旋转
	glColor3f(1.0f, 1.0f, 0.0f);m_bsipic.Square();		//画正方面
	glPopMatrix();
	glPushMatrix();
	glTranslatef ( 0, 0,-13);glRotatef(r,1.0,1.0,1.0); //整体旋转
	glColor3f(0.0f, 1.0f, 1.0f);m_bsipic.Esquare();		//画正方体
	glPopMatrix();
	glPushMatrix(); 
	glTranslatef ( 5, 0,-13);glRotatef(r,1.0,1.0,1.0); //整体旋转
	glColor3f(1.0f, 0.0f, 1.0f);m_bsipic.Park();		//画园
	glPopMatrix();
	glPushMatrix(); 
	glTranslatef (-5,-4,-13);glRotatef(r,1.0,1.0,1.0); //整体旋转
	glColor3f(1.0f, 1.0f, 1.0f);m_bsipic.Pillar();		//园柱
	glPopMatrix();
	glPushMatrix(); 
	glTranslatef ( 0, -4,-13);glRotatef(r,1.0,1.0,1.0); //整体旋转
	glColor3f(0.7f, 0.7f, 0.7f);auxSolidCone(1,1);	//辅助库物体实面园锥
	glPopMatrix();
	
	glPushMatrix(); 
	glTranslatef ( 5,-4,-13);glRotatef(r,1.0,1.0,1.0); //整体旋转
	glColor3f(0.4f, 0.4f, 0.4f);auxWireTeapot(1);	//辅助库物体线茶壶
	glPopMatrix();
}*/