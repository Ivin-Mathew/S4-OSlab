#!/bin/bash
#Qn 3 a
#Check if password is strong
#Ivin Mathew CSE S4 B2 roll 33
read -p "Enter password: " pass
if [[ ${#pass} -lt 8 || $pass != *[[:lower:]]* || $pass != *[[:upper:]]* || $pass != *[[:digit:]]* ]]; then
if [[ $pass =~ [@_#$\&*] ]]; then
echo "Contains special character"
else
echo " Weak password"
fi
else
if [[ $pass =~ [@_#$\&*] ]]; then
echo "Strong password"
fi
fi