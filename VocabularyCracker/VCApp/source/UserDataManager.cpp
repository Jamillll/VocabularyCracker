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

UserDataManager::~UserDataManager()
{
}
