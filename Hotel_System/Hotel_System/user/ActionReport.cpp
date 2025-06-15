#include "ActionReport.h"

ActionReport::ActionReport(const Date& date, const my_string& action, const my_string& username)
    : date(date), action(action), username(username) {}

Date ActionReport::getDate() const
{
    return date;
}

const my_string& ActionReport::getAction() const
{
    return action;
}

const my_string& ActionReport::getUsername() const
{
    return username;
}

void ActionReport::display() const
{
    std::cout << "[" << date.to_string().c_str() << "] "
        << username.c_str() << " -> "
        << action.c_str() << "\n";
}