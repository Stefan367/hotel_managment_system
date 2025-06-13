#pragma once

enum class GuestStatus
{
    Regular,
    Gold,
    Platinum
};

const char* to_string(GuestStatus status);
GuestStatus classify_from_history(int reservationsCount);