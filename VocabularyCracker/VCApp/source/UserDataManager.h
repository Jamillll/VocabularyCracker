#pragma once
#include <string>
#include <vector>

class UserDataManager
{
private:
	std::vector<std::pair<std::string, int>> m_ConfirmedWords;

	std::vector<std::string> m_DictionaryWords;
	std::vector<std::string> m_DictionarySlice;

public:
	int m_SliceIndex = 1;
	int m_EntriesPerSlice = 10000;

public:
	UserDataManager();

	// Log
	std::vector<std::pair<std::string, int>> GetLogData();
	void SortLogByCount(bool isAscending = true);
	void SortLogByLength(bool isAscending = true);

	// Dictionary
	void ResetDictionaryData();
	std::vector<std::string>* GetDictionaryData();
	void SetDictionarySlice();
	std::vector<std::string>* GetDictionarySlice();
	void SortDictionaryBySearch(std::string searchInput);
	int GetDictionarySliceCount();

	// Utility Functions
	int ReturnCollectionSliceCount(std::vector<std::string>* collectionToSlice);

	~UserDataManager();
};