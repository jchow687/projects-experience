#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "password_checker.h"

// puts the requirements into the args//
bool check_range(char letter, char lower, char upper);


// checks if length is less than or equal to 10//
bool check_length(const char *password) {
    int length = strlen(password);
    bool meets_len_req = (length >= 10);
    return meets_len_req;
}

// checks if its at least one uppercase//
bool check_upper(const char *password) {
    while (*password != '\0') {
        bool is_in_range = check_range(*password,'A','Z');
        if (is_in_range) {
            return true;
        }
        ++password;
    }
    return false;
}

//checks if its at least one uppercase//
bool check_lower(const char *password) {
	while (*password != '\0') {
		bool is_in_range = check_range(*password,'a','z');
		if (is_in_range) {
			return true;
		}
		++password;
	}
	return false;
}

// checks if the lower and upper are there in their respective range//
bool check_range(char letter, char lower, char upper) {
    bool is_in_range = (letter >= lower && letter <= upper);
    
    if (is_in_range){
	    return true;
    }
    else {
	    return false;
    }
}

// checks if there is at least one or more numbers //
bool check_number(const char *password) {
    while (*password != '\0') {
        if (check_range(*password, '0', '9')) {
            return true;
        }
        ++password;
    }
    return false;
}

// checks if the first and last name are not in the password otherwise returns false//
bool check_name(const char *first_name, const char *last_name, const char *password) {
    const char *first = strstr(password, first_name);
    const char *last = strstr(password, last_name);
    return (!first && !last);
}

// calling to see if it meets the conditions//
bool check_password(const char *first_name, const char *last_name, const char *password) {
    bool length, upper, lower, number, name;
    length = check_length(password);
    name = check_name(first_name, last_name, password);
    number = check_number(password);
    upper = check_upper(password);
    lower = check_lower(password);
    return (lower && length && name && upper && number);
}


