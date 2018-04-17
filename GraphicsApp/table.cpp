//#include<windows.h>
//#include<gl/gl.h>
//#include<gl/glu.h>
//#include<gl/glut.h>
//#include<math.h>
//void set3D();
//void displaytableleg(float x, float y, float z);
//void drawScene()
//{
//
//	displaytableleg(0.5, 0.0, 0.5);
//	displaytableleg(-0.5, 0.0, -0.5);
//	displaytableleg(0.5, 0.0, -0.5);
//	displaytableleg(-0.5, 0.0, 0.5);
//
//	glPushMatrix();
//	glTranslated(0.0, 0.3, 0.0);
//	glScaled(2.2, 0.1, 2.2);
//	glutSolidCube(0.5);
//	glPopMatrix();
//
//	glColor3f(1.0, 0.0, 0.0);
//	glPushMatrix();
//	glTranslated(0.0, 0.6, 0.0);
//	glutWireTeapot(0.3);
//	glPopMatrix();
//
//
//}
//
//void drawPointKeyboard(unsigned char key, int x, int y)
//{
//
//
//	switch (key)
//	{
//	case 'x':
//	{
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		glRotated(20, 1.0, 0.0, 0.0);
//
//		drawScene();
//
//		glFlush();
//		break;
//	}
//	case 'y':
//	{
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		glRotated(20, 0.0, 1.0, 0.0);
//		drawScene();
//
//		glFlush();
//		break;
//	}
//	case 'z':
//	{
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		glRotated(20, 0.0, 0.0, 1.0);
//
//		drawScene();
//
//		glFlush();
//		break;
//	}
//
//	}
//}
//
//
//void displaytableleg(float x, float y, float z)
//{
//	glColor3f(0.9, 0.9, 0.9);
//	glPushMatrix();
//	glTranslated(x, y, z);
//	glScaled(0.3, 3.0, 0.3);
//	glutSolidCube(0.2);
//	glPopMatrix();
//}
//void display()
//{
//
//	//clear device
//	glClear(GL_COLOR_BUFFER_BIT);
//	glClearColor(0.0, 0.0, 0.0, 0.0);
//	glColor3f(0.9, 0.9, 0.9);
//	set3D();
//	drawScene();
//	glFlush();
//}
//void main(int argc, char** argv)
//{
//	//Initializing the glut
//	glutInit(&argc, argv);
//
//	//Define the display mode
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//
//
//	//create window
//	glutInitWindowSize(600, 600);
//	glutInitWindowPosition(100, 100);
//	glutCreateWindow("first");
//	glutDisplayFunc(display);
//	glutKeyboardFunc(drawPointKeyboard);
//	glutMainLoop();
//}
//void set3D()
//{
//	//set up a view volume
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(30.0, 4 / 3, 0.1, 100);
//	//selecting the camera
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	gluLookAt(2.0, 1.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//}