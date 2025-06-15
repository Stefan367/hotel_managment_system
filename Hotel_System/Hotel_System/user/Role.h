#pragma once

#include "../core/my_string.h"

enum class Role
{
    Manager,
    Receptionist,
    Accountant,
    Unknown
};

my_string role_to_string(Role role);
Role string_to_role(const my_string& str);