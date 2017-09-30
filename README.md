# Ylikuutio. A 3D game and simulation engine.
A hobby project of mine. Work in progress.

Travis CI, master branch: ![Travis CI master branch status](https://travis-ci.org/nrz/ylikuutio.svg?branch=master)

Travis CI, coverity_scan branch: ![Travis CI coverity_scan branch status](https://travis-ci.org/nrz/ylikuutio.svg?branch=coverity_scan)

## License
Ylikuutio 3D engine is under The GNU General Public License 3,
or (at your option) any later version. See COPYING file.
All my code copyright (C) 2016-2017 Antti Nuortimo.

The source code from http://www.opengl-tutorial.org/ is licensed
under WTFPL Public Licence version 2.
http://www.opengl-tutorial.org/download/

Open Asset Import Library (assimp) is licensed
under a 3-clause BSD license.
http://www.assimp.org/main_license.html

TinyScheme is licensed under BSD-style license.
http://tinyscheme.sourceforge.net/license.txt

FastNoiseSIMD is licensed under the MIT license.
https://github.com/Auburns/FastNoiseSIMD/blob/master/LICENSE

The OpenGL Extension Wrangler Library (GLEW) is licensed
under the Modified BSD License, the Mesa 3-D License (MIT)
and the Khronos License (MIT).
https://github.com/nigels-com/glew#copyright-and-licensing

GLFW is licensed under the zlib/libpng license.
http://www.glfw.org/license.html

OpenGL Mathematics (GLM) is licensed under The Happy Bunny License
(Modified MIT License) and MIT License.
http://glm.g-truc.net/copying.txt

pugixml is licensed under MIT license.
https://github.com/zeux/pugixml/blob/master/README.md

Other resources are under their respective licenses.

Grass texture is from Free Seamless Green Grass Textures:
http://www.brusheezy.com/textures/20185-seamless-green-grass-textures

Pink Marble Pavers Or Tiles Background Texture is from www.myfreetextures.com .
pavers1b2.bmp is scaled down and converted into BMP from the original pavers1b2.jpg .
http://www.myfreetextures.com/marbles-pavers-tiles-background-texture/
License conditions are available on www.myfreetextures.com website:
http://www.myfreetextures.com/sample-page/

UV map texture is from opengl-tutorial:
http://www.opengl-tutorial.org/beginners-tutorials/tutorial-8-basic-shading/

kongtext font is made by codeman38 (http://zone38.net/), see
res/fonts/kongtext/license.txt for the license.

Laser scanning data of Helsinki, Joensuu, and other Finnish cities is
licensed under a Creative Commons Attribution 4.0 International License (CC-BY).
Contains data from the open data of the National Land Survey of Finland.
Reference system is ETRS-TM35FIN and distribution format is LAZ.
http://www.maanmittauslaitos.fi/en/professionals/digital-products/datasets-free-charge/terms-use-license/national-land-survey-open-data-cc-40-licence

Shuttle Radar Topography Mission (SRTM) data around Bolivian altiplano and
elsewhere in the world between 56° S and 60° N is in the public domain.
SRTM is a NASA (National Aeronautics and Space Administration) mission.
SRTM data shipped with Ylikuutio belongs to SRTMGL3 dataset.
OpenStreetMap Wiki provides information about different SRTM datasets:
http://wiki.openstreetmap.org/wiki/SRTM

Suzanne the monkey is a standard Blender object. According to Blender
license information: "All your artwork – images or movie files –
including the .blend files and other data files Blender can write,
is free for you to use as you like." Ylikuutio does not contain
any code from Blender, however. Blender itself is released under
the GNU General Public License (GPL) 2 or later.
https://www.blender.org/about/license/

## Compiling
Ylikuutio can be compiled with GCC, Clang or Visual Studio.
In Visual Studio the compiling may break due to compiler-specific bugs.
Cross compiling from Linux to Windows using GCC works fine.
C++14 support is required.
OpenGL 3.0 or newer is required.
CMake 2.6.2 or newer is needed for the compiling process.
CMake uses git for downloading Google Test testing framework.

In Linux it's simple.

First, install all the necessary compilers, tools and libs. You may use
your favorite package manager such as aptitude, apt-get, yum etc.
You all need these packages: cmake make g++ gcc libx11-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxrandr-dev libxext-dev libxi-dev libxinerama-dev
Eg. with aptitude:

    $ sudo aptitude install cmake build-essential libx11-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxrandr-dev libxext-dev libxi-dev libxinerama-dev

If you are doing a cross compile from Linux to Windows, you need also:

    $ sudo aptitude install g++-mingw-w64 gcc-mingw-w64 binutils-mingw-w64

If you are doing a cross compile from Linux to Android(TM), you need also:

    $ sudo aptitude install google-android-ndk-installer

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
A: In Finnish, "yli" means "over", and "kuutio" means "cube".
   So, "Ylikuutio" is a reference to a hypercube.
   https://en.wikipedia.org/wiki/Hypercube

Q: How is Ylikuutio software developed?
A: In Debian GNU/Linux (Debian Stretch at the moment), using Vim.

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
   Cross-compiling for Android is not implemented yet.
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
on http://www.opengl-tutorial.org/ , which I really recommend for anyone
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
* full support for different keyboard layouts in console
* partially transparent 2D text
* 3D text
* multiple scenes in the same `Universe`
* coordinates relative to other objects, not only to `Universe` object
* collision detection between objects
* octree space partitioning
* possibility to create scenes with different spatial scales
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
* water
* more physics
* artificial intelligence (AI) creatures
* TinyScheme as scripting language
* visual pattern recognition for AI
* GUI for scripting, asset creation etc.
* Internet gaming
* sound

## Trademarks:
Android is a trademark of Google Inc. See https://developer.android.com/legal.html .

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
