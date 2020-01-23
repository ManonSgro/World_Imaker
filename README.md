<!--
*** README Template by othneildrew
*** https://github.com/othneildrew
-->

<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://github.com/ManonSgro/World_Imaker">
    <img src="img/logo.png" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">World Imaker</h3>

  <p align="center">
    A 3D scene editor made with OpenGL and C++.
    <br />
  </p>
</p>



<!-- TABLE OF CONTENTS -->
## Table of Contents

* [About the Project](#about-the-project)
  * [Built With](#built-with)
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
  * [Installation](#installation)
* [Usage](#usage)
* [Authors](#authors)
* [Acknowledgements](#acknowledgements)



<!-- ABOUT THE PROJECT -->
## About The Project

![World Imaker Home Screen Shot](/img/screenshot1.png?raw=true "World Imaker")

The purpose of this project was to create a 3D scene editor-visualizer made of cubes with OpenGL/C++ technologies, and a bit of maths.


### Built With

* [CMake](https://cmake.org/) - Tools designed to build, test and package software
* [glm](https://github.com/g-truc/glm) - OpenGL Mathematics
* [Eigen](https://gitlab.com/libeigen/eigen) - C++ template library for linear algebra
* [imGui](https://github.com/ocornut/imgui) - Graphical user interface library for C++
* [Doxygen](http://www.doxygen.nl/) - Tool for generating documentation



<!-- GETTING STARTED -->
## Getting Started

To get a local copy up and running, follow these simple steps.

### Prerequisites

**This project has been tested on Linux Ubuntu 18.04.**

- OpenGL

Make sure your environnement supports OpenGL 3.0 or later.
```sh
glxinfo | grep "OpenGL version"
OUTPUT: OpenGL version string: 4.6.0 NVIBIA 430.26
```
- SDL

Make sure SDL 2.0 is intalled.
```sh
dpkg -l | grep libsdl2
OUTPUT: libsdl2-dev
```
If not, install it.
```sh
apt-get install libsdl2-dev
```
- CMake

Make sure CMake is installed for building the project. If not, install it :
```
apt-get install cmake
```
More information about CMake installing and running for different platforms on <a href="https://cmake.org">CMake official website</a>.

### Installation
 
1. Clone the repository
```sh
git clone https://github.com/ManonSgro/World_Imaker.git
cd World_Imaker
```
2. Create the build directory and move into it
```sh
mkdir build
cd build
```
3. Run CMake and build the project
```sh
cmake ..
make
```
4. Execute the program
```sh
./bin/World_Imaker
```
5. A window should appear. Have fun!


<!-- USAGE EXAMPLES -->
## Usage

This program include basic functionalities to create and edit a 3D scene. Once the program is running, use the keyboard or the menus to edit the scene.

You can move the cursor in the scene, add/delete cubes and modify their texture. You can also extrude/dig into the scene from the *cube menu*.

<img src="/img/screenshot2.png" alt="World Imaker - Cube Editing" title="World Imaker - Cube Editing" width="auto" height="600" />


You can control a directional light and a spotlight. Turn them on/off and move their position from the *light menu*. You can also change their intensity.

<img src="/img/screenshot4.png" alt="World Imaker - Light Editing" title="World Imaker - Light Editing" width="auto" height="600" />

The *file menu* allows you to save and load scenes. Your current scene will automatically be saved if you quit the program in `../backup/backup.txt`.

<img src="/img/screenshot5.png" alt="World Imaker - File Settings" title="World Imaker - File Settings" width="auto" height="600" />

You can use the *procedural generation* option to create a new scene based on the chosen control points. You can load the control points and the chosen radial basis function from a pre-written file.

<img src="/img/screenshot6.png" alt="World Imaker - Procedural generation" title="World Imaker - Procedural generation" width="auto" height="600" />


_For more information on the functionalities, please refer to the [Documentation](https://rawcdn.githack.com/ManonSgro/World_Imaker/master/build/doc/html/index.html)_.

<!-- AUTHORS -->
## Authors

* **Amélia Mansion** - [Github](https://github.com/MansionAmelia)
* **Manon Sgro'** - [Github](https://github.com/ManonSgro)

<!-- ACKNOWLEDGEMENTS -->
## Acknowledgements

* An IMAC project
* Thanks to [N. Lienart](https://framagit.org/nicolaslienart) for his [SDL2 template](https://framagit.org/nicolaslienart/imac-s3-opengl/tree/master/GLImac-Template-SDL2).
* Special thanks to C. Noel, [P. Thiel](https://github.com/opium75) and [J. Fouchy](https://github.com/julesfouchy) for their help on debugging this project.
```
while(project!=done){
    //live(); --> don't!
    for(int time = 0; time < infinity; time++){
        code();
    }
    if(bug){
        callForHelp();
        sayThanks();
        sayThanks(); // again
        project = done;
    }
}
sleep();
```
