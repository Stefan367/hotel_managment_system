#pragma once

enum class GuestStatus
{
    Regular,
    Gold,
    Platinum
};

const char* to_string(GuestStatus status);
GuestStatus classifyFromHistory(int reservationsCount);