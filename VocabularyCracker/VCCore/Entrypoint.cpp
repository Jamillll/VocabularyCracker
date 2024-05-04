#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <vector>

int main()
{
	std::cout << "Hello world from VCCore" << std::endl;

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

				if (key >= 65 && key <= 90)
				{
					key += 32;
				}

				switch (key)
				{
				case VK_BACK:
					buffer.resize(buffer.size() - 2);

				default:
					buffer += key;
				}
				
				system("cls");
				std::cout << buffer;
			}
		}

		system("cls");
		std::cout << buffer;

		for (size_t i = 0; i < words.size(); i++)
		{
			if (words[i] == buffer)
			{
				std::cout << "it worked" << std::endl;
			}
		}
	}
}