#pragma once
#include <string>
#include <vector>

class UserDataManager
{
private:
	std::vector<std::pair<std::string, int>> m_ConfirmedWords;
	std::vector<std::string> m_DictionaryWords;

public:
	UserDataManager();

	std::vector<std::pair<std::string, int>> GetLogData();
	void SortLogByCount(bool isAscending = true);
	void SortLogByLength(bool isAscending = true);

	std::vector<std::string> GetFullDictionaryData();
	std::vector<std::string> GetSingleCharacterData(char character);
	std::vector<std::string> GetSearchResultData(std::string search);

	~UserDataManager();
};