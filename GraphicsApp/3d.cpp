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

typedef struct polygon_struct
{
	point vertices[20];
	int nVertices;
};

typedef enum DrawMode
{
	line,
	circle,
	ellipse,
	parabola,
	polygon
};

line_struct line_coords;
circle_struct circle_coords;
ellipse_struct ellip;
parabola_struct parab;
polygon_struct poly;

int drawMode = line;
float gColor[3] = { 0, 1, 0 };

void getRGB()
{
	MessageBox(nullptr, TEXT("Please enter the parameters into the console."), TEXT("Enter parameters"), MB_OK);
	cout << "Plese use the [0...1] scale";
	cout << "Enter Red value: ";
	cin >> gColor[0];
	cout << "Enter Green value: ";
	cin >> gColor[1];
	cout << "Enter Blue value: ";
	cin >> gColor[2];
}

void getCMYK()
{
	double cyan, magenta, yellow, black;
	MessageBox(nullptr, TEXT("Please enter the parameters into the console."), TEXT("Enter parameters"), MB_OK);
	cout << "Plese use the [0...1] scale\n";
	cout << "Enter Cyan value: ";
	cin >> cyan;
	cout << "Enter Magenta value: ";
	cin >> magenta;
	cout << "Enter Yellow value: ";
	cin >> yellow;
	cout << "Enter Key(Black) value: ";
	cin >> black;

	gColor[0] = 1 - min(1, cyan * (1 - black) + black);
	gColor[1] = 1 - min(1, magenta * (1 - black) + black);
	gColor[2] = 1 - min(1, yellow * (1 - black) + black);
}

void getHSV()
{
	double hue, saturation, value, r, g, b;
	MessageBox(nullptr, TEXT("Please enter the parameters into the console."), TEXT("Enter parameters"), MB_OK);
	cout << "Enter Hue value ([0, 360]): ";
	cin >> hue;
	cout << "Enter Saturation value ([0, 1]): ";
	cin >> saturation;
	cout << "Enter Value ([0, 1]): ";
	cin >> value;

	double chroma = (value * saturation);
	double huePrime = hue / 60;

	double X = chroma * (1 - abs((int(huePrime) % 2) - 1));
	if (huePrime >= 0 && huePrime <= 1)
	{
		r = chroma;
		g = X;
		b = 0;
	}
	else if (huePrime > 1 && huePrime <= 2)
	{
		r = X;
		g = chroma;
		b = 0;
	}
	else if (huePrime > 2 && huePrime <= 3)
	{
		r = 0;
		g = chroma;
		b = X;
	}
	else if (huePrime > 3 && huePrime <= 4)
	{
		r = 0;
		g = X;
		b = chroma;
	}
	else if (huePrime > 4 && huePrime <= 5)
	{
		r = X;
		g = 0;
		b = chroma;
	}
	else if (huePrime > 5 && huePrime <= 6)
	{
		r = chroma;
		g = 0;
		b = X;
	}
	else
	{
		r = 0;
		g = 0;
		b = 0;
	}
	double m = value - chroma;
	gColor[0] = r + m;
	gColor[1] = g + m;
	gColor[2] = b + m;
}

void colorMenuFunc(int val)
{
	switch (val)
	{
	case 0:
		getRGB();
		break;
	case 1:
		getCMYK();
		break;
	case 2:
		getHSV();
		break;
	}
	display();
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

void getPolygonData()
{
	MessageBox(nullptr, TEXT("Please enter the parameters into the console."), TEXT("Enter parameters"), MB_OK);
	cout << "Enter the number of vertices of polygon (Between 3 and 20): ";
	cin >> poly.nVertices;

	for (int i = 0; i < poly.nVertices; i++)
	{
		cout << "Enter x coordinate of vertex " << i+1 << ": ";
		cin >> poly.vertices[i].x;
		cout << "Enter y coordinate of vertex " << i+1 << ": ";
		cin >> poly.vertices[i].y;
		cout << "Enter z coordinate of vertex " << i+1 << ": ";
		cin >> poly.vertices[i].z;
	}
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
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i <= 300; i++)
	{
		double angle = 2 * pi *  i / 300;
		double x = radius * cos(angle);
		double y = radius * sin(angle);
		glVertex3d(x + circle_coords.center.x, y + circle_coords.center.y, circle_coords.center.z);
	}
	glEnd();

}

