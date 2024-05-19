#include "UserDataManager.h"

#include <fstream>
#include <sstream>
#include <algorithm>

UserDataManager::UserDataManager()
{
    std::string input;
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

    input = "";
    readLog.open("../VCCore/User Data/words_alpha.txt");
    while (std::getline(readLog, input))
    {
        m_DictionaryWords.push_back(input);
    }
    readLog.close();
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

std::vector<std::string> UserDataManager::GetFullDictionaryData()
{
    return m_DictionaryWords;
}

std::vector<std::string> UserDataManager::GetSingleCharacterData(char character)
{
    if (character < 'a') character = 'a';
    else if (character > 'z') character = 'z';

    int vectorStart = -1;
    int vectorEnd = -1;

    for (size_t i = 0; i < m_DictionaryWords.size(); i++)
    {
        if (vectorStart == -1)
        {
            if (m_DictionaryWords[i][0] == character)
            {
                vectorStart = i;
                continue;
            }
        }
        else
        {
            if (m_DictionaryWords[i][0] != character)
            {
                vectorEnd = i;
                break;
            }
        }
    }

    if (vectorEnd == -1) vectorEnd = m_DictionaryWords.size();

    std::vector<std::string> characterData(m_DictionaryWords.begin() + vectorStart, m_DictionaryWords.begin() + vectorEnd);
    return characterData;
}

std::vector<std::string> UserDataManager::GetSearchResultData(std::string search)
{
    std::vector<std::string> doesContain;

    for (size_t i = 0; i < m_DictionaryWords.size(); i++)
    {
        if (m_DictionaryWords[i].find(search) != std::string::npos)
        {
            doesContain.push_back(m_DictionaryWords[i]);
        }
    }

    return doesContain;
}

int UserDataManager::ReturnCollectionSliceCount(std::vector<std::string>* collectionToSlice)
{
    // Code off of stack overflow to divide rounding up
    return (collectionToSlice->size() + m_EntriesPerPage - 1) / m_EntriesPerPage;
}

int UserDataManager::ReturnDictionarySliceCount()
{
    // Code off of stack overflow to divide rounding up
    return (m_DictionaryWords.size() + m_EntriesPerPage - 1) / m_EntriesPerPage;
}

std::vector<std::string> UserDataManager::GetDictionaryDataSlice(std::vector<std::string>* collectionToSlice, int sliceNumber)
{
    int sliceBegin = m_EntriesPerPage * (sliceNumber - 1);
    int sliceEnd = m_EntriesPerPage * sliceNumber;

    if (sliceEnd >= collectionToSlice->size())
    {
        sliceEnd = collectionToSlice->size();
    }

    std::vector<std::string> slice(collectionToSlice->begin() + sliceBegin, collectionToSlice->begin() + sliceEnd);
    return slice;
}

UserDataManager::~UserDataManager()
{
}
