#include "Matrix.h"
#include "assert.h"

#define _USE_MATH_DEFINES
#include <math.h>

Matrix3x3 MakeAffineMatrix(Vector2 Scale, float Rotate, Vector2 Translate)
{
	Matrix3x3 ResultAffine;

	ResultAffine.m[0][0] = Scale.x * cosf(Rotate);
	ResultAffine.m[0][1] = Scale.x * sinf(Rotate);
	ResultAffine.m[0][2] = 0;

	ResultAffine.m[1][0] = -Scale.y * sinf(Rotate);
	ResultAffine.m[1][1] = Scale.y * cosf(Rotate);
	ResultAffine.m[1][2] = 0;

	ResultAffine.m[2][0] = Translate.x;
	ResultAffine.m[2][1] = Translate.y;
	ResultAffine.m[2][2] = 1;

	return ResultAffine;

}

Matrix3x3 InverseMatrix(Matrix3x3 matrix) {

	float inverseA = (matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2]) + (matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0]) +
		(matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1]) - (matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0]) -
		(matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2]) - (matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1]);

	Matrix3x3 result;
	result.m[0][0] = (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1]);
	result.m[0][1] = -(matrix.m[0][1] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][1]);
	result.m[0][2] = (matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1]);

	result.m[1][0] = -(matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[0][2]);
	result.m[1][1] = (matrix.m[0][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][0]);
	result.m[1][2] = -(matrix.m[0][0] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][0]);

	result.m[2][0] = (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]);
	result.m[2][1] = -(matrix.m[0][0] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[2][0]);
	result.m[2][2] = (matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]);

	Matrix3x3 ResultInverse;

	ResultInverse.m[0][0] = result.m[0][0] / inverseA;
	ResultInverse.m[0][1] = result.m[0][1] / inverseA;
	ResultInverse.m[0][2] = result.m[0][2] / inverseA;

	ResultInverse.m[1][0] = result.m[1][0] / inverseA;
	ResultInverse.m[1][1] = result.m[1][1] / inverseA;
	ResultInverse.m[1][2] = result.m[1][2] / inverseA;

	ResultInverse.m[2][0] = result.m[2][0] / inverseA;
	ResultInverse.m[2][1] = result.m[2][1] / inverseA;
	ResultInverse.m[2][2] = result.m[2][2] / inverseA;

	return ResultInverse;

}

Matrix3x3 MakeOrthographicMatrix(float Left, float Top, float Right, float Bottom) {
	Matrix3x3 ResultOrghographic;

	ResultOrghographic.m[0][0] = 2.0f / (Right - Left);
	ResultOrghographic.m[0][1] = 0;
	ResultOrghographic.m[0][2] = 0;

	ResultOrghographic.m[1][0] = 0;
	ResultOrghographic.m[1][1] = 2.0f / (Top - Bottom);
	ResultOrghographic.m[1][2] = 0;

	ResultOrghographic.m[2][0] = (Left + Right) / (Left - Right);
	ResultOrghographic.m[2][1] = (Top + Bottom) / (Bottom - Top);
	ResultOrghographic.m[2][2] = 1.0f;

	return ResultOrghographic;
}

Matrix3x3 MakeViewportMatrix(float Left, float Top, float Width, float Height) {

	Matrix3x3 ResultViewport;

	ResultViewport.m[0][0] = Width / 2.0f;
	ResultViewport.m[0][1] = 0;
	ResultViewport.m[0][2] = 0;

	ResultViewport.m[1][0] = 0;
	ResultViewport.m[1][1] = -Height / 2.0f;
	ResultViewport.m[1][2] = 0;

	ResultViewport.m[2][0] = Left + Width / 2.0f;
	ResultViewport.m[2][1] = Top + Height / 2.0f;
	ResultViewport.m[2][2] = 1.0f;

	return ResultViewport;

}

Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2) {

	Matrix3x3 resultMultiply;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			resultMultiply.m[i][j] = 0;
			for (int k = 0; k < 3; k++) {
				resultMultiply.m[i][j] += matrix1.m[i][k] * matrix2.m[k][j];
			}
		}
	}
	return resultMultiply;
}

Vector2 Transform(Vector2 vector, Matrix3x3 matrix) {
	Vector2 result;

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];

	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;

	return result;
}
