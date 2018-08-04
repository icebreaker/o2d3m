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
#include "model.h"
#include "helper.h"

namespace od {

Model::Model(void) : mOffset(1)
{
	// nop
}

bool Model::load(const QString &filename)
{
	QFile file(filename);

	if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return false;

	mOffset = 1;
	mMeshes.clear();
	mLine.clear();

	return parse(file);
}

bool Model::parse(QFile &file)
{
	QTextStream stream(&file);

	while(!stream.atEnd())
	{
		if(!mLine.isEmpty() && mLine.at(0) == QChar::fromLatin1('o') && mLine.at(1) == QChar::Space)
		{
			const QStringList segs = mLine.split(QChar::Space);
			if(segs.size() != 2)
				return false;

			Mesh mesh;

			mesh.setName(segs.last());

			if(!parseMesh(mesh, stream))
				return false;

			mMeshes.append(mesh);
		}
		else
		{
			mLine = stream.readLine().simplified();
		}
	}

	return !mMeshes.isEmpty();
}

bool Model::parseMesh(Mesh &mesh, QTextStream &stream)
{
	QMap<QString, MaterialIndex> materials;
	MaterialIndex materialIndex;

	materialIndex = 0;
	materials["_default"] = 0;

	mesh.addMaterial("_default");

	while(!stream.atEnd())
	{
		mLine = stream.readLine().simplified();

		if(mLine.isEmpty() || mLine.at(0) == QChar::fromLatin1('#'))
			continue;

		if(mLine.at(0) == QChar::fromLatin1('o') && mLine.at(1) == QChar::Space)
			break;

		if(mLine.at(0) == QChar::fromLatin1('u') && mLine.at(1) == QChar::fromLatin1('s'))
		{
			const QStringList segs = mLine.split(QChar::Space);
			if(segs.size() != 2)
				return false;

			const QString material = od::text::sanitize(segs.at(1));
			if(QString::compare(material, QString("_default"), Qt::CaseInsensitive) == 0 ||
			   QString::compare(material, QString("none"), Qt::CaseInsensitive) == 0 ||
			   QString::compare(material, QString("material"), Qt::CaseInsensitive) == 0)
			{
				materialIndex = 0;
				continue;
			}

			QMap<QString, MaterialIndex>::const_iterator it = materials.constFind(material);
			if(it == materials.constEnd())
			{
				materialIndex = materials.size();
				materials[material] = materialIndex;

				mesh.addMaterial(material);
			}
			else
			{
				materialIndex = it.value();
			}

			continue;
		}

		if(mLine.at(0) == QChar::fromLatin1('v') && mLine.at(1) == QChar::Space)
		{
			const QStringList segs = mLine.split(QChar::Space);
			if(segs.size() != 4)
				return false;

			mesh.addVertex(segs.at(1).toFloat(), segs.at(2).toFloat(), segs.at(3).toFloat());
		}
		else if(mLine.at(0) == QChar::fromLatin1('f') && mLine.at(1) == QChar::Space)
		{
			const QStringList segs = mLine.split(QChar::Space);
			if(segs.size() < 4 || segs.size() > 5)
				return false;

			QVector<VertexIndex> vertexIndices;

			for(int i = 1; i < segs.size(); i++)
			{
				const QStringList faceSegs = segs.at(i).split(QChar::fromLatin1('/'));
				if(faceSegs.size() < 1)
					return false;

				vertexIndices.append(faceSegs.at(0).toUInt() - mOffset);
			}

			if(vertexIndices.size() < 3)
				return false;

			const VertexIndex v0 = vertexIndices.at(0);
			const VertexIndex v1 = vertexIndices.at(1);
			const VertexIndex v2 = vertexIndices.at(2);

			mesh.addFace(v0, v1, v2, materialIndex);

			if(vertexIndices.size() == 4)
			{
				const VertexIndex v3 = vertexIndices.at(3);
				mesh.addFace(v0, v2, v3, materialIndex);
			}
		}
	}

	if(mesh.isEmpty())
		return false;

	mesh.calculateNormals();
	mesh.calculateAABB();

	mOffset += mesh.vertices().size();

	return true;
}

/* od */ }

/* vim: set ts=4 sw=4 sts=4 noet: */
