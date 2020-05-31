#include "Automat.h"


Automat::Automat(int id, Set<char> alphabet, Set<State> states) :id(id)
{
	this->alphabet = alphabet;
	this->states = states;
}

Automat::Automat(int id, Set<char> alphabet) :id(id)
{
	this->alphabet = alphabet;
}

Automat::Automat(int id) : id(id)
{
}

Automat::Automat()
{
	id = -1;
}
/// Constuctor that creates an automat from a regex expresion and set of symbols(alphabet).
Automat::Automat(String& regex, Set<char> alphabet)
{
	Automat result(-1, alphabet);

	char lastOperation = '0';
	Vector<int> lastOpeningBraketIndex;
	for (size_t i = 0; i < regex.size(); i++)
	{
		if (regex[i] == '(') {
			lastOpeningBraketIndex.pushBack(i);
		}
		else if (regex[i] == ')') {
			Automat curr(-1, alphabet);
			String currExpresion = regex.Substr(lastOpeningBraketIndex.popBack() + 1, i - 1);
			Vector<String>currExpresions = currExpresion.SplitBy('+');
			for (size_t j = 0; j < currExpresions.size(); j++)
			{
				Vector<String> splitCurrExpresions = currExpresions[j].SplitBy('.');
				int m = 0;
				while (splitCurrExpresions[0][m] == '(')m++;
				Automat concats = BuildAutomatBySymbol(splitCurrExpresions[0][m]);
				if (splitCurrExpresions[0].size() > 1 && splitCurrExpresions[0][m + 1] == '*') {
					concats = concats.KleeneStar();
				}
				for (size_t k = 1; k < splitCurrExpresions.size(); k++)
				{
					Automat currConcat = BuildAutomatBySymbol(splitCurrExpresions[k][0]);
					if (splitCurrExpresions[k].size() > 1 && splitCurrExpresions[k][1] == '*') {
						currConcat = currConcat.KleeneStar();
					}
					concats = concats.Concat(currConcat);

				}
				curr = curr.UnionOfAtutomats(concats);
			}
			if (i < regex.size() - 1 && regex[i + 1] == '*') {
				curr = curr.KleeneStar();
			}
			if (lastOperation == '0') {
				result = curr;
			}
			else if (lastOperation == '+') {
				result = result.UnionOfAtutomats(curr);
			}
			else if (lastOperation == '.') {
				result = result.Concat(curr);
			}
			if (i < regex.size() - 1 && regex[i + 1] == '+') {
				lastOperation = '+';
			}
			else if (i < regex.size() - 1 && regex[i + 1] == '.') {
				lastOperation = '.';
			}
			else if (i < regex.size() - 2 && regex[i + 2] == '+') {
				lastOperation = '+';
			}
			else if (i < regex.size() - 2 && regex[i + 2] == '.') {
				lastOperation = '.';
			}
		}
	}
	*this = result;

}
/// Constuctor that creates an automat from a regex expresion and set of symbols(alphabet)
/// and bool it was an attempt to make the function work with nested brackets.
Automat::Automat(String& regex, Set<char> alphabet, bool sss)
{

	Vector<Automat> result;
	Vector<char> lastOperation;
	Vector<int> lastOpeningBraketIndex;
	for (size_t i = 0; i < regex.size(); i++)
	{
		if (regex[i] == '(') {
			lastOpeningBraketIndex.pushBack(i);
		}
		else if (regex[i] == ')') {
			Automat curr(-1, alphabet);
			String currExpresion = regex.Substr(lastOpeningBraketIndex.popBack() + 1, i - 1);
			Vector<String>currExpresions = currExpresion.SplitBy('+');
			for (size_t j = 0; j < currExpresions.size(); j++)
			{
				Vector<String> splitCurrExpresions = currExpresions[j].SplitBy('.');
				int m = 0;
				while (splitCurrExpresions[0][m] == '(')m++;
				Automat concats = BuildAutomatBySymbol(splitCurrExpresions[0][m]);
				if (splitCurrExpresions[0].size() > 1 && splitCurrExpresions[0][m + 1] == '*') {
					concats = concats.KleeneStar();
				}
				else if (splitCurrExpresions[0].size() > 1 && splitCurrExpresions[0][m + 1] == '-') {
					concats = concats.PositiveWrap();
				}
				for (size_t k = 1; k < splitCurrExpresions.size(); k++)
				{
					Automat currConcat = BuildAutomatBySymbol(splitCurrExpresions[k][0]);
					if (splitCurrExpresions[k].size() > 1 && splitCurrExpresions[k][1] == '*') {
						currConcat = currConcat.KleeneStar();
					}
					else if (splitCurrExpresions[k].size() > 1 && splitCurrExpresions[k][1] == '-') {
						concats = concats.PositiveWrap();
					}
					concats = concats.Concat(currConcat);

				}
				curr = curr.UnionOfAtutomats(concats);
			}
			if (i < regex.size() - 1 && regex[i + 1] == '*') {
				curr = curr.KleeneStar();
			}
			if (i < regex.size() - 1 && regex[i + 1] == '-') {
				curr = curr.PositiveWrap();
			}
			if (i < regex.size() - 2 && regex[i + 2] == '*') {
				curr = curr.KleeneStar();
			}
			if (i < regex.size() - 2 && regex[i + 2] == '-') {
				curr = curr.PositiveWrap();
			}
			if (lastOperation.size() == 0) {
				result.pushBack(curr);
			}
			else if (lastOperation[lastOperation.size()-1] == '+') {
				lastOperation.popBack();
				Automat a = result.popBack();
				result.pushBack(a.UnionOfAtutomats(curr)) ;
			}
			else if (lastOperation[lastOperation.size() - 1] == '.') {
				lastOperation.popBack();
				Automat a = result.popBack();
				result.pushBack(a.Concat(curr));
			}
			if (i < regex.size() - 1 && regex[i + 1] == '+') {
				lastOperation.pushBack('+');
			}
			else if (i < regex.size() - 1 && regex[i + 1] == '.') {
				lastOperation.pushBack('.');
			}
			else if (i < regex.size() - 2 && regex[i + 2] == '+') {
				lastOperation.pushBack('+');
			}
			else if (i < regex.size() - 2 && regex[i + 2] == '.') {
				lastOperation.pushBack('.');
			}
			else if (i < regex.size() - 1 && regex[i + 1] == '-') {
				lastOperation.pushBack('-');
			}
			else if (i < regex.size() - 2 && regex[i + 2] == '-') {
				lastOperation.pushBack('-');
			}
		}
	}
	*this = result.popBack();
}

