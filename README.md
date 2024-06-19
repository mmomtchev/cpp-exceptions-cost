# The cost of C++ exceptions

This is the code for my medium article

# Building

You will need `meson` on Linux.

## `gcc`

```shell
meson setup gcc
meson compile -v -C gcc
```

## `clang`

You must install `clang`.

```shell
CC=clang CXX=clang++ CFLAGS=-funroll-loops CXXFLAGS=-funroll-loops meson setup clang
meson compile -v -C clang
```

## Intel OneAPI

A very good compiler that few people use because it is not the default one on any OS. Available for Linux in a Debian/Ubuntu and RedHat style-repositories. Uses the `g++` runtime and library. Replace `12` with your `g++` version.

```shell
CC=/opt/intel/oneapi/compiler/latest/linux/bin/icx \
  CXX=/opt/intel/oneapi/compiler/latest/linux/bin/icpx \
  CFLAGS=--gcc-install-dir=/usr/lib/gcc/x86_64-linux-gnu/12 \
  CXXFLAGS=--gcc-install-dir=/usr/lib/gcc/x86_64-linux-gnu/12 \
  meson setup oneapi
meson compile -v -C oneapi
```

# Run

```shell
cd {gcc|clang|oneapi}
bash ../run.sh
```
