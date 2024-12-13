#include "Pattern.h"


Pattern::Pattern(int WINDOW_WIDTH, int WINDOW_HEIGHT, int DELAY)
{
	this->WINDOW_WIDTH = WINDOW_WIDTH;
	this->WINDOW_HEIGHT = WINDOW_HEIGHT;
	mData.push_back({ WINDOW_WIDTH, WINDOW_HEIGHT });
	this->DELAY = DELAY;
}

float Pattern::roundFloat(float x)
{
	return (int)(x + 0.5);
}

void Pattern::drawLine(int x1, int y1, int x2, int y2)
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

void Pattern::drawCircle(int xc, int yc, int r)
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


void Pattern::setInputData(PATTERN pattern)
{
	std::cout << "Enter data: " << std::endl;


	switch (pattern)
	{
	case Pattern::ONE:
	{
		mData[ONE] = std::vector<int>(4);
		// 4 data entries
		for (int i = 0; i < 4; i++)
		{
			std::cin >> mData[ONE][i];
		}
	}
		break;
	case Pattern::TWO: 
	{
		mData[TWO] = std::vector<int>(6);
		// 6 data entries
		for (int i = 0; i < 6; i++)
		{
			std::cin >> mData[TWO][i];
		}
	}
		break;
	case Pattern::THREE: {}
		break;
	case Pattern::FOUR: {}
		break;
	default: {}
		break;
	}
}



void Pattern::display(void)
{
	switch (mSelectedPattern)
	{
	case Pattern::ONE:
	{
		int x1 = mData[ONE][0];
		int y1 = mData[ONE][1];
		int x2 = mData[ONE][2];
		int y2 = mData[ONE][3];
		drawLine(x1, y1, x1, y2);
		drawLine(x1, y1, x2, y1);
		drawLine(x2, y1, x2, y2);
		drawLine(x2, y2, x1, y2);

		drawLine(x1, (y1 + y2) / 2, (x1 + x2) / 2, y2);
		drawLine((x1 + x2) / 2, y2, x2, (y1 + y2) / 2);
		drawLine(x2, (y1 + y2) / 2, (x1 + x2) / 2, y1);
		drawLine((x1 + x2) / 2, y1, x1, (y1 + y2) / 2);

		drawCircle((x1 + x2) / 2, (y1 + y2) / 2, sqrt(pow((x2 + x1) / 2 - (x1 + (x1 + x2) / 2) / 2, 2) + pow((y2 + y1) / 2 - ((y1 + y2) / 2 + y2) / 2, 2)));
	}
		break;
	case Pattern::TWO: 
	{
		int x1 = mData[TWO][0];
		int y1 = mData[TWO][1];
		int x2 = mData[TWO][2];
		int y2 = mData[TWO][3];
		int x3 = mData[TWO][4];
		int y3 = mData[TWO][5];

		double m1 = -1 * (static_cast<double>(x3) - x1) / (y3 - y1);
		double m2 = -1 * (static_cast<double>(x2) - x1) / (y2 - y1);
		double xAvg2 = (static_cast<double>(x1) + x2) / 2;
		double xAvg1 = (static_cast<double>(x1) + x3) / 2;
		double yAvg2 = (static_cast<double>(y1) + y2) / 2;
		double yAvg1 = (static_cast<double>(y3) + y1) / 2;

		double x = (yAvg2 + (xAvg2 * m2) - yAvg1 - (xAvg1 * m1)) / (m2 - m1);
		double y = m2 * x + yAvg2 + (xAvg2 * m2);

		double r = sqrt(pow(x1 - x, 2) + pow(y1 - y, 2));

		// Draw triangle
		drawLine(x1, y1, x2, y2);
		drawLine(x2, y2, x3, y3);
		drawLine(x3, y3, x1, y1);
		// Draw circumcircle

		// Draw incircle
	}
		break;
	case Pattern::THREE: {}
		break;
	case Pattern::FOUR: {}
		break;
	default: {}
		break;
	}
}
