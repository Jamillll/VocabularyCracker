#include <fstream>
#include <string>
#include <Windows.h>
#include <vector>
#include <unordered_map>
#include <sstream>

#include "Timer.h"

enum CoreState
{
	EXIT = -1,
	RUNNING = 0,
	PAUSED = 1,
	UNPAUSED = 2,
};

void Save(std::unordered_map<std::string, unsigned int>* confirmedWords);
CoreState LogKeys(std::string* bufferHandle);

//int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
int main()
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

	bool paused = false;
	while (true)
	{
		switch (LogKeys(&buffer))
		{
		case EXIT:
			goto close;

		case RUNNING:
			break;

		case PAUSED:
			paused = true;
			break;

		case UNPAUSED:
			paused = false;
			break;
		}

		if (paused) 
		{
			buffer.clear();
			continue;
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

CoreState LogKeys(std::string* bufferHandle)
{
	for (size_t i = 8; i <= 255; i++)
	{
		if (GetAsyncKeyState(i) == -32767)
		{
			char key = (char)i;

			switch (key)
			{
			case VK_SPACE:
				*bufferHandle += key;
				break;

			case VK_RETURN:
				*bufferHandle += VK_SPACE;
				break;

			case VK_BACK:
				if (bufferHandle->length() > 0)
				{
					bufferHandle->pop_back();
				}
				break;

			case VK_F7:
				return EXIT;

			case VK_F10:
				return PAUSED;

			case VK_F9:
				return UNPAUSED;

			default:
				if (key >= 65 && key <= 90)
				{
					*bufferHandle += key + 32;
				}
				break;
			}
		}
	}

	return RUNNING;
}