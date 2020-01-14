# HD2PC - Hardware Depth to Point Cloud C library

Placeholder for future library with rough software implementation.

Work in early progress. Not usable yet.

See [hardware-video-streaming](https://github.com/bmegli/hardware-video-streaming) for other related projects.

## Intent

- hardware accelerated
- unprojection of depth maps to point clouds
- with formats natively compatible with
     - HEVC Main10 Y plane
     - Unity Mesh NativeBuffer interface

This means that we natively wrap HEVC Main10 data and output native compatible Unity vertices data. 

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
git clone https://github.com/bmegli/hardware-depth-to-point-cloud.git

# finally build the library and examples
cd hardware-depth-to-point-cloud
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

For static linking of HD2PC
- copy `hd2pc.h` and `hd2pc.c` to your project and add them in your favourite IDE

For dynamic linking of HD2pC:
- place `hd2pc.h` where compiler can find it (e.g. `make install` for `/usr/local/include/hd2pc.h`)
- place `libhd2pc.so` where linker can find it (e.g. `make install` for `/usr/local/lib/libhd2pc.so`)
- make sure `/usr/local/...` is considered for libraries
- add `hd2pc` to linked libraries in IDE project configuration
- make sure `libhd2pc.so` is reachable to you program at runtime (e.g. set `LD_LIBRARIES_PATH`)

### CMake

Assuming directory structure with HD2PC as `hardware-depth-to-point-cloud` subdirectory (or git submodule) of your project.

```
your-project
│   main.cpp
│   CMakeLists.txt
│
└───hardware-depth-to-point-cloud
│   │   hd2pc.h
│   │   hd2pc.c
│   │   CMakeLists.txt
```

You may use the following top level CMakeLists.txt

``` CMake
cmake_minimum_required(VERSION 3.0)

project(
    your-project
)

# drop the SHARED if you would rather link with HVE statically
add_library(hd2pc SHARED hardware-depth-to-point-cloud/hd2pc.c)

add_executable(your-project main.cpp)
target_include_directories(your-project PRIVATE hardware-depth-to-point-cloud)
target_link_libraries(your-project hd2pc)
```

### Manually

Assuming your `main.c`/`main.cpp` and `hd2pc.h`, `hd2pc.c` are all in the same directory:

C
```bash
gcc main.c hd2pc.c -o your-program
```

C++
```bash
gcc -c hd2pc.c
g++ -c main.cpp
g++ hd2pc.o main.o -o your-program
```

## License

Library is licensed under Mozilla Public License, v. 2.0

This is similiar to LGPL but more permissive:
- you can use it as LGPL in prioprietrary software
- unlike LGPL you may compile it statically with your code

Like in LGPL, if you modify this library, you have to make your changes available.
Making a github fork of the library with your changes satisfies those requirements perfectly.
