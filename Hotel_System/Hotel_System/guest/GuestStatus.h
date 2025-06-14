#pragma once
#include "../core/my_string.h"

enum class GuestStatus
{
    Regular,
    Gold,
    Platinum
};

my_string to_string(GuestStatus status);

GuestStatus string_to_status(const my_string& str);

GuestStatus classifyFromHistory(int reservationsCount);