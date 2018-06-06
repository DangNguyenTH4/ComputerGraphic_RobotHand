#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "BasicCad.h"
BasicCad::BasicCad(void)
{
	
}
BasicCad::~BasicCad(void)
{
	
}
GLuint BasicCad::MakeShpere(const float& radius)
{
	GLuint dp_list;
	dp_list=glGenLists(1);
	glNewList(dp_list,GL_COMPILE);
	glutSolidSphere(radius,64,64);
	glEndList();
	return dp_list;
}
GLuint BasicCad::MakeCube(const float& sizes)
{
	float size = sizes/2;
	GLuint dp_list;
	dp_list = glGenLists(1);
	glNewList(dp_list,GL_COMPILE);
	glBegin(GL_QUADS);
	//Front face
	glNormal3f(0,0,1);
	glVertex3f(-size,-size,size);
	glVertex3f(size,-size,size);
	glVertex3f(size,size,size);
	glVertex3f(-size,size,size);
	//Back face
	glNormal3f(0,0,-1);
	glVertex3f(-size,-size,-size);
	glVertex3f(-size,size,-size);
	glVertex3f(size,size,-size);
	glVertex3f(size,-size,-size);
	//Top face
	glNormal3f(0,1,0);
	glVertex3f(-size,size,-size);
	glVertex3f(-size,size,size);
	glVertex3f(size,size,size);
	glVertex3f(size,size,-size);
	//Bottom face
	glNormal3f(0,-1,0);
	glVertex3f(-size,-size,-size);
	glVertex3f(size,-size,-size);
	glVertex3f(size,-size,size);
	glVertex3f(-size,-size,size);
	//Right face
	glNormal3f(1,0,0);
	glVertex3f(size,-size,-size);
	glVertex3f(size,size,-size);
	glVertex3f(size,size,size);
	glVertex3f(size,-size,size);
	//Left face
	glNormal3f(-1,0,0);
	glVertex3f(-size,-size,-size);
	glVertex3f(-size,-size,size);
	glVertex3f(-size,size,size);
	glVertex3f(-size,size,-size);
	
	glEnd();
	glEndList();
	return dp_list;
}
GLuint BasicCad::MakeBox( const float& length, const float& height, const float& width)
{
	float x = length/2;
	float y = height/2;
	float z = width/2;
	GLuint dp_list;
	dp_list =glGenLists(1);
	glNewList(dp_list,GL_COMPILE);
	 glBegin(GL_QUADS);
	
	//front
	glNormal3f(0,0,1);
//	glTexCoord2f(0,0);
	glVertex3f(-x,-y,z);
	glVertex3f(x,-y,z);
	glVertex3f(x,y,z);
	glVertex3f(-x,y,z);

	//Back
	glNormal3f(0,0,-1);
	glVertex3f(-x,-y,-z);
	glVertex3f(x,-y,-z);
	glVertex3f(x,y,-z);
	glVertex3f(-x,y,-z);
	
	//glEnd();
	
	//left
	//glBegin(GL_QUADS);
	glNormal3f(-1,0,0);
	glVertex3f(-x,-y,-z);
	glVertex3f(-x,-y,z);
	glVertex3f(-x,y,z);
	glVertex3f(-x,y,-z);
	//glEnd();
	//glEnd();	
	//glBegin(GL_QUADS);
	
	//right
	//glBegin(GL_QUADS);
	glNormal3f(0,1,0);
	glVertex3f(x,y,z);
	glVertex3f(x,y,-z);
	glVertex3f(x,-y,-z);
	glVertex3f(x,-y,z);
	glEnd();	
	
	//top
	//glBegin(GL_QUADS);
	glNormal3f(0,1,0);
	glVertex3f(x,y,z);
	glVertex3f(-x,y,z);
	glVertex3f(-x,y,-z);
	glVertex3f(x,y,-z);
	//glEnd();	
	
	//bottom
	//glBegin(GL_QUADS);
	glNormal3f(0,-1,0);
	glVertex3f(-x,-y,-z);
	glVertex3f(-x,-y,z);
	glVertex3f(x,-y,z);
	glVertex3f(x,-y,-z);
	glEnd();	
	
	glEndList();
	return dp_list;
}
GLuint BasicCad::MakeCylinder(const float& radius, const float& length)
{
	GLuint dplist;
	dplist = glGenLists(1);
	glNewList(dplist,GL_COMPILE);
	GLUquadricObj *quadratic_obj;
	quadratic_obj = gluNewQuadric();
	glRotatef(-90,1.0,0.0,0.0);
	gluCylinder(quadratic_obj,radius,radius,length,32,32);
	glEndList();
	return dplist;
}
GLuint BasicCad::MakeTruncatedCone(const float& base_rad,const float& top_rad,const float& length)
{
	GLuint dplist;
	dplist = glGenLists(1);
	glNewList(dplist,GL_COMPILE);
	GLUquadricObj *quadratic_obj;
	quadratic_obj = gluNewQuadric();
	glRotatef(-90,1.0,0.0,0.0);
	gluCylinder(quadratic_obj,base_rad,top_rad,length,32,32);
	glEndList();
	return dplist;
}
GLuint BasicCad::MakeCone(const float& base_rad,const float& length)
{
	GLuint dplist;
	dplist = glGenLists(1);
	glNewList(dplist,GL_COMPILE);
	GLUquadricObj *quadratic_obj;
	quadratic_obj = gluNewQuadric();
	glRotatef(-90,1.0,0.0,0.0);
	gluCylinder(quadratic_obj,base_rad,0.0,length,32,32);
	glEndList();
	return dplist;	
}
GLuint BasicCad::MakePyramid(const float& size, const float& height)
{
	GLuint dplist;
	dplist = glGenLists(1);
	glNewList(dplist,GL_COMPILE);
	double halfSize = size*0.5;
	double heig=height*0.5;
	glBegin(GL_TRIANGLES);
	//Front
	glNormal3f(0,0,1);
	glVertex3f(0,heig,0);
	glVertex3f(-halfSize,-heig,halfSize);
	glVertex3f(halfSize,-heig,halfSize);
	//left
	glNormal3f(-1,0,0);
	glVertex3f(0,heig,0);
	glVertex3f(-halfSize,-heig,halfSize);
	glVertex3f(-halfSize,-heig,-halfSize);
	//back
	glNormal3f(0,0,-1);
	glVertex3f(0,heig,0);
	glVertex3f(-halfSize,-heig,-halfSize);
	glVertex3f(halfSize,-heig,-halfSize);
	//right
	glNormal3f(0,0,-1);
	glVertex3f(0,heig,0);
	glVertex3f(halfSize,-heig,halfSize);
	glVertex3f(halfSize,-heig,-halfSize);
	
	glEnd();
	//bottom
	glBegin(GL_QUADS);
	glNormal3f(0,-1,0);
	glVertex3f(-halfSize,-heig,-halfSize);
	glVertex3f(-halfSize,-heig,halfSize);
	glVertex3f(halfSize,-heig,halfSize);
	glVertex3f(halfSize,-heig,-halfSize);
	glEnd();
	
	glEndList();
	return dplist;	
}
GLuint BasicCad::MakeFrustumShape(const float& bottom_size,const float& top_size,const float& height)
{
	GLuint dplist;
	dplist = glGenLists(1);
	glNewList(dplist,GL_COMPILE);
	double bot=bottom_size*0.5,top=top_size*0.5,halfHeight=height*0.5;
	
	glBegin(GL_QUADS);
	//Front
	glNormal3f(0,0,1);
	glTexCoord2f(0,0);
	glVertex3f(-bot,-halfHeight,bot);
	glTexCoord2f(1,0);
	glVertex3f(bot,-halfHeight,bot);
	glTexCoord2f(1,1);
	glVertex3f(top,halfHeight,top);
	glTexCoord2f(0,1);
	glVertex3f(-top,halfHeight,top);
	//Left
	glNormal3f(-1,0,0);
	glVertex3f(-bot,-halfHeight,bot);
	glVertex3f(-bot,-halfHeight,-bot);
	glVertex3f(-top,halfHeight,-top);
	glVertex3f(-top,halfHeight,top);
	//Right
	glNormal3f(1,0,0);
	glVertex3f(bot,-halfHeight,bot);
	glVertex3f(bot,-halfHeight,-bot);
	glVertex3f(top,halfHeight,-top);
	glVertex3f(top,halfHeight,top);
	//Back
	glNormal3f(0,0,-1);
	glVertex3f(bot,-halfHeight,-bot);
	glVertex3f(-bot,-halfHeight,-bot);
	glVertex3f(-top,halfHeight,-top);
	glVertex3f(top,halfHeight,-top);
	//Top
	glNormal3f(0,1,0);
	glVertex3f(top,halfHeight,top);
	glVertex3f(top,halfHeight,-top);
	glVertex3f(-top,halfHeight,-top);
	glVertex3f(-top,halfHeight,top);
	//Bottom
	glNormal3f(0,-1,0);
	glVertex3f(bot,-halfHeight,bot);
	glVertex3f(bot,-halfHeight,-bot);
	glVertex3f(-bot,-halfHeight,-bot);
	glVertex3f(-bot,-halfHeight,bot);
	
	glEnd();
	glEndList();
	return dplist;
}
GLuint MakeOctagon(const float&  size, const float& thickness);
GLuint BanTay(const float& sizeLapGhep)
{
	
}

