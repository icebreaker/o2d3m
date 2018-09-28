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
	src/od/model.cpp \
	src/od/brush.cpp \
	src/od/map.cpp \
	src/od/entity.cpp \
	src/od/vec3.cpp \
	src/od/mesh.cpp \
	src/od/plane.cpp \
	src/command_line_runner.cpp

HEADERS += \
	src/od/model.h \
	src/od/brush.h \
	src/od/map.h \
	src/od/entity.h \
	src/od/vec3.h \
	src/od/mesh.h \
	src/od/plane.h \
	src/od/face.h \
	src/od/helper.h \
	src/version.h \
	src/command_line_runner.h
	src/command_line_arguments.h
