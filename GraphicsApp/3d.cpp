#include<windows.h>
#include<gl/gl.h>
#include<gl/glu.h>
#include<gl/glut.h>
#include <iostream>
#include <math.h>

using namespace std;

const double pi = 3.14159265358979323846;

void set3D();
void display();

typedef struct point
{
	float x;
	float y;
	float z;

	void rotate(float theta)
	{
		
	}
} point;

typedef struct line_struct
{
	point start;
	point end;
};

typedef struct circle_struct
{
	point center;
	float radius;
};

typedef struct ellipse_struct
{
	point center;
	double rx;
	double ry;
} ellipse_struct;

typedef struct parabola_struct
{
	point center;
	double xMin;
	double xMax;
};

typedef enum DrawMode
{
	line,
	circle,
	ellipse,
	parabola
};

line_struct line_coords;
circle_struct circle_coords;

ellipse_struct ellip;
parabola_struct parab;

int drawMode = line;
float gColor[3] = { 0, 1, 0 };

void colorMenuFunc(int val)
{
	switch (val)
	{
	case 0:
		gColor[0] = 1;
		gColor[1] = 0;
		gColor[2] = 0;
		break;
	case 1:
		gColor[0] = 0;
		gColor[1] = 1;
		gColor[2] = 0;
		break;
	case 2:
		gColor[0] = 0;
		gColor[1] = 0;
		gColor[2] = 1;
		break;
	}
}

void getLineData()
{
	MessageBox(nullptr, TEXT("Please enter the parameters into the console."), TEXT("Enter parameters"), MB_OK);
	cout << "Enter x coordinate of starting point: ";
	cin >> line_coords.start.x;
	cout << "Enter y coordinate of starting point: ";
	cin >> line_coords.start.y;
	cout << "Enter z coordinate of starting point: ";
	cin >> line_coords.start.z;
	cout << "Enter x coordinate of ending point: ";
	cin >> line_coords.end.x;
	cout << "Enter y coordinate of ending point: ";
	cin >> line_coords.end.y;
	cout << "Enter z coordinate of starting point: ";
	cin >> line_coords.end.z;
}

void getCircleData()
{
	MessageBox(nullptr, TEXT("Please enter the parameters into the console."), TEXT("Enter parameters"), MB_OK);
	cout << "Enter x coordinate of center: ";
	cin >> circle_coords.center.x;
	cout << "Enter y coordinate of center: ";
	cin >> circle_coords.center.y;
	cout << "Enter z coordinate of center: ";
	cin >> circle_coords.center.z;
	cout << "Enter radius: ";
	cin >> circle_coords.radius;
}

void drawLine()
{
	glColor3fv(gColor);
	glBegin(GL_LINES);
	glVertex3d(line_coords.start.x, line_coords.start.y, line_coords.start.z);
	glVertex3d(line_coords.end.x, line_coords.end.y, line_coords.end.z);
	glEnd();
}

void drawCircle()
{
	glColor3fv(gColor);

	double radius = circle_coords.radius;
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= 300; i++)
	{
		double angle = 2 * pi *  i / 300;
		double x = radius * cos(angle);
		double y = radius * sin(angle);
		glVertex3d(x + circle_coords.center.x, y + circle_coords.center.y, circle_coords.center.z);
	}
	glEnd();

}

void shapeMenuFunc(int val)
{
	switch (val)
	{
	case 0:
		drawMode = line;
		getLineData();
		break;
	case 1:
		drawMode = circle;
		getCircleData();
		break;
	//case 2:
	//	drawMode = ellipse;
	//	getEllipseData();
	//	break;
	//case 3:
	//	drawMode = parabola;
	//	getParabolaData();
	//	break;
	//default:
	//	break;
	}
}

void transformMenuFunc(int val)
{

}

void mainMenuFunc(int val)
{

}

void createMenu()
{
	int colorMenu = glutCreateMenu(colorMenuFunc);
	glutAddMenuEntry("Red", 0);
	glutAddMenuEntry("Green", 1);
	glutAddMenuEntry("Blue", 2);

	int shapeMenu = glutCreateMenu(shapeMenuFunc);
	glutAddMenuEntry("Line", 0);
	glutAddMenuEntry("Circle", 1);
	glutAddMenuEntry("Ellipse", 2);
	glutAddMenuEntry("Parabola", 3);

	int transformMenu = glutCreateMenu(transformMenuFunc);
	glutAddMenuEntry("Transform", 0);

	int mainMenu = glutCreateMenu(mainMenuFunc);
	glutAddSubMenu("Color", colorMenu);
	glutAddSubMenu("Shapes", shapeMenu);
	glutAddSubMenu("Transform", transformMenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void drawPointKeyboard(unsigned char key, int x, int y)
{


	switch (key)
	{
	case 'x':
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glRotated(20, 1.0, 0.0, 0.0);

		display();

		glFlush();
		break;
	}
	case 'y':
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glRotated(20, 0.0, 1.0, 0.0);
		display();

		glFlush();
		break;
	}
	case 'z':
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glRotated(20, 0.0, 0.0, 1.0);

		display();

		glFlush();
		break;
	}

	}
}


//void displaytableleg(float x, float y, float z)
//{
//	glColor3f(0.9, 0.9, 0.9);
//	glPushMatrix();
//	glTranslated(x, y, z);
//	glScaled(0.3, 3.0, 0.3);
//	glutSolidCube(0.2);
//	glPopMatrix();
//}
void display()
{

	glClear(GL_COLOR_BUFFER_BIT);
	switch (drawMode)
	{
	case line:
		drawLine();
		break;
	case circle:
		drawCircle();
		break;
	//case ellipse:
	//	drawEllipse();
	//	break;
	//case parabola:
	//	drawParabola();
	//	break;
	}
	glutSwapBuffers();
}




void main(int argc, char** argv)
{
	//Initializing the glut
	glutInit(&argc, argv);

	//Define the display mode
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);


	//create window
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("first");
	glutDisplayFunc(display);
	glutKeyboardFunc(drawPointKeyboard);
	createMenu();
	glutMainLoop();
}
void set3D()
{
	//set up a view volume
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, 4 / 3, 0.1, 100);
	//selecting the camera
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2.0, 1.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}