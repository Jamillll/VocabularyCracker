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
		EDITDICTIONARYVIEW = 2,
		SETTINGSVIEW = 3,
	};

	State m_State = State::LOGVIEW;
	GLFWwindow* m_Window = nullptr;

	UserDataManager m_UserData;
	std::string m_SearchInput;

public:
	Application();

	void Run();

	~Application();

private:
	void Update();

	void LogView();
	void DictionaryView();
	void EditDictionaryView();
	void SettingsView();
};