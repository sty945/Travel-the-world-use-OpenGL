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
	void picter(float x,float y,float z);//组合图形
	void	Point();	//画点
	void	Line();		//画线
	void	Triangle();	//画面
	void	Square();	//画正方面
	void	Esquare();	//画正方体
	void	Park();		//画园
	void	Pillar();	//园柱
	
	//地
	float		g_terrain	[MAP_W*MAP_W][3];	    //地域数据
	GLuint		g_index		[MAP_W*MAP_W* 2];	    //顶点数组
	float		g_texcoord	[MAP_W*MAP_W][2];	    //索引数组
	void		InitTerrain(float h);	            //载入地域数组
	GLvoid		DrawGround();	//篮色网格地面线
	float		GetHeight(float x, float z);        //取当前位置高度
	
    //漫游
	GLdouble	g_eye[3];		//
	GLdouble	g_look[3];		//
	float		rad_xz;			//角度
	float		g_Angle;		//左右转
	float		g_elev;			//仰俯角
	BOOL		DisplayScene();	//摄像机

	//天空
	UINT		g_cactus[16];	                    //贴图
	BITMAPINFOHEADER  g_bit;                        //
	unsigned char     *g_imageData;                  //
	void		CreateSkyBox(int a,int wi,int he,int le);//显示天
	void		texture(UINT textur);				//设置贴图滤波
	void		light0();

	//树
	void		ShowTree(float x,float z,float h,float s,int cactus);//树
	void		ShowTree0(float x,float z,float h,float s,int cactus);//普通平面树

	bool		LoadT8(char *filename, GLuint &texture); //调8位贴图
	unsigned char* LoadBit(char *filename, BITMAPINFOHEADER *bitmap);
	void		LoadT16(char *filename, GLuint &texture);//调16位帖图

	
	GLUquadricObj *g_text;

};

#endif // !defined(AFX_BSIPIC_H__12ACFBC8_E1BF_4783_8E99_A35C6EEDA311__INCLUDED_)
