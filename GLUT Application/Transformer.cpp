#include "Transformer.h"


Transformer::Transform2D::Transform2D()
{
    mTransformData.push({
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
        });
}

// Add transforms to stack and multiply
void Transformer::Transform2D::addTransformTranslate(double tx, double ty)
{
    std::vector<std::vector<double>> data = {
        {1, 0, tx},
        {0, 1, ty},
        {0, 0, 1}
    };
    mTransformData.top() = matrixMultiply(mTransformData.top(), data);
    std::cout << "Added translation transform." << std::endl;
}
void Transformer::Transform2D::addTransformScale(double sx, double sy, double xf, double yf)
{
    std::vector<std::vector<double>> data = {
        {sx, 0, xf * (1 - sx)},
        {0, sy, yf * (1 - sy)},
        {0, 0, 1}
    };
    mTransformData.top() = matrixMultiply(mTransformData.top(), data);
    std::cout << "Added scaling transform." << std::endl;
}
void Transformer::Transform2D::addTransformRotate(double theta, double xr = 0, double yr = 0)
{   
    theta = theta * 3.1415926535 / 180;
    double c = cos(theta);
    double s = sin(theta);
    std::vector<std::vector<double>> data = {
        {c, -s, (xr * (1 - c)) + (yr * s)},
        {s, c, (yr * (1 - c)) - (xr * s)},
        {0, 0, 1}
    };
    displayMatrix(data);
    mTransformData.top() = matrixMultiply(mTransformData.top(), data);
    std::cout << "Added rotation transform." << std::endl;
}


// Apply transform to input data
std::vector<std::vector<double>> Transformer::Transform2D::applyTransform(std::vector<std::vector<double>> inputMatrix)
{
    return matrixMultiply(mTransformData.top(), inputMatrix);
}

// Private matrix multiply function
std::vector<std::vector<double>> Transformer::Transform2D::matrixMultiply(std::vector<std::vector<double>>& mat1, std::vector<std::vector<double>>& mat2)
{
    int rows1 = mat1.size();
    int cols1 = mat1[0].size();
    int rows2 = mat2.size();
    int cols2 = mat2[0].size();
    std::vector<std::vector<double>> result(rows1, std::vector<double>(cols2, 0.0));
    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols2; ++j) {
            for (int k = 0; k < cols1; ++k) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    return result;
}

// Private matrix display function
void Transformer::Transform2D::displayMatrix(std::vector<std::vector<double>> data)
{
    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < data[0].size(); j++)
        {
            std::cout << data[i][j] << " ";
        }
        std::cout << "\n";
    }
}

