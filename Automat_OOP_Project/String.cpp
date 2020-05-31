#include "String.h"
void String::copyStr(const String& other) {
	str = new char[strlen(other.str) + 1];
	strcpy(str, other.str);
	count = other.count;
}

void String::deleteStr() {
	delete[] str;
}

void String::addChar(const char ch)
{
	char a[2];
	a[0] = ch;
	a[1] = '\0';
	String temp(a);
	(*this) += temp;
}


String::String(const char* str) {
	this->str = new char[strlen(str) + 1];
	strcpy(this->str, str);
	count = strlen(str);
}

String::String(const String& other) {
	copyStr(other);
}

String& String::operator=(const String& other) {
	if (this != &other) {
		deleteStr();
		copyStr(other);
	}
	return *this;
}

String& String::operator=(const char* other)
{
	String temp(other);
	deleteStr();
	copyStr(temp);
	return *this;
}

String::~String() {
	deleteStr();
}

size_t String::size() const {
	return count;
}

Vector<String> String::SplitBy(char symbol) const
{
	Vector<String> result;
	String currString;
	for (size_t i = 0; i < count; i++)
	{
		if (str[i] != symbol) {
			currString.addChar(str[i]);
		}
		else
		{
			result.pushBack(currString);
			currString = "";
		}
		if (i == count - 1 && currString != "") {
			result.pushBack(currString);
		}
	}
	return result;
}

void String::RemoveAll(char charToRemove)
{
	String res;
	for (size_t i = 0; i < strlen(str); i++)
	{
		if (str[i] != charToRemove) {
			res.addChar(str[i]);
		}
	}
	strcpy(str, res.str);
	count = strlen(str);
}

bool String::HasChar(char ch)
{
	for (size_t i = 0; i < count; i++)
	{
		if (str[i] == ch) {
			return true;
		}
	}
	return false;
}


int String::getInt()
{
	int sum = 0;
	for (size_t i = 0; i < this->size(); i++)
	{
		sum *= 10;
		sum += str[i] - '0';
	}
	return sum;
}






String String::Substr(int start, int end)
{
	String res;
	if (start > 0 && end < count) {
		for (size_t i = start; i <= end; i++)
		{
			res.addChar(str[i]);
		}
	}
	return res;
}

bool String::operator==(const String& other) const {
	if (strcmp(str, other.str) == 0) return true;
	return false;
}

bool String::operator!=(const String& other) const
{
	return !((*this) == other);
}

bool String::operator<(const String& other) const {
	if (strcmp(str, other.str) < 0) return true;
	return false;
}

String String::operator+(const String& other) const {
	String temp(*this);
	temp += other;
	return temp;
}

String& String::operator+=(const String& other) {
	count += other.count;
	char* temp = new char[count + 1];
	strcpy(temp, str);
	strcat(temp, other.str);

	deleteStr();
	str = temp;
	return *this;
}

String String::operator+(const char* str) const
{
	String temp = str;
	return (*this) + temp;
}

String& String::operator+=(const char* str)
{
	String temp = str;
	return (*this) += temp;
}

String& String::operator+=(char)
{
	String temp = str;
	return (*this) += temp;
}

char& String::operator[](const int pos) {
	if (pos < 0 || pos >= count) return str[count - 1];
	return str[pos];
}

bool String::operator<=(const String& other) const {
	return !((*this) > other);
}

bool String::operator>=(const String& other) const {
	return !((*this) < other);
}

bool String::operator>(const String& other) const {
	if (strcmp(str, other.str) > 0) return true;
	return false;
}

bool String::operator==(const char* str) const
{
	String temp = str;
	return (*this) == temp;
}

bool String::operator!=(const char* other) const
{
	String temp(other);
	return !((*this) == temp);
}

bool String::operator<(const char* str) const
{
	String temp = str;
	return (*this) < temp;
}

bool String::operator<=(const char* str) const
{
	String temp = str;
	return (*this) <= temp;
}

bool String::operator>=(const char* str) const
{
	String temp = str;
	return (*this) >= temp;
}

bool String::operator>(const char* str) const
{
	String temp = str;
	return (*this) > temp;
}

String String::getIntToStr(int num)
{

	String res = "";
	if (num == 0) {
		res = "0";
		return res;
	}
	while (num > 0) {
		char a = char(num % 10 + 48);
		res.addChar(a);
		num /= 10;
	}
	String result = "";
	for (int i = res.size() - 1; i >= 0; i--)
	{
		result.addChar(res[i]);
	}
	return result;

}

std::istream& operator>>(std::istream& is, String& str)
{
	char ch;
	String temp;

	is.get(ch);

	while (ch != '\n' && ch != '\t' && ch != ' ')
	{
		temp.addChar(ch);
		is.get(ch);
	}
	str = temp;

	return is;
}

std::ifstream& operator>>(std::ifstream& is, String& str)
{
	char ch;
	String temp;
	is.get(ch);

	while (ch != '\n' && ch != '\t' && ch != ' ')
	{
		temp.addChar(ch);
		is.get(ch);
	}
	str = temp;

	return is;
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
	os << str.str;

	return os;
}

void getline(std::istream& is, String& str) {
	char ch;
	String temp;

	is.get(ch);

	while (ch != '\n')
	{
		temp.addChar(ch);
		is.get(ch);
	}
	str = temp;
}

char* String::getCharArray()
{
	return str;
}
void getline(std::ifstream& is, String& str)
{
	char ch;
	String temp;

	is.get(ch);
	while (ch != '\n')
	{
		temp.addChar(ch);
		is.get(ch);
	}
	str = temp;
}

void getline(String& is, String& str)
{
	if (is == "" || is.size() == 0) {
		str = "";
		return;
	}
	String temp;
	int index = -1;
	for (size_t i = 0; i < is.size(); i++)
	{
		if (is[i] == '\n') {
			index = i;
			break;
		}
		temp.addChar(is[i]);
	}
	if (index != -1) {
		is = is.Substr(index + 1, is.size() - 1);
	}
	else {
		is = "";
	}
	str = temp;
}
