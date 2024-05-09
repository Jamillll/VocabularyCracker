#include <fstream>
#include <string>
#include <Windows.h>
#include <vector>
#include <unordered_map>
#include <sstream>

#include "Timer.h"

void Save(std::unordered_map<std::string, unsigned int>* confirmedWords);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	std::unordered_map<std::string, unsigned int> confirmedWords;

	std::vector<std::string> words;
	std::string buffer;

	std::string input;
	std::ifstream readLog("User Data\\Log.txt");
	while (std::getline(readLog, input))
	{
		std::stringstream line(input);

		std::string word;
		std::getline(line, word, ' ');
		std::string count;
		std::getline(line, count, ' ');

		confirmedWords[word] = std::stoi(count);
	}
	readLog.close();

	input = input.empty();
	std::fstream wordList("User Data\\words_alpha.txt");
	while (std::getline(wordList, input))
	{
		words.push_back(input);
	}
	wordList.close();

	float keyDuration = 0;
	float dictionaryDuration = 0;
	float saveDuration = 0;

	while (true)
	{

		{
			Timer timer(&keyDuration);

			for (size_t i = 8; i <= 255; i++)
			{
				if (GetAsyncKeyState(i) == -32767)
				{
					char key = (char)i;

					switch (key)
					{
					case VK_F7:
						goto close;

					case VK_SPACE:
						buffer += key;
						break;

					case VK_RETURN:
						buffer += VK_SPACE;
						break;

					case VK_BACK:
						if (buffer.length() > 0)
						{
							buffer.pop_back();
						}
						break;

					default:
						if (key >= 65 && key <= 90)
						{
							buffer += key + 32;
						}
						break;
					}
				}
			}
		}

		if (buffer.length() <= 0) continue;
		else if (buffer[buffer.size() - 1] != ' ') continue;
		
		buffer.pop_back();

		// Catches the case that the buffer only had ' ' inside of it which is removed, leaving an empty buffer. 
		// This would cause it to waste time looping through the whole array, only to find nothing
		if (buffer.length() <= 0) continue;

		{
			Timer timer(&dictionaryDuration);

			for (size_t i = 0; i < words.size(); i++)
			{
				if (words[i] == buffer)
				{
					confirmedWords[words[i]]++;
					break;
				}
			}
		}
		buffer.clear();

		{
			Timer timer(&saveDuration);
			Save(&confirmedWords);
		}
	}

close:
	Save(&confirmedWords);
}

void Save(std::unordered_map<std::string, unsigned int>* confirmedWords)
{
	std::ofstream writeLog("User Data\\Log.txt");

	for (auto& word : *confirmedWords)
	{
		writeLog << word.first << " " << word.second << std::endl;
	}
	writeLog.close();
}