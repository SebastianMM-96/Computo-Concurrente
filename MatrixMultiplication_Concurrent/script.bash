#!/bin/bash
#Run this in terminal
g++ main.cpp -o Matrix -std=c++17 -Wall -g -lpthread -I.
# For para ejecutar 20 veces. 
for((i=0;i<=19;i++)); do ./Matrix 2000 2000 2000; done > output.txt