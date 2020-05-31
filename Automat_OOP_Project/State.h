#pragma once
#include "Transition.h"
class State {
private:
	int id;
	bool isStart;
	bool isFinal;
	Set<Transition> transitions;
	/// copies the state.
	void copyState(const State& other) {
		id = other.id;
		isStart = other.isStart;
		isFinal = other.isFinal;
		transitions = other.transitions;
	}
public:
	
	State();

	State(int id, bool isStart, bool isFinal);

	State(int id, bool isStart, bool isFinal, Set<Transition> transitions);

	State(const State& other);

	State& operator=(const State& other);

	bool operator==(State& other);

	bool operator==(const State& other);

	bool IsStart() const;

	bool IsFinal() const;

	void SetIsStart(bool isStart);

	void SetIsFinal(bool isFinal);

	bool AddTransition(Transition newTransition);

	void RemoveTransition(Transition newTransition);

	void SetId(int newId);

	int GetId();

	bool AddTransition(char symbol, Set<int> a);

	Set<int> GetTransitionSet(char ch);

	bool CanReach(int otherId);

	bool CanReach(Set<int> otherIds);

	bool CanReach(State other);

	bool CanReach(Set<State> other);

	bool IsError();

	int getTransitionsCount();

	void print() const;

	void print(std::ostream& os) const;

	void save(std::fstream& os) const;

	void save(std::ofstream& os) const;

	void save(String& file) const;

	bool deterministicTransitions() const;

	Set<Transition>& GetAllTransitions();

	void AddTransitions(Set<Transition> newTransitions);

	void ChangeEndIds(int change);

};