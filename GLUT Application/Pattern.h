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
		FRACTAL,
		COHENSUTHERLAND
	};

	Pattern(int WINDOW_WIDTH, int WINDOW_HEIGHT, int DELAY);

	void setInputData(PATTERN pattern);
	void display(void);
	static void drawLine(int x1, int y1, int x2, int y2, int DELAY);
	static void drawCircle(int xc, int yc, int r, int DELAY);
	float roundFloat(float x);

private:

	PATTERN mSelectedPattern = ONE;
	int WINDOW_WIDTH, WINDOW_HEIGHT, DELAY;

	std::vector<std::vector<int>> mData = { 4, std::vector<int>()};

};

