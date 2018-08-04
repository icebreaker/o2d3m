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
#include "vec3.h"

namespace od {

Vec3::Vec3(void) : mX(0.0f), mY(0.0f), mZ(0.0f)
{
	// nop
}

Vec3::Vec3(const Vec3 &other) : mX(other.x()), mY(other.y()), mZ(other.z())
{
	// nop
}

Vec3::Vec3(const float v) : mX(v), mY(v), mZ(v)
{
	// nop
}

Vec3::Vec3(const float x, const float y, const float z) : mX(x), mY(y), mZ(z)
{
	// nop
}

/* od */ }

/* vim: set ts=4 sw=4 sts=4 noet: */
