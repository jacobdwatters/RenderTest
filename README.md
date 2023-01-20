# Set up Developmnet Enviornment (From textbook)
For  coding, you  can  use  any  editor  of your  choice, but  at the  end  of  this  step y ou  should  be  able  to  use 
cmake to configure a Makefile and  use make to build your  OpenGL program from a terminal window. 
Below, we will give the steps for lab PCs, but you should be able to apply these to your own laptop/PC with 
small tweaks. The critical point here is that, in order to be able to use cmake, you need to do some extra 
work such as building glm  and  glfw from source code. Here is the step-by-step setup of the development 
environment:  
  
1. Install a compiler that includes OpenGL. We will use w64devkit:  
o Download it from 
▪ https://github.com/skeeto/w64devkit/releases  
▪ https://github.com/skeeto/w64devkit/releases/download/v1.17.0/w64devkit -
1.17.0.zip 
o Unzip to contents to your network folder  Z:\w64devkit 
▪ Hint: Use 7zip to unzip it faster 
o Set the environment variable PATH to the Z:\w64devkit\bin directory 
▪ In the PowerShell, type $Env:PATH = "Z:\w64devkit\bin;"+$Env:PATH 
▪ Note: We will use this PowerShell in the subsequent steps , and you need to set the 
PATH using the command above every time you open a new PowerShell 
o In a terminal window, check that this step is complete, by typing gcc --version 
▪ You should get an output like below: 
gcc (GCC) 12.2.0 
Copyright (C) 2022 Free Software Foundation, Inc. 
This is free software; see the source for copying conditions.  There is 
NO warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR 
PURPOSE. 
 
 
 
2. Install cmake: 
o Download it from 
▪ https://cmake.org/download/  Binary Distributions -> Windows X64 zip 
▪ https://github.com/Kitware/CMake/releases/download/v3.25.1/cmake -3.25.1-
windows-x86_64.zip  
o Unzip to contents to some temp folder  
▪ Hint: Use 7zip to unzip it faster 
o Copy the files in the bin directory to Z:\w64devkit\bin directory 
o Copy the folders in the share directory to Z:\w64devkit\share directory 
o Optional: Copy the doc and man directories to Z:\w64devkit 
o In a terminal window, check that this step is complete, by typing cmake --version 
▪ You should get an output like below: 
cmake version 3.25.1 
 
CMake suite maintained and supported by Kitware (kitware.com/cmake).  
 
3. Build GLFW from source: 
o Download it from 
▪ https://www.glfw.org/  The link at the top right. 
▪ https://github.com/glfw/glfw/releases/download/3.3.8/glfw -3.3.8.zip   
o Unzip to contents to some temp folder  
o Go to the unzipped folder in the PowerShell and configure a build directory using cmake: 
▪ cmake -G "MinGW Makefiles" -D CMAKE_INSTALL_PREFIX=Z:/GLFW . -B build 
o Go to the build directory 
o If you forget to use CMAKE_INSTALL_PREFIX option, you may manually edit the file 
CMakeCache.txt using your favorite editor 
▪ Change the two lines about CMAKE_INSTALL_PREFIX: 
• CMAKE_INSTALL_PREFIX:PATH=Z:/GLFW 
• _GNUInstallDirs_LAST_CMAKE_INSTALL_PREFIX:INTERNAL=Z:/GLFW 
o Create the GLFW directory in PowerShell: 
▪ mkdir Z:/GLFW  
o Build GLFW by typing make install in the build directory 
o The last 12 lines of the output of the build should look like below: 
[100%] Built target windows 
Install the project... 
-- Install configuration: "" 
-- Installing: Z:/GLFW/lib/libglfw3.a 
-- Installing: Z:/GLFW/include/GLFW 
-- Installing: Z:/GLFW/include/GLFW/glfw3.h 
-- Installing: Z:/GLFW/include/GLFW/glfw3native.h 
-- Installing: Z:/GLFW/lib/cmake/glfw3/glfw3Config.cmake 
-- Installing: Z:/GLFW/lib/cmake/glfw3/glfw3ConfigVersion.cmake 
-- Installing: Z:/GLFW/lib/cmake/glfw3/glfw3Targets.cmake 
-- Installing: Z:/GLFW/lib/cmake/glfw3/glfw3Targets-noconfig.cmake 
-- Installing: Z:/GLFW/lib/pkgconfig/glfw3.pc 
o The config file generated, glfw3Config.cmake, will be needed when building the sample 
programs of the textbook. 
o Copy the Z:/GLFW/include/GLFW  directory to Z:/w64devkit/x86_64-w64-
mingw32/include 
o Copy the file Z:/GLFW/lib/libglfw3.a to Z:/w64devkit/x86_64-w64-mingw32/lib 
 
4. Build glm from source 
o Clone the source from github (This is important. If you download a release instead, it will 
not have a “install” target in the makefile) 
▪ https://github.com/g-truc/glm    Code → Download zip    
o Unzip to contents to some temp folder  
▪ Hint: Use 7zip to unzip it faster 
o Go to the unzipped folder in PowerShell and configure a build directory using cmake: 
▪ cmake -G "MinGW Makefiles" -D GLM_TEST_ENABLE=OFF -D 
CMAKE_INSTALL_PREFIX=Z:/GLM . -B build 
o Go to the build directory 
o Create the GLM directory in PowerShell: 
▪ mkdir Z:/GLM  
o Build GLM by typing make install in the build directory. This will copy all the glm header 
files to Z:/GLM and create two cmake config files in the Z:/GLM/lib directory, which will be 
needed when building sample programs. 
o The last 4 lines of the output of the build should look like below: 
-- Installing: Z:/GLM/include/glm/vec4.hpp 
-- Installing: Z:/GLM/include/glm/vector_relational.hpp 
-- Installing: Z:/GLM/lib/cmake/glm/glmConfig.cmake 
-- Installing: Z:/GLM/lib/cmake/glm/glmConfigVersion.cmake  
o The config file generated, glmConfig.cmake, will be needed when building the sample 
programs of the textbook. 
o Copy the Z:/GLM/include/glm  directory to Z:/w64devkit/x86_64-w64-mingw32/include 
   
5. Download GLAD (this step is not required for building the sample programs, but you will need 
GLAD or GLEW for your own OpenGL Programs) 
o Go to https://glad.dav1d.de/    
o Select API → gl → Version 4.3 and Profile →Core 
o Under Extensions click on ADD ALL 
o Click on GENERATE and download the file, glad.zip, in the following page. 
o Unzip to contents to some temp folder  
o Copy the include/glad and include/KHR directories to Z:/w64devkit/x86_64-w64-
mingw32/include. When prompted, override the KHR header file. 
o You will use glad.c under the src directory as and additional source file in your own 
OpenGL projects.
