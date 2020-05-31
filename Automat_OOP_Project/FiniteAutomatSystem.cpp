#include "FiniteAutomatSystem.h"

FiniteAutomatSystem::FiniteAutomatSystem()
{


	for (size_t i = 97; i <= 122; i++)
	{
		alphabet.Add(char(i));
	}
	alphabet.Add(char(69));
	for (size_t i = 48; i <= 57; i++)
	{
		alphabet.Add(char(i));
	}
	fileOpen = false;
}
/// Starts the program.
void FiniteAutomatSystem::run()
{
	String line;
	getline(std::cin, line);
	while (line != "exit")
	{
		if (line == "") {
			getline(std::cin, line);
			continue;
		}

		Vector<String> lineSplited = line.SplitBy(' ');
		line = lineSplited[0];
		if (line != "open" && !fileOpen) {
			std::cout << "You need to open a file\n";
			getline(std::cin, line);
			continue;
		}

		if (line == "list")listAutomats();
		else if (line == "print") {
			Print(lineSplited[1].getInt());
		}
		else if (line == "save") {
			if (lineSplited.size() > 2) {
				Save(lineSplited[1].getInt(), lineSplited[2]);
			}
			else {
				Update(fileName);
			}
		}
		else if (line == "empty") {
			Empty(lineSplited[1].getInt());
		}
		else if (line == "deterministic") {
			Deterministic(lineSplited[1].getInt());
		}
		else if (line == "recognize") {
			Recognize(lineSplited[1].getInt(), lineSplited[2]);
		}
		else if (line == "union") {
			Union(lineSplited[1].getInt(), lineSplited[2].getInt());
		}
		else if (line == "concat") {
			Concat(lineSplited[1].getInt(), lineSplited[2].getInt());
		}
		else if (line == "un") {
			Un(lineSplited[1].getInt());
		}
		else if (line == "reg") {
			Reg(lineSplited[1]);
		}
		else if (line == "determinate") {
			Determinate(lineSplited[1].getInt());
		}
		else if (line == "finite") {
			Finite(lineSplited[1].getInt());
		}
		else if (line == "Kleene") {
			KleeneStar(lineSplited[1].getInt());
		}
		else if (line == "open") {
			Open(lineSplited[1]);
		}
		else if (line == "saveas") {
			SaveAs(lineSplited[1]);
		}
		else if (line == "help") {
			Help();
		}
		else if (line == "close") {
			Close();
		}


		getline(std::cin, line);
	}
	std::cout << "Exiting the program..." << std::endl;
}
/// Check the help function.
void FiniteAutomatSystem::listAutomats() const
{
	if (automats.size() == 0) {
		std::cout << "No automats in the system" << std::endl;
		return;
	}
	for (size_t i = 0; i < automats.size(); i++)
	{
		std::cout << "Id :" << automats[i].GetId() << std::endl;
	}

}
/// Check the help function.
void FiniteAutomatSystem::Print(int id) const
{
	automats[id].print(std::cout);

}
/// Check the help function.
void FiniteAutomatSystem::Save(int id, String outFile)
{
	
	String fileName = outFile;
	String fileContent = "";
	std::fstream in_file{};
	in_file.open(fileName.getCharArray());

	if (!in_file) {
		std::ofstream on_file{};
		on_file.open(fileName.getCharArray());
		if (!on_file) {
			std::cout << "Problem opening file" << std::endl;
			return;
		}
		fileOpen = true;
		on_file.close();
		std::cout << "Successfully opened " << fileName << std::endl;
		return;
	}
	fileOpen = true;
	char ch;
	while (in_file.get(ch)) {

		fileContent.addChar(ch);
	}
	in_file.close();
	std::ofstream on_file{};
	on_file.open(fileName.getCharArray());
	on_file << fileContent;
	automats[id].save(on_file);
	on_file.close();
	std::cout << "Successfully opened " << fileName << std::endl;
	

}
/// Check the help function.
void FiniteAutomatSystem::Empty(int id) const
{
	Automat a = automats[id];
	if (a.empty()) {
		std::cout << "The language of the automat is empty." << std::endl;
	}
	else {
		std::cout << "The language of the automat not is empty." << std::endl;
	}
}


