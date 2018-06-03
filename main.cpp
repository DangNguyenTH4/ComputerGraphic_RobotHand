#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "BasicCad.h"
#include "cacham.h"
/*--------------
Cac bien de thay doi LookAt
--------------*/
GLfloat eyex=0,eyey=5,eyez=6,centerx=0,centery=3,centerz=0,upx=0,upy=1,upz=0;
//*-----------------------------------------------------------------------------------------------

/*------------------------------------------------
Cac bien luu chu do dai khuyu tay,canh tay,ban tay
------------------------------------------------*/
GLfloat chieudai_khuyutay=3,chieudai_canhtay=2,chieudai_bantay=0.8;
//chieu dai 1 dot moi ngon tay
GLfloat chieudai_ngonTro,chieudai_ngonGiua,chieudai_ngonAput,chieudai_ngonUt,chieudai_ngonCai;
///////////////////////////////////////////////////////////////////////////////////////////////

/*------------------------------------------------------------
Cac bien kiem soat goc quay cua ngon tay,ban tay,canh tay....
-------------------------------------------------------------*/
GLint spin =0,khuyu_tay_angle=0,canh_tay_angle=0,ban_tay_angle=0;
GLint angle_ngonCai_dot1=0,angle_ngonCai_dot2=0;
GLint angle_ngonTro_dot1=0,angle_ngonTro_dot2=0,angle_ngonTro_dot3=0;
GLint angle_ngonGiua_dot1=0,angle_ngonGiua_dot2=0,angle_ngonGiua_dot3=0;
GLint angle_ngonAput_dot1=0,angle_ngonAput_dot2=0, angle_ngonAput_dot3=0;
GLint angle_ngonUt_dot1=0,angle_ngonUt_dot2=0,angle_ngonUt_dot3=0;
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

/*-----------------------------------------------------
Cac bien luu display list Canh tay, Khuyu tay, Ban tay
------------------------------------------------------*/
GLuint ban_tay,canh_tay,khuyu_tay;
GLuint co_tay;
/////////////////////////////////////////////////////////////////////////

/*-----------------------------------------
Cac bien luu display list cac dot ngon tay
------------------------------------------*/
GLuint ngonCai1,ngonTro1,ngonGiua1,ngonAput1,ngonUt1;
/////////////////////////////////////////////////////////////////////////

/*----------------------------
	Khai bao cac ham
----------------------------*/
void vetay();
void nambantay();
void mobantay();
void thaydoiLookAt();
void init(void);
void display(void);
void reshape(int w, int h);
void keyboard(unsigned char key,int a ,int b);
void onSpecialKeyDown(int key,int x,int y);
void veheTrucToaDo();
void vaytay();
//////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
glutInitWindowSize (500,500);
glutInitWindowPosition (100, 100);
glutCreateWindow (argv[0]);
init ();
glutDisplayFunc(display);
glutReshapeFunc(reshape);
glutKeyboardFunc(keyboard);
glutSpecialFunc(onSpecialKeyDown);

