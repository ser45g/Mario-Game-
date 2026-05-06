#pragma once
#include "BaseState.h"
//#include "../EventManager.h"
#include "../Textbox.h"

class State_History : public BaseState {
public:
	State_History(StateManager* l_stateManager);
	~State_History();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();
	void HandleInput(const sf::Event& event) override {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
			Continue();
		}
		else if (sf::Mouse::Button::Left == event.mouseButton.button and
			event.type==sf::Event::MouseButtonPressed) {

			MouseClick(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
		}
		else if (event.type == sf::Event::MouseWheelScrolled) {
			Scroll(event.mouseWheelScroll.delta);		
		}
	}
	//void Update(const sf::Time& l_time);
	void Update(const float l_time);
	void Draw();
	void MouseClick(const sf::Vector2i& l_details);
	void Continue();
	void Scroll(float delta);
private:
	sf::Text m_headline;
	sf::Sprite m_backgroundSprite;
	float m_elapsed = 0.0f;

	std::vector<std::string> history_info;
	int scroll_pos = 0;

	sf::Vector2f m_buttonSize;
	sf::Vector2f m_buttonPos;
	unsigned int m_buttonPadding;
	const int m_amountButtons = 7;
	std::vector<sf::RectangleShape >m_notActiveRects;
	std::vector<sf::Text> m_notActiveLabels;

	sf::Vector2f GoBackButtonSize;
	sf::RectangleShape GoBackButtonRect;
	sf::Text GoBackButtonText;
	sf::Font m_font;
	sf::Text m_text;
};

