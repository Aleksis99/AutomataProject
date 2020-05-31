#pragma once
#include "MySet.hpp"
#include "String.h"
class Transition {

private:
	char symbol;
	Set<int> end;
public:
	
	Transition();

	Transition(char symbol);

	Transition(char symbol, Set<int> end);

	bool operator==(Transition& other);

	bool operator==(const Transition& other);

	char GetSymbol();

	Set<int> GetEnd() const;

	void SetSymbol(char ch);

	void SetEnd(Set<int> a);

	void AddTransition(Set<int> a);

	void AddTransition(int a);

	void print() const;

	void print(std::ostream& os) const;

	void save(std::fstream& os) const;

	void save(std::ofstream& os) const;

	void save(String& file) const;


	void ChangeEndIds(int change);

};