#pragma once

namespace MathLib
{

	typedef union Vector2D
	{
		struct
		{
			float x, y;
		};

		float m[2];

		Vector2D() : x(0.0f), y(0.0f) {}
		Vector2D(float _x, float _y);

		Vector2D& operator=(const Vector2D& rhs) = default;
		Vector2D(const Vector2D & rhs) = default;

		Vector2D& operator += (const Vector2D &rhs);
		Vector2D& operator -= (const Vector2D &rhs);
		Vector2D& operator *= (float rhs);
		Vector2D& operator /= (float rhs);

		Vector2D operator -() const;

	} Vector2D, Vec2, Point2D, Pt2;

	Vector2D operator + (const Vector2D &lhs, const Vector2D &rhs);
	Vector2D operator - (const Vector2D &lhs, const Vector2D &rhs);
	Vector2D operator * (const Vector2D &lhs, float rhs);
	Vector2D operator * (float lhs, const Vector2D &rhs);
	Vector2D operator / (const Vector2D &lhs, float rhs);

	void	Vector2DNormalize(Vector2D &pResult, const Vector2D &pVec0);
	
	float	Vector2DLength(const Vector2D &pVec0);
	
	float	Vector2DSquareLength(const Vector2D &pVec0);
	
	float	Vector2DDistance(const Vector2D &pVec0, const Vector2D &pVec1);
	
	float	Vector2DSquareDistance(const Vector2D &pVec0, const Vector2D &pVec1);
	
	float	Vector2DDotProduct(const Vector2D &pVec0, const Vector2D &pVec1);
	
	float	Vector2DCrossProductMag(const Vector2D &pVec0, const Vector2D &pVec1);

}