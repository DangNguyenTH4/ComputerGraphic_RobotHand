#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <windows.h>
#include <math.h>
#include "BasicCad.h"
#include "BmpLoader.h"
bool khoidau =true;
bool dichuyentamnhin = true;;
/*--------------
Cac bien de thay doi LookAt
t--------------*/
GLfloat eyex=-8,eyey=0,eyez=-8,centerx=0,centery=3,centerz=0,upx=0,upy=1,upz=0;

//khai bao bien camera quay quanh oy
static GLfloat Dis_cam_to_Oy=8;
bool mouse_clicked=false;
//camera quay canh oz
GLfloat y_now;
bool mouseRight_clicked = false;
//*-----------------------------------------------------------------------------------------------

/***********************************
	Khai bao bien Phan texture
**********************************/
GLuint texture;
char addres_texture_file[20]="index.bmp";
void loadtexture(const char* filename);
void loadtexture(const char* filename,GLuint destination);


//////////////////////////////////////////////////


/*---------------------------------------------
	Khai bao bien Kiem soat anh sang
---------------------------------------------*/
GLfloat mat_specular[] ={1,1,1,1};
GLfloat mat_shininess[] = {1000};
GLfloat light_position[] = {0,0,1,0};
GLfloat light_specular[] = {1,1,1,1}; // dinh nghia mau cua noi co cuong do manh nhat
GLfloat light_diffuse[] = {1,1,0,1}; //Mau xxung quanh
GLfloat light_ambient[] = {1,1,0,1};

GLfloat light_ambient_trang[]={1,1,1,1};
GLfloat light_diffuse_trang[]={1,1,1,1};
GLfloat light_specular_trang[]={1,1,1,1};
GLfloat light_black[] = {0,0,0};

GLfloat scalef_ratruong=1;
GLfloat* light_ratruong = light_diffuse_trang;
bool coratruong = false;
/*------------------------------------------------
	Khai bao bien luu chieu dai canh tay, khuyu tay..
------------------------------------------------*/
GLfloat chieudai_khuyutay=3,chieudai_canhtay=2,chieudai_bantay=0.8;
//chieu dai 1 dot moi ngon tay
GLfloat chieudai_ngonTro,chieudai_ngonGiua,chieudai_ngonAput,chieudai_ngonUt,chieudai_ngonCai;
///////////////////////////////////////////////////////////////////////////////////////////////

/*------------------------------------------------------------
Khai bao bien kiem soat goc quay cua ngon tay,ban tay,canh tay....
-------------------------------------------------------------*/
GLint khuyu_tay_angle=0,canh_tay_angle=0,ban_tay_angle=0,canh_tay_angle_y=0,ban_tay_angle_y=0;
GLint angle_ngonCai_dot1=0,angle_ngonCai_dot2=0,angle_ngonCai_dot3=0;
GLint angle_ngonTro_dot1=0,angle_ngonTro_dot2=0,angle_ngonTro_dot3=0;
GLint angle_ngonGiua_dot1=0,angle_ngonGiua_dot2=0,angle_ngonGiua_dot3=0;
GLint angle_ngonAput_dot1=0,angle_ngonAput_dot2=0, angle_ngonAput_dot3=0;
GLint angle_ngonUt_dot1=0,angle_ngonUt_dot2=0,angle_ngonUt_dot3=0;
GLint angle_tocdonambantay = 6;
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

/*-----------------------------------------------------
Khai bao bien luu display list Canh tay, Khuyu tay, Ban tay
------------------------------------------------------*/
GLuint ban_tay,canh_tay,khuyu_tay;
GLuint co_tay,cuitro;
/////////////////////////////////////////////////////////////////////////

/*-----------------------------------------
Khai bao bien luu display list cac dot ngon tay
------------------------------------------*/
GLuint ngonCai1,ngonTro1,ngonGiua1,ngonAput1,ngonUt1;
GLuint daungonGiua;
/////////////////////////////////////////////////////////////////////////

/*----------------------------
	Khai bao cac ham
----------------------------*/
	//cac su kien cu dong
void vetay();
void nambantay();
void nambantay1();

void mua();
void mobantay();
void vaytay();
void nguacotay();
void gapcotay();
void ratruong();
void gaptay();
void duoitay();
void tym();
//su kien camera
void thaydoiLookAt();
void dichuyencamerasangtrai();
void dichuyencamerasangphai();
void dichuyencameraxuongduoi();
void dichuyencameralentren();
//cac ham mac dinh
void init(void);
void display(void);
void reshape(int w, int h);

