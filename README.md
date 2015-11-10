# Project Outline

Alta is a project to implement a cross platform Digital Audio Workstation.

Alta because some of this code has been a response to code I've seen in
Ardour, hence Alt-A(rdour). This project is a way for me to flesh out
some ideas before hopefully integrating them into Ardour or presenting
alternative designs to Ardour developers.

The differences between this project and Ardour is the scope and development
process. The intended scope being much smaller and development process being
more test driven.

Latin origin, and the meaning of Alta is "high, elevated", if that comes
across as arrogant and condescending that is not my intention, I just like
the name.

The platforms initially being targetted are Linux, Windows and OS X.

# Building Alta

[Waf](http://waf.io) is used to build the source in the Alta repository but it
is called by the alta-build.sh script to build in an out of tree location so
that different configurations and branches are located in unique directories.

Using alta-build.sh is undocumented at the moment as this project is in its
early stages.

# Directory Structure

## build

Intended to contain files related to the build system. Visual Studio files,
CMake etc

## data

Application files that are not source files, resources like icons, images,
possibly some test files.

## doc

The documentation files.

## ext

The external git submodules that this project depends on.

## src

The source files

## tools

Utilities and scripts for maintaining the source code and running tests