/// Getter for the id.
int Automat::GetId() const
{
	return id;
}
/// Builds an automat by a single  symbol.
Automat Automat::BuildAutomatBySymbol(char symbol)const
{
	if (symbol != 'E') {
		Set<int> end;
		end.Add(1);
		Transition tr(symbol, end);
		Set<Transition> trs;
		trs.Add(tr);
		State a(0, true, false, trs);
		State b(1, false, true);
		Set<State> sts;
		sts.Add(a);
		sts.Add(b);
		Automat result(-1, alphabet, sts);
		return result;
	}
	else {
		State a(0, 1, 1);
		Set<State> sts;
		sts.Add(a);
		Automat result(-1, alphabet, sts);

		return result;
	}
}
/// Setter for the id.
void Automat::SetId(int id)
{
	this->id = id;
}
/// Ads a symbol to the alphabet.
bool Automat::AddSymbolToAlphabet(char ch)
{
	return alphabet.Add(ch);
}
/// Setter for the alphabet.
void Automat::SetAlphabet(Set<char> chrs)
{
	alphabet = chrs;
}
/// Ads a state.
bool Automat::AddState(bool isStart, bool isFinal, Set<Transition>& transitions)
{
	int setId = states.getSize();
	while (HasState(setId)) {
		setId++;
	}
	State a(setId, isStart, isFinal, transitions);
	return states.Add(a);
}
/// Ads a state.
bool Automat::AddState(int id, bool isStart, bool isFinal, Set<Transition>& transitions)
{
	int setId = states.getSize();
	while (HasState(setId)) {
		setId++;
	}
	State a(setId, isStart, isFinal, transitions);
	return states.Add(a);
}
/// Ads a state.
bool Automat::AddState(State& state)
{
	int setId = states.getSize();
	while (HasState(setId)) {
		setId++;
	}
	state.SetId(setId);
	return states.Add(state);
}
/// Getter for the id.
int Automat::GetId()
{
	return id;
}
/// Ads a transition to a given state.
bool Automat::AddTransition(int id, Transition& transition)
{
	for (size_t i = 0; i < states.getSize(); i++)
	{
		if (states[i].GetId() == id) {
			return states[i].AddTransition(transition);
		}
	}
	return false;
}
/// Returns the amount of states that the automat has.
int Automat::GetStatesCount()
{
	return states.getSize();
}
/// Changes the transiton whit a given symbol of given state.
void Automat::ChangeTransition(int idOfState, char symbol, Set<int> newEnd)
{
	for (size_t i = 0; i < states.getSize(); i++)
	{
		if (states[i].GetId() == idOfState) {
			for (size_t j = 0; j < states[i].GetAllTransitions().getSize(); j++)
			{
				if (states[i].GetAllTransitions()[j].GetSymbol() == symbol) {
					states[i].GetAllTransitions()[j].SetEnd(newEnd);
				}
			}
		}
	}
}
/// Merges a set of states int a single state and return it.
State Automat::MergeStates(Set<State> statesToMerge)
{
	State result = statesToMerge[0];
	for (size_t i = 1; i < statesToMerge.getSize(); i++)
	{
		result.AddTransitions(statesToMerge[i].GetAllTransitions());
		if (statesToMerge[i].IsStart()) {
			result.SetIsStart(1);
		}
		if (statesToMerge[i].IsFinal()) {
			result.SetIsFinal(1);
		}
	}
	return result;
}
/// Getter for the states.
Set<State> Automat::GetAllStates()
{
	return states;
}
/// Returns the set of ids that all transitions return.
Set<int> Automat::GetAllStatesIds()
{
	Set<int> result;
	for (size_t i = 0; i < states.getSize(); i++)
	{
		result.Add(states[i].GetId());

	}
	return result;
}
/// Getter the set of start states.
Set<State> Automat::GetStartStates()const
{
	Set<State> result;
	for (size_t i = 0; i < states.getSize(); i++)
	{
		if (states[i].IsStart()) {
			result.Add(states[i]);
		}
	}
	return result;
}
/// Getter the set of start states ids.
Set<int> Automat::GetStartStatesIds()
{
	Set<int> result;
	for (size_t i = 0; i < states.getSize(); i++)
	{
		if (states[i].IsStart()) {
			result.Add(states[i].GetId());
		}
	}
	return result;
}
/// Getter the set of final states.
Set<State> Automat::GetFinalStates()
{
	Set<State> result;
	for (size_t i = 0; i < states.getSize(); i++)
	{
		if (states[i].IsFinal()) {
			result.Add(states[i]);
		}
	}
	return result;
}

