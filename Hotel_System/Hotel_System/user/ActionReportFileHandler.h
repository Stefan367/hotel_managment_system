#pragma once

#include "ActionReport.h"
#include "../core/my_vector.hpp"

class ActionReportFileHandler
{
public:
    static void saveToFile(const my_vector<ActionReport>& reports, const char* filename);
    static void loadFromFile(my_vector<ActionReport>& reports, const char* filename);

    static Date getNextDateFromLastReport(const my_vector<ActionReport>& reports);
};