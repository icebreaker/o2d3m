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
#ifndef OD_MESH_H
#define OD_MESH_H

#include "face.h"
#include "aabb.h"

#include <QString>
#include <QStringList>
#include <QVector>

namespace od {

class Mesh
{
public:
	Mesh(void);
	void setName(const QString &name);

	void addMaterial(const QString &material);
	void addVertex(const float x, const float y, const float z);
	void addVertex(const Vec3 &v);
	void addFace(const VertexIndex v0, const VertexIndex v1, const VertexIndex v2, const MaterialIndex material);
	void addFace(const Face &face);

	void calculateAABB(void);
	void calculateNormals(void);

	inline bool isPlane(void) const
	{
		return mFaces.count() == 2;
	}

	inline bool isPlaneUsingDefaultMaterial(void) const
	{
		return isPlane() && mFaces.at(0).material == 0;
	}

	inline bool isEmpty(void) const
	{
		return mVertices.isEmpty() || mFaces.isEmpty();
	}

	inline const QString &name(void) const
	{
		return mName;
	}

	inline const QStringList &materials(void) const
	{
		return mMaterials;
	}

	inline const QVector<Vec3> &vertices(void) const
	{
		return mVertices;
	}

	inline const QVector<Face> &faces(void) const
	{
		return mFaces;
	}

	inline const AABB &aabb(void) const
	{
		return mAABB;
	}

private:
	QString mName;
	QStringList mMaterials;
	QVector<Vec3> mVertices;
	QVector<Face> mFaces;
	AABB mAABB;
};

/* od */ }

#endif

/* vim: set ts=4 sw=4 sts=4 noet: */