//cac su kien nhan phim
void keyboard(unsigned char key,int a ,int b);
void keyboardUp(unsigned char key,int a ,int b);
void onSpecialKeyDown(int key,int x,int y);
void onSpecialKeyUp(int key,int x,int y);
void mousemove(int x,int y);
void mouseclick(int type,int state,int x,int y);

void veheTrucToaDo();
void setlightingcolor(float* mangmau);
void refresh();
void vetungbophan();
//////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
glutInitWindowSize (500,500);
glutInitWindowPosition (100, 100);
glutCreateWindow (argv[0]);
loadtexture(addres_texture_file);
init ();
glutDisplayFunc(display);
//glutDisplayFunc(vetungbophan);
glutReshapeFunc(reshape);
glutMouseFunc(mouseclick);

glutKeyboardFunc(keyboard);
glutSpecialFunc(onSpecialKeyDown);
glutSpecialUpFunc(onSpecialKeyUp);
glutKeyboardUpFunc(keyboardUp);
//glutIdleFunc(vaytay);
glutMainLoop();
return 0;
}

/*----------------------------------------------
	Cac ham mac dinh
----------------------------------------------*/
void init(void)
{

   khuyu_tay = BasicCad::MakeFrustumShape(1,0.8,chieudai_khuyutay);
   cuitro = BasicCad::MakeShpere(0.4);
   canh_tay = BasicCad::MakeFrustumShape(0.8,0.5,chieudai_canhtay);
   //co_tay = BasicCad::MakeBox(0.5,0.2,0.5);
   co_tay = BasicCad::MakeShpere(0.3);
   ban_tay = BasicCad::MakeBox(0.5,chieudai_bantay,0.2);
   
   ngonCai1 = BasicCad::MakeBox(0.16,0.37,0.16);
   ngonTro1 = BasicCad::MakeBox(0.15,0.3,0.15);
   ngonGiua1 = BasicCad::MakeBox(0.16,0.3,0.16);
   ngonAput1 = BasicCad::MakeBox(0.16,0.35,0.16);
	ngonUt1 = BasicCad::MakeBox(0.14,0.27,0.14);
   daungonGiua =BasicCad::MakeShpere(0.1);
	glClearColor(0,0,0,0);
	glShadeModel (GL_SMOOTH);  //Tao do tron de chieu sang 

   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, light_specular); 
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, light_ambient);
   
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_TEXTURE_2D);
   glEnable(GL_DEPTH_TEST);
}


