#include "Vector2D.h"
#include <math.h>
#include <iostream>

namespace CSD1130
{
	Vector2D::Vector2D(float _x, float _y) : x(_x), y(_y) {};

	/*----------------------------------------------------------
	* 
	* assignment operators
	* 
	----------------------------------------------------------*/
	Vector2D& Vector2D::operator += (const Vector2D &rhs)
	{
		x += rhs.x;
		y += rhs.y;

		return *this;
	}

	Vector2D& Vector2D::operator -= (const Vector2D &rhs)
	{
		x -= rhs.x;
		y -= rhs.y;

		return *this;
	}

	Vector2D& Vector2D::operator *= (float rhs)
	{
		x *= rhs;
		y *= rhs;

		return *this;
	}

	Vector2D& Vector2D::operator /= (float rhs)
	{
		x /= rhs;
		y /= rhs;

		return *this;
	}

	/*----------------------------------------------------------
	*
	* unary operators
	*
	----------------------------------------------------------*/
	Vector2D Vector2D::operator - () const
	{
		return {-x, -y};
	}

	/*----------------------------------------------------------
	*
	* binary operators
	*
	----------------------------------------------------------*/
	Vector2D operator + (const Vector2D& lhs, const Vector2D& rhs)
	{
		Vector2D result;

		result.x = lhs.x + rhs.x;
		result.y = lhs.y + rhs.y;

		return result;
	}

	Vector2D operator - (const Vector2D& lhs, const Vector2D& rhs)
	{
		Vector2D result;

		result.x = lhs.x - rhs.x;
		result.y = lhs.y - rhs.y;

		return result;
	}

	Vector2D operator * (const Vector2D& lhs, float rhs)
	{
		Vector2D result;

		result.x = lhs.x * rhs;
		result.y = lhs.y * rhs;

		return result;
	}

	Vector2D operator * (float lhs, const Vector2D& rhs)
	{
		Vector2D result;

		result.x = lhs * rhs.x;
		result.y = lhs * rhs.y;

		return result;
	}

	Vector2D operator / (const Vector2D& lhs, float rhs)
	{
		Vector2D result;

		result.x = lhs.x / rhs;
		result.y = lhs.y / rhs;

		return result;
	}

	/**************************************************************************/
	/*!
		In this function, pResult will be the unit vector of pVec0
	 */
	 /**************************************************************************/
	void	Vector2DNormalize(Vector2D& pResult, const Vector2D& pVec0)
	{
		float len = Vector2DLength(pVec0);
		pResult = pVec0;
		pResult /= len;
	}

	/**************************************************************************/
	/*!
		This function returns the length of the vector pVec0
	 */
	 /**************************************************************************/
	float	Vector2DLength(const Vector2D& pVec0)
	{
		return sqrtf(pVec0.x * pVec0.x + pVec0.y * pVec0.y);
	}

	/**************************************************************************/
	/*!
		This function returns the square of pVec0's length. Avoid the square root
	 */
	 /**************************************************************************/
	float	Vector2DSquareLength(const Vector2D& pVec0)
	{
		return powf(pVec0.x, 2.0f) + powf(pVec0.y, 2.0f);
	}

	/**************************************************************************/
	/*!
		In this function, pVec0 and pVec1 are considered as 2D points.
		The distance between these 2 2D points is returned
	 */
	 /**************************************************************************/
	float	Vector2DDistance(const Vector2D& pVec0, const Vector2D& pVec1)
	{
		float x_dist = pVec0.x - pVec1.x;
		float y_dist = pVec0.y - pVec1.y;

		return sqrtf(powf(x_dist, 2.0f) + powf(y_dist, 2.0f));
	}

	/**************************************************************************/
	/*!
		In this function, pVec0 and pVec1 are considered as 2D points.
		The squared distance between these 2 2D points is returned.
		Avoid the square root
	 */
	 /**************************************************************************/
	float	Vector2DSquareDistance(const Vector2D& pVec0, const Vector2D& pVec1)
	{
		float x_dist = pVec0.x - pVec1.x;
		float y_dist = pVec0.y - pVec1.y;

		return powf(x_dist, 2.0f) + powf(y_dist, 2.0f);
	}

	/**************************************************************************/
	/*!
		This function returns the dot product between pVec0 and pVec1
	 */
	 /**************************************************************************/
	float	Vector2DDotProduct(const Vector2D& pVec0, const Vector2D& pVec1)
	{
		return (pVec0.x * pVec1.x) + (pVec0.y * pVec1.y);
	}

	/**************************************************************************/
	/*!
		This function returns the cross product magnitude
		between pVec0 and pVec1
	 */
	 /**************************************************************************/
	float	Vector2DCrossProductMag(const Vector2D& pVec0, const Vector2D& pVec1)
	{
		return (pVec0.x * pVec1.y) - (pVec0.y * pVec1.x);
	}
} //end namespace CSD1130