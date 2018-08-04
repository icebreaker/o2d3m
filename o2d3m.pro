lessThan(QT_MAJOR_VERSION, 5): error("At least Qt 5 or later is required")

QT += core
QT -= gui

CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle

TARGET = o2d3m

DESTDIR = build
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
RCC_DIR = build

TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += src

SOURCES += \
	src/main.cpp \
	src/model.cpp \
	src/brush.cpp \
	src/map.cpp \
	src/entity.cpp \
	src/vec3.cpp \
	src/mesh.cpp \
	src/plane.cpp \
	src/command_line_runner.cpp

HEADERS += \
	src/model.h \
	src/brush.h \
	src/map.h \
	src/entity.h \
	src/vec3.h \
	src/mesh.h \
	src/plane.h \
	src/face.h \
	src/version.h \
	src/command_line_runner.h
	src/command_line_arguments.h
	src/helper.h
