#!/bin/bash

diff=ppmdiff

make build

gcc bin/ppmdiff.c -o bin/ppmdiff

cat input.txt | ./main

score=0

# convert tests
./bin/$diff santa.pgm ref/santa.pgm
if [[ $? -eq 0 ]]; then
	score=$(($score+10))
	echo "santa.pgm conversion passed"
fi
./bin/$diff santa.ppm ref/santa.ppm
if [[ $? -eq 0 ]]; then
	score=$(($score+10))
	echo "santa.ppm conversion passed"
fi
./bin/$diff santa_gray.pgm ref/santa_gray.pgm
if [[ $? -eq 0 ]]; then
	score=$(($score+10))
	echo "santa_gray.pgm conversion passed"
fi

# blur tests
./bin/$diff santa_blur.pgm ref/santa_blur.pgm
if [[ $? -eq 0 ]]; then
	score=$(($score+10))
	echo "santa_blur.pgm passed"
fi
./bin/$diff santa_blur.ppm ref/santa_blur.ppm
if [[ $? -eq 0 ]]; then
	score=$(($score+10))
	echo "santa_blur.ppm passed"
fi

# crop tests
./bin/$diff santa_crop.pgm ref/santa_crop.pgm
if [[ $? -eq 0 ]]; then
	score=$(($score+10))
	echo "santa_crop.pgm passed"
fi
./bin/$diff santa_crop.ppm ref/santa_crop.ppm
if [[ $? -eq 0 ]]; then
	score=$(($score+10))
	echo "santa_crop.ppm passed"
fi
echo
echo
echo Your Grade is $score out of 70

