#pragma once
#include "Automat.h"
class FiniteAutomatSystem {
private:
	Vector<Automat> automats;
	Set<char> alphabet;
	String fileName;
	String fileContent;
	bool fileOpen;
public:
	FiniteAutomatSystem();

	void run();

	void listAutomats()const;

	void Print(int)const;

	void Save(int, String);

	void Empty(int)const;

	void Deterministic(int)const;

	void Recognize(int, String)const;

	void Union(int, int);

	void Concat(int, int);

	void Un(int);

	void Reg(String);

	bool HasId(int);

	void Determinate(int);

	void Finite(int);

	void KleeneStar(int);

	void Open(String);

	void Close();

	void SaveAs(String);

	void Update(String);

	void Help();

	void Read(String);


};