#!/bin/bash
#expt 2b
#armstrong number
#23/2/2024 Ivin Mathew
echo "Enter n1"
read n1
echo "Enter n2"
read n2
for (( i=$n1;i<$n2;i++ ))
    do
    sum=0
    count=0
    n=$i
    while [[ $n -gt 0 ]]; do
        count=$((count+1))
        n=$((n/10))
    done
    n=$i
    while [ $n -gt 0 ]
    do
        temp=$((n%10))
        sum=$(( sum + temp**count ))
        n=$(( n/10 ))
    done
    if [[ $sum -eq $i ]]
        then
        echo $i
    fi
done

