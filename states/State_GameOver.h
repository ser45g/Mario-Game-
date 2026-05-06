#pragma once
#include "BaseState.h"
#include <SFML/Graphics.hpp>
#include<fstream>
#include<sstream>

class State_GameOver : public BaseState{
public:
	State_GameOver(StateManager* l_stateManager);
	~State_GameOver();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();
	void MouseClick(const sf::Vector2i& l_details);
	void HandleInput(const sf::Event& event) override {
		if (sf::Mouse::Button::Left == event.mouseButton.button) {
			MouseClick(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
		}
	}
	void Continue();
	void Update(const float l_time);
	void Draw();
private:
	//Textbox m_textbox;
	sf::Font m_font;
	sf::Text m_text;
	sf::Text m_headline;
	sf::Texture m_backgroundTexture;
	sf::Sprite m_backgroundSprite;
	sf::Vector2f m_buttonSize;
	sf::Vector2f m_buttonPos;
	unsigned int m_buttonPadding;
	const int m_amountButtons = 2;
	std::vector<sf::RectangleShape >m_rects;
	std::vector<sf::Text> m_labels;

	float m_elapsed = 0;
};