void display(void)
{
glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glColor3f (1.0, 1.0, 1.0);
glLoadIdentity (); 
gluLookAt (eyex,eyey,eyez,centerx,centery,centerz,upx,upy,upz);
vetay();
if(dichuyentamnhin)
{
	eyex+=0.1;
	if(eyey<8)
	{
		eyey+=0.1;
		eyez+=0.2;
	}
	if(eyex>=8)
	{
		eyez-=0.2;
		khuyu_tay_angle=0;
		ban_tay_angle_y=0;
		if(eyez<0)
		{
			dichuyentamnhin = false;
			khoidau=false;
		}	
	}
}
if(khoidau)
{
		
	glutIdleFunc(vaytay);
	glutPostRedisplay();
}
else glutIdleFunc(NULL);
glFlush ();
}
GLfloat khungnhin = 1.5;
void reshape (int w, int h)
{
glViewport (0, 0, (GLsizei) w, (GLsizei) h);
glMatrixMode (GL_PROJECTION);
glLoadIdentity ();
glFrustum (-khungnhin, khungnhin, -khungnhin, khungnhin, 5, 50.0);
glMatrixMode (GL_MODELVIEW);
}
/**---------------------------------------------
	Cac ham hanh dong
----------------------------------------------*/
void ratruong()
{
			if(ban_tay_angle>-80)
			{
				nguacotay();
				if(angle_ngonGiua_dot3<50)
				{
					nambantay1();
				}
			}
			else
			{
				scalef_ratruong++;
				coratruong=true;
			}
}
void gaptay()
{
	canh_tay_angle+=3;
			if(canh_tay_angle>115)
				canh_tay_angle=115;
}
void duoitay()
{
	canh_tay_angle-=3;
			if(canh_tay_angle<0)
				canh_tay_angle=0;
}
void nguacotay()
{
	ban_tay_angle -=3;
	if(ban_tay_angle<-84)
	{
		ban_tay_angle=-84;
	}
}
void gapcotay()
{
	ban_tay_angle+=3;
	if(ban_tay_angle>80)
	{
		ban_tay_angle=80;
	}
}
bool vaytay1=true;
void vaytay()
{
	if(vaytay1)
	{
		canh_tay_angle_y+=3;
		ban_tay_angle_y+=6;
		if(canh_tay_angle_y>25)
		{
			vaytay1=false;
		}
	}
	if(!vaytay1)
	{
		canh_tay_angle_y-=3;
		ban_tay_angle_y-=6;
		if(canh_tay_angle_y<-25)
		{
			vaytay1=true;
		}
	}
}
void nambantay1()
{
			angle_ngonCai_dot1+=angle_tocdonambantay;
			angle_ngonTro_dot3+=angle_tocdonambantay;
			angle_ngonGiua_dot3+=angle_tocdonambantay;
			angle_ngonAput_dot3+=angle_tocdonambantay;
			angle_ngonUt_dot3+=angle_tocdonambantay;
			if(angle_ngonUt_dot3>65)
			{
				angle_ngonUt_dot3=65;
				angle_ngonUt_dot2+=angle_tocdonambantay;
				if(angle_ngonUt_dot2>80)
				{
					angle_ngonUt_dot2=80;
					angle_ngonUt_dot1+=angle_tocdonambantay;
					if(angle_ngonUt_dot1>85)
						angle_ngonUt_dot1=85;
				}
			}
			if(angle_ngonAput_dot3>65)
			{
				angle_ngonAput_dot3=65;
				angle_ngonAput_dot2+=angle_tocdonambantay;
				if(angle_ngonAput_dot2>80)
				{
					angle_ngonAput_dot2=80;
					angle_ngonAput_dot1+=angle_tocdonambantay;
					if(angle_ngonAput_dot1>85)
						angle_ngonAput_dot1=85;
				}
			}
			if(angle_ngonTro_dot3>65)
			{
				angle_ngonTro_dot3=65;
				angle_ngonTro_dot2+=angle_tocdonambantay;
				if(angle_ngonTro_dot2>80)
				{
					angle_ngonTro_dot2=80;
					angle_ngonTro_dot1+=angle_tocdonambantay;
					if(angle_ngonTro_dot1>85)
						angle_ngonTro_dot1=85;
				}
			}
			if(angle_ngonGiua_dot3>65)
			{
				angle_ngonGiua_dot3=65;
				angle_ngonGiua_dot2+=angle_tocdonambantay;
				if(angle_ngonGiua_dot2>80)
				{
					angle_ngonGiua_dot2=80;
					
					angle_ngonGiua_dot1+=angle_tocdonambantay;
					if(angle_ngonGiua_dot1>85)
						angle_ngonGiua_dot1=85;
				}	
			}		
			if(angle_ngonCai_dot1>170)
				angle_ngonCai_dot1=170;

}

