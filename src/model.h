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
#ifndef OD_MODEL_H
#define OD_MODEL_H

#include "mesh.h"

#include <QVector>
#include <QString>
#include <QFile>
#include <QTextStream>

namespace od {

class Model
{
public:
	Model(void);
	bool load(const QString &filename);

	inline const QVector<Mesh> &meshes(void) const
	{
		return mMeshes;
	}

protected:
	bool parse(QFile &file);
	bool parseMesh(Mesh &mesh, QTextStream &stream);

private:
	QVector<Mesh> mMeshes;
	QString mLine;
	VertexIndex mOffset;
};

/* od */ }

#endif

/* vim: set ts=4 sw=4 sts=4 noet: */
