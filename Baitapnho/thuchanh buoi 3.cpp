//Su dung cac phim a b c A B C, x y x X Y Z de dieu khien 

#define GLUT_DISABLE_ATEXIT_HACK
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<stdlib.h>
static GLfloat spin = 0.0;
int Kichthuoc =1;
void init(void)
{
	glClearColor(0,0,0,0);
	glShadeModel(GL_FLAT);
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
		glTranslatef(-25,-25,0);
		glRotatef(spin,0,0,1);
		glPushMatrix();
			glTranslatef(25,25,0);
			glColor3f(1,1,1);
			glRectf(-25*Kichthuoc,-25*Kichthuoc,25*Kichthuoc,25*Kichthuoc);
		glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
}
void spinDisplay(void)
{
	spin+=2;
	if(spin>360.0)
		spin-=360;
	glutPostRedisplay();
}
void reshape(int w,int h)
{
	glViewport(0,0,(GLsizei) w,(GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50,50,-50,50,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
}
void mouse(int button,int state,int x,int y)
{
	switch(button)
	{
		case GLUT_LEFT_BUTTON:
			if (state==GLUT_DOWN)
				glutIdleFunc(spinDisplay);
				break;
		case GLUT_MIDDLE_BUTTON:
			if (state==GLUT_DOWN)
				glutIdleFunc(NULL);
				break;
		case GLUT_RIGHT_BUTTON:
			if(state==GLUT_DOWN)
				
				{
					spin+=15;
					if(spin>360.0)
						spin-=360;
					glutPostRedisplay();
				}
			break;
		default:
			break;
	}
}
void keyboard (unsigned char key, int a, int b)
{
	switch(key)
	{
		case 'a':
			Kichthuoc+=1;
			glutPostRedisplay();
			break;
		case 'A':
			Kichthuoc-=1;
			glutPostRedisplay();
			break;
		default:
			break;
	}
}

int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(250,250);
	glutInitWindowPosition(100,100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
