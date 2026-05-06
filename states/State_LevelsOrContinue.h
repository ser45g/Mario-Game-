#pragma once
#include "BaseState.h"
#include <SFML/Graphics.hpp>
#include<fstream>
#include<sstream>

class State_LevelsOrContinue : public BaseState {
public:
	State_LevelsOrContinue(StateManager* l_stateManager);
	~State_LevelsOrContinue();

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
	void Levels();
	void MainMenu();

	void Update(const float l_time);
	void Draw();
private:
	sf::Font m_font;
	sf::Text m_text;
	
	sf::Vector2f m_buttonSize;
	sf::Vector2f m_buttonPos;
	unsigned int m_buttonPadding;
	const int m_amountButtons = 3;
	std::vector<sf::RectangleShape >m_rects;
	std::vector<sf::Text> m_labels;
	sf::RectangleShape m_rect;
	float m_elapsed = 0;
};