#include "Role.h"

my_string role_to_string(Role role)
{
    switch (role)
    {
    case Role::Manager: return "Manager";
    case Role::Receptionist: return "Receptionist";
    case Role::Accountant: return "Accountant";
    default: return "Unknown";
    }
}

Role string_to_role(const my_string& str)
{
    if (str == "Manager") return Role::Manager;
    if (str == "Receptionist") return Role::Receptionist;
    if (str == "Accountant") return Role::Accountant;
    return Role::Unknown;
}