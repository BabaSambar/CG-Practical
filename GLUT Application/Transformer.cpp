#include "Transformer.h"

// Base class: Apply transforms stored in queue on given points
std::vector<std::vector<double>> Transformer::applyTransform(std::vector<std::vector<double>> inputMatrix)
{
	std::vector<std::vector<double>> data = mTransformQueue.front();
	mTransformQueue.pop();
	while (mTransformQueue.size() != 0)
	{
		data = matrixMultiply(mTransformQueue.front(), data);
		mTransformQueue.pop();
	}
	std::cout << "Calculated transforms." << std::endl;
	return data;
}
// Base class: Matrix multiplication function
std::vector<std::vector<double>> Transformer::matrixMultiply(std::vector<std::vector<double>>& mat1, std::vector<std::vector<double>>& mat2)
{
	int rows1 = mat1.size();
	int cols1 = mat1[0].size();
	int rows2 = mat2.size();
	int cols2 = mat2[0].size();
	std::vector<std::vector<double>> result(rows1, std::vector<double>(cols2, 0.0));
	for (int i = 0; i < rows1; ++i) 
	{
		for (int j = 0; j < cols2; ++j)
		{
			for (int k = 0; k < cols1; ++k)
			{
				result[i][j] += mat1[i][k] * mat2[k][j];
			}
		}
	}
	return result;
}
// Base class: For debugging, function to display matrix
void Transformer::displayMatrix(std::vector<std::vector<double>> data)
{
	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; j < data[0].size(); j++) {
			std::cout << data[i][j] << " ";
		}
		std::cout << std::endl;	
	}
}


// 2D Transforms: Push identity matrix in queue
Transform2D::Transform2D(std::vector<std::vector<double>>& data)
{
	mTransformQueue.push(data);
}
// 2D Transforms: Push translation matrix in queue
void Transform2D::addTranslation(double tx, double ty)
{
	std::vector<std::vector<double>> data = {
		{1, 0, tx},
		{0, 1, ty},
		{0, 0, 1}
	};
	mTransformQueue.push(data);
	std::cout << "Added translation transform." << std::endl;
}
// 2D Transforms: Push scaling matrix in queue
void Transform2D::addScaling(double sx, double sy, double xf, double yf)
{
	std::vector<std::vector<double>> data = {
		{sx, 0, xf * (1 - sx)},
		{0, sy, yf * (1 - sy)},
		{0, 0, 1}
	};
	mTransformQueue.push(data);
	std::cout << "Added scaling transform." << std::endl;
}
// 2D Transforms: Push rotation matrix in queue
void Transform2D::addRotation(double theta, double xr, double yr)
{   
	theta = theta * 3.1415926535 / 180;
	double c = cos(theta);
	double s = sin(theta);
	std::vector<std::vector<double>> data = {
		{c, -s, (xr * (1 - c)) + (yr * s)},
		{s, c, (yr * (1 - c)) - (xr * s)},
		{0, 0, 1}
	};
	mTransformQueue.push(data);
	std::cout << "Added rotation transform." << std::endl;
}


// 3D Transforms: Push identity matrix in queue
Transform3D::Transform3D()
{
	mTransformQueue.push({
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
		});
}
// 3D Transforms: Push translation matrix in queue
void Transform3D::addTranslation(double tx, double ty, double tz)
{
	std::vector<std::vector<double>> data = {
		{1, 0, 0, tx},
		{0, 1, 0, ty},
		{0, 0, 1, tz},
		{0, 0, 0, 1}
	};
	mTransformQueue.push(data);
	std::cout << "Added translation transform." << std::endl;
}
// 3D Transforms: Push scaling matrix in queue
void Transform3D::addScaling(double sx, double sy, double sz, double xf, double yf, double zf)
{
	std::vector<std::vector<double>> data = {
		{sx, 0, 0, xf * (1 - sx)},
		{0, sy, 0, yf * (1 - sy)},
		{0, 0, sz, zf * (1 - sz)},
		{0, 0, 0, 1}
	};
	mTransformQueue.push(data);
	std::cout << "Added scaling transform." << std::endl;
}
// 3D Transforms: Push rotation matrix in queue
void Transform3D::addRotation(double theta, char axis, double xr, double yr, double zr)
{
	theta = theta * 3.1415926535 / 180;
	double c = cos(theta);
	double s = sin(theta);
	std::vector<std::vector<double>> data;
	switch (axis)
	{
	case 'x':
		data = {
			{1, 0, 0, 0},
			{0, c, -s, 0},
			{0, s, c, 0},
			{0, 0, 0, 1}
		};
	case 'y':
		data = {
			{c, 0, s, 0},
			{0, 1, 0, 0},
			{-s, 0, c, 0},
			{0, 0, 0, 1}
		};
	case 'z':
		data = {
			{c, -s, 0, 0},
			{s, c, 0, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 1}
		};
	default:
		std::cout << "Invalid rotation axis. Enter either x, y, z or leave blank for x axis." << std::endl;
		return;
	}
	mTransformQueue.push(data);
	std::cout << "Added rotation transform." << std::endl;
}
