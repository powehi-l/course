#!/bin/bash

rm input
rm main

gcc -o input random.c
g++ -o main pro6.cpp

K=1000
wid=30
hei=50
num=30

rm time_used

while(($num<=300))
do
    echo $K $wid $hei $num >temp
    ./input $num >> temp
    ./main < temp > result

    grep "number of packages:" result >> time_used
    grep "round ,the time" result >> time_used
    echo " " >> time_used
    let "num+=10"
done

echo output success