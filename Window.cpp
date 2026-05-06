#include "Window.h"

Window::Window() {
	Setup("Window", sf::Vector2u(640, 480));
}

Window::Window(const std::string& title, const sf::Vector2u& size) {
	Setup(title, size);
}

Window::~Window() { m_window.close(); }

void Window::Setup(const std::string& title, const sf::Vector2u& size) {
	m_windowTitle = title;
	m_windowSize = size;
	m_isFullscreen = false;
	m_isDone = false;
	m_isFocused = true;
	Create();
}

void Window::Create() {
	sf::Uint32 style = sf::Style::
		Default;
	if (m_isFullscreen) { style = sf::Style::Fullscreen; }
	m_window.create(sf::VideoMode(m_windowSize.x, m_windowSize.y, 32), m_windowTitle, style);
}

void Window::BeginDraw() { 
	m_window.clear(sf::Color::Blue);
}
void Window::EndDraw() { m_window.display(); }

bool Window::IsDone() const{ return m_isDone; }
bool Window::IsFullscreen()const { return m_isFullscreen; }

sf::RenderWindow* Window::GetRenderWindow() { return &m_window; }
sf::Vector2u Window::GetWindowSize() const{ return m_windowSize; }

sf::FloatRect Window::GetViewSpace() const{
	sf::Vector2f viewCenter(m_window.getView().getCenter());
	sf::Vector2f viewSize(m_window.getView().getSize());
	sf::Vector2f viewSizeHalf(viewSize.x / 2, viewSize.y / 2);
	sf::FloatRect viewSpace(viewCenter - viewSizeHalf, viewSize);
	return viewSpace;
}
void Window::ToggleFullscreen() {
	m_isFullscreen = !m_isFullscreen;
	m_window.close();
	Create();
}

void Window::Update() {}