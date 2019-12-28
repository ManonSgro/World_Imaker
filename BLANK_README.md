<!--
*** README Template by othneildrew
*** https://github.com/othneildrew
*** an issue with the tag "enhancement".
*** Thanks again! Now go create something AMAZING! :D
***
***
***
*** To avoid retyping too much info. Do a search and replace for the following:
*** github_username, repo, twitter_handle, email
-->





<!-- PROJECT SHIELDS -->
<!--[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]-->



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

This project has been tested on Linux Ubuntu 18.04.

Make sure your environnement supports OpenGL 3 or higher.
```sh
glxinfo | grep "OpenGL version"
OUTPUT: OpenGL version string: 4.6.0 NVIBIA 430.26
```
Make sure SDL2 is intalled.
```sh
dpkg -l | grep libsdl2
OUTPUT: libsdl2-dev
```
If not, install it.
```sh
apt-get install libsdl2-dev
```

### Installation
 
1. Clone the repo
```sh
git clone https://github.com/ManonSgro/World_Imaker.git
```
2. Create the build directory and move into it
```sh
mkdir build
cd build
```
3. Run cmake and build the project
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

This program include basic functionnalities to create and edit a 3D scene. Once the program is running, use the keyboard or the menus to edit the scene.

You can move the cursor in the scene, add/delete cubes and modify their texture. You can also extrude/dig into the scene from the *cube menu*.

![World Imaker Screenshot](/img/screenshot1.png?raw=true "World Imaker - Cube Editing")

You can control a directional light and a poncutal light. Turn them on/off and move their position from the *light menu*.

![World Imaker Screenshot](/img/screenshot1.png?raw=true "World Imaker - Light Editing")

The *file menu* allows you to save and load scenes. Your current scene will automatically be saved if you quit the program in `../backup/backup.txt`.

![World Imaker Screenshot](/img/screenshot1.png?raw=true "World Imaker - File settings")

You can use the *procedural generation* option to create a new scene based on the chosen control points.

![World Imaker Screenshot](/img/screenshot1.png?raw=true "World Imaker - Procedural generation")


_For more examples, please refer to the [Documentation](https://rawcdn.githack.com/ManonSgro/World_Imaker/Manon/build/doc/html/index.html)_

<!-- AUTHORS -->
## Authors

* **Amélia Mansion** - [Github](https://github.com/MansionAmelia)
* **Manon Sgro'** - [Github](https://github.com/ManonSgro)

<!-- ACKNOWLEDGEMENTS -->
## Acknowledgements

* An IMAC Project
* Thanks to [N. Lienart](https://framagit.org/nicolaslienart) for his [SDL2 template](https://framagit.org/nicolaslienart/imac-s3-opengl/tree/master/GLImac-Template-SDL2).
* Special thanks to C. Noel, [P. Thiel](https://github.com/opium75) and [J. Fouchy](https://github.com/julesfouchy) for their help on debugging this project.
```
while(project!=done){
    //live(); --> don't!
    for(int time = 0; time < infinity; time++){
        code();
    }
    if(bug){
        cry();
        callForHelp();
        sayThanks();
        sayThanks(); // again
        project = done;
    }
}
sleep();
```