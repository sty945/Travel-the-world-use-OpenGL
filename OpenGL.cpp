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
	int nPixelFormat;					  // ���ص��ʽ
	hDC=hDC0;
	PIXELFORMATDESCRIPTOR pfd = 
	{ 
		sizeof(PIXELFORMATDESCRIPTOR),    // pfd�ṹ�Ĵ�С 
			1,                                // �汾�� 
			PFD_DRAW_TO_WINDOW |              // ֧���ڴ����л�ͼ 
			PFD_SUPPORT_OPENGL |              // ֧�� OpenGL 
			PFD_DOUBLEBUFFER,                 // ˫����ģʽ 
			PFD_TYPE_RGBA,                    // RGBA ��ɫģʽ 
			16,                               // 24 λ��ɫ��� 
			0, 0, 0, 0, 0, 0,                 // ������ɫλ 
			0,                                // û�з�͸���Ȼ��� 
			0,                                // ������λλ 
			0,                                // ���ۼӻ��� 
			0, 0, 0, 0,                       // �����ۼ�λ 
			16,                               // 32 λ��Ȼ���     
			0,                                // ��ģ�建�� 
			0,                                // �޸������� 
			PFD_MAIN_PLANE,                   // ���� 
			0,                                // ���� 
			0, 0, 0                           // ���Բ�,�ɼ��Ժ������ģ 
	}; 
	if (!(nPixelFormat = ChoosePixelFormat(hDC, &pfd)))
	{ 
		MessageBox(NULL,"û�ҵ����ʵ���ʾģʽ","Error",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}
	SetPixelFormat(hDC,nPixelFormat,&pfd);//���õ�ǰ�豸�����ص��ʽ
	hRC = wglCreateContext(hDC);          //��ȡ��Ⱦ�������
	wglMakeCurrent(hDC, hRC);             //������Ⱦ�������
	m_bsipic = new bsipic();
	m_bsipic->light0();
	return TRUE;
}

void OpenGL::init(int Width, int Height)
{	
	glViewport(0,0,Width,Height);			// ����OpenGL�ӿڴ�С��	
	glMatrixMode(GL_PROJECTION);			// ���õ�ǰ����ΪͶӰ����
	glLoadIdentity();						// ���õ�ǰָ���ľ���Ϊ��λ����
	gluPerspective							// ����͸��ͼ
		( 55.0f,							// ͸�ӽ�����Ϊ 45 ��
		(GLfloat)Width/(GLfloat)Height,	// ���ڵĿ���߱�
		1.0f,								// ��Ұ͸�����:����1.0f
		3000.0f							// ��Ұ͸�����:ʼ��0.1fԶ��1000.0f
		);
	// �������������ƣ���һ���������þ�ͷ��Ƕȣ��ڶ��������ǳ���ȣ�������Զ�����С�
	glMatrixMode(GL_MODELVIEW);				// ���õ�ǰ����Ϊģ����ͼ����
	glLoadIdentity();						// ���õ�ǰָ���ľ���Ϊ��λ����
	//====================================================
}
void OpenGL::Render()//OpenGLͼ�δ���
{	
	if(m_bsipic==NULL) return;
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);			 // ����ˢ�±���ɫ
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);// ˢ�±���
	glLoadIdentity();								 // ���õ�ǰ��ģ�͹۲����
    m_bsipic->DisplayScene();
	m_bsipic->DrawGround();
	m_bsipic->CreateSkyBox(3,6,3,6);				 // ��ʾ��
	//play();
	srand(100);//�������Ĺ̶����������
	for(int i=0;i<300;i++)						//��������			
	{
		float x= RAND_COORD((MAP_W-1)*MAP_SCALE);	//λ��x
		float z= RAND_COORD((MAP_W-1)*MAP_SCALE);	//λ��z
		float size=4.0f+rand()%4;					//��С2-4���
		float h=-size/10;							//��ǳ
		int   cactus=rand()%4+11;					//�������4��  
		//m_bsipic->ShowTree(x,z,size,h,cactus);	//��ʾƽ����
		m_bsipic->ShowTree(x,z,size,h,cactus);	//��ʾ��

	}
	glFlush();										 // ���´���
	SwapBuffers(hDC);								 // �л�������
	//r+=1;if(r>360) r=0;
}
void OpenGL::CleanUp()//���OpenGL
{	 
	wglMakeCurrent(hDC, NULL);                       //���OpenGL
	wglDeleteContext(hRC);                           //���OpenGL
}

/*
void OpenGL::play()
{
	glPushMatrix(); 
	glPointSize(4);										//��Ĵ�С
	glTranslatef (-5, 4,-13);glRotatef(r,1.0,1.0,1.0);	//������ת
	glColor3f(1.0f, 0.0f, 0.0f);
	m_bsipic.Point();		//����
	glPopMatrix();
	
	glPushMatrix(); 
	glTranslatef ( 0, 4,-13);glRotatef(r,1.0,1.0,1.0); //������ת
	glColor3f(0.0f, 1.0f, 0.0f);m_bsipic.Line();		//����
	glPopMatrix();
	glPushMatrix();
	glTranslatef ( 5, 4,-13);glRotatef(r,1.0,1.0,1.0); //������ת
	glColor3f(0.0f, 0.0f, 1.0f);m_bsipic.Triangle();	//����
	glPopMatrix();
	glPushMatrix();
	glTranslatef (-5, 0,-13);glRotatef(r,1.0,1.0,1.0); //������ת
	glColor3f(1.0f, 1.0f, 0.0f);m_bsipic.Square();		//��������
	glPopMatrix();
	glPushMatrix();
	glTranslatef ( 0, 0,-13);glRotatef(r,1.0,1.0,1.0); //������ת
	glColor3f(0.0f, 1.0f, 1.0f);m_bsipic.Esquare();		//��������
	glPopMatrix();
	glPushMatrix(); 
	glTranslatef ( 5, 0,-13);glRotatef(r,1.0,1.0,1.0); //������ת
	glColor3f(1.0f, 0.0f, 1.0f);m_bsipic.Park();		//��԰
	glPopMatrix();
	glPushMatrix(); 
	glTranslatef (-5,-4,-13);glRotatef(r,1.0,1.0,1.0); //������ת
	glColor3f(1.0f, 1.0f, 1.0f);m_bsipic.Pillar();		//԰��
	glPopMatrix();
	glPushMatrix(); 
	glTranslatef ( 0, -4,-13);glRotatef(r,1.0,1.0,1.0); //������ת
	glColor3f(0.7f, 0.7f, 0.7f);auxSolidCone(1,1);	//����������ʵ��԰׶
	glPopMatrix();
	
	glPushMatrix(); 
	glTranslatef ( 5,-4,-13);glRotatef(r,1.0,1.0,1.0); //������ת
	glColor3f(0.4f, 0.4f, 0.4f);auxWireTeapot(1);	//�����������߲��
	glPopMatrix();
}*/