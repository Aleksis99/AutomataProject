#include "Transition.h"
Transition::Transition()
	:symbol('\0') {
}
Transition::Transition(char symbol) : symbol(symbol)
{
}
Transition::Transition(char symbol, Set<int> end)
	:symbol(symbol) {
	this->end = end;

}
bool Transition::operator==(Transition& other) {
	if (symbol == other.symbol) {
		return true;
	}
	return false;
}
bool Transition::operator==(const Transition& other) {
	if (symbol == other.symbol) {
		return true;
	}
	return false;
}
/// Gets the symbol that the transition requares.
char Transition::GetSymbol() {
	return symbol;
}
/// Gets the set of states that the transition returns.
Set<int> Transition::GetEnd() const {
	return end;
}
/// Setter for the symbol.
void Transition::SetSymbol(char ch) {
	symbol = ch;
}
/// Setter for the end.
void Transition::SetEnd(Set<int> a) {
	end = a;

}
/// Ads a set of staters that the transition terurns.
void Transition::AddTransition(Set<int> a) {
	end = Union(end, a);
}
/// Ads a state that the transition terurns.
void Transition::AddTransition(int a)
{
	end.Add(a);
}
/// Prints the transition.
void Transition::print()const {
	std::cout << "With : " << symbol << " to states: " << std::endl;
	std::cout << "( ";
	for (size_t i = 0; i < end.getSize(); i++)
	{
		std::cout << end[i] << " ";
	}
	std::cout << ")" << std::endl;
}
/// Prints the transition to a selected stream.
void Transition::print(std::ostream& os)const {
	os << "With : " << symbol << " to states: " << std::endl;
	os << "( ";
	for (size_t i = 0; i < end.getSize(); i++)
	{
		os << end[i] << " ";
	}
	os << ")" << std::endl;
}
/// Saves the transition to a selected file.
void Transition::save(std::fstream& os)const {
	os << "With : " << symbol << " to states: " << std::endl;
	os << "( ";
	for (size_t i = 0; i < end.getSize(); i++)
	{
		os << end[i] << " ";
	}
	os << ")" << std::endl;
}
/// Saves the transition to a selected file.
void Transition::save(std::ofstream& os) const
{
	os << "With : " << symbol << " to states: " << std::endl;
	os << "( ";
	for (size_t i = 0; i < end.getSize(); i++)
	{
		os << end[i] << " ";
	}
	os << ")" << std::endl;
}
/// Saves the transition to a String object.
void Transition::save(String& file)const {
	file += "With : ";
	file.addChar(symbol);
	file += " to states: ";
	file += "\n";
	file += "( ";
	for (size_t i = 0; i < end.getSize(); i++)
	{
		file += file.getIntToStr(end[i]);
	}
	file += ")";
	file += "\n";
}
/// Changes the the ids that the transition returns by increasing them whit the given value.
void Transition::ChangeEndIds(int change) {
	for (size_t i = 0; i < end.getSize(); i++)
	{
		end[i] += change;
	}
}