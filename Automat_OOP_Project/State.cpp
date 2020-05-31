#include "State.h"
State::State()
	: id(-1), isStart(0), isFinal(0) {
	this->id = id;
}
State::State(int id, bool isStart = 0, bool isFinal = 0)
	: isStart(isStart), isFinal(isFinal) {
	this->id = id;
}
State::State(int  id, bool isStart, bool isFinal, Set<Transition> transitions)
	: isStart(isStart), isFinal(isFinal) {
	this->id = id;
	this->transitions = transitions;
}
State::State(const State& other) {
	copyState(other);
}
State& State::operator=(const State& other) {
	if (this != &other) {

		copyState(other);
	}
	return *this;
}
bool State::operator==(State& other) {
	if (id == other.id) {
		return true;
	}
	return false;
}
bool State::operator==(const State& other) {
	if (id == other.id) {
		return true;
	}
	return false;
}
///  Checks if the state is a start state.
bool State::IsStart()const {
	return isStart;
}
///  Checks if the state is a final state.
bool State::IsFinal()const {
	return isFinal;
}
///  Sets the state isStart value.
void State::SetIsStart(bool isStart) {
	this->isStart = isStart;
}
///  Sets the state isFinal value.
void State::SetIsFinal(bool isFinal) {
	this->isFinal = isFinal;
}
///  Adds a new transition.
bool State::AddTransition(Transition newTransition) {
	return transitions.Add(newTransition);
}
///  Removes a given transition.
void State::RemoveTransition(Transition newTransition) {
	transitions.Remove(newTransition);
}
///  Setter for the id.
void State::SetId(int newId) {
	id = newId;
}
///  Getter for the id.
int State::GetId() {
	return id;
}
///  Ads a new transtion by given transition symbol and set of end ids.
bool State::AddTransition(char symbol, Set<int> a) {
	for (size_t i = 0; i < transitions.getSize(); i++)
	{
		if (transitions[i].GetSymbol() == symbol) {
			transitions[i].AddTransition(a);
			return true;
		}
	}
	Transition transition(symbol, a);
	transitions.Add(transition);
	return true;
}


///  Returns the transition set that the transtion return corresponding to the given symbol.
Set<int> State::GetTransitionSet(char ch) {
	Set<int>result;
	for (size_t i = 0; i < transitions.getSize(); i++)
	{
		if (transitions[i].GetSymbol() == ch) {
			return transitions[i].GetEnd();
		}
	}
}
///  Checks if the state can reach the given state by any of its transitions.
bool State::CanReach(int otherId) {
	for (size_t i = 0; i < transitions.getSize(); i++)
	{
		if (transitions[i].GetEnd().Contains(otherId)) {
			return true;
		}
	}
	return false;
}
///  Checks if the state can reach the given states by any of its transitions.
bool State::CanReach(Set<int> otherIds) {
	for (size_t i = 0; i < otherIds.getSize(); i++)
	{
		if (CanReach(otherIds[i])) {
			return true;
		}
	}
	return false;
}
///  Checks if the state can reach the given state by any of its transitions.
bool State::CanReach(State other) {
	for (size_t i = 0; i < transitions.getSize(); i++)
	{
		if (transitions[i].GetEnd().Contains(other.GetId())) {
			return true;
		}
	}
	return false;
}
//  Checks if the state can reach the given states by any of its transitions.
bool State::CanReach(Set<State> other) {
	for (size_t i = 0; i < other.getSize(); i++)
	{
		if (CanReach(other[i])) {
			return true;
		}
	}
	return false;
}
//  Checks if the state is error state.
bool State::IsError()
{
	if (transitions.isEmpty()) {
		return true;
	}
	for (size_t i = 0; i < transitions.getSize(); i++)
	{
		if (transitions[i].GetEnd().getSize() > 1)return false;
		if (transitions[i].GetEnd().getSize() == 1 && !transitions[i].GetEnd().Contains(id))return false;
	}
	return true;
}
//  Returns the amout of unique states the state can reach.
int State::getTransitionsCount() {
	Set<int> uniqueTransitions;
	for (size_t i = 0; i < transitions.getSize(); i++)
	{
		uniqueTransitions = Union(uniqueTransitions, transitions[i].GetEnd());
	}
	return uniqueTransitions.getSize();
}
//  Prints the state.
void State::print()const {
	std::cout << "From state : " << id << " S = " << isStart << " F = " << isFinal << std::endl;
	for (size_t i = 0; i < transitions.getSize(); i++)
	{
		transitions[i].print();
	}
}
//  Prints the state to a selected stream.
void State::print(std::ostream& os)const {
	os << "From state : " << id << " S = " << isStart << " F = " << isFinal << std::endl;
	for (size_t i = 0; i < transitions.getSize(); i++)
	{
		transitions[i].print(os);
	}
}
//  Saves the state to a selected file stream.
void State::save(std::fstream& os)const {
	os << "From state : " << id << " S = " << isStart << " F = " << isFinal << std::endl;
	for (size_t i = 0; i < transitions.getSize(); i++)
	{
		transitions[i].save(os);
	}
}
//  Saves the state to a selected output file stream.
void State::save(std::ofstream& os) const
{
	os << "From state : " << id << " S = " << isStart << " F = " << isFinal << std::endl;
	for (size_t i = 0; i < transitions.getSize(); i++)
	{
		transitions[i].save(os);
	}
}
//  Saves the state to a selected String object.
void State::save(String& file)const {
	file += "From state : ";
	file += file.getIntToStr(id);
	file += " S = ";
	if (isStart)file += "1";
	else file += "0";
	file += " F = ";
	if (isFinal)file += "1";
	else file += "0";
	file += "\n";
	for (size_t i = 0; i < transitions.getSize(); i++)
	{
		transitions[i].save(file);
	}
}
//  Checks if the states transitions are deterministic.
bool State::deterministicTransitions()const {
	for (size_t i = 0; i < transitions.getSize(); i++)
	{
		if (transitions[i].GetEnd().getSize() > 1)return false;
	}
	return true;
}
//  Returns all transitions of the state.
Set<Transition>& State::GetAllTransitions() {
	return transitions;
}
//  Ads a set of transition to the current transitions.
void State::AddTransitions(Set<Transition> newTransitions) {
	transitions = Union(transitions, newTransitions);
	for (size_t i = 0; i < newTransitions.getSize(); i++)
	{
		for (size_t j = 0; j < transitions.getSize(); j++)
		{
			if (transitions[j].GetSymbol() == newTransitions[i].GetSymbol()) {
				transitions[j].AddTransition(newTransitions[i].GetEnd());
			}
		}
	}
}
//  Changes the ids that the state transitons returns by increasing them by the given value.
void State::ChangeEndIds(int change) {
	for (size_t i = 0; i < transitions.getSize(); i++)
	{
		transitions[i].ChangeEndIds(change);
	}
}