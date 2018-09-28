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
#include "brush.h"
#include "plane.h"

namespace od {

Brush::Brush(void)
{
	// nop
}

void Brush::setMaterial(const QString &material)
{
	for(Side &side : mSides)
		side.material = material;
}

void Brush::setMaterial(const SideIndex index, const QString &material)
{
	Side &side = mSides[index];
	side.material = material;
}

void Brush::add(const Vec3 &normal, const float dist, const QString &material)
{
	Side side;
	side.material = material;
	side.normal = normal;
	side.dist = dist;

	mSides.append(side);
}

void Brush::add(const Vec3 &point, const Vec3 &normal, const QString &material)
{
	add(Plane(point, normal), material);
}

void Brush::add(const Plane &plane, const QString &material)
{
	add(plane.normal(), plane.dist_signed_to_origin(), material);
}

void Brush::serialize(QTextStream &stream, const float scale) const
{
	stream << "\t{\n\t\tbrushDef3\n\t\t{\n";

	for(const Side &side : mSides)
	{
		stream << "\t\t\t";
		stream << "( " << side.normal.x() << " " << side.normal.y() << " " << side.normal.z() << " ";
		stream << side.dist * scale << " )";
		stream << " ( ( 0.031250 0 0 ) ( 0 0.031250 0 ) ) ";
		stream << side.material;
		stream << " 0 0 0";
		stream << "\n";
	}

	stream << "\t\t}\n\t}\n";
}

Brush Brush::fromMesh(const Mesh &mesh, const QString &material)
{
	return fromMesh(mesh, material, Vec3::zero());
}

Brush Brush::fromMesh(const Mesh &mesh, const QString &material, const Vec3 &origin)
{
	const QVector<Face> &faces = mesh.faces();
	const QVector<Vec3> &vertices = mesh.vertices();
	const QStringList &materials = mesh.materials();

	Brush brush;

	for(int i = 0; i < faces.size(); i += 2)
	{
		const Face &face = faces.at(i);
		const Vec3 &v0 = vertices.at(face.v0);
		const Vec3 &normal = face.normal;
		const Vec3 point = v0.sub(origin);
		const MaterialIndex materialIndex = face.material;

		if(materialIndex == 0)
			brush.add(point, normal, material);
		else
			brush.add(point, normal, materials.at(materialIndex));
	}

	return brush;
}

/* od */ }

/* vim: set ts=4 sw=4 sts=4 noet: */