/// Getter the set of final states ids.
Set<int> Automat::GetFinalStatesIds()
{
	Set<int> result;
	for (size_t i = 0; i < states.getSize(); i++)
	{
		if (states[i].IsFinal()) {
			result.Add(states[i].GetId());
		}
	}
	return result;
}
/// Getter the set of states by given a set of their ids.
Set<State> Automat::GetStates(Set<int> id)
{
	Set<State> result;
	for (size_t i = 0; i < id.getSize(); i++)
	{
		result.Add(GetState(id[i]));
	}
	return result;
}
/// Getter the id of the state whit the biggest id by a given set of states.
int Automat::GetMaxStateId(Set<State> statesToCheck) const
{
	int max = -1;
	for (size_t i = 0; i < statesToCheck.getSize(); i++)
	{
		if (statesToCheck[i].GetId() >= max) {
			max = statesToCheck[i].GetId();
		}
	}
	return max;
}
/// Getter the id of the state whit the biggest id by a given set of states.
Set<State> Automat::ChangeStatesIds(Set<State> statesToChange, int change)
{
	for (size_t i = 0; i < statesToChange.getSize(); i++)
	{
		statesToChange[i].SetId(statesToChange[i].GetId() + change);
		statesToChange[i].ChangeEndIds(change);
	}
	return statesToChange;
}