void nambantayHi()
{
			angle_ngonCai_dot1+=angle_tocdonambantay-3;
			angle_ngonAput_dot3+=angle_tocdonambantay;
			angle_ngonUt_dot3+=angle_tocdonambantay;
			if(angle_ngonUt_dot3>65)
			{
				angle_ngonUt_dot3=65;
				angle_ngonUt_dot2+=angle_tocdonambantay;
				if(angle_ngonUt_dot2>80)
				{
					angle_ngonUt_dot2=80;
					angle_ngonUt_dot1+=angle_tocdonambantay;
					if(angle_ngonUt_dot1>85)
						angle_ngonUt_dot1=85;
				}
			}
			if(angle_ngonAput_dot3>65)
			{
				angle_ngonAput_dot3=65;
				angle_ngonAput_dot2+=angle_tocdonambantay;
				if(angle_ngonAput_dot2>80)
				{
					angle_ngonAput_dot2=80;
					angle_ngonAput_dot1+=angle_tocdonambantay;
					if(angle_ngonAput_dot1>85)
						angle_ngonAput_dot1=85;
				}
			}
			
			if(angle_ngonCai_dot1>110)
				angle_ngonCai_dot1=110;

}
void mobantay()
{
			angle_ngonCai_dot1-=angle_tocdonambantay;
			angle_ngonTro_dot1-=angle_tocdonambantay;
			angle_ngonGiua_dot1-=angle_tocdonambantay;
			angle_ngonAput_dot1-=angle_tocdonambantay;
			angle_ngonUt_dot1-=angle_tocdonambantay;
			if(angle_ngonUt_dot1<0)
			{
				angle_ngonUt_dot1=0;
				angle_ngonUt_dot2-=angle_tocdonambantay;
				if(angle_ngonUt_dot2<0)
				{
					angle_ngonUt_dot2=0;
					angle_ngonUt_dot3-=angle_tocdonambantay;
					if(angle_ngonUt_dot3<0)
						angle_ngonUt_dot3=0;
				}
			}
			if(angle_ngonAput_dot1<0)
			{
				angle_ngonAput_dot1=0;
				angle_ngonAput_dot2-=angle_tocdonambantay;
				if(angle_ngonAput_dot2<0)
				{
					angle_ngonAput_dot2=0;
					angle_ngonAput_dot3-=angle_tocdonambantay;
					if(angle_ngonAput_dot3<0)
						angle_ngonAput_dot3=0;
				}
			}
			if(angle_ngonTro_dot1<0)
			{
				angle_ngonTro_dot1=0;
				angle_ngonTro_dot2-=angle_tocdonambantay;
				if(angle_ngonTro_dot2<0)
				{
					angle_ngonTro_dot2=0;
					angle_ngonTro_dot3-=angle_tocdonambantay;
					if(angle_ngonTro_dot3<0)
						angle_ngonTro_dot3=0;
				}
			}
			if(angle_ngonGiua_dot1<0)
			{
				angle_ngonGiua_dot1=0;
				angle_ngonGiua_dot2-=angle_tocdonambantay;
				if(angle_ngonGiua_dot2<0)
				{
					angle_ngonGiua_dot2=0;
					
					angle_ngonGiua_dot3-=angle_tocdonambantay;
					if(angle_ngonGiua_dot3<0)
						angle_ngonGiua_dot3=0;
				}	
			}		
			if(angle_ngonCai_dot1<0)
				angle_ngonCai_dot1=0;

}
bool xoaycotay1 = true;
void xoaycotay(void)
{
	if(xoaycotay1)
	{
		ban_tay_angle_y+=8;
		if(ban_tay_angle_y>60)
		{
			ban_tay_angle_y=60;
			xoaycotay1=false;
		}
	}
	else 
	{
		ban_tay_angle_y-=8;
		if(ban_tay_angle_y<-60)
		{
			xoaycotay1=true;
			ban_tay_angle_y=-60;
		}
	}
}
void thaydoiLookAt()
{
	
}

