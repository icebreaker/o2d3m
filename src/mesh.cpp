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
#include "mesh.h"

namespace od {

Mesh::Mesh(void) : mName("_default")
{
	// nop
}

void Mesh::setName(const QString &name)
{
	mName = name;
}

void Mesh::addMaterial(const QString &material)
{
	mMaterials.append(material);
}

void Mesh::addVertex(const float x, const float y, const float z)
{
	addVertex(Vec3(x, y, z));
}

void Mesh::addVertex(const Vec3 &v)
{
	mVertices.append(v.flipYZ());
}

void Mesh::addFace(const Face &face)
{
	mFaces.append(face);
}

void Mesh::addFace(const VertexIndex v0, const VertexIndex v1, const VertexIndex v2, const MaterialIndex material)
{
	Face face;
	face.v0 = v0;
	face.v1 = v1;
	face.v2 = v2;
	face.material = material;

	addFace(face);
}

void Mesh::calculateAABB(void)
{
	Vec3 &min = mAABB.min;
	Vec3 &max = mAABB.max;

	min.set(+999999.0f);
	max.set(-999999.0f);

	for(const Vec3 &v : mVertices)
	{
		if(v.x() < min.x())
			min.setX(v.x());

		if(v.y() < min.y())
			min.setY(v.y());

		if(v.z() < min.z())
			min.setZ(v.z());

		if(v.x() > max.x())
			max.setX(v.x());

		if(v.y() > max.y())
			max.setY(v.y());

		if(v.z() > max.z())
			max.setZ(v.z());
	}

	mAABB.radius = max.sub(min).mul(0.5);
	mAABB.origin = min.add(mAABB.radius);
	mAABB.normal = mFaces.at(0).normal;
}

void Mesh::calculateNormals(void)
{
	for(Face &face : mFaces)
	{
		const Vec3 &v0 = mVertices.at(face.v0);
		const Vec3 &v1 = mVertices.at(face.v1);
		const Vec3 &v2 = mVertices.at(face.v2);

		face.normal = v0.normal(v1, v2).normalized();
	}
}

/* od */ }


/* vim: set ts=4 sw=4 sts=4 noet: */