/// Gets the state by a given id.
State Automat::GetState(int id)
{
	for (size_t i = 0; i < states.getSize(); i++)
	{
		if (states[i].GetId() == id) {
			return states[i];
		}
	}
}
/// Checks if the automat has a state whit the given id.
bool Automat::HasState(int id)
{
	for (size_t i = 0; i < states.getSize(); i++)
	{
		if (states[i].GetId() == id) {
			return true;
		}
	}
	return false;
}
/// Returns the set of ids that the state returns by a given symbol.
Set<int> Automat::GetTransitionStates(int id, char symbol)
{
	State state = GetState(id);
	Set<int> result = state.GetTransitionSet(symbol);
	return result;
}
/// Returns the set of ids that the a set of states returns by a given symbol.
Set<int> Automat::GetTransitionStates(Set<int> start, char symbol)
{
	Set<int> transitionStates;
	for (size_t i = 0; i < start.getSize(); i++)
	{
		Set<int> currStates = GetTransitionStates(start[i], symbol);
		transitionStates = Union(currStates, transitionStates);
	}
	return transitionStates;
}
/// Returns the set of ids that the automat will return by reading a String and a given start state.
Set<int> Automat::GetTransitionStates(int start, String word)
{
	Set<int> curentStates;
	curentStates.Add(start);

	for (size_t i = 0; i < word.size(); i++)
	{

		Set<int> transitionStates;
		for (size_t j = 0; j < curentStates.getSize(); j++)
		{
			transitionStates = Union(GetTransitionStates(curentStates[j], word[i]), transitionStates);
		}

		curentStates = transitionStates;
	}
	return curentStates;
}
/// Returns the set of states that can reach the final state.
Set<State> Automat::GetStatesThatCanReachFinal()
{
	Set<State> finalStates = GetFinalStates();
	Set<State> result;
	for (size_t i = 0; i < states.getSize(); i++)
	{
		if (states[i].CanReach(finalStates)) {
			result.Add(states[i]);
		}
	}
	int resultCount = result.getSize();
	while (true) {
		resultCount = result.getSize();
		for (size_t i = 0; i < states.getSize(); i++)
		{
			if (states[i].CanReach(result)) {
				if (result.Add(states[i])) {
					resultCount++;
				}
			}
		}
		if (resultCount == result.getSize()) {
			break;
		}
	}
	return result;
}
/// Checks if the state can reach a final state.
bool Automat::CanReachFinal(State other)
{
	if (GetStatesThatCanReachFinal().Contains(other)) {
		return true;
	}
	return false;
}
/// Checks if a given state can reach another given state.
bool Automat::CanReachState(State start, State end)
{
	Set<State> finalStates;
	finalStates.Add(end);
	Set<State> result;
	for (size_t i = 0; i < states.getSize(); i++)
	{
		if (states[i].CanReach(finalStates)) {
			result.Add(states[i]);
		}
	}
	int resultCount = result.getSize();
	while (true) {
		resultCount = result.getSize();
		for (size_t i = 0; i < states.getSize(); i++)
		{
			if (states[i].CanReach(result)) {
				if (result.Add(states[i])) {
					resultCount++;
				}

			}
		}
		if (resultCount == result.getSize()) {
			break;
		}
	}
	if (result.Contains(start))return true;
	return false;
}


