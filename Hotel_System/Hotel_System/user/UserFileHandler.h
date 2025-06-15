#pragma once

#include "../user/UserManager.h"

class UserFileHandler
{
public:
    static void saveToFile(const my_vector<User*>& users, const char* filename);
    static void loadFromFile(my_vector<User*>& users, const char* filename);
};
