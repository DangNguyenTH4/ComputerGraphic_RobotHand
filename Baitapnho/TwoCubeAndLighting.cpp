#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
GLfloat eyex=0.0,eyey=0.0,eyez=0.0,centerx=0.0,centery=0.0,centerz=0.0,upx=0.0,upy=0.0,upz=0.0;
GLint spin =0;
void init(void)
{
GLfloat mat_specular[] ={1,1,1,1};
GLfloat mat_shininess[] = {50};
GLfloat light_position[] = {1,1,1,0};

   GLfloat light_specular[] = {1,1,0}; // dinh nghia mau cua noi co cuong do manh nhat
   
   GLfloat light_diffuse[] = {1.0,0.0,0.0};  //Mau xxung quanh
   
   GLfloat light_ambient[] = {0.0,0.0,1.0};
   
glClearColor(0,0,0,0);

glShadeModel (GL_SMOOTH);


glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular); //Dinh nghia cho nguon sang light0
   glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse); //Dinh nghia cho nguon sang light0
   glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
   
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);

}
void display(void)
{
glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

glColor3f (1.0, 1.0, 1.0);
glLoadIdentity (); /* clear the matrix */
gluLookAt (2, 2, 5.0, 0.0, 1, 0.0, 0.0, 1.0, 0.0);
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

GLfloat light_diffuse[] = {1.0,0.0,0.0};  //Mau xxung quanh
glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse); //Dinh nghia cho nguon sang light0

glPushMatrix();

	glRotatef(spin,0,0,1);
	glTranslatef(0,0.5,0);
	//glScalef(1,2,1);
	glutSolidCube (1);
	
glPopMatrix();

// GLfloat light_diffuse[] = {1.0,0.0,1.0};  //Mau xxung quanh
GLfloat light_diffuse2[] = {1.0,0.0,1.0};  //Mau xxung quanh
glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse2); //Dinh nghia cho nguon sang light0

glColor3f(0,1,1);
glTranslatef(0,-1,0);
glScalef(1,2,1);
glutSolidCube(1);
glFlush ();
}
void reshape (int w, int h)
{
glViewport (0, 0, (GLsizei) w, (GLsizei) h);
glMatrixMode (GL_PROJECTION);
glLoadIdentity ();
glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
glMatrixMode (GL_MODELVIEW);
}
void keyboard (unsigned char key, int a, int b)
{
	switch (key) {
		case 't':
		eyex=0;	
		eyey = 5;
		eyez=0;
		centerx=0;
		centery=0;
		centerz=0;
		upx=1;
		upy=0;
		upz=0;
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
		default:
		break;
	}
}


int main(int argc, char** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
glutInitWindowSize (500, 500);
glutInitWindowPosition (100, 100);
glutCreateWindow (argv[0]);
init ();
glutDisplayFunc(display);
glutReshapeFunc(reshape);
glutKeyboardFunc(keyboard);
glutMainLoop();
return 0;
}