/// Prints the automat.
void Automat::print()const
{
	std::cout << "Id : " << id << std::endl;

	for (size_t i = 0; i < states.getSize(); i++)
	{
		states[i].print();
	}
}
/// Prints the automat to a given stream.
void Automat::print(std::ostream& os) const
{
	os << "Id : " << id << std::endl;

	for (size_t i = 0; i < states.getSize(); i++)
	{
		states[i].print(os);
	}
}
/// Saves the automat to a given file stream.
void Automat::save(std::fstream& outFile)const
{
	outFile << "Id : " << id << std::endl;
	for (size_t i = 0; i < states.getSize(); i++)
	{
		states[i].save(outFile);
	}
}
/// Saves the automat to a given output file stream.
void Automat::save(std::ofstream& outFile) const
{
	outFile << "Id : " << id << std::endl;
	for (size_t i = 0; i < states.getSize(); i++)
	{
		states[i].save(outFile);
	}
}
/// Saves the automat to a given String object.
void Automat::save(String& file)const
{
	file += "Id : ";
	file += file.getIntToStr(id);
	file += "\n";


	for (size_t i = 0; i < states.getSize(); i++)
	{
		states[i].save(file);
	}
}
/// Checks if the language of the automat is empty.
bool Automat::empty()
{
	if (Intersection(GetStatesThatCanReachFinal(), GetStartStates()).isEmpty()) {
		return true;
	}
	return false;
}
/// Checks if the automat is deterministic.
bool Automat::deterministic()
{
	if (GetStartStates().getSize() != 1)return false;
	for (size_t i = 0; i < states.getSize(); i++)
	{
		if (!states[i].deterministicTransitions())return false;
	}
	return true;
}
/// Checks if the automat can recognize a word.
bool Automat::recognize(String word)
{
	word.RemoveAll('E');

	Set<State> startStates = GetStartStates();
	Set<int> finalStates = GetFinalStatesIds();
	if (word.size() == 0 && Intersection(startStates, GetFinalStates()).getSize() >= 1) {
		return true;

	}
	for (size_t i = 0; i < startStates.getSize(); i++)
	{
		Set<int> resStates = GetTransitionStates(startStates[i].GetId(), word);
		if (Intersection(resStates, finalStates).getSize() >= 1)return true;
	}
	return false;
}
/// Return the union of the automat whit a given automat.
Automat Automat::UnionOfAtutomats(const Automat& other)const
{

	Automat result = *this;
	Automat rhs = other;

	Set<State> otherStates = rhs.GetAllStates();
	int maxId = GetMaxStateId(result.states);
	otherStates = rhs.ChangeStatesIds(otherStates, maxId + 1);
	result.states = Union(result.states, otherStates);
	return result;
}
/// Return the concatenation of the automat whit a given automat.
Automat Automat::Concat(const Automat& other)const
{
	Automat rhs = other;
	Automat result = *this;

	int maxLhsId = GetMaxStateId(result.states);
	rhs.states = rhs.ChangeStatesIds(rhs.states, maxLhsId + 1);
	Set<State> rhsStates = rhs.GetAllStates();
	bool rhsHasStartWhichIsFinal = (Intersection(rhs.GetFinalStates(), rhs.GetStartStates()).getSize() >= 1);
	bool lhsHasStartWhichIsFinal = (Intersection(result.GetFinalStates(), result.GetStartStates()).getSize() >= 1);
	Set<State> rhsStartStates = rhs.GetStartStates();
	Set<State> lhsFinalStates = result.GetFinalStates();

	result.states = Union(result.states, rhs.states);
	for (size_t i = 0; i < result.states.getSize(); i++)
	{
		if (lhsFinalStates.Contains(result.states[i])) {
			for (size_t j = 0; j < rhsStartStates.getSize(); j++)
			{
				result.states[i].AddTransitions(rhsStartStates[j].GetAllTransitions());
			}
		}
	}
	if (!lhsHasStartWhichIsFinal) {
		for (size_t i = 0; i < result.states.getSize(); i++)
		{
			if (rhsStartStates.Contains(result.states[i])) {
				result.states[i].SetIsStart(0);
			}
		}
	}
	if (!rhsHasStartWhichIsFinal) {
		for (size_t i = 0; i < result.states.getSize(); i++)
		{
			if (lhsFinalStates.Contains(result.states[i])) {
				result.states[i].SetIsFinal(0);
			}
		}
	}

	return result;
}
/// Return the positive wrap of the automat.
Automat Automat::PositiveWrap()const
{
	Automat result = *this;
	Set<State> s = GetStartStates();
	for (size_t i = 0; i < result.states.getSize(); i++)
	{
		if (result.GetFinalStates().Contains(result.states[i])) {
			for (size_t j = 0; j < s.getSize(); j++)
			{
				result.states[i].AddTransitions(s[j].GetAllTransitions());
			}
		}
	}
	return result;

}
/// Return the Kleene's star of the automat.
Automat Automat::KleeneStar() const
{
	Automat result = *this;
	result = result.PositiveWrap();
	if (Intersection(result.GetFinalStates(), result.GetStartStates()).getSize() < 1) {
		Set<Transition >a;
		result.AddState(1, 1, a);
	}
	return result;
}



