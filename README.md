O2D3M
=====
O2D3M is a _Wavefront OBJ_ to _DOOM3_ map converter.

![O2D3M][1]

Watch a video showcasing it in action by clicking [here][2].

Getting Started
---------------
You'll need a C++ compiler with C++11 support and Qt 5
or later in order to compile this.

Why does it use Qt? Well, because this project started
as a _plugin_ for [Tiled][3], but then I lost interest
and turned it into a _CLI_ tool without moving away
from Qt.

Open `o2d3m.pro` in QtCreator or if you are a _CLI_
kind of person type in the following incantations in
a terminal:

```bash
$ mkdir build
$ cd build
$ qmake ..
$ make
```

This will result in an executable called `o2d3m` in
the _build_ directory.

To _convert_ an OBJ file into a D3 map one would type:

```bash
$ build/o2d3m --no-monster-attack -o example/base/maps/example.map example/src/example.obj
```

To test the resulting D3 map one would type:

```bash
$ dhewm3 +set fs_savepath example +disconnect +dmap example +map example
```

Replace _dhewm3_ above with the name of your D3 flavour's executable.

Contribute
----------
* Fork the project.
* Make your feature addition or bug fix.
* Do **not** bump the version number.
* Send me a pull request. Bonus points for topic branches.

License
-------
Copyright (c) 2018, Mihail Szabolcs

O2D3M is provided **as-is** under the **MIT** license.
For more information see LICENSE.

[1]: o2d3m.png
[2]: https://www.youtube.com/watch?v=7Hsy--jAUQE
[3]: https://www.mapeditor.org/
