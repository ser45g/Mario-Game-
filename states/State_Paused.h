#pragma once
#include "BaseState.h"
//#include "../EventManager.h"

class State_Paused : public BaseState{
public:
	State_Paused(StateManager* l_stateManager);
	~State_Paused();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	//void Update(const sf::Time& l_time);
	void HandleInput(const sf::Event& event) override {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
			Unpause();
		}
	}
	void Update(const float l_time);
	void Draw();

	void Unpause();
private:
	sf::Font m_font;
	sf::Text m_text;
	sf::RectangleShape m_rect;
	sf::Time m_clock;
	float m_elapsed = 0;
};