/// Check the help function.
void FiniteAutomatSystem::Deterministic(int id) const
{
	Automat a = automats[id];
	if (a.deterministic()) {
		std::cout << "The automat is deterministic." << std::endl;
	}
	else {
		std::cout << "The automat is not deterministic." << std::endl;
	}
}
/// Check the help function.
void FiniteAutomatSystem::Recognize(int id, String word) const
{
	for (size_t i = 0; i < word.size(); i++)
	{
		if (!alphabet.Contains(word[i])) {
			std::cout << "Sorry some of characters are not in the alphabet." << std::endl;
			return;
		}
	}
	Automat a = automats[id];
	if (a.recognize(word)) {
		std::cout << "The word is in the language of the automat." << std::endl;
	}
	else {
		std::cout << "The word is not in the language of the automat." << std::endl;
	}
}
/// Check the help function.
void FiniteAutomatSystem::Union(int id1, int id2)
{
	Automat a = automats[id1].UnionOfAtutomats(automats[id2]);
	a.SetId(automats.size());
	std::cout << "The new automat id is :" << automats.size() << std::endl;
	automats.pushBack(a);

}
/// Check the help function.
void FiniteAutomatSystem::Concat(int id1, int id2)
{
	Automat a = automats[id1].Concat(automats[id2]);
	a.SetId(automats.size());
	std::cout << "The new automat id is :" << automats.size() << std::endl;
	automats.pushBack(a);

}
/// Check the help function.
void FiniteAutomatSystem::Un(int id)
{
	Automat a = automats[id].PositiveWrap();
	a.SetId(automats.size());
	std::cout << "The new automat id is :" << automats.size() << std::endl;
	automats.pushBack(a);
}
/// Check the help function.
void FiniteAutomatSystem::Reg(String word)
{
	for (size_t i = 0; i < word.size(); i++)
	{
		if (!alphabet.Contains(word[i]) && word[i] != '(' && word[i] != ')' && word[i] != '+' && word[i] != '*' && word[i] != '.') {
			std::cout << "Sorry some of characters are not in the alphabet." << std::endl;
			return;
		}
	}
	Automat a(word, alphabet);
	a.SetId(automats.size());
	while (HasId(a.GetId()))
	{
		a.SetId(a.GetId()+1);
	}
	std::cout << "The new automat id is :" << automats.size() << std::endl;
	automats.pushBack(a);
}
/// Check the help function.
bool FiniteAutomatSystem::HasId(int id)
{
	for (size_t i = 0; i < automats.size(); i++)
	{
		if (automats[i].GetId() == id)return true;
	}
	return false;
}
/// Check the help function.
void FiniteAutomatSystem::Determinate(int id)
{
	Automat a = automats[id];
	a.determinate();
	a.SetId(automats.size());
	std::cout << "The new automat id is :" << automats.size() << std::endl;
	automats.pushBack(a);
}
/// Check the help function.
void FiniteAutomatSystem::Finite(int id)
{

	if (automats[id].isFinite()) {
		std::cout << "The language of the automat is finite." << std::endl;
	}
	else {
		std::cout << "The language of the automat is not finite." << std::endl;
	}
}
/// Check the help function.
void FiniteAutomatSystem::KleeneStar(int id)
{
	Automat a = automats[id].KleeneStar();
	a.SetId(automats.size());
	std::cout << "The new automat id is :" << automats.size() << std::endl;
	automats.pushBack(a);
}
/// Check the help function.
void FiniteAutomatSystem::Open(String file)
{
	fileName = file;
	fileContent = "";
	std::fstream in_file{};
	in_file.open(fileName.getCharArray());

	if (!in_file) {
		std::ofstream on_file{};
		on_file.open(fileName.getCharArray());
		if (!on_file) {
			std::cout << "Problem opening file" << std::endl;
			return;
		}
		fileOpen = true;
		on_file.close();
		std::cout << "Successfully opened " << fileName << std::endl;
		return;
	}
	fileOpen = true;
	char ch;
	while (in_file.get(ch)) {

		fileContent.addChar(ch);
	}
	in_file.close();
	if (fileContent.size() > 0 && fileContent != "") {

		String tempData = fileContent;
		Read(tempData);
	}
	std::cout << "Successfully opened " << fileName << std::endl;
}
/// Check the help function.
void FiniteAutomatSystem::Close()
{
	std::cout << "Successfully closed " << fileName << std::endl;
	fileName = "";
	fileContent = "";
	fileOpen = false;
}
/// Check the help function.
void FiniteAutomatSystem::SaveAs(String file)
{
	String fileName = file;
	String fileContent = "";
	std::fstream in_file{};
	in_file.open(fileName.getCharArray());

	if (!in_file) {
		std::ofstream on_file{};
		on_file.open(fileName.getCharArray());
		if (!on_file) {
			std::cout << "Problem opening file" << std::endl;
			return;
		}
		fileOpen = true;
		on_file.close();
		std::cout << "Successfully opened " << fileName << std::endl;
		return;
	}
	fileOpen = true;
	char ch;
	while (in_file.get(ch)) {

		fileContent.addChar(ch);
	}
	in_file.close();
	

	std::ofstream o_file{};

	o_file.open(file.getCharArray());
	if (!o_file) {
		std::cout << "Problem opening file" << std::endl;
		return;
	}
	o_file << fileContent;
	for (size_t i = 0; i < automats.size(); i++)
	{
		automats[i].save(o_file);
	}
	o_file.close();
	std::cout << "Successfully saved " << fileName << std::endl;
}
/// Check the help function.
void FiniteAutomatSystem::Update(String file)
{
	std::ofstream o_file{};

	o_file.open(file.getCharArray(), std::ofstream::trunc);
	if (!o_file) {
		std::cout << "Problem opening file" << std::endl;
		return;
	}
	for (size_t i = 0; i < automats.size(); i++)
	{
		automats[i].save(o_file);
	}
	o_file.close();
	std::cout << "Successfully saved " << fileName << std::endl;


}
/// Explain how to use the program.
void FiniteAutomatSystem::Help()
{
	std::cout <<
		"The following commands are supported: \n" <<
		"open <file>                opens <file>.\n" <<
		"close                      closes currently opened file.\n" <<
		"save                       saves the currently open file.\n" <<
		"saveas <file>              saves the currently open file in <file>.\n" <<
		"help                       prints this information.\n" <<
		"exit                       exists the program.\n" <<
		"list                       list of identifiers of all read automats.\n" <<
		"print <id>                 displays information about all transitions in the automat.\n" <<
		"save <id> <filename>       saves an automat in a file.\n" <<
		"empty <id>                 checks if the language of the automat is empty.\n" <<
		"deterministic <id>         checks if the automat is deterministic.\n" <<
		"recognize <id> <word>      checks if a word is in the language of the automat.\n" <<
		"union <id1> <id2>          finds the union of two automats and creates a new automat.\n" <<
		"Prints the ID of the new automat.\n" <<
		"concat <id1> <id2>         finds the concatenation of two automata and creates a new automaton.\n" <<
		"Prints the ID of the new automat.\n" <<
		"un <id>                    finds the positive wrap of the automat and creates a new automat.\n" <<
		"Prints the ID of the new automat.\n" <<
		"reg <regex>                creates a new automat on a given regular expression (Kline's theorem).\n" <<
		"Prints the ID of the new automat.\n" <<
		"determinate <id>           creates a new automat that is determinated.\n" <<
		"Prints the ID of the new automat .\n" <<
		"Kleene <id>                finds the Kleene's star of the automat and creates a new automat.\n" <<
		"Prints the ID of the new automat.\n" <<
		"finite <id>                checks if the language of the automat is finite.\n";

}
/// Parses automats from a String object.
void FiniteAutomatSystem::Read(String is)
{
	String line;

	getline(is, line);
	while (true)
	{
		if(line.size() > 0 && line[0] != 'I')
			getline(is, line);

		if (line == "" || line.size() == 0)break;
		Automat automat(-1);
		if (line[0] == 'I') {
			int id = line.SplitBy(' ')[2].getInt();
			while (HasId(id))
			{
				id++;
			}
			automat.SetId(id);
			while (true) {
				if(line.size() > 0 && line[0] != 'F')getline(is, line);
				if (line == "" || line.size() == 0)break;
				if (line[0] == 'I')break;
				if (line[0] == 'F') {
					int stateId = line.SplitBy(' ')[3].getInt();
					int isStart = line.SplitBy(' ')[6].getInt();
					int isFinal = line.SplitBy(' ')[9].getInt();

					State state(stateId, isStart, isFinal);
					while (true) {
						getline(is, line);
						if (line == "" || line.size() == 0)break;
						if (line[0] == 'I')break;
						if (line[0] == 'F')break;
						Transition tr(line.SplitBy(' ')[2].getCharArray()[0]);

						getline(is, line);

						Set<int> end;
						if (line[0] == '(') {
							Vector<String> idsOfEnd = line.SplitBy(' ');
							for (size_t i = 1; i < idsOfEnd.size()-1; i++)
							{
								end.Add(idsOfEnd[i].getInt());
							}
							tr.SetEnd(end);
						}
						state.AddTransition(tr);
						

					}
					automat.AddState(state);
				}
				if (line.size() > 0 && line[0] == 'I')break;
			}

			automats.pushBack(automat);
		}
		
		
	}
}

