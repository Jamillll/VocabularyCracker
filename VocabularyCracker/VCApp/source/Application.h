#pragma once
#include <GLFW/glfw3.h>

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