#pragma once
#include "State.h"

class Automat {

private:

	int id;
	Set<char> alphabet;
	Set<State> states;

public:
	Automat(int id, Set<char> alphabet, Set<State> states);

	Automat(int id, Set<char> alphabet);

	Automat(int id);

	Automat();

	Automat(String&, Set<char>);

	Automat(String&, Set<char>,bool);


	int GetId()const;

	Automat BuildAutomatBySymbol(char)const;

	void SetId(int);

	bool AddSymbolToAlphabet(char ch);

	void SetAlphabet(Set<char> chrs);

	bool AddState(bool, bool, Set<Transition>&);

	bool AddState(int, bool, bool, Set<Transition>&);

	bool AddState(State&);

	int GetId();

	bool AddTransition(int, Transition&);

	int GetStatesCount();

	void ChangeTransition(int idOfState, char symbol, Set<int> newEnd);

	State MergeStates(Set<State>);

	Set<State> GetAllStates();

	Set<int> GetAllStatesIds();

	Set<State> GetStartStates()const;

	Set<int> GetStartStatesIds();

	Set<State> GetFinalStates();

	Set<int> GetFinalStatesIds();

	Set<State> GetStates(Set<int> id);

	int GetMaxStateId(Set<State>)const;

	Set<State> ChangeStatesIds(Set<State>, int);

	State GetState(int id);

	bool HasState(int id);

	Set<int> GetTransitionStates(int start, char symbol);

	Set<int> GetTransitionStates(Set<int> start, char symbol);

	Set<int> GetTransitionStates(int start, String word);

	Set<State> GetStatesThatCanReachFinal();


	bool CanReachFinal(State);

	bool CanReachState(State, State);

	void print()const;

	void print(std::ostream& os)const;

	void save(std::fstream&)const;

	void save(std::ofstream&)const;

	void save(String&)const;

	bool empty();

	bool deterministic();

	bool recognize(String);


	Automat UnionOfAtutomats(const Automat&)const;

	Automat Concat(const Automat&)const;

	Automat PositiveWrap()const;

	Automat KleeneStar()const;


	void determinate();

	bool isFinite();

};