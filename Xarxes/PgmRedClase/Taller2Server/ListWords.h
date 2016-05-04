#pragma once
#include <vector>

class ListWords
{
private:
	std::vector<std::string> aWords;
	int indexWord;
	std::vector<bool> aSent;

public:
	ListWords();
	void LoadFromFile(std::string _fileName);
	void LoadDefault();
	bool WordToSend(std::string& _word);
	void WordSent();
	bool Compare(std::string _word);
	bool IncIndex();
	bool EndList();

	~ListWords();
};

