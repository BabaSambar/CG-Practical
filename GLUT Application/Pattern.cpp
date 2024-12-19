#include "Pattern.h"


Pattern::Pattern(int WINDOW_WIDTH, int WINDOW_HEIGHT, int DELAY)
{
	this->WINDOW_WIDTH = WINDOW_WIDTH;
	this->WINDOW_HEIGHT = WINDOW_HEIGHT;
	mData.push_back({ WINDOW_WIDTH, WINDOW_HEIGHT });
	this->DELAY = DELAY;
}

enum CohenSutherlandStateCode
{
	INSIDE = 0,
	LEFT = 1,
	RIGHT = 2,
	BOTTOM = 4,
	TOP = 8
};

float Pattern::roundFloat(float x)
{
	return (int)(x + 0.5);
}

void Pattern::drawLine(int x1, int y1, int x2, int y2, int DELAY = 1)
{
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

void Pattern::drawCircle(int xc, int yc, int r, int DELAY = 1)
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


void Pattern::setInputData(PATTERN pattern)
{
	std::cout << "Enter data for pattern " << static_cast<int>(pattern) << " (" << mData[pattern].size() << " entries)." << std::endl;

	switch (pattern)
	{
	case Pattern::ONE:
	{
		// 4 data entries
		mData[ONE] = std::vector<int>(4);
		for (int i = 0; i < mData[ONE].size(); i++)
			std::cin >> mData[ONE][i];
		this->mSelectedPattern = ONE;
		break;
	}	
	case Pattern::TWO: 
	{
		// 6 data entries
		mData[TWO] = std::vector<int>(6);
		for (int i = 0; i < mData[TWO].size(); i++)
			std::cin >> mData[TWO][i];
		this->mSelectedPattern = TWO;
		break;
	}
	case Pattern::FRACTAL: 
	{
		// 2 data entries
		mData[FRACTAL] = std::vector<int>(2);
		for (int i = 0; i < mData[FRACTAL].size(); i++)
			std::cin >> mData[FRACTAL][i];
		this->mSelectedPattern = FRACTAL;
		break;
	}
	case Pattern::COHENSUTHERLAND:
	{
		// 4 data entries, hard coded rectangle bounds
		mData[COHENSUTHERLAND] = {100, 100, 700, 500};
		for (int i = 0; i < 4; i++)
		{
			int data;
			std::cin >> data;
			mData[COHENSUTHERLAND].push_back(data);
		}
		this->mSelectedPattern = COHENSUTHERLAND;
		break;
	}
	default: 
	{
		break;
	}
	}
}


void move(int j, int h, int& x, int& y)
{
	if (j == 1)
		y -= h;
	else if (j == 2)
		x += h;
	else if (j == 3)
		y += h;
	else if (j == 4)
		x -= h;
}

void hilbert(int level, int dir, int size, int& x, int& y)
{
	if (level == 0) return;

	hilbert(level - 1, 3 - dir, size, x, y);
	int newX = x;
	int newY = y;
	move(dir, size, newX, newY);
	Pattern::drawLine(x, y, newX, newY);
	hilbert(level - 1, dir, size, newX, newY);
	move(3 - dir, size, newX, newY);
	Pattern::drawLine(x, y, newX, newY);
	hilbert(level - 1, dir, size, newX, newY);
	move(dir, size, newX, newY);
	Pattern::drawLine(x, y, newX, newY);
	hilbert(level - 1, 3 - dir, size, newX, newY);
}

void drawHilbert(int level, int size)
{
	int x = size / 2;
	int y = size / 2;
	hilbert(level, 1, size / (1 << level), x, y);
}


int computeCode(int x, int y, std::vector<std::vector<int>>& mData)
{
	int xmin = mData[Pattern::COHENSUTHERLAND][0];
	int ymin = mData[Pattern::COHENSUTHERLAND][1];
	int xmax = mData[Pattern::COHENSUTHERLAND][2];
	int ymax = mData[Pattern::COHENSUTHERLAND][3];
	int code = INSIDE;
	if (x < xmin) code |= LEFT;
	else if (x > xmax) code |= RIGHT;
	if (y < ymin) code |= BOTTOM;
	else if (y > ymax) code |= TOP;
	return code;
}

void cohenSutherland(std::vector<std::vector<int>>& mData)
{
	int xmin = mData[Pattern::COHENSUTHERLAND][0];
	int ymin = mData[Pattern::COHENSUTHERLAND][1];
	int xmax = mData[Pattern::COHENSUTHERLAND][2];
	int ymax = mData[Pattern::COHENSUTHERLAND][3];
	int x1 = mData[Pattern::COHENSUTHERLAND][4];
	int y1 = mData[Pattern::COHENSUTHERLAND][5];
	int x2 = mData[Pattern::COHENSUTHERLAND][6];
	int y2 = mData[Pattern::COHENSUTHERLAND][7];

	int code1 = computeCode(x1, y1, mData);
	int code2 = computeCode(x2, y2, mData);

	bool accept = true;
	while (true)
	{
		if (code1 == 0 && code2 == 0)
		{
			accept = true;
			break;
		}
		else if (code1 & code2)
			break;
		else
		{
			int code_out;
			int x, y;
			if (code1 != 0) code_out = code1;
			else code_out = code2;

			if (code_out & TOP)
			{
				x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
				y = ymax;
			}
			else if (code_out & BOTTOM) {
				x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
				y = ymin;
			}
			else if (code_out & RIGHT) {
				y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
				x = xmax;
			}
			else if (code_out & LEFT) {
				y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
				x = xmin;
			}
			
			if (code_out == code1)
			{
				x1 = x;
				y1 = y;
				code1 = computeCode(x1, y1, mData);
			}
			else
			{
				x2 = x;
				y2 = y;
				code2 = computeCode(x2, y2, mData);
			}
		}
	}
	if (accept)
	{
		glColor3f(0.0, 1.0, 0.0);
		Pattern::drawLine(x1, y1, x2, y2);
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
		break;
	}
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

		break;
	}
	case Pattern::FRACTAL: 
	{
		int depth = mData[FRACTAL][0];
		int size = mData[FRACTAL][1];

		drawHilbert(depth, size);
		glFlush();
		break;
	}
	case Pattern::COHENSUTHERLAND:
	{	
		// Draw the boundary rectangle
		int xmin = mData[Pattern::COHENSUTHERLAND][0];
		int ymin = mData[Pattern::COHENSUTHERLAND][1];
		int xmax = mData[Pattern::COHENSUTHERLAND][2];
		int ymax = mData[Pattern::COHENSUTHERLAND][3];
		drawLine(xmin, ymax, xmax, ymax);
		drawLine(xmax, ymax, xmax, ymin);
		drawLine(xmax, ymin, xmin, ymin);
		drawLine(xmin, ymin, xmin, ymax);

		// Draw original lines
		drawLine(mData[COHENSUTHERLAND][4], mData[COHENSUTHERLAND][5], mData[COHENSUTHERLAND][6], mData[COHENSUTHERLAND][7]);
		// Cohen Sutherland clipping
		cohenSutherland(mData);
		break;
	}
	default: 
	{
		break;
	}
	}
}
