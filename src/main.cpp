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
#include "version.h"
#include "command_line_runner.h"
#include "od/helper.h"

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QFileInfo>
#include <QTimer>

#ifndef OD_DEFAULT_SCALE
	#define OD_DEFAULT_SCALE 32.0f
#endif

#ifndef OD_DEFAULT_MATERIAL
	#define OD_DEFAULT_MATERIAL "textures/base_floor/squaretile"
#endif

using namespace od;

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);

	app.setApplicationName(QFileInfo(argv[0]).fileName());
	app.setApplicationVersion(OD_VERSION_STRING);

	QCommandLineParser parser;
	parser.setApplicationDescription("Converts any Wavefront OBJ to a DOOM3 map.");
	parser.addHelpOption();
	parser.addVersionOption();

	QCommandLineOption watchOption(
			QStringList() << "w" << "watch", "Watches input file for changes.");
	parser.addOption(watchOption);

	QCommandLineOption outputOption(
			QStringList() << "o" << "output", "Sets output file. (default: stdout)", "file");
	parser.addOption(outputOption);

	QCommandLineOption scaleOption(
			QStringList() << "s" << "scale",
			QString("Sets scale. (default: %1)").arg(OD_DEFAULT_SCALE), "scale");
	parser.addOption(scaleOption);

	QCommandLineOption materialOption(
			QStringList() << "m" << "material",
			QString("Sets default material.\n(default: %1)").arg(OD_DEFAULT_MATERIAL), "material");
	parser.addOption(materialOption);

	QCommandLineOption noWeaponsOption(
			QStringList() << "no-weapons", "Starts with no weapons.");
	parser.addOption(noWeaponsOption);

	QCommandLineOption noMonsterAttackOption(
			QStringList() << "no-monster-attack", "Monsters do not attack.");
	parser.addOption(noMonsterAttackOption);

	parser.addPositionalArgument("file", "Input file.");

	if(argc < 2)
	{
		parser.showHelp();
		return -1;
	}

	parser.process(app);

	QStringList input = parser.positionalArguments();
	if(input.isEmpty())
	{
		parser.showHelp();
		return -1;
	}

	CommandLineArguments args;
	args.noWeapons = parser.isSet(noWeaponsOption);
	args.noMonsterAttack = parser.isSet(noMonsterAttackOption);
	args.watch = parser.isSet(watchOption);
	args.scale = parser.value(scaleOption).toFloat();
	args.output = parser.value(outputOption);
	args.material = parser.value(materialOption);
	args.input = input.first();

	if(args.scale <= 0.0f)
		args.scale = OD_DEFAULT_SCALE;

	if(args.material.isEmpty())
		args.material = OD_DEFAULT_MATERIAL;
	else
		args.material = text::sanitize(args.material);

	CommandLineRunner runner(args);
	QTimer::singleShot(0, &runner, SLOT(exec()));

	return app.exec();
}

/* vim: set ts=4 sw=4 sts=4 noet: */
