**main function : pro6.cpp**

> Input format (all inputs support integers only)
>
> 1. input the number of iterations K (preferably around 1000), for the loop time
>
> 2. Input the size of package, width first, then height eg: 30 50
>
> 3. enter the number of texture N
>
> 4. enter the size of the N Texture first width and then height eg: 3 5 (the width and height of the texture must be less than or equal to the width and height of the package)--In test, we use randomly generated inputs.
>
>    



**random.c**

generate random input data



To build the program, run

```shell
g++ -o main pro6.cpp
./main
```



or if you want to test the program with multiple input sequence, for convenience, a shell script is written called **load.sh**

modify at will

```shell
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
```



to use, run

```shell
./load.sh
```

