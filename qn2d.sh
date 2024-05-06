#!/bin/bash
#expt 2d
#check validity of date
#23/2/2024 Ivin Mathew
check(){
date=$1
d=${date:0:2}
m=${date:3:2}
y=${date:6:4}
flag=0
if [[ 1951 -le $y && $y -le 2025 ]]; then
if [[ 1 -le $m && $m -le 12 ]]; then
if [[ $m -eq 2 ]]; then
    if [[ $((y%4)) -eq 0 ]]; then
        if [[ $((y%400)) -eq 0 ]]; then
        if [[ 1 -le $d && $d -le 29 ]]; then
        echo "Valid date"
        flag=1
        fi
        fi
        if [[ 1 -le $d && $d -le 29 && $((y%100)) -ne 0 ]]; then
        echo "Valid date"
        flag=1
        fi
    else
        if [[ 1 -le $d && $d -le 28 ]]; then
        echo "Valid date"
        flag=1
        fi
    fi
elif [[ $m -eq 1 || $m -eq 3 || $m -eq 5 || $m -eq 7 || $m -eq 8 || $m -eq 10 || $m -eq 12 ]]; then
    if [[ 1 -le $d && $d -le 31 ]]; then
    echo "Valid date"
    flag=1
    fi
elif [[ $m -eq 4 || $m -eq 6 || $m -eq 9 || $m -eq 11 ]]; then
    if [[ 1 -le $d && $d -le 30 ]]; then
    echo "Valid date"
    flag=1
    fi
fi
fi
fi
if [[ flag -eq 0 ]]; then
echo "Invalid date"
fi
}
echo "Enter dd/mm/yyyy"
read date
check "$date"