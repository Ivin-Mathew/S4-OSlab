#!/bin/bash
#Expt 2c
#convert decimal to binary octal hexadecimal
#23/2/24 Ivin Mathew
echo -e "\n1:Convert to binary\n2:Convert to octal\n3:Convert to hexadecimal\n"
for (( i=0;i<3;i=i+1 ))
do
echo "Enter integer "
read n
echo "Enter option"
read opt

case $opt in
1)
k=$n
bin=""
while [[ $k -gt 0 ]]; do
bin="$((k%2))${bin}"
k=$(( k/2 ))
done
echo "Binary = $bin"
;;

2)
k=$n
oct=""
while [[ $k -gt 0 ]]; do
oct="$((k%8))${oct}"
k=$((k/8))
done
echo "Octal = $oct"
;;

3)
k=$n
hex=""
while [[ $k -gt 0 ]]; do
if [[ $((k%16)) -lt 10 ]]; then
hex="$((k%16))${hex}"
elif [[ $((k%16)) -eq 10 ]]; then
hex="A${hex}"
elif [[ $((k%16)) -eq 11 ]]; then
hex="B${hex}"
elif [[ $((k%16)) -eq 12 ]]; then
hex="C${hex}"
elif [[ $((k%16)) -eq 13 ]]; then
hex="D${hex}"
elif [[ $((k%16)) -eq 14 ]]; then
hex="E${hex}"
elif [[ $((k%16)) -eq 15 ]]; then
hex="F${hex}"
fi
k=$((k/16))
done
echo -e "hexadecimal = $hex\n"
;;
esac
done