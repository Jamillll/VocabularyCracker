#pragma once
#include <string>
#include <vector>

class UserDataManager
{
private:
	std::vector<std::pair<std::string, int>> m_ConfirmedWords;

public:
	UserDataManager();

	std::vector<std::pair<std::string, int>> GetLogData();
	void SortLogByCount(bool isAscending = true);
	void SortLogByLength(bool isAscending = true);

	~UserDataManager();
};