#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

#define GLUT_KEY_ESCAPE		27
#define GLUT_KEY_U		119
#define GLUT_KEY_D		115
#define GLUT_KEY_L		97
#define GLUT_KEY_R		100

const GLsizei windowWidth = 500;
const GLsizei windowHeight = 500;

GLfloat cubeRotateX = 45.0f;
GLfloat cubeRotateY = 45.0f;

bool keys[255];

GLvoid establishProjectionMatrix(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 200.0f);
}

GLvoid initGL(GLsizei width, GLsizei height)
{
	establishProjectionMatrix(width, height);

	glShadeModel(GL_SMOOTH);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_PERSPECTIVE_CORRECTION_HINT);
}

GLvoid displayFPS(GLvoid)
{
	static long lastTime = glutGet(GLUT_ELAPSED_TIME);
	static long loops = 0;
	static GLfloat fps = 0.0f;

	int newTime = glutGet(GLUT_ELAPSED_TIME);

	if (newTime - lastTime > 100)
	{
		float newFPS = (float)loops / float(newTime - lastTime) * 1000.0f;
		fps = (fps + newFPS) / 2.0f;

		char title[80];
		sprintf_s(title, "OpenGL demo - %f", fps);

		glutSetWindowTitle(title);

		lastTime = newTime;

		loops = 0;
	}

	loops++;
}

GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0, 0, -5.0f);
	glRotatef(cubeRotateX, 1, 0, 0);
	glRotatef(cubeRotateY, 0, 1, 0);
	//Draw cube
	glBegin(GL_QUADS);
		//Top face
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f( 1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f,  1.0f);
		glVertex3f( 1.0f, 1.0f,  1.0f);

		//Bottom face
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f( 1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f( 1.0f, -1.0f, 1.0f);

		//Front face
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f( 1.0f,  1.0f, 1.0f);
		glVertex3f(-1.0f,  1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f( 1.0f, -1.0f, 1.0f);

		//Back face
		glColor3f(1.0f, 0.5f, 0.0f);
		glVertex3f( 1.0f,  1.0f, -1.0f);
		glVertex3f(-1.0f,  1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f( 1.0f, -1.0f, -1.0f);

		//Left face
		glColor3f(0.0f, 1.0f, 0.5f);
		glVertex3f(-1.0f, 1.0f,  1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f,-1.0f, -1.0f);
		glVertex3f(-1.0f,-1.0f,  1.0f);

		//Right face
		glColor3f(0.5f, 0.0f, 1.0f);
		glVertex3f( 1.0f,  1.0f,  1.0f);
		glVertex3f( 1.0f,  1.0f, -1.0f);
		glVertex3f( 1.0f, -1.0f, -1.0f);
		glVertex3f( 1.0f, -1.0f,  1.0f);
	glEnd();

	glFlush();

	//This line is MODIFIED in other window interfaces
	glutSwapBuffers();

	displayFPS();
}

GLboolean checkKeys(GLvoid)
{
	const GLfloat speed = 1.0f;

	if (keys[GLUT_KEY_ESCAPE])
	{
		return true;
	}

	if (keys[GLUT_KEY_L])
	{
		cubeRotateY -= speed;
	}

	if (keys[GLUT_KEY_R])
	{
		cubeRotateY += speed;
	}
	if (keys[GLUT_KEY_U])
	{
		cubeRotateX -= speed;
	}
	if (keys[GLUT_KEY_D])
	{
		cubeRotateX += speed;
	}
	return false;
}

GLvoid timerLoop(int value)
{
	if (checkKeys())
	{
		exit(0);
	}

	glutPostRedisplay();

	glutTimerFunc(1, timerLoop, 0);
}


GLvoid keyboardCB(unsigned char key, int x, int y)
{
	keys[key] = true;
}

GLvoid keyboardUpCB(unsigned char key, int x, int y)
{
	keys[key] = false;
}

GLvoid keyboardSpecialCB(unsigned char key, int x, int y)
{
	keys[key] = true;
}

GLvoid keyboardSpecialUpCB(unsigned char key, int x, int y)
{
	keys[key] = false;
}

int main(int argc, char* argv[]) {

	//Initialize GLUT
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE);

	int windowID = glutCreateWindow("OpenGL GLUT");
	glutReshapeWindow(windowWidth, windowHeight);

	initGL(windowWidth, windowHeight);
	glutDisplayFunc(drawScene);

	glutKeyboardFunc(keyboardCB);
	glutKeyboardUpFunc(keyboardUpCB);
	glutKeyboardFunc(keyboardSpecialCB);
	glutKeyboardUpFunc(keyboardSpecialUpCB);

	glutTimerFunc(1, timerLoop, 0);

	glutMainLoop();

	//It never gets here
	return 0;
}