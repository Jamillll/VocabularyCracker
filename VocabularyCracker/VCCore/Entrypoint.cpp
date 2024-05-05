#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <vector>

int main()
{
	std::cout << "Hello world from VCCore" << std::endl;

	std::vector<std::string> confirmedWords;
	std::vector<std::string> words;
	std::string buffer;
	char key;

	std::fstream wordList("words_alpha.txt");
	std::string input;
	while (std::getline(wordList, input))
	{
		words.push_back(input);
	}

	while (true)
	{
		for (size_t i = 8; i <= 255; i++)
		{
			if (GetAsyncKeyState(i) == -32767)
			{
				key = (char)i;

				switch (key)
				{
				case ' ':
					buffer += key;
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
				
				system("cls");
				std::cout << buffer;
			}
		}

		system("cls");
		std::cout << buffer << std::endl;
		std::cout << "Confirmed words: ";

		for (size_t i = 0; i < confirmedWords.size(); i++)
		{
			std::cout << confirmedWords[i] << ", ";
		}

		if (buffer.length() <= 0) continue;
		else if (buffer[buffer.size() - 1] != ' ') continue;
		
		buffer.pop_back();

		for (size_t i = 0; i < words.size(); i++)
		{
			if (words[i] == buffer)
			{
				confirmedWords.push_back(words[i]);
				break;
			}
		}
		buffer.clear();
	}
}