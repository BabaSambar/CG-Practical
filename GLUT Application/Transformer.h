#pragma once
#include <Windows.h>
#include <freeglut.h>
#include <gl/GLU.h>
#include <gl/GL.h>
#include <vector>
#include <iostream>
#include <stack>
#include <math.h>

/*
NOTE:
    Transformer only supports drawing and transforming polygons, not circles.

DIRECTIONS TO USE:
    Initialize transformer class (Either enter number of vertices at end else it dynamically identifies them)
    Add transforms using addTransform<Transform> methods
    Update the transformer to multiply transformation matrices
    Apply the transformed matrix to any input matrix of 3xV dimensions (V are number of vertices)
    Returns output as 3xV 2D vector matrix
*/
namespace Transformer
{
    class Transform2D
    {
    public:

        Transform2D();

        // Add transforms to queue
        void addTransformTranslate(double tx, double ty);
        void addTransformScale(double sx, double sy, double xf, double yf);
        void addTransformRotate(double theta, double xr, double yr);

        // Apply transform to data matrix
        std::vector<std::vector<double>> applyTransform(std::vector<std::vector<double>> inputMatrix);

        // matrix display function for debugging
        void displayMatrix(std::vector<std::vector<double>> data);
    private:

        // Private matrix multiply function
        std::vector<std::vector<double>> matrixMultiply(std::vector<std::vector<double>>& mat1, std::vector<std::vector<double>>& mat2);

        std::stack<std::vector<std::vector<double>>> mTransformData;
    };
}