/*********************************
	Doi tuong Arm
*********************************/
void vetay()
{
glPushMatrix();
	/*-------------------------
		Khu vu Khuyu Tay
	--------------------------*/
	glRotatef(khuyu_tay_angle,0,1,0);
	glTranslatef(0,chieudai_khuyutay/2,0);
	//glScalef(1,2,1);
	glCallList(khuyu_tay);
	/*--------------------------
		Khu vuc Canh Tay
	--------------------------*/
	glPushMatrix();
		glTranslatef(0,chieudai_khuyutay/2-0.1,0);
		/*-------------------------
					Phan Cui tro
			-------------------------*/
			glPushMatrix();
				glTranslatef(0,0,-0.07);
				glScalef(1,1.2,1.1);
				glCallList(cuitro);
			glPopMatrix();
		glRotatef(canh_tay_angle_y,0,1,0);
		glRotatef(canh_tay_angle,1,0,0);
		glTranslatef(0,chieudai_canhtay/2,0);
		glCallList(canh_tay);
		/*---------------------------------
			Khu vuc Ban tay
		---------------------------------*/
		glPushMatrix();
			glTranslatef(0,chieudai_canhtay/2,0);
			/*---------------------------------
				Phan co tay
			---------------------------------*/
			glPushMatrix();
				glScalef(1,0.5,1);
				glCallList(co_tay);			
			glPopMatrix();
			//glTranslatef(0,0,-0.25); Xoay theo truc Z thi can
			glRotatef(ban_tay_angle_y,0,1,0);
			glRotatef(ban_tay_angle,1,0,0);			
			glTranslatef(0,chieudai_bantay/2,0); 
			glCallList(ban_tay);
			if(coratruong)
			{
				glPushMatrix();
					setlightingcolor(light_ratruong);
	
					glTranslatef(0,0,scalef_ratruong*0.1);
					glScalef(1,1,scalef_ratruong);
					glCallList(ban_tay);
					setlightingcolor(light_diffuse);
				glPopMatrix();
			}
			/*----------------
			Ngon tay Cai
			-----------------*/
			glPushMatrix();	
				glTranslatef(0.25,-0.1,0);
				glRotatef(-45,0,0,1);
				//veheTrucToaDo();
				/*--------------------------
					Ngon Cai dot 1
				---------------------------*/
					glTranslatef(0,-0.1,0);
					glRotatef(-angle_ngonCai_dot1,-1,1,0); //Xoay ca ngon tay cai
					glTranslatef(0,0.1,0);
				glCallList(ngonCai1);
				/*---------------------------
					Ngon cai dot 2
				---------------------------*/
				glPushMatrix();
					glTranslatef(0,0.18,0);
					glRotatef(-angle_ngonCai_dot2,1,0,0); // xoay dot tay thu 2
					
					glScalef(1,0.6,1);
					glTranslatef(0,0.19,0);
					glCallList(ngonCai1);					
				/****************************
					Ngon cai dot 3
				***************************/
					glPushMatrix();
						glTranslatef(0,0.1,0);
						glRotatef(angle_ngonCai_dot3,1,0,0);
						glTranslatef(0,0.18,0);
						glCallList(ngonCai1);						
					glPopMatrix();				
				glPopMatrix();
			glPopMatrix();
			/*----------------
			Ngon tay Tro
			-----------------*/
			glPushMatrix();
				glTranslatef(0.25,chieudai_bantay/4,0);
				/*--------------------------
					Ngon tro dot 1
				---------------------------*/
				glRotatef(angle_ngonTro_dot1,1,0,0);
				glTranslatef(0,chieudai_bantay/4-0.1,0);
				glRotatef(-20,0,0,1);
				glCallList(ngonTro1);
				glPushMatrix();
				/*--------------------------
					Ngon tro dot 2
				---------------------------*/
					glTranslatef(0,0.15,0);
					glRotatef(angle_ngonTro_dot2,1,0,0);
					glTranslatef(0,0.15,0);
					glCallList(ngonTro1);
				/*--------------------------
					Ngon tro dot 3
				---------------------------*/					
					glPushMatrix();
						glTranslatef(0,0.15,0);
						glRotatef(angle_ngonTro_dot3,1,0,0);
						glTranslatef(0,0.15,0);
						glCallList(ngonTro1);
						
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
			
			/*----------------
			Ngon tay Giua
			-----------------*/
			glPushMatrix();
				/*--------------------------------
					Ngon giua dot 1
				---------------------------------*/
				glTranslatef(0.1,chieudai_bantay/4,0);
				glRotatef(angle_ngonGiua_dot1,1,0,0);
				glTranslatef(0,chieudai_bantay/4,0);
				glCallList(ngonGiua1);
				glPushMatrix();
				/*--------------------------------
					Ngon giua dot 2
				---------------------------------*/
					glTranslatef(0,0.15,0);
					glRotatef(angle_ngonGiua_dot2,1,0,0);
					glTranslatef(0,0.15,0);
					glCallList(ngonGiua1);
				/*--------------------------------
					Ngon giua dot 3
				---------------------------------*/
					glPushMatrix();
						glTranslatef(0,0.15,0);
						glRotatef(angle_ngonGiua_dot3,1,0,0);
						glTranslatef(0,0.15,0);
						glCallList(ngonGiua1);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
			/*----------------
			Ngon tay Ap ut
			-----------------*/
			glPushMatrix();
				glTranslatef(-0.1,chieudai_bantay/4,0);
				glRotatef(angle_ngonAput_dot1,1,00,0);
				glTranslatef(0,chieudai_bantay/4,0);
				glRotatef(10,0,0,1);
				glCallList(ngonAput1);
				glPushMatrix();
					glTranslatef(0,0.15,0);
					glRotatef(angle_ngonAput_dot2,1,0,0);
					glTranslatef(0,0.15,0);
					glCallList(ngonAput1);
					glPushMatrix();
						glTranslatef(0,0.15,0);
						glRotatef(angle_ngonAput_dot3,1,0,0);
						glTranslatef(0,0.15,0);
						glCallList(ngonAput1);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
			/*----------------
			Ngon tay ut
			-----------------*/
			glPushMatrix();
				glTranslatef(-0.25,chieudai_bantay/4,0);
				glRotatef(angle_ngonUt_dot1,1,0,0);
				glTranslatef(0,chieudai_bantay/4,0);
				glRotatef(25,0,0,1);
				glCallList(ngonUt1);
				glPushMatrix();
					glTranslatef(0,0.15,0);
					glRotatef(angle_ngonUt_dot2,1,0,0);
					glTranslatef(0,0.05,0);
					glCallList(ngonUt1);
					glPushMatrix();
						glTranslatef(0,0.10,0);
						glRotatef(angle_ngonUt_dot3,1,0,0);		
						glTranslatef(0,0.1,0);
						glCallList(ngonUt1);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
			glEnable(GL_LIGHTING);
		glPopMatrix();
	glPopMatrix();
glPopMatrix();
}
/**********************************
	Cac ham bat su kien nhan phim
**********************************/
void mouseclick(int type,int state,int x,int y)
{
	switch(type)
	{
	case GLUT_LEFT_BUTTON:
	{
		if(state==GLUT_DOWN)
		{
			if(eyex>0)
			{
				if(eyez>=0)
				{
					//eyex--;
					eyez--;
				}
				else if(eyez<=0)
				{
					eyez++;
				}
				eyex--;
			}
			else if(eyex=0)
			{
				if(eyez>0)
					eyez--;
				else if(eyez<0)
				{
					eyez++;	
				}
			}
			else if(eyex<0)
			{
				if(eyez>=0)
				{
					eyez--;
				}
				
				else if(eyez<=0)
				{
					eyez++;
				}
				eyex++;
			}
		}
	}
		break;
	case GLUT_RIGHT_BUTTON :
	{
		if(state==GLUT_DOWN)
		{
			if(eyex>0)
			{
				if(eyez>0)
				{
					eyex++;
					eyez++;
				}
				else if(eyez<0)
				{
					eyez--;
				}
				eyex++;
			}
			else if(eyex=0)
			{
				if(eyez>=0)
					eyez++;
				else if(eyez<0)
				{
					eyez--;	
				}
			}
			else if(eyex<0)
			{
				if(eyez>0)
				{
					eyez++;
				}
				
				else if(eyez<0)
				{
					eyez--;
				}
				eyex--;
			}
		}
	}
		break;
	default :
		break;
	}
	glutPostRedisplay();
	
}
void keyboardUp(unsigned char key,int a,int b)
{
	switch(key)
	{
		case 'r' :
			coratruong=false;
			scalef_ratruong=1;
			glutPostRedisplay();
			break;
		default :
			break;
	}
}
void keyboard (unsigned char key, int a, int b)
{
	switch (key) {
		case 'l':
		mua();
		glutPostRedisplay();
		break;
		
		case 't':
		xoaycotay();
		glutPostRedisplay();
		break;
		case 'v':
		vaytay();
		glutPostRedisplay();
		break;
		case 'V':
		khuyu_tay_angle-=3;
		glutPostRedisplay();
		break;
		case 'x':
			gaptay();
			glutPostRedisplay();
		break;
		case 'X':
			duoitay();
			glutPostRedisplay();
		break;
		case 'n' :
			nambantay1();
			glutPostRedisplay();
			break;
		case 'h' :
			nambantayHi();
			glutPostRedisplay();
			break;
		case 'm' :
			mobantay();
			glutPostRedisplay();
			break;
		case 'q' :
			tym();
			glutPostRedisplay();
			break;
		case 'r' :
			ratruong();
			glutPostRedisplay();
		default:
		break;
	}
}
void onSpecialKeyUp(int key,int x,int y)
{
	switch(key)
	{
		case GLUT_KEY_F3 :
			coratruong=false;
			scalef_ratruong=1;
			glutPostRedisplay();
			break;
		case GLUT_KEY_UP :
			
			break;
		default :
			break;
	}
}
void onSpecialKeyDown(int key, int x,int y)
{
	switch(key)
	{
		case GLUT_KEY_F1 : 
			khoidau=false;
			glutIdleFunc(NULL);
			break;
		case GLUT_KEY_F2 : 
			khoidau=true;
			glutIdleFunc(vaytay);
			glutPostRedisplay();
			break;
		case GLUT_KEY_F3 :
			eyex+=0.2;
			if(ban_tay_angle>-80)
			{
				nguacotay();
				if(angle_ngonGiua_dot3<50)
				{
					nambantay1();
				}
			}
			else
			{
				scalef_ratruong++;
				coratruong=true;
			}
			glutPostRedisplay();
			break;
		case GLUT_KEY_F5 :
			refresh();
			glutPostRedisplay();
			break;
		case GLUT_KEY_UP :
			dichuyencameralentren();
			glutPostRedisplay();
			break;
		case GLUT_KEY_DOWN :
			dichuyencameraxuongduoi();
			glutPostRedisplay();
			break;
		case GLUT_KEY_LEFT :
			dichuyencamerasangtrai();
			glutPostRedisplay();
			break;
		case GLUT_KEY_RIGHT :
			dichuyencamerasangphai();
			glutPostRedisplay();
			break;
		default:
			break;
	}
}
void veheTrucToaDo()
{
	
glDisable(GL_LIGHTING);
glBegin(GL_LINES);
glColor3f(1,0,0);
glVertex3f(0,0,0);
glVertex3f(5,0,0);

glColor3f(0,1,0);
glVertex3f(0,0,0);
glVertex3f(0,5,0);

glColor3f(0,0,1);
glVertex3f(0,0,0);
glVertex3f(0,0,5);
glEnd();
glEnable(GL_LIGHTING);
glColor3f(1,0,0);

}
void setlightingcolor(float* mangmau)
{
	
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mangmau); 
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mangmau);
   				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mangmau);
				
}
void refresh()
{
khuyu_tay_angle=0;canh_tay_angle=0;ban_tay_angle=0;canh_tay_angle_y=0;ban_tay_angle_y=0;
angle_ngonCai_dot1=0;angle_ngonCai_dot2=0;
angle_ngonTro_dot1=0;angle_ngonTro_dot2=0;angle_ngonTro_dot3=0;
angle_ngonGiua_dot1=0;angle_ngonGiua_dot2=0;angle_ngonGiua_dot3=0;
angle_ngonAput_dot1=0;angle_ngonAput_dot2=0; angle_ngonAput_dot3=0;
angle_ngonUt_dot1=0;angle_ngonUt_dot2=0;angle_ngonUt_dot3=0;
eyex=8,eyey=8,eyez=8,centerx=0,centery=3,centerz=0,upx=0,upy=1,upz=0;
khoidau=false;
dichuyentamnhin=false;
}

