# Set up Development Environment (From textbook)

1. Install a compiler that includes OpenGL. We will use w64devkit:  
   o Download it from
    - https://github.com/skeeto/w64devkit/releases  
   - https://github.com/skeeto/w64devkit/releases/download/v1.17.0/w64devkit -
   1.17.0.zip
   o Unzip to contents to your network folder  C:\w64devkit
   - Hint: Use 7zip to unzip it faster
   o Set the environment variable PATH to the C:\w64devkit\bin directory
   - In the PowerShell, type $Env:PATH = "C:\w64devkit\bin;"+$Env:PATH
   - Note: We will use this PowerShell in the subsequent steps , and you need to set the
   PATH using the command above every time you open a new PowerShell
   o In a terminal window, check that this step is complete, by typing gcc --version
   - You should get an output like below:
   gcc (GCC) 12.2.0
   Copyright (C) 2022 Free Software Foundation, Inc.
   This is free software; see the source for copying conditions.  There is
   NO warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR
   PURPOSE.


2. Install cmake:
   o Download it from
   - https://cmake.org/download/  Binary Distributions -> Windows X64 zip
   - https://github.com/Kitware/CMake/releases/download/v3.25.1/cmake -3.25.1-windows-x86_64.zip  
   o Unzip to contents to some temp folder  
   - Hint: Use 7zip to unzip it faster
   o Copy the files in the bin directory to C:\w64devkit\bin directory
   o Copy the folders in the share directory to C:\w64devkit\share directory
   o Optional: Copy the doc and man directories to C:\w64devkit
   o In a terminal window, check that this step is complete, by typing cmake --version
   - You should get an output like below:
   cmake version 3.25.1

CMake suite maintained and supported by Kitware (kitware.com/cmake).

3. Build GLFW from source:
   o Download it from
   - https://www.glfw.org/  The link at the top right.
   - https://github.com/glfw/glfw/releases/download/3.3.8/glfw -3.3.8.zip   
   o Unzip to contents to some temp folder  
   o Go to the unzipped folder in the PowerShell and configure a build directory using cmake:
   - cmake -G "MinGW Makefiles" -D CMAKE_INSTALL_PREFIX=C:/GLFW . -B build
   o Go to the build directory
   o If you forget to use CMAKE_INSTALL_PREFIX option, you may manually edit the file
   CMakeCache.txt using your favorite editor
   - Change the two lines about CMAKE_INSTALL_PREFIX:
   • CMAKE_INSTALL_PREFIX:PATH=C:/GLFW
   • _GNUInstallDirs_LAST_CMAKE_INSTALL_PREFIX:INTERNAL=C:/GLFW
   o Create the GLFW directory in PowerShell:
   - mkdir C:/GLFW  
   o Build GLFW by typing make install in the build directory
   o The last 12 lines of the output of the build should look like below:
   [100%] Built target windows
   Install the project...
   -- Install configuration: ""
   -- Installing: C:/GLFW/lib/libglfw3.a
   -- Installing: C:/GLFW/include/GLFW
   -- Installing: C:/GLFW/include/GLFW/glfw3.h
   -- Installing: C:/GLFW/include/GLFW/glfw3native.h
   -- Installing: C:/GLFW/lib/cmake/glfw3/glfw3Config.cmake
   -- Installing: C:/GLFW/lib/cmake/glfw3/glfw3ConfigVersion.cmake
   -- Installing: C:/GLFW/lib/cmake/glfw3/glfw3Targets.cmake
   -- Installing: C:/GLFW/lib/cmake/glfw3/glfw3Targets-noconfig.cmake
   -- Installing: C:/GLFW/lib/pkgconfig/glfw3.pc
   o The config file generated, glfw3Config.cmake, will be needed when building the sample
   programs of the textbook.
   o Copy the C:/GLFW/include/GLFW  directory to C:/w64devkit/x86_64-w64-
   mingw32/include
   o Copy the file C:/GLFW/lib/libglfw3.a to C:/w64devkit/x86_64-w64-mingw32/lib

4. Build glm from source
   o Clone the source from github (This is important. If you download a release instead, it will
   not have a “install” target in the makefile)
   - https://github.com/g-truc/glm    Code → Download zip    
   o Unzip to contents to some temp folder  
   - Hint: Use 7zip to unzip it faster
   o Go to the unzipped folder in PowerShell and configure a build directory using cmake:
   - cmake -G "MinGW Makefiles" -D GLM_TEST_ENABLE=OFF -D
   CMAKE_INSTALL_PREFIX=C:/GLM . -B build
   o Go to the build directory
   o Create the GLM directory in PowerShell:
   - mkdir C:/GLM  
   o Build GLM by typing make install in the build directory. This will copy all the glm header
   files to C:/GLM and create two cmake config files in the C:/GLM/lib directory, which will be
   needed when building sample programs.
   o The last 4 lines of the output of the build should look like below:
   -- Installing: C:/GLM/include/glm/vec4.hpp
   -- Installing: C:/GLM/include/glm/vector_relational.hpp
   -- Installing: C:/GLM/lib/cmake/glm/glmConfig.cmake
   -- Installing: C:/GLM/lib/cmake/glm/glmConfigVersion.cmake  
   o The config file generated, glmConfig.cmake, will be needed when building the sample
   programs of the textbook.
   o Copy the C:/GLM/include/glm  directory to C:/w64devkit/x86_64-w64-mingw32/include

5. Download GLAD (this step is not required for building the sample programs, but you will need
   GLAD or GLEW for your own OpenGL Programs)
   o Go to https://glad.dav1d.de/    
   o Select API → gl → Version 4.3 and Profile →Core
   o Under Extensions click on ADD ALL
   o Click on GENERATE and download the file, glad.zip, in the following page.
   o Unzip to contents to some temp folder  
   o Copy the include/glad and include/KHR directories to C:/w64devkit/x86_64-w64-
   mingw32/include. When prompted, override the KHR header file.
   o You will use glad.c under the src directory as and additional source file in your own
   OpenGL projects.

OpenGL is provided by tour graphics drivers so just ensure those are up to date.

# Note on Projections
You may see 3D vertex points multiplied with a 4x4 transformation matrix. This multiplication works on homogeneous coordinates.
For more information see https://www.tomdalling.com/blog/modern-opengl/explaining-homogenous-coordinates-and-projective-geometry/
which discusses this and uses the same library to compute these transforms (glm) as in the project

# Project Layout
1. The ingredients directory is mostly provided by the textbook. It has some minor changes and a lot of unnecessary files
have been removed. It contains meshes for the teapot (which have been defined as vertex data in the teapotdata.h file).
It also contains classed for defining object meshes and textures. scenerunner.h contains the main rendering loop.
2. The renderTests directory contains my code (which more or less follows the guide in the textbook).
Most of the code is c++ but there are 4 shader files written in OpenGL shading language (.glsl extension). There are
very simple vertex and fragment shaders for the background and teapot.
3. The image in the background is in the media/texture directory and is a hdr.
4. The build directory contains all the generated files from building the project. This is where the .exe file is 
(build/renderTest/renderTest.exe).

# Building the project.
Assuming you have the environment set up correctly, to build the project you should be able to go to OpenGLTesting/build/renderTest directory in the powershell and type `make`.
Then enter `.\renderTest.exe` to run the file.
