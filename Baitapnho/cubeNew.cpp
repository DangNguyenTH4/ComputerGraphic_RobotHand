#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
GLfloat eyex=0.0,eyey=0.0,eyez=0.0,centerx=0.0,centery=0.0,centerz=0.0,upx=0.0,upy=0.0,upz=0.0;

void init(void)
{
glClearColor (0.0, 0.0, 0.0, 0.0);
glShadeModel (GL_FLAT);
}
void display(void)
{
glClear (GL_COLOR_BUFFER_BIT);
glColor3f (1.0, 1.0, 1.0);
glLoadIdentity (); /* clear the matrix */
/* viewing transformation */
//OpenGL Programming Guide (Addison-Wesley Publishing Company)
//http://heron.cc.ukans.edu/ebt-bin/nph-dweb/dynaw.../@Generic__BookTextView/6635;cs=fullhtml;pt=1963 (6 of 49) [4/28/2000 9:45:03 PM]
//gluLookAt (0.0, 0.0, 5.0, 0.0, 1, 0.0, 0.0, 1.0, 0.0);
gluLookAt (eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
//glScalef (1.0, 2.0, 1.0); /* modeling transformation */
glutWireTeapot (1);
//glTranslatef(0,1,0);
//glutWireTeapot (1);
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
		case 't':
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
		
		default:
		break;
	}
}


int main(int argc, char** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
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
