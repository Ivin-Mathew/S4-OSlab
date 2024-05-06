#!/bin/bash
#expt 2a
#sum of digits and reverse of number
#23/2/2024 Ivin Mathew
n=$1
sum=0
rev=0
k=$n
while [[ k -gt 0 ]]; do
sum=$((sum+(k%10)))
rev=$((rev*10 + (k%10)))
k=$((k/10))
done
echo "Sum= $sum "
echo "Reverse = $rev"


