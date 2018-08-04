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
#include "map.h"

#include <QFile>

namespace od {

Map::Map(void)
{
	mWorldSpawn.set("classname", "worldspawn");
}

void Map::set(const QString &name, const QString &value)
{
	mWorldSpawn.set(name, value);
}

void Map::addEntity(const Entity &entity)
{
	mEntities.append(entity);
}

void Map::addBrush(const Brush &brush)
{
	mWorldSpawn.addBrush(brush);
}

void Map::serialize(QTextStream &stream, const float scale) const
{
	stream << "Version 2\n";

	mWorldSpawn.serialize(stream, scale);

	for(const Entity &entity : mEntities)
		entity.serialize(stream, scale);
}

bool Map::serialize(const QString &filename, const float scale) const
{
	QFile file;

	if(filename.isEmpty() || filename == "stdout")
	{
		if(!file.open(stdout, QIODevice::WriteOnly | QIODevice::Text))
			return false;
	}
	else
	{
		file.setFileName(filename);

		if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
			return false;
	}

	QTextStream stream(&file);
	stream.setRealNumberNotation(QTextStream::FixedNotation);
	stream.setRealNumberPrecision(6);

	serialize(stream, scale);

	stream.flush();

	return true;
}

/* od */ }

/* vim: set ts=4 sw=4 sts=4 noet: */
