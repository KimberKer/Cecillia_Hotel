#include "duckpch.h"
#include "Matrix3x3.h"


constexpr float PI = 3.14159265358f;

namespace MathLib
{
	Matrix3x3::Matrix3x3(const float *pArr)
	{
		m00 = *pArr++;
		m01 = *pArr++;
		m02 = *pArr++;

		m10 = *pArr++;
		m11 = *pArr++;
		m12 = *pArr++;

		m20 = *pArr++;
		m21 = *pArr++;
		m22 = *pArr;
	};

	Matrix3x3::Matrix3x3(float _00, float _01, float _02,
						 float _10, float _11, float _12,
						 float _20, float _21, float _22) :	m00(_00), m01(_01), m02(_02),
															m10(_10), m11(_11), m12(_12),
															m20(_20), m21(_21), m22(_22) {};

	Matrix3x3& Matrix3x3::operator = (const Matrix3x3 &rhs)
	{	
		m00 = rhs.m00;
		m01 = rhs.m01;
		m02 = rhs.m02;

		m10 = rhs.m10;
		m11 = rhs.m11;
		m12 = rhs.m12;

		m20 = rhs.m20;
		m21 = rhs.m21;
		m22 = rhs.m22;

		return *this;
	}



	/*----------------------------------------------------------
	*
	* assignment operators
	*
	----------------------------------------------------------*/
	Matrix3x3& Matrix3x3::operator *= (const Matrix3x3& rhs)
	{
		float _m00, _m01, _m02, _m10, _m11, _m12, _m20, _m21, _m22;

		//cross multiplication
		_m00 = (m00 * rhs.m00) + (m01 * rhs.m10) + (m02 * rhs.m20);
		_m01 = (m00 * rhs.m01) + (m01 * rhs.m11) + (m02 * rhs.m21);
		_m02 = (m00 * rhs.m02) + (m01 * rhs.m12) + (m02 * rhs.m22);

		_m10 = (m10 * rhs.m00) + (m11 * rhs.m10) + (m12 * rhs.m20);
		_m11 = (m10 * rhs.m01) + (m11 * rhs.m11) + (m12 * rhs.m21);
		_m12 = (m10 * rhs.m02) + (m11 * rhs.m12) + (m12 * rhs.m22);

		_m20 = (m20 * rhs.m00) + (m21 * rhs.m10) + (m22 * rhs.m20);
		_m21 = (m20 * rhs.m01) + (m21 * rhs.m11) + (m22 * rhs.m21);
		_m22 = (m20 * rhs.m02) + (m21 * rhs.m12) + (m22 * rhs.m22);

		m00 = _m00;
		m01 = _m01;
		m02 = _m02;

		m10 = _m10;
		m11 = _m11;
		m12 = _m12;

		m20 = _m20;
		m21 = _m21;
		m22 = _m22;

		return *this;
	}

	Matrix3x3 operator * (const Matrix3x3 &lhs, const Matrix3x3 &rhs)
	{
		Matrix3x3 result = lhs;
		result *= rhs;

		return result;
	}

	/**************************************************************************/
	/*!
		This operator multiplies the matrix pMtx with the vector rhs
		and returns the result as a vector
	 */
	 /**************************************************************************/
	Vector2D  operator * (const Matrix3x3& pMtx, const Vector2D& rhs)
	{
		Vector2D result;

		result.x = (pMtx.m00 * rhs.x) + (pMtx.m01 * rhs.y) + pMtx.m02;
		result.y = (pMtx.m10 * rhs.x) + (pMtx.m11 * rhs.y) + pMtx.m12;

		return result;
	}

	/**************************************************************************/
	/*!
		This function sets the matrix pResult to the identity matrix
	 */
	 /**************************************************************************/
	void Mtx33Identity(Matrix3x3& pResult)
	{
		pResult.m00 = 1;
		pResult.m01 = 0;
		pResult.m02 = 0;

		pResult.m10 = 0;
		pResult.m11 = 1;
		pResult.m12 = 0;

		pResult.m20 = 0;
		pResult.m21 = 0;
		pResult.m22 = 1;
	}

	/**************************************************************************/
	/*!
		This function creates a translation matrix from x & y
		and saves it in pResult
	 */
	 /**************************************************************************/
	void Mtx33Translate(Matrix3x3& pResult, float x, float y)
	{
		Mtx33Identity(pResult);

		pResult.m02 = x;
		pResult.m12 = y;
	}