void drawEllipse()
{
	glColor3fv(gColor);

	glBegin(GL_LINE_LOOP);
	for (GLfloat theta = 0; theta <= 360; theta += 1) {
		double x = ellip.center.x + (ellip.rx * cos(theta));
		double y = ellip.center.y + (ellip.ry * sin(theta));
		glVertex3d(x, y, 0);
	}
	glEnd();
}

void drawParabola()
{
	glColor3fv(gColor);

	glBegin(GL_LINE_LOOP);
	for (GLfloat x = parab.xMin; x <= parab.xMax; x += (parab.xMax - parab.xMin)/250)
	{
		double y = x * x;
		glVertex3d(parab.center.x + x, parab.center.y + y, 0.5);
	}
	glEnd();
}

void drawPolygon()
{
	glColor3fv(gColor);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < poly.nVertices-1; i++)
	{
		glVertex3d(poly.vertices[i].x, poly.vertices[i].y, poly.vertices[i].z);
		glVertex3d(poly.vertices[i+1].x, poly.vertices[i+1].y, poly.vertices[i+1].z);
	}
	glEnd();
}

void getScaleParameters()
{
	double xScale, yScale, zScale;
	MessageBox(nullptr, TEXT("Please enter the parameters into the console."), TEXT("Enter parameters"), MB_OK);
	cout << "Enter x scale value: ";
	cin >> xScale;
	cout << "Enter y scale value: ";
	cin >> yScale;
	cout << "Enter z scale value: ";
	cin >> zScale;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glScaled(xScale, yScale, zScale);

	display();

	glFlush();
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
	case 2:
		drawMode = ellipse;
		getEllipseData();
		break;
	case 3:
		drawMode = parabola;
		getParabolaData();
		break;
	case 4:
		drawMode = polygon;
		getPolygonData();
	default:
		break;
	}
}

void transformMenuFunc(int val)
{
	switch (val)
	{
	case 0:
		getScaleParameters();
	}

}

void mainMenuFunc(int val)
{

}

void createMenu()
{
	int colorMenu = glutCreateMenu(colorMenuFunc);
	glutAddMenuEntry("RGB", 0);
	glutAddMenuEntry("CMYK", 1);
	glutAddMenuEntry("HSV", 2);

	int shapeMenu = glutCreateMenu(shapeMenuFunc);
	glutAddMenuEntry("Line", 0);
	glutAddMenuEntry("Circle", 1);
	glutAddMenuEntry("Ellipse", 2);
	glutAddMenuEntry("Parabola", 3);
	glutAddMenuEntry("Polygon", 4);

	int transformMenu = glutCreateMenu(transformMenuFunc);
	glutAddMenuEntry("Scale", 0);

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
	case '+':
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glTranslated(0, 0, 0.1);

		display();

		glFlush();
		break;
	}
	case '-':
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glTranslated(0, 0, -0.1);

		display();

		glFlush();
		break;
	}
	}

}


void translateObjects(int key, int x, int y)
{


	switch (key)
	{
	case GLUT_KEY_UP:
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glTranslated(0, -0.1, 0);

		display();

		glFlush();
		break;
	}
	case GLUT_KEY_DOWN:
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glTranslated(0, 0.1, 0);

		display();

		glFlush();
		break;
	}
	case GLUT_KEY_RIGHT:
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glTranslated(0.1, 0, 0);

		display();

		glFlush();
		break;
	}
	case GLUT_KEY_LEFT:
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glTranslated(-0.1, 0, 0);

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
	case ellipse:
		drawEllipse();
		break;
	case parabola:
		drawParabola();
		break;
	case polygon:
		drawPolygon();
		break;
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
	glutSpecialFunc(translateObjects);
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