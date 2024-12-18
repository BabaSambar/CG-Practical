#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <iostream>
#include <freeglut.h>

//#include "Transformer.h"
#include "Pattern.h"

const int WINDOW_HEIGHT = 600;
const int WINDOW_WIDTH = 800;
const int DELAY = 1;

using namespace std;

float roundFloat(float x)
{
	return (int)(x + 0.5);
}

void drawLine(int x1, int y1, int x2, int y2, int DELAY = 1)
{
	std::cout << ">>" << x1 << ", " << y1 << ", " << x2 << ", " << y2 << "\n";
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int sx = (x1 < x2) ? 1 : -1;
	int sy = (y1 < y2) ? 1 : -1;
	int err = dx - dy;

	while (true)
	{
		glBegin(GL_POINTS);
		glVertex2i(x1, y1);
		glEnd();
		Sleep(DELAY);
		glFlush();
		if (x1 == x2 && y1 == y2)
			break;

		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x1 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y1 += sy;
		}
	}

	glFlush();
}

void drawCircle(int xc, int yc, int r, int DELAY = 1)
{
	int x = 0, y = r;
	int d = 3 - 2 * r;

	while (x <= y)
	{
		glBegin(GL_POINTS);
		glVertex2i(xc + x, yc + y);
		glVertex2i(xc - x, yc + y);
		glVertex2i(xc + x, yc - y);
		glVertex2i(xc - x, yc - y);
		glVertex2i(xc + y, yc + x);
		glVertex2i(xc - y, yc + x);
		glVertex2i(xc + y, yc - x);
		glVertex2i(xc - y, yc - x);
		glEnd();
		Sleep(DELAY);
		glFlush();

		if (d < 0)
			d += 4 * x + 6;
		else {
			d += 4 * (x - y) + 10;
			y--;
		}
		x++;
	}
	glFlush();
}


void move(int j, int h, int& x, int& y, int& x1, int& y1)
{
	int newX = x;
	int newY = y;

	if (j == 1)
	{
		newY -= h;
	}
	else if (j == 2)
	{
		newX += h;
	}

	else if (j == 3)
	{
		newY += h;
	}

	else if (j == 4)
	{
		newX -= h;
	}

	drawLine(x1, y1, newX, newY);
	x1 = newX;
	y1 = newY;
	x = newX;
	y = newY;
}

void display(void)
{
	/*
	// TRANSFORMS
	vector<vector<double>> data =
	{
		{0, 0, 40},
		{0, 40, 40},
		{1, 1, 1}
	};
	Transform2D T(data);
	// Add transforms
	// ...
	data = T.applyTransform(data);

	for (int i=0; i<data[0].size()-1; i++)
	{
		drawLine(data[0][i], data[1][i], data[0][i + 1], data[1][i + 1]);
	}
	drawLine(data[0][0], data[1][0], data[0][data[0].size() - 1], data[1][data[0].size() - 1]);
	*/

	// PATTERNS
	Pattern p(WINDOW_WIDTH, WINDOW_HEIGHT, DELAY);
	p.setInputData(Pattern::COHENSUTHERLAND);
	p.display();

	/*
	int xStart = 0;
	int yStart = 0;
	int depth = 5;
	int stepsize = 600 / (1 << depth);
	drawHilbert(depth, stepsize);
	*/


	glFlush();
}


int main(int argc, char** argv)
{
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Window");
	glClearColor(0.0, 0.0, 0.0, 0.0); // Set background color to black
	glMatrixMode(GL_PROJECTION);      // Set projection
	glLoadIdentity();
	gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT);
	
	glutDisplayFunc(display);
	
	glutMainLoop();



	return 0;
	
}