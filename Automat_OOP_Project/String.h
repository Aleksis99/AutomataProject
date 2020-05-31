#pragma once
#pragma warning (disable : 4996)
#include <iostream>
#include<fstream>
#include "MyVec.hpp"
class String {
private:
	char* str;
	size_t count;

	void copyStr(const String&);
	void deleteStr();
public:

	String(const char* = "");
	String(const String&);
	String& operator=(const String&);
	String& operator=(const char*);
	~String();

	size_t size()const;
	Vector<String> SplitBy(char)const;
	void RemoveAll(char);
	bool HasChar(char);
	int getInt();
	String getIntToStr(int);
	String Substr(int, int);


	void addChar(const char);
	String operator+(const String&)const;
	String& operator+=(const String&);

	String operator+(const char*)const;
	String& operator+=(const char*);
	String& operator+=(char);

	char& operator[](const int);

	bool operator==(const String&)const;
	bool operator!=(const String&)const;
	bool operator<(const String&)const;
	bool operator<=(const String&)const;
	bool operator>=(const String&)const;
	bool operator>(const String&)const;

	bool operator==(const char*)const;
	bool operator!=(const char*)const;
	bool operator<(const char*)const;
	bool operator<=(const char*)const;
	bool operator>=(const char*)const;
	bool operator>(const char*)const;

	friend std::istream& operator>>(std::istream& is, String& str);
	friend std::ifstream& operator>>(std::ifstream& is, String& str);
	friend std::ostream& operator<<(std::ostream& os, const String& str);
	friend void getline(std::istream& is, String& str);
	friend void getline(std::ifstream& is, String& str);

	friend void getline(String& is, String& str);
	char* getCharArray();
};

