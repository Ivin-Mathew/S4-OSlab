#!/bin/bash

# Function to check if the password contains lowercase letters
contains_lowercase() {
    [[ "$1" =~ [a-z] ]]
}

# Function to check if the password contains uppercase letters
contains_uppercase() {
    [[ "$1" =~ [A-Z] ]]
}

# Function to check if the password contains digits
contains_digit() {
    [[ "$1" =~ [0-9] ]]
}

# Function to check if the password contains special characters
contains_special() {
    [[ "$1" =~ [@_#$%\&*] ]]
}

# Main function to validate the password
validate_password() {
    local password=$1

    # Check length
    if [ ${#password} -lt 8 ]; then
        echo "Weak password: Length should be minimum of 8 characters."
        return 1
    fi

    # Check lowercase
    if ! contains_lowercase "$password"; then
        echo "Weak password: Should contain lowercase letters."
        return 1
    fi

    # Check uppercase
    if ! contains_uppercase "$password"; then
        echo "Weak password: Should contain uppercase letters."
        return 1
    fi

    # Check digit
    if ! contains_digit "$password"; then
        echo "Weak password: Should contain minimum one digit."
        return 1
    fi

    # Check special character
    if ! contains_special "$password"; then
        echo "Weak password: Should contain minimum one special character."
        return 1
    fi

    # Password is strong
    echo "Strong password"
    return 0
}

# Main script

# Check if password is provided as argument
if [ -z "$1" ]; then
    echo "Usage: $0 <password>"
    exit 1
fi

# Validate the password
validate_password "$1"
