#include "../core/Date.h"
#include "../core/my_string_utils.h"

bool Date::isValidDate(int day, int month, int year) const
{
	if (year < YEAR_OF_OPENING || year > MAX_YEAR_FOR_RESERVATIONS)
	{
		return false;
	}

	if (month < 1 || month > 12)
	{
		return false;
	}

	int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (month == 2 && isLeapYear(year))
	{
		return day >= 1 && day <= 29;
	}

	return day >= 1 && day <= daysInMonth[month- 1];
}


Date::Date(int d, int m, int y) : day(d), month(m), year(y)
{
	if (!isValidDate(d, m, y))
	{
		throw std::invalid_argument("Invalid date!");
	}
}

Date::Date(const my_string& str)
{
	parseFromString(str);
}

my_string Date::to_string() const
{
	return int_to_string(day) + "-" + int_to_string(month) + "-" + int_to_string(year);
}

void Date::parseFromString(const my_string& str)
{
	int d = 0, m = 0, y = 0;
	int part = 0, num = 0;

	for (size_t i = 0; i < str.get_length(); i++)
	{
		char ch = str[i];

		// Convert char to int
		if (ch >= '0' && ch <= '9')
		{
			num = num * 10 + (ch - '0');
		}
		else if (ch == '-')
		{
			if (part == 0) d = num;
			else if (part == 1) m = num;

			num = 0;
			part++;
		}
	}
	y = num;

	if (!isValidDate(d, m, y))
	{
		throw std::invalid_argument("Invalid date or invalid date format!");
	}

	day = d;
	month = m;
	year = y;
}

bool Date::isLeapYear(const int year) const
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool Date::isDateWithValidFormat(const my_string date)
{
	return (date.get_length() == 10 && date.c_str()[2] == '-' && date.c_str()[5] == '-');
}

int Date::getDay() const
{
	return day;
}

int Date::getMonth() const
{
	return month;
}

int Date::getYear() const
{
	return year;
}

bool Date::operator<(const Date& other) const
{
	if (year != other.year) return year < other.year;
	if (month != other.month) return month < other.month;
	return day < other.day;
}

bool Date::operator==(const Date& other) const
{
	return day == other.day && month == other.month && year == other.year;
}

bool Date::operator>=(const Date& other) const
{
	return !(*this < other);
}

bool Date::operator>(const Date& other) const
{
	return other < *this;
}

bool Date::operator<=(const Date& other) const
{
	return *this < other || *this == other;
}


int Date::daysSinceYearStart() const
{
	static int monthDays[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int total = day;

	for (int i = 0; i < month - 1; ++i)
	{
		total += monthDays[i];
	}

	if (month > 2 && isLeapYear(year))
	{
		total += 1;
	}

	return total;
}

int Date::daysUntil(const Date& other) const
{
	if (*this == other) return 0;

	if (year == other.year)
	{
		return other.daysSinceYearStart() - this->daysSinceYearStart();
	}

	int daysThis = isLeapYear(year) ? 366 - this->daysSinceYearStart() : 365 - this->daysSinceYearStart();
	int daysOther = other.daysSinceYearStart();

	int yearsInBetween = other.year - year - 1;
	int middleDays = 0;

	for (int y = year + 1; y < other.year; ++y)
	{
		middleDays += isLeapYear(y) ? 366 : 365;
	}

	return daysThis + middleDays + daysOther;
}


int Date::daysSince1900() const
{
	int totalDays = 0;

	for (int y = 1900; y < year; ++y)
	{
		totalDays += isLeapYear(y) ? 366 : 365;
	}

	totalDays += daysSinceYearStart();

	return totalDays;
}

bool Date::isWeekend() const
{
	int dayOfWeek = daysSince1900() % 7;
	return dayOfWeek == 5 || dayOfWeek == 6;
}

void Date::addDays(int days)
{
	for (int i = 0; i < days; ++i)
	{
		++day;

		if (day > getDaysInMonth(month, year))
		{
			day = 1;
			++month;

			if (month > 12)
			{
				month = 1;
				++year;
			}
		}
	}
}

int Date::getDaysInMonth(int month, int year)
{
	switch (month)
	{
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		return 31;
	case 4: case 6: case 9: case 11:
		return 30;
	case 2:
		Date temp(1, 1, year);
		return temp.isLeapYear(year) ? 29 : 28;
	default:
		throw std::invalid_argument("Invalid month.");
	}
}

void Date::print() const
{
	std::cout << day << "-" << month << "-" << year << "\n";
}