#pragma once
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
//#include "EventManager.h"

class Window{
public:
	Window();
	Window(const std::string& title, const sf::Vector2u& size);
	~Window();

	void BeginDraw();
	void EndDraw();

	void Update();

	bool IsDone() const;
	bool& IsFocused()  {return m_isFocused;}

	sf::FloatRect GetViewSpace() const;

	void Close() {m_isDone = true;}
	bool IsFullscreen() const;
	sf::RenderWindow* GetRenderWindow();
	sf::Vector2u GetWindowSize() const;

	void ToggleFullscreen();

	int bitsPixel = 32;
private:
	void Setup(const std::string& title, const sf::Vector2u& size);
	void Create();

	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	bool m_isDone;
	bool m_isFullscreen;
	bool m_isFocused;
};