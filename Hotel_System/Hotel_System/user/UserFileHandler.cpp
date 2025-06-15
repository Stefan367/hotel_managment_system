#include "UserFileHandler.h"
#include <fstream>
#include "../core/my_string_utils.h"
#include "../user/Manager.h"
#include "../user/Receptionist.h"
#include "../user/Accountant.h"

const size_t INPUT_LINE_PARTS_COUNT = 3;

void UserFileHandler::saveToFile(const my_vector<User*>& users, const char* filename)
{
    std::ofstream out(filename);
    if (!out.is_open())
    {
        throw std::runtime_error("Could not open user file for writing.");
    }

    for (size_t i = 0; i < users.get_size(); ++i)
    {
        User* user = users[i];
        out << user->getUsername().c_str() << ";"
            << user->getPassword().c_str() << ";"
            << role_to_string(user->getRole()).c_str() << "\n";
    }

    out.close();
}

void UserFileHandler::loadFromFile(my_vector<User*>& users, const char* filename)
{
    std::ifstream in(filename);
    if (!in.is_open())
    {
        throw std::runtime_error("Could not open user file for reading.");
    }

    char line[256];
    while (in.getline(line, sizeof(line)))
    {
        my_string str(line);
        my_vector<my_string> parts = split_string(str, ';');

        if (parts.get_size() != INPUT_LINE_PARTS_COUNT) continue;

        my_string username = parts[0];
        my_string password = parts[1];
        Role role = string_to_role(parts[2]);

        User* user = nullptr;
        switch (role)
        {
        case Role::Manager: 
            user = new Manager(username, password); 
            break;

        case Role::Receptionist:
            user = new Receptionist(username, password);
            break;

        case Role::Accountant:
            user = new Accountant(username, password);
            break;

        default: continue;
        }

        users.push_back(user);
    }

    in.close();
}