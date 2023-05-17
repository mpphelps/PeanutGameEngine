# PeanutGameEngine
OpenGL Game Engine

To build, clone or fork the repo, open in visual studio and run in x64 platform.  x86 is not supported due to library dependencies not having support.

First build will likely fail due to missing assimp-vc140-mt.dll.
The ASSIMP file assimp-vc140-mt.dll needs manually moved into either the release or debug folder.  Need to figure out how to reference this DLL correctly so it gets copied during build. 
File is located in $\PeanutGameEngine\Dependencies\ASSIMP
