#!/bin/bash
contains_lowercase() {
    [[ "$1" =~ [a-z] ]]
}
contains_uppercase() {
    [[ "$1" =~ [A-Z] ]]
}
contains_digit() {
    [[ "$1" =~ [0-9] ]]
}
contains_special() {
    [[ "$1" =~ [@_#$%\&*] ]]
}
validate_password() {
    local password=$1

    if [ ${#password} -lt 8 ]; then
        echo "Weak password: Length should be minimum of 8 characters."
        return 1
    fi

    if ! contains_lowercase "$password"; then
        echo "Weak password: Should contain lowercase letters."
        return 1
    fi

    if ! contains_uppercase "$password"; then
        echo "Weak password: Should contain uppercase letters."
        return 1
    fi

    if ! contains_digit "$password"; then
        echo "Weak password: Should contain minimum one digit."
        return 1
    fi

    if ! contains_special "$password"; then
        echo "Weak password: Should contain minimum one special character."
        return 1
    fi

    echo "Strong password"
    return 0
}

if [ -z "$1" ]; then
    echo "Usage: $0 <password>"
    exit 1
fi

validate_password "$1"
