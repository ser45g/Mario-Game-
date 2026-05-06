#pragma once
#include "BaseState.h"
#include <vector>
class State_EndCredits : public BaseState {
public:
	State_EndCredits(StateManager* l_stateManager);
	~State_EndCredits();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();
	void HandleInput(const sf::Event& event) override {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
			Continue();
		} else if (sf::Mouse::Button::Left == event.mouseButton.button){

			MouseClick(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
		}
	}
	void MouseClick(const sf::Vector2i& l_details);

	void Update(const float l_time);
	void Draw();

	void Continue();
private:

	sf::Font m_font;
	sf::Text m_text;
	sf::Text m_headline;
	sf::Sprite m_backgroundSprite;
	float m_elapsed = 0.0f;

	sf::Vector2f m_buttonSize;
	sf::Vector2f m_buttonPos;
	unsigned int m_buttonPadding;
	const int m_amountButtons = 1;
	std::vector<sf::RectangleShape >m_rects;
	std::vector<sf::Text> m_labels;
};

