# HDU - Hardware Depth Unprojector library

Hardware implementation of depth map to point cloud unprojection (with color).

See [hardware-video-streaming](https://github.com/bmegli/hardware-video-streaming) for other related projects.

## Intent

For equivalent software implementation see [software](https://github.com/bmegli/hardware-depth-unprojector/tree/software) branch.

## Platforms

Hardware implemenenation uses compute shaders.

This should (in theory) work with:
- Windows and Windows Store, with a DirectX 11 or DirectX 12 graphics API and Shader Model 5.0 GPU
- macOS and iOS using Metal graphics API
- Android, Linux and Windows platforms with Vulkan API
- Modern OpenGL platforms (OpenGL 4.3 on Linux or Windows; OpenGL ES 3.1 on Android). Note that Mac OS X does not support OpenGL 4.3
- Modern consoles (Sony PS4 and Microsoft Xbox One)

Tested only with OpenGL on Desktop (Linux).

Shaders use Unity flavoured HLSL. You may recompile them with Unity for OpenGL, Vulkan etc.

## Hardware

TODO

## Using

Shaders have to be integrated into your workflow.

## License

Code is licensed under Mozilla Public License, v. 2.0

This is similiar to LGPL but more permissive:
- you can use it as LGPL in prioprietrary software
- unlike LGPL you may compile it statically with your code

Like in LGPL, if you modify this library, you have to make your changes available.
Making a github fork of the library with your changes satisfies those requirements perfectly.
