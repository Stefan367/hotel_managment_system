#include "my_string_utils.h"

int string_to_int(const my_string& str)
{
    int result = 0;
    bool isNegative = false;
    size_t i = 0;

    if (str[0] == '-')
    {
        isNegative = true;
        i = 1;
    }

    for (; i < str.get_length(); ++i)
    {
        if (str[i] < '0' || str[i] > '9')
        {
            throw std::runtime_error("All other symbols except digits cannot be transformed into numbers.");
        }

        result = result * 10 + (str[i] - '0');
    }

    return isNegative ? -result : result;
}

my_string int_to_string(int number)
{
    if (number == 0) return "0";

    char buffer[32];
    int i = 0;
    bool isNegative = false;

    if (number < 0)
    {
        isNegative = true;
        number = -number;
    }

    while (number > 0)
    {
        buffer[i++] = '0' + (number % 10);
        number /= 10;
    }

    if (isNegative) buffer[i++] = '-';

    my_string result;
    for (int j = i - 1; j >= 0; --j)
    {
        result += buffer[j];
    }

    return result;
}