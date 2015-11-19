#!/bin/bash

# TODO install all these at once

pacman -S git gitk mingw-w64-i686-tk rsync python || exit

# install gcc

pacman -S mingw-w64-i686-gcc mingw-w64-x86_64-gcc || exit

pacman -S pkg-config

#? mingw-w64-i686-pkg-config mingw-w64-x86_64-pkg-config || exit

pacman -S mingw-w64-i686-gtkmm3 mingw-w64-x86_64-gtkmm3

pacman -S mingw-w64-i686-boost mingw-w64-x86_64-boost

pacman -S mingw-w64-i686-libsndfile mingw-w64-x86_64-libsndfile

pacman -S make

pacman -S diff