/**********************************
	Load Textures
************************************/
void loadtexture(const char* filename)
{
	BmpLoader bl(filename);
	glGenTextures(1,&khuyu_tay);
	glBindTexture(GL_TEXTURE_2D,khuyu_tay);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB,bl.Width,bl.Height,GL_RGB,GL_UNSIGNED_BYTE,bl.textureData);
}

void loadtexture(const char* filename,GLuint destination)
{
	BmpLoader bl(filename);
	glGenTextures(1,&destination);
	glBindTexture(GL_TEXTURE_2D,destination);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB,bl.Width,bl.Height,GL_RGB,GL_UNSIGNED_BYTE,bl.textureData);
}
void tym()
{
	    	angle_ngonGiua_dot3+=angle_tocdonambantay;
			angle_ngonAput_dot3+=angle_tocdonambantay;
			angle_ngonUt_dot3+=angle_tocdonambantay;
			angle_ngonTro_dot1+=angle_tocdonambantay;
			if(angle_ngonUt_dot3>65)
			{
				angle_ngonUt_dot3=65;
				angle_ngonUt_dot2+=angle_tocdonambantay;
				if(angle_ngonUt_dot2>80)
				{
					angle_ngonUt_dot2=80;
					angle_ngonUt_dot1+=angle_tocdonambantay;
					if(angle_ngonUt_dot1>85)
						angle_ngonUt_dot1=85;
				}
			}
			if(angle_ngonAput_dot3>65)
			{
				angle_ngonAput_dot3=65;
				angle_ngonAput_dot2+=angle_tocdonambantay;
				if(angle_ngonAput_dot2>80)
				{
					angle_ngonAput_dot2=80;
					angle_ngonAput_dot1+=angle_tocdonambantay;
					if(angle_ngonAput_dot1>85)
						angle_ngonAput_dot1=85;
				}
			}
			if(angle_ngonGiua_dot3>65)
			{
				angle_ngonGiua_dot3=65;
				angle_ngonGiua_dot2+=angle_tocdonambantay;
				if(angle_ngonGiua_dot2>80)
				{
					angle_ngonGiua_dot2=80;
					angle_ngonGiua_dot1+=angle_tocdonambantay;
					if(angle_ngonGiua_dot1>85)
					{
						angle_ngonGiua_dot1=85;
					}
				}
			}
			if(angle_ngonTro_dot1>45)
			{
				angle_ngonTro_dot1=45;
				angle_ngonTro_dot2+=angle_tocdonambantay;
				if(angle_ngonTro_dot2>70)
				     {
					 angle_ngonTro_dot2=70;
					 angle_ngonTro_dot3+=6;
					 if(angle_ngonTro_dot3>20)
					 angle_ngonTro_dot3=20;
					 }
				
			}
			angle_ngonCai_dot1+=3;
			if(angle_ngonCai_dot1>40)
			{
				angle_ngonCai_dot1=40;
				if(angle_ngonCai_dot3>30)
					angle_ngonCai_dot3=30;
			}
}
void dichuyencamerasangphai()
{
	Dis_cam_to_Oy=(sqrt(eyex*eyex+eyez*eyez));
	
	if(eyez>=0)
	{
		eyex+=0.5;
		if(eyex>=0)
			eyez -=0.5;
		else eyez+=0.5;
	}	
	if(eyez<0)
	{
		eyex-=0.5;
		if(eyex>=0)
			eyez -=0.5 ;
		else eyez+=0.5;
	}
}
void dichuyencamerasangtrai()
{

	if(eyez>=0)
	{
		eyex-=0.5;
		if(eyex>=0)
			eyez +=0.5;
		else eyez-=0.5;
	}	
	if(eyez<0)
	{
		eyex+=0.5;
		if(eyex<0)
			eyez -=0.5 ;
		else eyez+=0.5;
	}
}
void dichuyencameraxuongduoi()
{
	if(eyez>=0)
	{
		eyey-=0.5;
		if(eyey>=0)
		{
			eyez+=0.5;
		}
		else eyez-=0.5;
	}
	if(eyez<0)
	{
		eyey+=0.5;
		if(eyey>=0)
			eyez-=0.5;
		else eyez+=0.5;
	}
}
void dichuyencameralentren()
{
	if(eyez>=0)
	{
		eyey+=0.5;
		if(eyey>=0)
		{
			eyez-=0.5;
		}
		else eyez+=0.5;
	}
	if(eyez<0)
	{
		eyey-=0.5;
		if(eyey>=0)
			eyez+=0.5;
		else eyez-=0.5;
	}
}
int tocdoMua=10;
int tocdoMua1=12;
bool trolai1 =false;
bool trolai2 =false;
bool trolai3 =false;
bool trolai4 =false;

