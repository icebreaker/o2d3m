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
#ifndef OD_PLANE_H
#define OD_PLANE_H

#include "vec3.h"

namespace od {

class Plane
{
public:
	Plane(void);
	Plane(const float x, const float y, const float z, const float w);
	Plane(const Vec3 &p, const Vec3 &n);

	inline const Vec3 &normal(void) const
	{
		return mNormal;
	}

	inline float w(void) const
	{
		return mW;
	}

	inline float dist_signed_to_point(const Vec3 &p) const
	{
		const float len = mNormal.lengthSqr();
		const float side = p.dot(mNormal) + mW;

		return sqrtf(len) * (side / len);
	}

	inline float dist_signed_to_origin(void) const
	{
		const float len = mNormal.lengthSqr();
		return sqrtf(len) * (mW / len);
	}

private:
	Vec3 mNormal;
	float mW;
};

/* od */ }

#endif

/* vim: set ts=4 sw=4 sts=4 noet: */
