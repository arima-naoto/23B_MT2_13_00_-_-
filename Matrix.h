#pragma once
#include "Struct.h"

Matrix3x3 MakeAffineMatrix(Vector2 scale, float theta, Vector2 translate);

Matrix3x3 InverseMatrix(Matrix3x3 matrix);

Matrix3x3 MakeOrthographicMatrix(float Left, float Top, float Right, float Bottom);

Matrix3x3 MakeViewportMatrix(float Left, float Top, float Width, float Height);

Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2);

Vector2 Transform(Vector2 vector, Matrix3x3 matrix);