#pragma once

#include "../core/Date.h"
#include "../user/User.h"
//#include "../core/my_string.h"

class ActionReport
{
private:
    Date date;
    my_string action;
    my_string username;

public:
    ActionReport() = default;
    ActionReport(const Date& date, const my_string& action, const my_string& username);

    Date getDate() const;
    const my_string& getAction() const;
    const my_string& getUsername() const;

    void display() const;
};