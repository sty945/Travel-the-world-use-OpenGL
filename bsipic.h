// bsipic.h: interface for the bsipic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BSIPIC_H__12ACFBC8_E1BF_4783_8E99_A35C6EEDA311__INCLUDED_)
#define AFX_BSIPIC_H__12ACFBC8_E1BF_4783_8E99_A35C6EEDA311__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class bsipic  
{
public:
	bsipic();
	virtual ~bsipic();
	void picter(float x,float y,float z);//���ͼ��
	void	Point();	//����
	void	Line();		//����
	void	Triangle();	//����
	void	Square();	//��������
	void	Esquare();	//��������
	void	Park();		//��԰
	void	Pillar();	//԰��
	
	//��
	float		g_terrain	[MAP_W*MAP_W][3];	    //��������
	GLuint		g_index		[MAP_W*MAP_W* 2];	    //��������
	float		g_texcoord	[MAP_W*MAP_W][2];	    //��������
	void		InitTerrain(float h);	            //�����������
	GLvoid		DrawGround();	//��ɫ���������
	float		GetHeight(float x, float z);        //ȡ��ǰλ�ø߶�
	
    //����
	GLdouble	g_eye[3];		//
	GLdouble	g_look[3];		//
	float		rad_xz;			//�Ƕ�
	float		g_Angle;		//����ת
	float		g_elev;			//������
	BOOL		DisplayScene();	//�����

	//���
	UINT		g_cactus[16];	                    //��ͼ
	BITMAPINFOHEADER  g_bit;                        //
	unsigned char     *g_imageData;                  //
	void		CreateSkyBox(int a,int wi,int he,int le);//��ʾ��
	void		texture(UINT textur);				//������ͼ�˲�
	void		light0();

	//��
	void		ShowTree(float x,float z,float h,float s,int cactus);//��
	void		ShowTree0(float x,float z,float h,float s,int cactus);//��ͨƽ����

	bool		LoadT8(char *filename, GLuint &texture); //��8λ��ͼ
	unsigned char* LoadBit(char *filename, BITMAPINFOHEADER *bitmap);
	void		LoadT16(char *filename, GLuint &texture);//��16λ��ͼ

	
	GLUquadricObj *g_text;

};

#endif // !defined(AFX_BSIPIC_H__12ACFBC8_E1BF_4783_8E99_A35C6EEDA311__INCLUDED_)
