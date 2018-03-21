#!/bin/bash

#FILENAME=D-small-practice
FILENAME=D-large-practice

g++ -std=c++11 main.cpp && ./a.out < "${FILENAME}.in" | tee "${FILENAME}.out"

