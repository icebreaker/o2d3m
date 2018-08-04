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
#include "helper.h"
#include "command_line_runner.h"
#include "model.h"
#include "map.h"

#include <QCoreApplication>
#include <QThread>
#include <QSocketNotifier>
#include <QFileSystemWatcher>
#include <QTextStream>
#include <QString>
#include <QDebug>

namespace od {

CommandLineRunner::CommandLineRunner(const CommandLineArguments &args) : QObject(nullptr), mArgs(args), mWatching(true)
{
	// nop
}

void CommandLineRunner::watch(void)
{
	QSocketNotifier socket(fileno(stdin), QSocketNotifier::Read);
	connect(&socket, SIGNAL(activated(int)), this, SLOT(quit()));

	QFileSystemWatcher watcher(QStringList() << mArgs.input);
	connect(&watcher, SIGNAL(fileChanged(QString)), this, SLOT(fileChanged(QString)));

	while(mWatching)
	{
		QCoreApplication::processEvents();
		QThread::msleep(200);
	}
}

int CommandLineRunner::process(void)
{
	const QString &material = mArgs.material;
	const float scale = mArgs.scale;

	Model model;
	if(!model.load(mArgs.input))
	{
		qCritical() << "Failed to open input file:" << mArgs.input;
		return -1;
	}

	Map map;
	if(mArgs.noWeapons)
		map.set("no_Weapons", "1");

	for(const Mesh &mesh : model.meshes())
	{
		const QString &name = mesh.name();
		const AABB &aabb = mesh.aabb();
		const Vec3 &origin = aabb.origin;
		const Vec3 &normal = aabb.normal;
		const Vec3 &radius = aabb.radius;

		qInfo() << name;

		if(name.startsWith("class_"))
		{
			const QString className = od::text::sanitize(name.mid(6));

			Entity entity;

			entity.set("name", name);
			entity.set("classname", className);
			entity.set("origin", origin.mul(scale).serialize());

			if(className.startsWith("light"))
			{
				const int noShadowsIndex = className.lastIndexOf("_no_shadows");
				if(noShadowsIndex != -1)
				{
					entity.set("classname", className.left(noShadowsIndex));
					entity.set("noshadows", "1");
				}

				entity.set("light_center", Vec3::zero().serialize());
				entity.set("light_radius", radius.mul(2.0f * scale).serialize());

				map.addEntity(entity);
				continue;
			}

			if(mesh.isPlane())
			{
				if(mArgs.noMonsterAttack && className.startsWith("monster_"))
					entity.set("team", "0");

				entity.set("angle", QString::number(normal.angle()));

				if(!mesh.isPlaneUsingDefaultMaterial())
					entity.set("skin", material);

				const int targetIndex = name.indexOf("_target_");
				if(targetIndex != -1)
				{
					const QString modelTarget = name.mid(targetIndex + 8);

					if(modelTarget.count(QChar::fromLatin1('.')) > 1)
						entity.set("target", od::text::sanitize(modelTarget));
					else
						entity.set("target", modelTarget);

					entity.set("classname", className.left(className.indexOf("_target_")));
				}
				else
				{
					const int modelIndex = name.indexOf("_model_");
					if(modelIndex != -1)
					{
						const QString modelName = name.mid(modelIndex + 7);

						if(modelName.count(QChar::fromLatin1('.')) > 1)
							entity.set("model", od::text::sanitize(modelName));
						else
							entity.set("model", modelName);

						entity.set("classname", className.left(className.indexOf("_model_")));
					}
				}
			}
			else
			{
				if(className.startsWith("func_plat"))
				{
					entity.set("origin", Vec3(origin.x(), origin.y(), origin.z() * 2.0f).mul(scale).serialize());
					entity.set("height", QString::number(origin.z() * scale));
					entity.set("speed", QString::number(origin.z() * scale));
				}
				else if(className.startsWith("func_door"))
				{
					entity.set("movedir", "-1");
				}

				if(name.indexOf("."))
				{
					QString modelName = QString(name).replace(".", "_");
					entity.set("name", modelName);
					entity.set("model", modelName);
				}
				else
				{
					entity.set("model", name);
				}
				entity.addBrush(Brush::fromMesh(mesh, material, origin));
			}

			map.addEntity(entity);
		}
		else
		{
			map.addBrush(Brush::fromMesh(mesh, material));
		}
	}

	if(!map.serialize(mArgs.output, mArgs.scale))
	{
		qCritical() << "Failed to serialize to output file: " << mArgs.output;
		return -1;
	}

	if(mArgs.watch)
		qInfo() << "Press [enter] to quit ...";

	return 0;
}

void CommandLineRunner::exec(void)
{
	int ret = process();

	if(ret == 0 && mArgs.watch)
	{
		watch();
		qInfo() << "Done ...";
	}

	QCoreApplication::exit(ret);
}

void CommandLineRunner::quit(void)
{
	QTextStream in(stdin); 

	if(in.atEnd() || in.readLine().isEmpty())
	{
		qInfo() << "Trying to quit ...";
		mWatching = false;
	}
}

void CommandLineRunner::fileChanged(const QString &filename)
{
	qInfo() << "File changed" << filename;
	process();
}

/* od */ }

/* vim: set ts=4 sw=4 sts=4 noet: */
