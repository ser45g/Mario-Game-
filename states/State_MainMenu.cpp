#include "State_MainMenu.h"
#include "StateManager.h"
#include "../SharedContext.h"

State_MainMenu::State_MainMenu(StateManager* l_stateManager)
	: m_labels(m_amountButtons),m_rects(m_amountButtons), BaseState(l_stateManager) {}

State_MainMenu::~State_MainMenu(){}

void State_MainMenu::OnCreate(){

	sf::Vector2u windowSize = m_stateMgr->GetContext()
		->m_wind->GetRenderWindow()->getSize();

	//m_backgroundTexture.loadFromFile(Utils::GetWorkingDirectory() + "Game\\Menu\\screen.png");
	backgroundTexture = m_stateMgr->GetContext()->m_levelManager->get_textureManager()->
		get_texture("MainMenu");
	m_backgroundSprite.setTexture(*backgroundTexture);
	float a = float(windowSize.x) / m_backgroundSprite.getGlobalBounds().width;
	float b = float(windowSize.y) / m_backgroundSprite.getGlobalBounds().height;
	m_backgroundSprite.setScale(a, b);

	m_backgroundSprite.setOrigin(backgroundTexture->getSize().x / 2.0f, backgroundTexture->getSize().y / 2.0f);
	//m_backgroundSprite.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);
	m_backgroundSprite.setPosition(m_view.getCenter());

	m_font.loadFromFile(Utils::GetWorkingDirectory() + "Game\\Fonts\\arial.ttf");
	m_text.setFont(m_font);
	m_text.setString(sf::String("MAIN MENU:"));
	m_text.setCharacterSize(24);

	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin( textRect.width / 2.0f,
		textRect.height / 2.0f);
	//m_text.setOrigin(textRect.left + textRect.width / 2.0f,
		//textRect.top + textRect.height / 2.0f);

	m_text.setPosition(windowSize.x / 2.0f, windowSize.y/10.0f);

	m_buttonSize = sf::Vector2f(windowSize.x/2.0f,32.0f);
	m_buttonPos = sf::Vector2f(windowSize.x / 2.0f , windowSize.y / 3.0f );
	m_buttonPadding = 6; // 4px.
	std::string str[6];
	str[0] = "PLAY";
	str[1] = "LEVELS";
	str[2] = "HISTORY";
	str[3] = "SETTINGS";
	str[4] = "CREDITS";
	str[5] = "EXIT";

	for(int i = 0; i < m_amountButtons; ++i){
		sf::Vector2f buttonPosition(
			m_buttonPos.x,m_buttonPos.y + 
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
		m_labels[i].setOutlineColor(sf::Color::White);
		m_labels[i].setOutlineThickness(1);

		sf::FloatRect rect = m_labels[i].getLocalBounds();
		m_labels[i].setOrigin(
			rect.left + rect.width / 2.0f,
			rect.top + rect.height / 2.0f);

		m_labels[i].setPosition(buttonPosition);
	}
}

void State_MainMenu::OnDestroy(){}

void State_MainMenu::Activate(){
	if (m_stateMgr->HasState(StateType::Game)
		&& m_labels[0].getString() != "RESUME") {
		sf::FloatRect rect = m_labels[0].getLocalBounds();
		m_labels[0].setString(sf::String("RESUME"));
		m_labels[0].setOrigin(
			rect.left + rect.width / 2.0f,
			rect.top + rect.height / 2.0f);
		m_labels[0].setPosition(m_buttonPos);
	} else {
		m_labels[0].setString(sf::String("PLAY"));
	}
	//if (m_stateMgr->HasState(StateType::Game)
	//	&& m_labels.back().getString() != "EXIT LEVEL")
	//{
	//	m_labels.back().setString(sf::String("EXIT LEVEL"));
	//} else {
	//	m_labels.back().setString(sf::String("EXIT"));
	//}
}
void State_MainMenu::HandleInput(const sf::Event& event)  {

	if (sf::Mouse::Button::Left==event.mouseButton.button) {
		MouseClick(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
	}
	if (event.type == sf::Event::Resized) {
		sf::Vector2u windowSize = m_stateMgr->GetContext()
			->m_wind->GetRenderWindow()->getSize();
		m_backgroundSprite.setPosition(m_view.getCenter());
		
		//float a = float(windowSize.x) / backgroundTexture->getSize().x;
		//float b = float(windowSize.y) / backgroundTexture->getSize().y;
		//m_backgroundSprite.setScale(a, b);
		//sf::Vector2f abc= m_backgroundSprite.getGlobalBoun
		//m_view.setSize(m_backgroundSprite.getLocalBounds().width,
			//m_backgroundSprite.getLocalBounds().height);
	}
}


void State_MainMenu::MouseClick(const sf::Vector2i& l_details) {
	if (ChangeTime >= ChangeTimeThreshold) {
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
					if (m_stateMgr->HasState(StateType::Game)) {
						m_stateMgr->SwitchTo(StateType::Game);
					} else
					m_stateMgr->SwitchTo(StateType::LevelsOrContinue);
					break;
				case 1:
					m_stateMgr->SwitchTo(StateType::Levels);
					break;
				case 2:
					m_stateMgr->SwitchTo(StateType::History);
					break;
				case 3:
					m_stateMgr->SwitchTo(StateType::Settings);
					break;
				case 4:
					m_stateMgr->SwitchTo(StateType::EndCredits);
					break;
				case 5:
					if (m_stateMgr->HasState(StateType::Game)) {
						m_stateMgr->Remove(StateType::Game);
						m_labels[0].setString(sf::String("PLAY"));
					} else
					m_stateMgr->GetContext()->m_wind->Close();
					break;
				}
			}
		}
	ChangeTime = 0;
	}
}

void State_MainMenu::Draw(){
	sf::RenderWindow* window = m_stateMgr->
		GetContext()->m_wind->GetRenderWindow();
	window->draw(m_backgroundSprite);
	window->draw(m_text);
	for(int i = 0; i < m_amountButtons; ++i){
		window->draw(m_rects[i]);
		window->draw(m_labels[i]);
	}
}

void State_MainMenu::Update(const float l_time) {
	ChangeTime += l_time; 
	sf::Vector2u windowSize = m_stateMgr->GetContext()
		->m_wind->GetRenderWindow()->getSize();

}
void State_MainMenu::Deactivate(){}