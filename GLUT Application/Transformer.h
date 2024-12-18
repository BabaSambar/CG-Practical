#pragma once
#include <Windows.h>
#include <freeglut.h>
#include <gl/GLU.h>
#include <gl/GL.h>
#include <vector>
#include <iostream>
#include <queue>
#include <math.h>


class Transformer
{
public:
	virtual std::vector<std::vector<double>> applyTransform(std::vector<std::vector<double>> inputMatrix);
	virtual std::vector<std::vector<double>> matrixMultiply(std::vector<std::vector<double>>& mat1, std::vector<std::vector<double>>& mat2);
	virtual void displayMatrix(std::vector<std::vector<double>> data);
protected:
	std::queue<std::vector<std::vector<double>>> mTransformQueue;
};

class Transform2D : public Transformer
{
public:
	Transform2D(std::vector<std::vector<double>>& data);
	void addTranslation(double tx, double ty);
	void addScaling(double sx, double sy, double xf=0, double yf=0);
	void addRotation(double theta, double xr=0, double yr=0);
};

class Transform3D: public Transformer
{
public:
	Transform3D();
	void addTranslation(double tx, double ty, double tz);
	void addScaling(double sx, double sy, double sz, double xf=0, double yf=0, double zf=0);
	void addRotation(double theta, char axis='x', double xr = 0, double yr = 0, double zr = 0);
};