/// Determinates the automat.
void Automat::determinate()
{
	Automat result(-1, alphabet);
	Set<State> startStates = GetStartStates();
	Set<int> startStatesIds = GetStartStatesIds();
	State startState = MergeStates(startStates);
	startState.SetId(0);
	Vector<Set<int>> preMergedIds;
	preMergedIds.pushBack(startStatesIds);
	result.AddState(startState);
	int statesIncreased = 1;
	while (statesIncreased != 0) {
		int statesIncreasedOnlastStep = statesIncreased;
		statesIncreased = 0;
		for (size_t j = 0; j < statesIncreasedOnlastStep; j++)
		{
			State currState = result.GetState(result.GetMaxStateId(result.states) - j);
			for (size_t i = 0; i < alphabet.getSize(); i++)
			{
				Set<int> currTransitionStates = currState.GetTransitionSet(alphabet[i]);
				if (preMergedIds.findItem(currTransitionStates) == -1 && currTransitionStates.getSize() > 0) {

					State newState = MergeStates(GetStates(currTransitionStates));
					newState.SetId(preMergedIds.size());
					if (newState.IsStart()) {
						newState.SetIsStart(0);
					}
					preMergedIds.pushBack(currTransitionStates);
					result.AddState(newState);
					statesIncreased++;
					Set<int> newEnd;
					newEnd.Add(newState.GetId());

					result.ChangeTransition(currState.GetId(), alphabet[i], newEnd);

				}
				else if (currTransitionStates.getSize() > 0) {

					Set<int> newEnd;
					newEnd.Add(preMergedIds.findItem(currTransitionStates));
					result.ChangeTransition(currState.GetId(), alphabet[i], newEnd);

				}
			}


		}
	}
	for (size_t i = 0; i < result.GetAllStates().getSize(); i++)
	{
		for (size_t j = 0; j < result.GetAllStates()[i].GetAllTransitions().getSize(); j++)
		{
			if (result.GetAllStates()[i].GetAllTransitions()[j].GetEnd().getSize() > 1) {
				if (preMergedIds.findItem(result.GetAllStates()[i].GetAllTransitions()[j].GetEnd()) != -1) {
					Set<int> newEnd;
					newEnd.Add(preMergedIds.findItem(result.GetAllStates()[i].GetAllTransitions()[j].GetEnd()));
					result.ChangeTransition(result.GetAllStates()[i].GetId(),
						result.GetAllStates()[i].GetAllTransitions()[j].GetSymbol(), newEnd);
				}
			}
		}
	}
	*this = result;


}
/// Checks if the language of the automat is finite.
bool Automat::isFinite()
{
	if (empty())return true;
	Set<State> statesThatCanReachFinal = GetStatesThatCanReachFinal();
	int transitionsCount = 0;
	for (size_t i = 0; i < statesThatCanReachFinal.getSize(); i++)
	{
		for (size_t j = 0; j < statesThatCanReachFinal.getSize(); j++)
		{
			if (CanReachState(statesThatCanReachFinal[i], statesThatCanReachFinal[j])
				&& CanReachState(statesThatCanReachFinal[j], statesThatCanReachFinal[i]))return false;
		}
	}


	return true;
}
