#include "UserDataManager.h"

#include <fstream>
#include <sstream>
#include <algorithm>

UserDataManager::UserDataManager()
{
    std::string input = "";
    std::ifstream readLog("../VCCore/User Data/Log.txt");
    while (std::getline(readLog, input))
    {
        std::stringstream line(input);
        std::pair<std::string, int> word;

        std::getline(line, word.first, ' ');
        std::string count;
        std::getline(line, count, ' ');
        word.second = std::stoi(count);

        m_ConfirmedWords.push_back(word);
    }
    readLog.close();

    ResetDictionaryData();
    SetDictionarySlice();
}

std::vector<std::pair<std::string, int>> UserDataManager::GetLogData()
{
    return m_ConfirmedWords;
}

void UserDataManager::SortLogByCount(bool isAscending)
{
    if (isAscending)
    {
        std::sort(m_ConfirmedWords.begin(), m_ConfirmedWords.end(),
            [](auto& left, auto& right)
            {
                return left.second > right.second;
            });
    }
    else std::sort(m_ConfirmedWords.begin(), m_ConfirmedWords.end(),
        [](auto& left, auto& right)
        {
            return left.second < right.second;
        });
}

void UserDataManager::SortLogByLength(bool isAscending)
{
    if (isAscending)
    {
        std::sort(m_ConfirmedWords.begin(), m_ConfirmedWords.end(),
            [](auto& left, auto& right)
            {
                return left.first.length() > right.first.length();
            });
    }
    else std::sort(m_ConfirmedWords.begin(), m_ConfirmedWords.end(),
        [](auto& left, auto& right)
        {
            return left.first.length() < right.first.length();
        });
}

void UserDataManager::ResetDictionaryData()
{
    m_SliceIndex = 1;

    std::string input;
    std::ifstream readLog("../VCCore/User Data/words_alpha.txt");
    while (std::getline(readLog, input))
    {
        m_DictionaryWords.push_back(input);
    }
    readLog.close();
}

std::vector<std::string>* UserDataManager::GetDictionaryData()
{
    return &m_DictionaryWords;
}

void UserDataManager::SetDictionarySlice()
{
    int sliceBegin = m_EntriesPerSlice * (m_SliceIndex - 1);
    int sliceEnd = m_EntriesPerSlice * m_SliceIndex;

    if (sliceEnd >= m_DictionaryWords.size())
    {
        sliceEnd = m_DictionaryWords.size();
    }

    std::vector<std::string> slice(m_DictionaryWords.begin() + sliceBegin, m_DictionaryWords.begin() + sliceEnd);
    m_DictionarySlice = slice;
}

std::vector<std::string>* UserDataManager::GetDictionarySlice()
{
    return &m_DictionarySlice;
}

void UserDataManager::SortDictionaryBySearch(std::string searchInput)
{
    m_SliceIndex = 1;
    std::vector<std::string> filteredResults;

    for (size_t i = 0; i < m_DictionaryWords.size(); i++)
    {
        if (m_DictionaryWords[i].find(searchInput) != std::string::npos)
        {
            filteredResults.push_back(m_DictionaryWords[i]);
        }
    }

    m_DictionaryWords = filteredResults;
}

int UserDataManager::GetDictionarySliceCount()
{
    // Code off of stack overflow to divide rounding up
    return (m_DictionaryWords.size() + m_EntriesPerSlice - 1) / m_EntriesPerSlice;
}

int UserDataManager::ReturnCollectionSliceCount(std::vector<std::string>* collectionToSlice)
{
    // Code off of stack overflow to divide rounding up
    return (collectionToSlice->size() + m_EntriesPerSlice - 1) / m_EntriesPerSlice;
}

UserDataManager::~UserDataManager()
{
}
