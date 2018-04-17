#include<windows.h>
#include<gl/gl.h>
#include<gl/glu.h>
#include<gl/glut.h>
#include <iostream>
#include <math.h>

using namespace std;

const double pi = 3.14159265358979323846;

typedef enum state {
	waitingForClick,
	clickedOnce,
};

typedef struct point
{
	int x;
	int y;
} point;

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

point line_coords[2];
point circle_coords[2];

ellipse_struct ellip;
parabola_struct parab;

int drawMode = line;
int gState = waitingForClick;
bool lineisvalid = false;
int gHeight;
float gColor[3] = { 0, 1, 0 };

void drawLine()
{
	glColor3fv(gColor);
	glBegin(GL_LINES);
	glVertex2i(line_coords[0].x, gHeight - line_coords[0].y);
	glVertex2i(line_coords[1].x, gHeight - line_coords[1].y);
	//cout << line_coords[1].x << "," << line_coords[1].y;
	glEnd();
}

void drawCircle()
{
	glColor3fv(gColor);

	double radius = sqrt(pow(circle_coords[1].y - circle_coords[0].y, 2) + pow(circle_coords[1].x - circle_coords[0].x, 2));
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i <= 300; i++)
	{
		double angle = 2 * pi *  i / 300;
		double x = radius * cos(angle);
		double y = radius * sin(angle);
		glVertex2d(x + circle_coords[0].x, y + circle_coords[0].y);
	}
	glEnd();

}

void drawEllipse()
{
	glColor3fv(gColor);

	glBegin(GL_POINTS);
	for (GLfloat theta = 0; theta <= 3600; theta += 1) {
		double x = ellip.center.x + (ellip.rx * cos(theta));
		double y = ellip.center.y + (ellip.ry * sin(theta));
		glVertex2d(x, y);
	}
	glEnd();
}

void drawParabola()
{
	glColor3fv(gColor);

	glBegin(GL_POINTS);
	for (GLfloat x = parab.xMin; x <= parab.xMax; x += 0.05) {
		double y = x * x;
		glVertex2d(parab.center.x + x, parab.center.y + y);
	}
	glEnd();
}

void getParabolaData()
{
	MessageBox(nullptr, TEXT("Please enter the parameters into the console."), TEXT("Enter parameters"), MB_OK);
	cout << "Enter x coordinate of center: ";
	cin >> parab.center.x;
	cout << "Enter y coordinate of center:";
	cin >> parab.center.y;
	cout << "Enter minimum X:";
	cin >> parab.xMin;
	cout << "Enter maximum X:";
	cin >> parab.xMax;
}

void getEllipseData()
{
	MessageBox(nullptr, TEXT("Please enter the parameters into the console."), TEXT("Enter parameters"), MB_OK);
	cout << "Enter x coordinate of center: ";
	cin >> ellip.center.x;
	cout << "Enter y coordinate of center:";
	cin >> ellip.center.y;
	cout << "Enter rx:";
	cin >> ellip.rx;
	cout << "Enter ry:";
	cin >> ellip.ry;
}

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
	case ellipse:
		drawEllipse();
		break;
	case parabola:
		drawParabola();
		break;
	}
	glutSwapBuffers();
}

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

void shapeMenuFunc(int val)
{
	gState = waitingForClick;
	switch (val)
	{
	case 0:
		drawMode = line;
		break;
	case 1:
		drawMode = circle;
		break;
	case 2:
		drawMode = ellipse;
		getEllipseData();
		break;
	case 3:
		drawMode = parabola;
		getParabolaData();
		break;
	default:
		break;
	}
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

	int mainMenu = glutCreateMenu(mainMenuFunc);
	glutAddSubMenu("Color", colorMenu);
	glutAddSubMenu("Shapes", shapeMenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void init()
{
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1, 1.0, -1, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	createMenu();
}

void reshape(int width, int height)
{
	gHeight = height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, (GLdouble)width, 0.0, (GLdouble)height,
		-1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
}

void mouseclick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		switch (drawMode)
		{

		case circle:

			switch (gState)
			{
			case waitingForClick:
				circle_coords[0].x = x;
				circle_coords[0].y = y;
				circle_coords[1].x = x;
				circle_coords[1].y = y;
				gState++;
				break;
			case clickedOnce:
				circle_coords[1].x = x;
				circle_coords[1].y = y;
				gState = waitingForClick;
				break;
			}
			break;

		case line:

			switch (gState)
			{

			case waitingForClick:
				line_coords[0].x = x;
				line_coords[0].y = y;
				line_coords[1].x = x;
				line_coords[1].y = y;
				gState++;
				break;
			case clickedOnce:
				line_coords[1].x = x;
				line_coords[1].y = y;
				gState = waitingForClick;
				break;
			}
			break;
		}
	}
	glutPostRedisplay();
}

void mousedrag(int x, int y)
{
	if (gState == clickedOnce)
	{
		switch (drawMode)
		{
		case line:
			line_coords[1].x = x;
			line_coords[1].y = y;
			break;
		case circle:
			circle_coords[1].x = x;
			circle_coords[1].y = y;
			break;
		}
	}
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1000, 800);
	glutCreateWindow("My Drawing App");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMouseFunc(mouseclick);
	glutPassiveMotionFunc(mousedrag);

	init();
	glutMainLoop();
	return 0;
}