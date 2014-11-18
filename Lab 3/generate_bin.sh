#!/bin/bash
# Takes an exploit text file as the first imput, outputs a binary file of the same name
./sendstring < $1.txt > $1.bin