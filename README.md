## Before getting started
Because I'm using C++ to compiling OpenGL files, there are some step to get start

---

1. PC setups:
    - Operating System: Windows 10 professional(21H1)
    - Compiler: Visual studio 2019
2. GLUT library source: **http://www.opengl.org/resources/libraries/glut/glutdlls37beta.zip**
3. Install GLUT library in your C++ compiler:
    1. After unzip the zip file, you will get:
        1. glut.dll
        2. glut.h
        3. glut.lib
        4. glut32.dll
        5. glut32.lib
    2. Creating a new folder **GL** in **C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.29.30133\include** , then put **glut.h** in the folder
    3. Putting **glut.lib** and **glut32.lib** in **C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.29.30133\lib\x86**
    4. Putting **glut.dll** and **glut32.dll** in **C:\Windows\SysWOW64**
    5. Back to Visual Studio, and creating a new .cpp file.
    6. Find: Project(P) -> Manage NuGet Packages(N)
    7. Search **nupengl** and download the first one.
    8. Start Compiling your OpenGL files.
