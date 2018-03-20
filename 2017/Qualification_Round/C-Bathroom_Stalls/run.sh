#!/bin/bash

#FILENAME=C-small-practice-1
#FILENAME=C-small-practice-2
FILENAME=C-large-practice

g++ -std=c++11 main.cpp && ./a.out < "${FILENAME}.in" | tee "${FILENAME}.out"

