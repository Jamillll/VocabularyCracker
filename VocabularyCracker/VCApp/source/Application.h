#pragma once
#include <GLFW/glfw3.h>
#include "UserDataManager.h"
#include "Timer.h"

class Application
{
private:
	enum class State
	{
		CRASH = -1,
		LOGVIEW = 0,
		DICTIONARYVIEW = 1,
		SETTINGSVIEW = 2,
	};

	State m_State = State::LOGVIEW;
	GLFWwindow* m_Window = nullptr;

	UserDataManager m_UserData;
	std::vector<std::string> m_WorkingDictionaryData;
	std::vector<std::string> m_WorkingDictionaryDataSlice;
	int m_DefaultDictionaryCharacter = 1;
	std::string m_SearchInput;
	bool m_HasSearched = false;

public:
	Application();

	void Run();

	~Application();

private:
	void Update();

	void LogView();
	void DictionaryView();
	void SettingsView();
};