glutMainLoop();
return 0;
}
bool vaytay1=true;
void vaytay()
{
	if(vaytay)
	{
		khuyu_tay_angle+=3;
		if(khuyu_tay_angle>25)
		{
			vaytay1=false;
		//	khuyu_tay_angle=25;
		}
	}
	if(!vaytay1)
	{
		khuyu_tay_angle-=3;
		if(khuyu_tay_angle<-25)
		{
			vaytay1=true;
		//	khuyu_tay_angle=-25;
		}
	}
}
void nambantay()
{
			angle_ngonCai_dot1+=3;
			angle_ngonTro_dot1+=3;
			angle_ngonGiua_dot1+=3;
			angle_ngonAput_dot1+=3;
			angle_ngonUt_dot1+=3;
			if(angle_ngonUt_dot1>85)
			{
				angle_ngonUt_dot1=85;
				angle_ngonUt_dot2+=3;
				if(angle_ngonUt_dot2>80)
				{
					angle_ngonUt_dot2=80;
					angle_ngonUt_dot3+=3;
					if(angle_ngonUt_dot3>65)
						angle_ngonUt_dot3=65;
				}
			}
			if(angle_ngonAput_dot1>85)
			{
				angle_ngonAput_dot1=85;
				angle_ngonAput_dot2+=3;
				if(angle_ngonAput_dot2>80)
				{
					angle_ngonAput_dot2=80;
					angle_ngonAput_dot3+=3;
					if(angle_ngonAput_dot3>65)
						angle_ngonAput_dot3=65;
				}
			}
			if(angle_ngonTro_dot1>85)
			{
				angle_ngonTro_dot1=85;
				angle_ngonTro_dot2+=3;
				if(angle_ngonTro_dot2>80)
				{
					angle_ngonTro_dot2=80;
					angle_ngonTro_dot3+=3;
					if(angle_ngonTro_dot3>65)
						angle_ngonTro_dot3=65;
				}
			}
			if(angle_ngonGiua_dot1>85)
			{
				angle_ngonGiua_dot1=85;
				angle_ngonGiua_dot2+=3;
				if(angle_ngonGiua_dot2>80)
				{
					angle_ngonGiua_dot2=80;
					
					angle_ngonGiua_dot3+=3;
					if(angle_ngonGiua_dot3>65)
						angle_ngonGiua_dot3=65;
				}	
			}		
			if(angle_ngonCai_dot1>170)
				angle_ngonCai_dot1=170;

}
void mobantay()
{
			angle_ngonCai_dot1-=3;
			angle_ngonTro_dot1-=3;
			angle_ngonGiua_dot1-=3;
			angle_ngonAput_dot1-=3;
			angle_ngonUt_dot1-=3;
			if(angle_ngonUt_dot1<0)
			{
				angle_ngonUt_dot1=0;
				angle_ngonUt_dot2-=3;
				if(angle_ngonUt_dot2<0)
				{
					angle_ngonUt_dot2=0;
					angle_ngonUt_dot3-=3;
					if(angle_ngonUt_dot3<0)
						angle_ngonUt_dot3=0;
				}
			}
			if(angle_ngonAput_dot1<0)
			{
				angle_ngonAput_dot1=0;
				angle_ngonAput_dot2-=3;
				if(angle_ngonAput_dot2<0)
				{
					angle_ngonAput_dot2=0;
					angle_ngonAput_dot3-=3;
					if(angle_ngonAput_dot3<0)
						angle_ngonAput_dot3=0;
				}
			}
			if(angle_ngonTro_dot1<0)
			{
				angle_ngonTro_dot1=0;
				angle_ngonTro_dot2-=3;
				if(angle_ngonTro_dot2<0)
				{
					angle_ngonTro_dot2=0;
					angle_ngonTro_dot3-=3;
					if(angle_ngonTro_dot3<0)
						angle_ngonTro_dot3=0;
				}
			}
			if(angle_ngonGiua_dot1<0)
			{
				angle_ngonGiua_dot1=0;
				angle_ngonGiua_dot2-=3;
				if(angle_ngonGiua_dot2<0)
				{
					angle_ngonGiua_dot2=0;
					
					angle_ngonGiua_dot3-=3;
					if(angle_ngonGiua_dot3<0)
						angle_ngonGiua_dot3=0;
				}	
			}		
			if(angle_ngonCai_dot1<0)
				angle_ngonCai_dot1=0;

}
void xoaycotay(void)
{
	ban_tay_angle+=3;
	if(ban_tay_angle>30)
	{
		ban_tay_angle=30;
	}
	//glutPostRediplay();
}
void thaydoiLookAt()
{
	
}
void vetay()
{

glPushMatrix();
	/*-------------------------
		Khu vu Khuyu Tay
	--------------------------*/
	glRotatef(khuyu_tay_angle,0,0,1);
	glTranslatef(0,chieudai_khuyutay/2,0);
	//glScalef(1,2,1);
	glCallList(khuyu_tay);
	/*--------------------------
		Khu vuc Canh Tay
	--------------------------*/
	glPushMatrix();
		/*
		glPushMatrix();
			glDisable(GL_LIGHTING);
			glColor3f(1,0,0);
			glTranslatef(0,0.1,0);
			glCallList(vungdemCanhTay_KhuyuTay);
			glEnable(GL_LIGHTING);
		glPopMatrix();
		*/
		glTranslatef(0,chieudai_khuyutay/2-0.1,0);
		/*-------------------------
					Phan Cui tro
			-------------------------*/
			glPushMatrix();
				glTranslatef(0,0,-0.125);
				GLuint cuitro = BasicCad::MakeBox(0.7,0.8,0.6);
				glCallList(cuitro);
			glPopMatrix();
			
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
				glCallList(co_tay);			
			glPopMatrix();
			glTranslatef(0,0,-0.25);
			glRotatef(ban_tay_angle,0,0,1);
			
			glTranslatef(0,0,0.25);
			glTranslatef(0,chieudai_bantay/2,0); 	
			glCallList(ban_tay);
			
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
					glTranslatef(0,0.19,0);
					glCallList(ngonCai1);
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
				//veheTrucToaDo();
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
//				veheTrucToaDo();
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
			
		glPopMatrix();
	glPopMatrix();
	
glPopMatrix();

}
void init(void)
{
GLfloat mat_specular[] ={1,1,1,1};
GLfloat mat_shininess[] = {50};
GLfloat light_position[] = {1,1,1,0};

GLfloat light_specular[] = {1,1,0}; // dinh nghia mau cua noi co cuong do manh nhat
   
GLfloat light_diffuse[] = {1.0,0.0,0.0};  //Mau xxung quanh
   
GLfloat light_ambient[] = {1,1,0};
   
   
   khuyu_tay = BasicCad::MakeFrustumShape(1,0.8,chieudai_khuyutay);
   canh_tay = BasicCad::MakeFrustumShape(0.8,0.5,chieudai_canhtay);
   co_tay = BasicCad::MakeBox(0.5,0.2,0.5);
   ban_tay = BasicCad::MakeBox(0.5,chieudai_bantay,0.2);
   ngonCai1 = BasicCad::MakeBox(0.16,0.37,0.16);
   ngonTro1 = BasicCad::MakeBox(0.15,0.3,0.15);
   ngonGiua1 = BasicCad::MakeBox(0.16,0.3,0.16);
   ngonAput1 = BasicCad::MakeBox(0.16,0.35,0.16);
	ngonUt1 = BasicCad::MakeBox(0.14,0.27,0.14);
   
	glClearColor(0,0,0,0);
	glShadeModel (GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular); 
   glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
   glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
   
 //  glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
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
void display(void)
{
glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

glColor3f (1.0, 1.0, 1.0);
glLoadIdentity (); /* clear the matrix */
//gluLookAt (6, 6, 6, 0.0, 1, 0.0, 0.0, 1.0, 0.0);
//gluLookAt (0, 5, 6, 0, 3, 0.0, 0.0, 1.0, 0.0);
gluLookAt (eyex,eyey,eyez,centerx,centery,centerz,upx,upy,upz);


/*--------------------------
	He truc toa do Oxyz
--------------------------*/
veheTrucToaDo();
GLfloat light_diffuse[] = {1,1,0.4};
glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
/*
vetay();
glTranslatef(-2,0,0);
vetay();
glTranslatef(4,0,0);
vetay();

*/
for(int i =0;i<10;i+=2)
{
	if(i==0)
		vetay();
	else
	{
		glPushMatrix();
			glTranslatef(i,0,0);
			vetay();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-i,0,0);
			vetay();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,0,i);
			vetay();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,0,-i);
			vetay();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(i,0,i);
			vetay();
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(i,0,-i);
			vetay();
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(-i,0,i);
			vetay();
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(-i,0,-i);
			vetay();
		glPopMatrix();
	}
}
glFlush ();
}
void reshape (int w, int h)
{
glViewport (0, 0, (GLsizei) w, (GLsizei) h);
glMatrixMode (GL_PROJECTION);
glLoadIdentity ();
glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
//glFrustum(-3,3,-3,3,1,20);
glMatrixMode (GL_MODELVIEW);
}
void keyboard (unsigned char key, int a, int b)
{
	switch (key) {
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

		case 'b':
		eyex=0;	
		eyey = -5;
		eyez=0;
		centerx=0;
		centery=0;
		centerz=0;
		upx=1;
		upy=0;
		upz=0;
		glutPostRedisplay();
		break;
		case 'a':
			spin+=3;
			if(spin>360)
				spin-=360;
		glutPostRedisplay();
		break;
		case 'x':
			canh_tay_angle+=3;
			if(canh_tay_angle>115)
				canh_tay_angle=115;
		glutPostRedisplay();
		break;
		case 'X':
			canh_tay_angle-=3;
			if(canh_tay_angle<0)
				canh_tay_angle=0;
		glutPostRedisplay();
		break;
		default:
		break;
	}
}

void onSpecialKeyDown(int key, int x,int y)
{
	switch(key)
	{
		case GLUT_KEY_UP :
			eyez -=0.2;
			glutPostRedisplay();
			break;
		case GLUT_KEY_DOWN :
			eyez+=0.2;
			glutPostRedisplay();
			break;
		case GLUT_KEY_LEFT :
			eyex-=0.2;
			glutPostRedisplay();
			break;
		case GLUT_KEY_RIGHT :
			eyex+=0.2;
			glutPostRedisplay();
			break;
		default:
			break;
	}
}

