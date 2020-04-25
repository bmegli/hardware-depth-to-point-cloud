# HDU - Hardware Depth Unprojector C library

Placeholder for future library.
Currently simple software implementation.

Work in early progress.

See [hardware-video-streaming](https://github.com/bmegli/hardware-video-streaming) for other related projects.

## Intent

- hardware accelerated
- unprojection of depth maps to point clouds
- with formats natively compatible with
     - HEVC Main10 p010le Y plane
     - Unity Mesh float3 NativeBuffer interface
     - rgb0/rgba color pixel format
     - Unity Mesh color32 NativeBuffer interface

This means that we natively wrap HEVC Main10 and rgb0/rgba data and output native compatible Unity vertices/colors data. 

## Platforms 

## Hardware

## Dependencies

## Building Instructions

Tested on Ubuntu 18.04.

``` bash
# update package repositories
sudo apt-get update 
# get compilers and make and cmake
sudo apt-get install build-essential
# get cmake - we need to specify libcurl4 for Ubuntu 18.04 dependencies problem
sudo apt-get install libcurl4 cmake
# get git
sudo apt-get install git
# clone the repository
git clone https://github.com/bmegli/hardware-depth-unprojector.git

# finally build the library and examples
cd hardware-depth-unprojector
mkdir build
cd build
cmake ..
make
```

## Running Example

## Using

## Compiling your code

You have several options.

### IDE (recommended)

For static linking of HDU
- copy `hdu.h` and `hdu.c` to your project and add them in your favourite IDE

For dynamic linking of HD2PC:
- place `hdu.h` where compiler can find it (e.g. `make install` for `/usr/local/include/hdu.h`)
- place `libhdu.so` where linker can find it (e.g. `make install` for `/usr/local/lib/libhdu.so`)
- make sure `/usr/local/...` is considered for libraries
- add `hdu` to linked libraries in IDE project configuration
- make sure `libhdu.so` is reachable to you program at runtime (e.g. set `LD_LIBRARIES_PATH`)

### CMake

Assuming directory structure with HDU as `hardware-depth-unprojector` subdirectory (or git submodule) of your project.

```
your-project
│   main.cpp
│   CMakeLists.txt
│
└───hardware-depth-unprojector
│   │   hdu.h
│   │   hdu.c
│   │   CMakeLists.txt
```

You may use the following top level CMakeLists.txt

``` CMake
cmake_minimum_required(VERSION 3.0)

project(
    your-project
)

# drop the SHARED if you would rather link with HDU statically
add_library(hdu SHARED hardware-depth-unprojector/hdu.c)

add_executable(your-project main.cpp)
target_include_directories(your-project PRIVATE hardware-depth-unprojector)
target_link_libraries(your-project hdu)
```

### Manually

Assuming your `main.c`/`main.cpp` and `hdu.h`, `hdu.c` are all in the same directory:

C
```bash
gcc main.c hdu.c -o your-program
```

C++
```bash
gcc -c hdu.c
g++ -c main.cpp
g++ hdu.o main.o -o your-program
```

## License

Library is licensed under Mozilla Public License, v. 2.0

This is similiar to LGPL but more permissive:
- you can use it as LGPL in prioprietrary software
- unlike LGPL you may compile it statically with your code

Like in LGPL, if you modify this library, you have to make your changes available.
Making a github fork of the library with your changes satisfies those requirements perfectly.
