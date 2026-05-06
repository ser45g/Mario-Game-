#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

using MessageContainer = std::vector<std::string>;

class Textbox{
public:
	Textbox();
	Textbox(int l_visible, int l_charSize, 
		int l_width, sf::Vector2f l_screenPos);
	~Textbox();

	void Setup(int l_visible, int l_charSize, 
		int l_width, sf::Vector2f l_screenPos);
	void Add(std::string l_message);
	void Clear();
	void setPosition(sf::Vector2f l_screenPos);
	int get_width() const { return m_backdrop.getSize().x; }
	void Render(sf::RenderWindow& l_wind);
	const MessageContainer& GetContent() const {
		return m_messages;
	}
private:
	MessageContainer m_messages;
	int m_numVisible;
	int amount_of_messages=6;

	sf::RectangleShape m_backdrop;
	sf::Font m_font;
	sf::Text m_content;
};