#!/bin/bash
#Run this in terminal
g++ mp_Semaphores.cpp -o main -std=c++17 -Wall -g -lpthread -I.
#Run the compiled file
./main 10;