void mua()
{
	if(angle_ngonTro_dot2<30)
	{
		nambantay1();
	}
	if(!trolai1||!trolai2||!trolai3||!trolai4)
	{
		if(!trolai1)
		{
			angle_ngonUt_dot1+=tocdoMua;
		}
		
		if(angle_ngonUt_dot1>20)
			{
				trolai2=false;
				if(!trolai2)
				{
					angle_ngonAput_dot1+=tocdoMua;
				}
				
				if(angle_ngonAput_dot1>20)
				{
					trolai3=false;
					if(!trolai3)
					{
						angle_ngonGiua_dot1+=tocdoMua;
					}
					
					if(angle_ngonGiua_dot1>20)
					{
						trolai4=false;
						if(!trolai4)
						{
							angle_ngonTro_dot1+=tocdoMua;
							if(angle_ngonTro_dot1>20)
								trolai1=true;
						}
						
					}
				}
			}
	}
	if(trolai1||trolai2||trolai3||trolai4)
	{
		if(trolai1&&angle_ngonUt_dot1>0)
		{
			angle_ngonUt_dot1-=tocdoMua1;
			if(angle_ngonUt_dot1<0)
				trolai1=false;
		}
		
		
		if(angle_ngonUt_dot1<60)
			{
				trolai2=true;
				if(trolai2&&angle_ngonAput_dot1>0)
				{
					angle_ngonAput_dot1-=tocdoMua1;
					if(angle_ngonAput_dot1<0)
						trolai2=false;
				}
				
				if(angle_ngonAput_dot1<60)
				{
					trolai3=true;
					if(trolai3&&angle_ngonGiua_dot1>0)
					{
						angle_ngonGiua_dot1-=tocdoMua1;
						if(angle_ngonGiua_dot1<0)
							trolai3=false;
					}
					
					if(angle_ngonGiua_dot1<60)
					{
						trolai4=true;
						if(trolai4&&angle_ngonTro_dot1>0)
						{
							angle_ngonTro_dot1-=tocdoMua1;
							if(angle_ngonTro_dot1<0)
								trolai4=false;
						}
						if(angle_ngonTro_dot1<60)
							trolai1=false;
						
					}
				}
			}
		
	}
}

