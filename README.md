# Ylikuutio. A 3D game and simulation engine.
A hobby project of mine. Work in progress.

[![Build status](https://travis-ci.org/nrz/ylikuutio.svg?branch=master)](https://travis-ci.org/nrz/ylikuutio)
[![Coverity Scan](https://scan.coverity.com/projects/nrz-ylikuutio/badge.svg)](https://scan.coverity.com/projects/nrz-ylikuutio)

## License
Ylikuutio is under The GNU General Public License 3,
or (at your option) any later version. See COPYING file.
All my code copyright (C) 2016-2017 Antti Nuortimo.

### Currently in use
* The source code from http://www.opengl-tutorial.org/ is licensed under [WTFPL Public Licence version 2](http://www.opengl-tutorial.org/download/).
* OpenGL Mathematics (GLM) is licensed under [The Happy Bunny License (Modified MIT License) and MIT License](http://glm.g-truc.net/copying.txt).
* GLFW is licensed under [the zlib/libpng license](http://www.glfw.org/license.html).
* The OpenGL Extension Wrangler Library (GLEW) is licensed under [the Modified BSD License, the Mesa 3-D License (MIT) and the Khronos License (MIT)](https://github.com/nigels-com/glew#copyright-and-licensing).
* OpenFBX is licensed under [the MIT license](https://github.com/nem0/OpenFBX/blob/master/LICENSE).
* TinyScheme is licensed under [BSD-style license](http://tinyscheme.sourceforge.net/license.txt).
* pugixml is licensed under [the MIT license](https://github.com/zeux/pugixml/blob/master/README.md).

### Not yet in use
* Asio is licensed under [Boost software license](https://github.com/chriskohlhoff/asio/blob/master/asio/LICENSE_1_0.txt).
* GLFM is licensed under [the zlib license](https://github.com/brackeen/glfm/blob/master/LICENSE).
* FastNoiseSIMD is licensed under [the MIT license](https://github.com/Auburns/FastNoiseSIMD/blob/master/LICENSE).
* TinySpline is licensed under [the MIT license](https://github.com/msteinbeck/tinyspline/blob/master/LICENSE).

### Currently not in use
* Open Asset Import Library (assimp) is licensed under [a 3-clause BSD license](http://www.assimp.org/main_license.html).

### Other resources
Other resources are licensed under their respective licenses.

Grass texture is from [Free Seamless Green Grass Textures](http://www.brusheezy.com/textures/20185-seamless-green-grass-textures).

Pink Marble Pavers Or Tiles Background Texture is from [My Free Textures](http://www.myfreetextures.com/marbles-pavers-tiles-background-texture/).
pavers1b2.bmp is scaled down and converted into BMP from the original `pavers1b2.jpg`.
License conditions are available on [My Free Textures License/TOU page](http://www.myfreetextures.com/sample-page/).

kongtext font is made by [codeman38](http://zone38.net/), see
res/fonts/kongtext/license.txt for the license.

Laser scanning data of Helsinki, Joensuu, and other Finnish cities is
licensed under a Creative Commons Attribution 4.0 International License (CC-BY).
Contains data from [the National Land Survey of Finland Topographic Database 08/2016](http://www.maanmittauslaitos.fi/en/opendata-licence-cc40).
Reference system is ETRS-TM35FIN and distribution format is LAZ.

[Shuttle Radar Topography Mission (SRTM)](https://www2.jpl.nasa.gov/srtm/) data around Bolivian altiplano and
elsewhere in the world between 56° S and 60° N is in the public domain.
SRTM is a [NASA (National Aeronautics and Space Administration)](https://www.nasa.gov/) mission.
SRTM data shipped with Ylikuutio belongs to SRTMGL3 dataset.
Information about different SRTM datasets is available in [OpenStreetMap Wiki](http://wiki.openstreetmap.org/wiki/SRTM).

[Rigged and animated cat](https://www.blendswap.com/blends/view/86110) is made by JonasDichelle and it is licensed
under [Creative Commons Attribution 3.0 Unported (CC BY 3.0) license](https://creativecommons.org/licenses/by/3.0/).
The `cat.fbx` file shipped with Ylikuutio is made from the original
`cat.blend` by exporting the object in [FBX](https://en.wikipedia.org/wiki/FBX) file format, using [Blender](https://www.blender.org/).

Suzanne the monkey is a standard [Blender](https://www.blender.org/) object. According to Blender
license information: "All your artwork – images or movie files –
including the .blend files and other data files Blender can write,
is free for you to use as you like." Ylikuutio does not contain
any code from Blender, however. [Blender itself is released under
the GNU General Public License (GPL) 2 or later](https://www.blender.org/about/license/).

## Compiling
Ylikuutio can be compiled with GCC, Clang or Visual Studio.
In Visual Studio the compiling may break due to compiler-specific bugs.
Cross compiling from Linux© to Windows© using GCC works fine.
C++14 support is required.
OpenGL 3.0 or newer is required.
CMake 2.6.2 or newer is needed for the compiling process.
CMake uses git for downloading Google Test testing framework.

Ylikuutio repository in GitHub has 2 branches: `master` & `coverity_scan`.
master is the branch that should be up to date and it's the one to build.
`coverity_scan` is for Synopsys© Coverity Scan© analysis tool which is run through
Travis CI. However, Coverity Scan analysis tool configuration in `.travis.yml`
is not yet ready and does not yet work.

In Linux it's simple.

First, install all the necessary compilers, tools and libs. You may use
your favorite package manager such as apt, aptitude, apt-get, yum etc.
You all need these packages: cmake make g++ gcc libx11-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxrandr-dev libxext-dev libxi-dev libxinerama-dev
Eg. with apt:

    $ sudo apt install cmake build-essential libx11-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxrandr-dev libxext-dev libxi-dev libxinerama-dev

If you are doing a cross compile from Linux to Windows, you need also:

    $ sudo apt install g++-mingw-w64 gcc-mingw-w64 binutils-mingw-w64

If you are doing a cross compile from Linux to Android(TM), you need also:

    $ sudo apt install google-android-ndk-installer

However, cross compiling from Linux to Android does not work yet!

Then, to compile with GCC, in Ylikuutio install directory:

    $ mkdir build
    $ cd build
    $ cmake ..
    $ make

To make compiling faster you probably want to use several threads:

    $ make -j $(($(nproc) - 1))

Or, to compile with Clang, again in Ylikuutio install directory:

    $ mkdir build
    $ cd build
    $ export CC='/usr/bin/clang'
    $ export CXX='/usr/bin/clang++'
    $ cmake ..
    $ make

If you have problems compiling tests or for some other reason don't want
to compile tests, in CMakeLists.txt comment out the line that says:
`set(DO_UNIT_TESTS_WITH_GOOGLE_TEST true)`

To cross compile from Linux to Windows:

    $ mkdir build_windows
    $ cd build_windows
    $ cmake -DCMAKE_TOOLCHAIN_FILE=../w64.cmake ..
    $ make

To cross compile from Linux to Android(TM) (using Android(TM) NDK):

    $ mkdir build_android
    $ cd build_android
    $ cmake -DCMAKE_TOOLCHAIN_FILE=../android.cmake ..
    $ make

However, cross compiling from Linux to Android does not work yet!

Compiling in Visual Studio is more difficult. The recommended way to
get a binary for Windows is to cross compile from Linux to Windows.

To run Ajokki (working title based on Finnish bus body manufacturer),
a demo program to check out some properties of Ylikuutio 3D engine:

In Linux:

    $ ./ajokki

In Windows:

    > ajokki.exe

F to toggle flying on off, arrow keys work too.
F1 toggles help display and there you'll see some more options to try.

To run tests (coverage is still quite limited but underway):

    $ ./unit_tests_with_Google_Test

## Ylikuutio usage
This part reflects the current usage of Ylikuutio and will change as new
functionality is implemented.

At the moment, you need a main class (for an example, please see
`code/ajokki/ajokki.cpp`) which starts your game/simulation (initialization),
runs the game/simulation (the main loop) and ends the program (cleaning-up).
In all these phases mentioned above Ylikuutio library functions may be used.
Ylikuutio library code is located in `code/ylikuutio/` tree. Ylikuutio code
may change a lot and so far no API has been defined. Ajokki and Ylikuutio
code itself are the best references on how to use Ylikuutio in practice.

## FAQ
Q: What is "Ylikuutio"?
A: In Finnish, "yli" means ["over"](https://en.wiktionary.org/wiki/yli-), and "kuutio" means ["cube"](https://en.wiktionary.org/wiki/kuutio).
   So, "Ylikuutio" is a reference to a [hypercube](https://en.wikipedia.org/wiki/Hypercube).

Q: How is Ylikuutio software developed?
A: In [Debian GNU/Linux](https://www.debian.org/) ([Debian Stretch](https://wiki.debian.org/DebianStretch) at the moment), using [Vim](http://www.vim.org/).

Q: For what kinds of software Ylikuutio can be used?
A: Ylikuutio can be used for all kinds of 3D games and simulations.
   At the moment no specific support for 2D is available, but naturally
   3D graphics can also be used to present a 2D world.

Q: What are the design goals for Ylikuutio?
A: Ylikuutio aims to be a fast and flexible 3D game/simulation engine
   and fulfil my own requirements for my own indie game projects.

Q: What are the target platforms of Ylikuutio?
A: Ylikuutio targets Linux, Windows and Android, in this order.
   Cross-compiling from Linux to Windows works!
   Cross-compiling from Linux to Android is not implemented yet.
   Currently only 64-bit environments are supported.

Q: What graphics APIs Ylikuutio uses?
A: Ylikuutio targets OpenGL version 3.1, but so far 3.0 works too,
   ie. all currently used functionality is available in OpenGL 3.0.

Q: Are there plans to support other graphics APIs?
A: Newer OpenGL versions may be supported in the future, but so far
   OpenGL 3.1 fulfils my requirements.

Q: Does Ylikuutio use modern OpenGL (VBOs)?
A: Yes, Ylikuutio uses VBOs (vertex buffer objects) and VBO indexing.

Q: Is Ylikuutio based on some other 3D engine?
A: Some parts of Ylikuutio (shaders, some file loaders, etc.) are based
on [http://www.opengl-tutorial.org/](http://www.opengl-tutorial.org/), which I really recommend for anyone
interested in learning OpenGL programming. Ylikuutio also uses external
libraries such as TinyScheme, FastNoiseSIMD, GLEW, GLFW, GLM, and
pugixml. The rest is written from scratch.

Q: Why TinyScheme is chosen as the scripting language of Ylikuutio?
A: I like Lisp-family languages and TinyScheme fulfils my
   requirements related to a small size and a suitable license.

## Implemented functionality
* 3D rendering
* 2D text
* support for different height map formats (SRTM, LAZ)
* instant rebinding of instances of classes belonging to rendering hierarchy
* callbacks
* fully functioning in-game console

## Future developments underway:
* option for wireframe models (`enable wireframe`, `disable wireframe`)
* full support for different keyboard layouts in console
* custom keyboard mappings in Ajokki
* command to read console command input from file
* command to record gameplay
* command to play recorded gameplay
* running some Linux command line commands in console, with Toybox
* option to disassemble some Ylikuutio code (`Entity` objects) using NDISASM
* copy-paste in console (Shift-Ins for paste)
* console reference manual (`man` command)
* rendering to texture (for mirrors and displays)
* partially transparent 2D text
* 3D text
* partially transparent 3D text
* multiple scenes in the same `Universe` (`activate` console command)
* coordinates relative to other objects, not only to `Universe` object
* practically infinite voxel worlds (limited by `float` precision)
* collision detection between objects
* octree space partitioning
* possibility to create scenes with different spatial scales
* background loading of `Scene`s
* objects (`Species` in Ylikuutio terminology) with modifiable vertices
* making holes in objects
* splitting of objects into 2 or more pieces
* cementing of 2 or more objects into one
* morphing between objects (`Species` in Ylikuutio terminology)
* morphing between objects (`Species`) and 3D text (`Glyph`s)
* ray casting for vertex selection and vertex modifications
* vegetation created with L-system fractals
* objects with 4 or more spatial dimensions, projected to 3D space before rendering to screen
* more shaders
* sky dome
* railways
* roads
* trains, trams, and road vehicles
* more realistic static water
* flowing water
* snow and ice
* more physics
* artificial intelligence (AI) creatures
* A\* and Theta\* pathfinding
* TinyScheme as scripting language
* visual pattern recognition for AI: V1 (primary visual cortex) and V2 simulation
* GUI for scripting, asset creation etc.
* Internet gaming with ASIO
* audio with Simple DirectMedia Layer (SDL)

## Trademarks:
Android© is a trademark of Google Inc. See [https://developer.android.com/legal.html](https://developer.android.com/legal.html).
Coverity© and Coverity Scan© are registered trademarks of Synopsys, Inc. in the US and/or other countries. See [https://www.synopsys.com/company/legal/trademarks-brands.html](https://www.synopsys.com/company/legal/trademarks-brands.html).
Linux© is the registered trademark of Linus Torvalds in the U.S. and other countries. See [https://www.linuxmark.org/programs/legal/trademark/attribution](https://www.linuxmark.org/programs/legal/trademark/attribution).
Synopsys© is a registered trademarks of Synopsys, Inc. in the US and/or other countries. See [https://www.synopsys.com/company/legal/trademarks-brands.html](https://www.synopsys.com/company/legal/trademarks-brands.html).
Windows© is a registered trademark of Microsoft. See [https://www.microsoft.com/en-us/legal/intellectualproperty/trademarks/usage/general.aspx](https://www.microsoft.com/en-us/legal/intellectualproperty/trademarks/usage/general.aspx).

## Contact info
(found bugs and suggestions are very welcome!)

| variable       | value                                                         |
|:-------------- |:------------------------------------------------------------- |
| name           | Antti Nuortimo                                                |
| GitHub         | https://github.com/nrz                                        |
| Stack Overflow | http://stackoverflow.com/users/1310991/nrz                    |
| email          | antti dot nuortimo at gmail dot com                           |
|                | (please write 'ylikuutio' to email title to escape /dev/null) |

Work offers are also very welcome!
