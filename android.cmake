# https://cmake.org/Wiki/CMake_Cross_Compiling
# http://www.glfw.org/docs/latest/compile.html#compile_deps_mingw_cross
# the name of the target operating system
set(CMAKE_SYSTEM_NAME Android)
set(CMAKE_SYSTEM_VERSION 23)
set(CMAKE_ANDROID_ARCH_ABI arm64-v8a)
set(CMAKE_ANDROID_NDK /usr/lib/android-ndk)
# set(CMAKE_ANDROID_ARM_MODE ON)
# set(CMAKE_ANDROID_ARM_NEON ON)
