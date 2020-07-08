# https://cmake.org/Wiki/CMake_Cross_Compiling
# http://www.glfw.org/docs/latest/compile.html#compile_deps_mingw_cross
# the name of the target operating system
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_VERSION 1)

# which compilers to use for C and C++
set(CMAKE_C_COMPILER /usr/bin/x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/x86_64-w64-mingw32-g++)
set(CMAKE_RC_COMPILER /usr/bin/x86_64-w64-mingw32-windres)
set(CMAKE_ASM_YASM_COMPILER /usr/bin/yasm)
set(CMAKE_RANLIB /usr/bin/x86_64-w64-mingw32-gcc-ranlib)

# here is the target environment located
set(CMAKE_FIND_ROOT_PATH /usr/x86_64-w64-mingw32/)

# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search
# programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(CMAKE_C_FLAGS "-Wl,-Bstatic -DSDL_STATIC -static -static-libgcc -lpthread -O3 -Wall -Werror=return-type -s")
set(CMAKE_CXX_FLAGS "-Wl,-Bstatic -static -static-libgcc -static-libstdc++ -lpthread -O3 -Wall -Werror=return-type -s")
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "-Wl,-Bstatic -static -static-libgcc -O3 -Wall -Werror=return-type -s")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "-Wl,-Bstatic -static -static-libgcc -static-libstdc++ -O3 -Wall -Werror=return-type -s")
