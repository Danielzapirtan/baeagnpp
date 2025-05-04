#! /usr/bin/bash

g++ -o baeagn baeagn.cpp -ansi -Wall -Wno-unused-result -O4 -lm -march=native
strip baeagn

