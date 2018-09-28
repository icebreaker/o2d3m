/* {{{
	MIT LICENSE

	Copyright (c) 2018, Mihail Szabolcs

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the 'Software'), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
}}} */
#ifndef OD_VEC3_H
#define OD_VEC3_H

#include <QtMath>
#include <QString>

namespace od {

class Vec3
{
public:
	Vec3(void);
	Vec3(const Vec3 &other);
	Vec3(const float v);
	Vec3(const float x, const float y, const float z);

	static inline const Vec3 &zero(void)
	{
		static Vec3 v;
		return v;
	}

	inline void set(const float v)
	{
		mX = v;
		mY = v;
		mZ = v;
	}

	inline void setX(const float x)
	{
		mX = x;
	}

	inline void setY(const float y)
	{
		mY = y;
	}

	inline void setZ(const float z)
	{
		mZ = z;
	}

	inline float x(void) const
	{
		return mX;
	}

	inline float y(void) const
	{
		return mY;
	}

	inline float z(void) const
	{
		return mZ;
	}

	inline float angle(void) const
	{
		return qRadiansToDegrees(qAtan2(mY, mX));
	}

	inline float dot(const Vec3 &other) const
	{
		return (mX * other.x()) + (mY * other.y()) + (mZ * other.z());
	}

	inline Vec3 mul(const float v) const
	{
		return mul(Vec3(v));
	}

	inline Vec3 mul(const Vec3 &other) const
	{
		return Vec3(mX * other.x(), mY * other.y(), mZ * other.z());
	}

	inline Vec3 add(const Vec3 &other) const
	{
		return Vec3(mX + other.x(), mY + other.y(), mZ + other.z());
	}

	inline Vec3 sub(const Vec3 &other) const
	{
		return Vec3(mX - other.x(), mY - other.y(), mZ - other.z());
	}

	inline Vec3 cross(const Vec3 &other) const
	{
		return Vec3(
			(mY * other.z()) - (mZ * other.y()),
			(mZ * other.x()) - (mX * other.z()),
			(mX * other.y()) - (mY * other.x())
		);
	}

	inline float lengthSqr(void) const
	{
		return dot(*this);
	}

	inline float length(void) const
	{
		return qSqrt(lengthSqr());
	}

	inline void normalize()
	{
		const float len = 1.0f / length();

		mX *= len;
		mY *= len;
		mZ *= len;
	}

	inline Vec3 normalized(void) const
	{
		Vec3 v(*this);
		v.normalize();
		return v;
	}

	inline Vec3 normal(const Vec3 v1, const Vec3 v2) const
	{
		return sub(v1).cross(sub(v2));
	}

	inline Vec3 flipYZ(void) const
	{
		// "flip" axis from (Y up, -Z forward) to (Z up, -Y forward)
		return Vec3(mX, -mZ, mY);
	}

	inline QString serialize(void) const
	{
		return QString().sprintf("%.02f %.02f %.02f", mX, mY, mZ);
	}

private:
	float mX, mY, mZ;
};

/* od */ }

#endif

/* vim: set ts=4 sw=4 sts=4 noet: */
