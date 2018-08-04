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
#ifndef OD_BRUSH_H
#define OD_BRUSH_H

#include "mesh.h"
#include "plane.h"

#include <QVector>
#include <QString>
#include <QTextStream>

namespace od {

typedef unsigned int SideIndex;

struct Side
{
	Vec3 normal;
	float dist;
	QString material;
};

class Brush
{
public:
	Brush(void);

	void setMaterial(const QString &material);
	void setMaterial(const SideIndex index, const QString &material);

	void add(const Vec3 &normal, const float dist, const QString &material = "_default");
	void add(const Vec3 &point, const Vec3 &normal, const QString &material = "_default");
	void add(const Plane &plane, const QString &material = "_default");

	void serialize(QTextStream &stream, const float scale) const;

	static Brush fromMesh(const Mesh &mesh);
	static Brush fromMesh(const Mesh &mesh, const QString &material);
	static Brush fromMesh(const Mesh &mesh, const QString &material, const Vec3 &origin);

private:
	QVector<Side> mSides;
};

/* od */ }

#endif

/* vim: set ts=4 sw=4 sts=4 noet: */