	/**************************************************************************/
	/*!
		This function creates a scaling matrix from x & y
		and saves it in pResult
	 */
	 /**************************************************************************/
	void Mtx33Scale(Matrix3x3& pResult, float x, float y)
	{
		Mtx33Identity(pResult);

		pResult.m00 = x;
		pResult.m11 = y;
	}

	/**************************************************************************/
	/*!
		This matrix creates a rotation matrix from "angle" whose value
		is in radian. Save the resultant matrix in pResult.
	 */
	 /**************************************************************************/
	void Mtx33RotRad(Matrix3x3& pResult, float angle)
	{
		Mtx33Identity(pResult);

		pResult.m00 = cosf(angle);
		pResult.m01 = -sinf(angle);

		pResult.m10 = sinf(angle);
		pResult.m11 = cosf(angle);
	}

	/**************************************************************************/
	/*!
		This matrix creates a rotation matrix from "angle" whose value
		is in degree. Save the resultant matrix in pResult.
	 */
	 /**************************************************************************/
	void Mtx33RotDeg(Matrix3x3& pResult, float angle)
	{
		Mtx33Identity(pResult);
		pResult.m00 = cosf(angle * PI / 180);
		pResult.m01 = -sinf(angle * PI / 180);
		
		pResult.m10 = sinf(angle * PI / 180);
		pResult.m11 = cosf(angle * PI / 180);
	}

	/**************************************************************************/
	/*!
		This functions calculated the transpose matrix of pMtx
		and saves it in pResult
	 */
	 /**************************************************************************/
	void Mtx33Transpose(Matrix3x3& pResult, const Matrix3x3& pMtx)
	{
		pResult.m00 = pMtx.m00;
		pResult.m01 = pMtx.m10;
		pResult.m02 = pMtx.m20;

		pResult.m10 = pMtx.m01;
		pResult.m11 = pMtx.m11;
		pResult.m12 = pMtx.m21;

		pResult.m20 = pMtx.m02;
		pResult.m21 = pMtx.m12;
		pResult.m22 = pMtx.m22;
	}

	/**************************************************************************/
	/*!
		This function calculates the inverse matrix of pMtx and saves the
		result in pResult. If the matrix inversion fails, pResult
		would be set to NULL.
	*/
	/**************************************************************************/
	void Mtx33Inverse(Matrix3x3* pResult, float* determinant, const Matrix3x3& pMtx)
	{
		// Calculate the determinant of the matrix
		*determinant = ((pMtx.m00 * pMtx.m11 * pMtx.m22) + (pMtx.m01 * pMtx.m12 * pMtx.m20) + (pMtx.m02 * pMtx.m10 * pMtx.m21)) 
					 - ((pMtx.m02 * pMtx.m11 * pMtx.m20) + (pMtx.m01 * pMtx.m10 * pMtx.m22) + (pMtx.m00 * pMtx.m12 * pMtx.m21));

		if (*determinant <= 0)
		{
			pResult = NULL;
		}

		else
		{
			Matrix3x3 temp;
			Mtx33Transpose(temp, pMtx);

			//get adj
			pResult->m00 = (temp.m11 * temp.m22 - temp.m21 * temp.m12);
			pResult->m01 = -(temp.m10 * temp.m22 - temp.m20 * temp.m12);
			pResult->m02 = (temp.m10 * temp.m21 - temp.m20 * temp.m11);

			pResult->m10 = -(temp.m01 * temp.m22 - temp.m21 * temp.m02);
			pResult->m11 = (temp.m00 * temp.m22 - temp.m20 * temp.m02);
			pResult->m12 = -(temp.m00 * temp.m21 - temp.m20 * temp.m01);

			pResult->m20 = (temp.m01 * temp.m12 - temp.m11 * temp.m02);
			pResult->m21 = -(temp.m00 * temp.m12 - temp.m10 * temp.m02);
			pResult->m22 = (temp.m00 * temp.m11 - temp.m10 * temp.m01);


			//divide by det
			pResult->m00 /= *determinant;
			pResult->m01 /= *determinant;
			pResult->m02 /= *determinant;
			pResult->m10 /= *determinant;
			pResult->m11 /= *determinant;
			pResult->m12 /= *determinant;
			pResult->m20 /= *determinant;
			pResult->m21 /= *determinant;
			pResult->m22 /= *determinant;
		}
	}
} //end namespace MathLib