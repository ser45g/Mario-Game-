#include "State_LevelsOrContinue.h"
#include "StateManager.h"


State_LevelsOrContinue::State_LevelsOrContinue(StateManager* l_stateManager)
	: BaseState(l_stateManager), m_rects(m_amountButtons), m_labels(m_amountButtons) {}

State_LevelsOrContinue::~State_LevelsOrContinue() {}

void State_LevelsOrContinue::OnCreate() {
	SetTransparent(true); // Set our transparency flag.

	sf::Vector2u windowSize = m_stateMgr->GetContext()
		->m_wind->GetRenderWindow()->getSize();

	m_rect.setSize(m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getDefaultView().getSize());
	//m_rect.setPosition(view_center.x,view_center.y);
	m_rect.setPosition(0, 0);
	m_rect.setFillColor(sf::Color(0, 0, 0, 150));

	m_font.loadFromFile(Utils::GetWorkingDirectory() + "Game\\Fonts\\arial.ttf");
	
	m_text.setFont(m_font);
	m_text.setString(
		sf::String("DO YOU WANT TO GO TO THE LEVELS \n") +
		sf::String("  AND CHOOSE A PARTICULAR ONE \n")+
		sf::String("	OR YOU WANT TO CONTINUE\n")+
		sf::String("		THE STORY?\n")
	
	);

	m_text.setCharacterSize(25);
	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);

	m_text.setFillColor(sf::Color::White);
	m_text.setOutlineColor(sf::Color::Blue);
	m_text.setOutlineThickness(1.5);

	m_text.setPosition(windowSize.x / 2.0F, windowSize.y / 2.0f);


	m_buttonSize = sf::Vector2f(300.0f, 32.0f);
	m_buttonPos = sf::Vector2f(windowSize.x / 2.0f, windowSize.y - m_buttonSize.y * 3.5f);
	m_buttonPadding = 10; // 4px.
	std::string str[3];
	str[0] = "CONTINUE";
	str[1] = "LEVELS";
	str[2] = "MAIN MENU";

	for (int i = 0; i < m_amountButtons; ++i) {
		sf::Vector2f buttonPosition(
			m_buttonPos.x, m_buttonPos.y +
			(i * (m_buttonSize.y + m_buttonPadding)));
		m_rects[i].setSize(m_buttonSize);
		m_rects[i].setFillColor(sf::Color::Transparent);
		m_rects[i].setOutlineColor(sf::Color::White);
		m_rects[i].setOutlineThickness(3);

		m_rects[i].setOrigin(
			m_buttonSize.x / 2.0f, m_buttonSize.y / 2.0f);
		m_rects[i].setPosition(buttonPosition);

		m_labels[i].setFont(m_font);
		m_labels[i].setFillColor(sf::Color::White);
		m_labels[i].setString(sf::String(str[i]));
		m_labels[i].setCharacterSize(20);
		m_labels[i].setOutlineColor(sf::Color::Blue);
		m_labels[i].setOutlineThickness(1);

		sf::FloatRect rect = m_labels[i].getLocalBounds();
		m_labels[i].setOrigin(
			rect.left + rect.width / 2.0f,
			rect.top + rect.height / 2.0f);

		m_labels[i].setPosition(buttonPosition);
	}
}

void State_LevelsOrContinue::OnDestroy() {}

void State_LevelsOrContinue::Activate() {}
void State_LevelsOrContinue::Deactivate() {}

void State_LevelsOrContinue::Update(const float l_time) {
	m_elapsed += l_time;
	if (m_elapsed >= 15.0f) {
		m_stateMgr->Remove(StateType::LevelsOrContinue);
		m_stateMgr->SwitchTo(StateType::MainMenu);
		m_elapsed = 0;
	}
}

void State_LevelsOrContinue::MouseClick(const sf::Vector2i& l_details) {
	SharedContext* context = m_stateMgr->GetContext();
	sf::Vector2i mousePos = l_details;

	float halfX = m_buttonSize.x / 2.0f;
	float halfY = m_buttonSize.y / 2.0f;
	for (int i = 0; i < m_amountButtons; ++i) {
		if (mousePos.x >= m_rects[i].getPosition().x - halfX &&
			mousePos.x <= m_rects[i].getPosition().x + halfX &&
			mousePos.y >= m_rects[i].getPosition().y - halfY &&
			mousePos.y <= m_rects[i].getPosition().y + halfY)
		{
			switch (i) {
			case 0:
				Continue();
				break;
			case 1:
				Levels();
				break;
			case 2:
				MainMenu();
			}
		}
	}
}

void State_LevelsOrContinue::Continue() {
	m_stateMgr->GetContext()->m_levelManager->Continue();
	m_stateMgr->SwitchTo(StateType::Game);
	m_stateMgr->Remove(StateType::LevelsOrContinue);
}
void State_LevelsOrContinue::MainMenu() {
	m_stateMgr->SwitchTo(StateType::MainMenu);
	m_stateMgr->Remove(StateType::LevelsOrContinue);
}
void State_LevelsOrContinue::Levels() {
	m_stateMgr->SwitchTo(StateType::Levels);
	m_stateMgr->Remove(StateType::LevelsOrContinue);

}
void State_LevelsOrContinue::Draw() {
	sf::RenderWindow* window = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
	window->draw(m_rect);
	for (int i = 0; i < m_amountButtons; ++i) {
		window->draw(m_rects[i]);
		window->draw(m_labels[i]);
	}
	window->draw(m_text);
}