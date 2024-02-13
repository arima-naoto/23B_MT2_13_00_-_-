#pragma once

//Vector2構造体の宣言
typedef struct Vector2 
{
	float x;
	float y;

}Vector2;

typedef struct Matrix3x3
{
	float m[3][3];

}Matrix3x3;

//Ball構造体の宣言
typedef struct Ball 
{
	Vector2 position; //座標
	Vector2 Velocity; //速度
	Vector2 acceleration; //加速度
	float mass; //質量 
	float radius; //半径
	unsigned int color; //色

}Ball;
