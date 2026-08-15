MyInput&ValidationLibrary

A C++ utility library designed to simplify user input handling, validation, number range checking, and date validation.

Features:
Number Validation, Check if an integer is between two values.
Check if a floating-point number is between two values.
Validate numbers within a specific range.
Date Validation, Check whether a date is between two dates.
Uses clsDate for date-related operations.
Input Functions:
1-Read and validate integer input.
2-Read an integer within a specific range.
3-Read and validate floating-point numbers.
4-Handle invalid input using cin.clear() and cin.ignore().

Requirements:
C++ compiler supporting modern C++.
clsDate.h for date-related validation functions.

Example:
#include "clsInputValidate.h"
int main()
{
    cout << clsInputValidate::IsNumberBetween(5, 1, 10) << endl;

    cout << clsInputValidate::IsNumberBetween(5.5f, 1.3f, 10.8f) << endl;

    cout << clsInputValidate::IsDateBetween(
        clsDate(15, 12, 2026),
        clsDate(8, 12, 2026),
        clsDate(31, 12, 2026)
    ) << endl;

    int Number =
        clsInputValidate::ReadIntNumber(
            "Invalid Number, Enter again:\n"
        );

    cout << "Number = " << Number << endl;

    return 0;
}
Usage:

Include the library header in your C++ project:
#include "clsInputValidate.h"
Then call the required function using:
clsInputValidate::FunctionName();

Purpose:
This library was created as a reusable collection of common input and validation functions that can be used in C++ console applications and larger projects.

Author
Reem Ahmed

-This project is part of my C++ learning journey and focuses on building reusable libraries and improving object-oriented programming and problem-solving skills.
