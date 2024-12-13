#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <iostream>
#include <freeglut.h>

using namespace std;

#include "Transformer.h"
#include "Pattern.h"

const int WINDOW_HEIGHT = 600;
const int WINDOW_WIDTH = 800;
const int DELAY = 1;

float roundFloat(float x)
{
	return (int)(x + 0.5);
}

void drawLine(int x1, int y1, int x2, int y2)
{
	int dx = x2 - x1, dy = y2 - y1, steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	int xinc = dx / (float)steps, yinc = dy / (float)steps;
	float x = x1, y = y1;

	glBegin(GL_POINTS);
	glVertex2d(x1, y1);
	for (int i = 0; i < steps; i++)
	{
		glVertex2d(roundFloat(x), roundFloat(y));
		x += xinc;
		y += yinc;
		glEnd();
		glFlush();
		Sleep(DELAY);
		glBegin(GL_POINTS);
	}
	glEnd();
	glFlush();
}

void drawCircle(int xc, int yc, int r)
{
	int x = 0, y = r;
	int d = 3 - 2 * r;

	while (y >= x) {
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
		glFlush();
		Sleep(DELAY / 10);
		x++;
		if (d > 0) {
			y--;
			d += 4 * (x - y) + 10;
		}
		else {
			d += 4 * x + 6;
		}
		glEnd();
	}
	glFlush();
}

void display(void)
{

	Transformer::Transform2D Transformer;
	Transformer.addTransformScale(1.2, 1.2, 0, 0);
	Transformer.addTransformTranslate(300, 100);
	

	vector<vector<double>> data = {
		{0, 300, 300, 0},
		{0, 0, 300, 300},
		{1, 1, 1, 1}
	};
	vector<vector<double>> answer = Transformer.applyTransform(data);
	Transformer.displayMatrix(answer);

	// Draw original and non transformed shapes
	for (int i = 0; i < data[0].size() - 1; i++)
	{
		drawLine(data[0][i], data[1][i], data[0][i + 1], data[1][i + 1]);
	}
	drawLine(data[0][data[0].size() - 1], data[1][data[0].size() - 1], data[0][0],data[1][0]);
	for (int i = 0; i < answer[0].size() - 1; i++)
	{
		drawLine(answer[0][i], answer[1][i], answer[0][i + 1], answer[1][i + 1]);
	}
	drawLine(answer[0][answer[0].size() - 1], answer[1][answer[0].size() - 1], answer[0][0], answer[1][0]);


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