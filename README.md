# Worldsimulator
A Worldsimulator, can be used to show interaction of software pattern

Based on the works of David Jorzik, Felix Schwagereit, Torsten Wohlberedt, Elmar Macek, Frank Haedrich


Prerequisites:
A graphics driver capable of OpenGL
Qt
Qt-Creator (optional, can skip if you know what you do)

How to install:
1. clone repository
2. open src.pro in Qt-Creator, choose Compiler (GNU GCC/MinGW recommended)
3. run qmake
4. build project

if you chose to do a shadow build, you have to copy create a folder named 'viewcontroller' inside your shadow build directory and copy the folder and its contents of src/viewcontroller/Resources into the newly created viewcontroller-folder inside your shadow build directory
