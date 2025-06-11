#include "my_string.h"

#include <cassert>

my_string::my_string()
{
	data = new char[1];
	data[0] = '\0';
}

my_string::my_string(const char* string_data)
{
	if (string_data == nullptr)
	{
		data = new char[1];
		data[0] = '\0';
	}
	else
	{
		size_t string_length = strlen(string_data);
		data = new char[string_length + 1];
		strcpy_s(data, string_length + 1, string_data);
	}
}

void my_string::free()
{
	delete[] data;
}

void my_string::copy_from(const my_string& other)
{
	size_t string_length = strlen(other.data);
	data = new char[string_length + 1];
	strcpy_s(data, string_length + 1, other.data);
}

my_string::my_string(const my_string& other)
{
	copy_from(other);
}

my_string& my_string::operator=(const my_string& other)
{
	if (this != &other)
	{
		free();
		copy_from(other);
	}

	return *this;
}

my_string::~my_string()
{
	free();
}

const char* my_string::c_str() const
{
	return data;
}

size_t my_string::get_length() const
{
	return strlen(data);
}

char& my_string::operator[](size_t index)
{
	assert(index < this->get_length());

	return data[index];
}

char my_string::operator[](size_t index) const
{
	assert(index < this->get_length());

	return data[index];
}

my_string& my_string::operator+=(const my_string& other)
{
	size_t new_length = get_length() + other.get_length();

	char* new_data = new char[new_length + 1];

	new_data[0] = '\0';

	strcat_s(new_data, new_length + 1, data);
	strcat_s(new_data, new_length + 1, other.data);

	free();
	data = new_data;

	return *this;
}

my_string operator+(const my_string& lhs, const my_string& rhs)
{
	my_string result(lhs);

	result += rhs;

	return result;
}

istream& operator>>(istream& in, my_string& str)
{
	char buffer[1024];
	in >> buffer;

	delete[] str.data;
	size_t len = strlen(buffer);
	str.data = new char[len + 1];
	strcpy_s(str.data, len + 1, buffer);

	return in;
}

ostream& operator<<(ostream& out, const my_string& str)
{
	return out << str.c_str();
}

bool operator<(const my_string& lhs, const my_string& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator<=(const my_string& lhs, const my_string& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}

bool operator>=(const my_string& lhs, const my_string& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}

bool operator>(const my_string& lhs, const my_string& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

bool operator==(const my_string& lhs, const my_string& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const my_string& lhs, const my_string& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) != 0;
}


std::istream& getline(std::istream& in, my_string& str)
{
	char buffer[1024];
	in.getline(buffer, 1024);

	delete[] str.data;
	str.data = new char[strlen(buffer) + 1];
	strcpy_s(str.data, strlen(buffer) + 1, buffer);

	return in;
}
