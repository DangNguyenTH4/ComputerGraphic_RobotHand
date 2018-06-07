#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
GLuint moonRotatef=0,earthRotatef=0;
void init(void)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	//glOrtho(-200.0, 200.0, -200.0, 200.0, -100.0, 100.0);
	glShadeModel (GL_FLAT);
}
void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (1.0, 1.0, 1.0);
	glLoadIdentity (); 
	gluLookAt (12.0,0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//Nhin tu truc Ox

	glPushMatrix();
		glRotatef(earthRotatef,0,5,2);
		glColor3f(0.1,0.2,0.3);
		glutWireSphere(2.0,60,60);
	glPopMatrix();
	
	glPushMatrix();
		glColor3f(0.2,0.2,0.0);
		glRotatef(moonRotatef,0,5,2);	
		glTranslatef(0.0,-2.0,5.0);
		glutWireSphere(0.8,60,60);
	glPopMatrix();
	Sleep(83);
	earthRotatef+=90;
	if(earthRotatef>360)
	{
		earthRotatef=0;
	}
	
	moonRotatef+=13;
	if(moonRotatef>360)
	{
		moonRotatef=0;
	}
	glutPostRedisplay();
	glutSwapBuffers();
	glFlush ();
}


void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0); //Phep chieu phoi canh
	glMatrixMode (GL_MODELVIEW);
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
	glutMainLoop();
	return 0;
}
