#pragma once

#include <Windows.h>
#include <freeglut.h>
#include <gl/GLU.h>
#include <gl/GL.h>
#include <vector>
#include <iostream>
#include <queue>
#include <math.h>

/*
DIRECTIONS FOR USE:
	Initialize Pattern object with window width and height
	Set input pattern
	Call display function
*/

class Pattern
{
public:
	// Name of pattern corresponds to index of data stored
	enum PATTERN
	{
		ONE = 1,
		TWO,
		THREE,
		FOUR
	};

	Pattern(int WINDOW_WIDTH, int WINDOW_HEIGHT, int DELAY);

	void setInputData(PATTERN pattern);
	void display(void);

private:
	void drawLine(int x1, int y1, int x2, int y2);
	void drawCircle(int xc, int yc, int r);
	float roundFloat(float x);

	PATTERN mSelectedPattern = ONE;
	int WINDOW_WIDTH, WINDOW_HEIGHT, DELAY;

	std::vector<std::vector<int>> mData = { 4, std::vector<int>()};

};

