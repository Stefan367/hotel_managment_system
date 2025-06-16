#include "ActionReportFileHandler.h"
#include "../core/my_string_utils.h"
#include <fstream>

void ActionReportFileHandler::saveToFile(const my_vector<ActionReport>& reports, const char* filename)
{
    std::ofstream out(filename);
    if (!out.is_open())
    {
        throw std::runtime_error("Could not open action report file for writing.");
    }

    for (size_t i = 0; i < reports.get_size(); ++i)
    {
        const ActionReport& report = reports[i];

        out << report.getDate().to_string().c_str() << ";"
            << report.getUsername().c_str() << ";"
            << report.getAction().c_str() << "\n";
    }

    out.close();
}

void ActionReportFileHandler::loadFromFile(my_vector<ActionReport>& reports, const char* filename)
{
    std::ifstream in(filename);
    if (!in.is_open())
    {
        throw std::runtime_error("Could not open action report file for reading.");
    }

    char line[256];
    while (in.getline(line, sizeof(line)))
    {
        my_string str(line);
        my_vector<my_string> parts = split_string(str, ';');

        if (parts.get_size() != 3)
            continue;

        Date date(parts[0]);
        my_string username = parts[1];
        my_string action = parts[2];

        reports.push_back(ActionReport(date, action, username));
    }

    in.close();
}

Date ActionReportFileHandler::getNextDateFromLastReport(const my_vector<ActionReport>& reports)
{
    if (reports.get_size() == 0)
    {
        // if we dont have any report we start from the current year
        return Date(1, 1, 2025);
    }

    Date lastDate = reports[reports.get_size() - 1].getDate();
    lastDate.addDays(1);
    return lastDate;
}