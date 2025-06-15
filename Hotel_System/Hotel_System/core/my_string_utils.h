#pragma once

#include "my_string.h"
#include "my_vector.hpp"

int string_to_int(const my_string& str);
my_string int_to_string(int number);
double string_to_double(const my_string& str);
my_vector<my_string> split_string(const my_string& str, char delimiter);