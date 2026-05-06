#include "State_Settings.h"
#include "StateManager.h"

State_Settings::State_Settings(StateManager* l_stateManager):
	m_rects(m_amountButtons),m_labels(m_amountButtons),m_state(m_amountButtons,true),
	BaseState(l_stateManager) {}

State_Settings::~State_Settings() {}

void State_Settings::OnCreate() {
	sf::Vector2u windowSize = m_stateMgr->GetContext()
		->m_wind->GetRenderWindow()->getSize();
	
	sf::Texture* backgroundTexture = m_stateMgr->GetContext()->m_levelManager->get_textureManager()->
		get_texture("BackgroundStarsSky");
	m_backgroundSprite.setTexture(*(backgroundTexture));
	m_backgroundSprite.setScale(0.7,
		0.5);

	m_backgroundSprite.setOrigin(backgroundTexture->getSize().x / 2.0f, backgroundTexture->getSize().y / 2.0f);
	m_backgroundSprite.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

	m_font.loadFromFile(Utils::GetWorkingDirectory() + "Game\\Fonts\\arial.ttf");

	m_headline.setFont(m_font);
	m_headline.setString(sf::String("SETTINGS:"));
	m_headline.setCharacterSize(30);
	m_headline.setFillColor(sf::Color::Cyan);

	sf::FloatRect headtextRect = m_headline.getLocalBounds();
	m_headline.setOrigin(headtextRect.left + headtextRect.width / 2.0f,
		headtextRect.top + headtextRect.height / 2.0f);

	m_headline.setPosition(windowSize.x / 2.0f, 50);


	m_text.setFont(m_font);
	m_text.setString(
		sf::String("\n")
		
	);
	m_text.setCharacterSize(25);
	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);

	m_text.setFillColor(sf::Color::White);
	m_text.setOutlineColor(sf::Color::Red);
	m_text.setOutlineThickness(1.5);

	m_text.setPosition(windowSize.x / 2.0F, windowSize.y / 2.0f);


	m_buttonSize = sf::Vector2f(400.0f, 32.0f);
	m_buttonPos = sf::Vector2f(windowSize.x / 2.0f, windowSize.y/2.0F);
	m_buttonPadding = 10; // 4px.
	std::string str[4];
	str[0] = "MUSIC";
	str[1] = "RESET";
	str[2] = "DELETE HISTORY";
	str[3] = "GO BACK TO MENU";

	for (int i = 0; i < m_amountButtons; ++i) {
		sf::Vector2f buttonPosition(
			m_buttonPos.x, m_buttonPos.y +
			(i * (m_buttonSize.y + m_buttonPadding)));
		m_rects[i].setSize(m_buttonSize);
		m_rects[i].setFillColor(sf::Color::Transparent);
		m_rects[i].setOutlineColor(i==0 ?sf::Color::Green:sf::Color::Yellow);
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

void State_Settings::OnDestroy() {
	
}
void State_Settings::MouseClick(const sf::Vector2i& l_details) {
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
				//if (!m_stateMgr->HasState(StateType::Game)) {
				//	return;
				//}
				m_state[0] = !m_state[0];
				m_stateMgr->GetContext()->m_levelManager->
					get_currentLevel()->setMusicOn(!(m_stateMgr->GetContext()->m_levelManager->
						get_currentLevel()->IsMusicOn()));
				m_rects[0].setOutlineColor(m_state[0]?sf::Color::Green:sf::Color::Red);
				ToggleMusic(m_state[0]);
				break;
			case 1:
				Reset();
				break;

			case 2:
				DeleteHistory();
				break;
			case 3:
				Continue();
				break;
			}
		}
	}
	
}
void State_Settings::Reset() {
	m_stateMgr->GetContext()->m_levelManager->Reset();
}

void State_Settings::ToggleMusic(bool play) {
	if (!m_stateMgr->HasState(StateType::Game)) {
		m_stateMgr->GetContext()->m_levelManager->get_currentLevel()->setMusicOn(play);
		return;
	}
	Music* music = m_stateMgr->GetContext()->m_levelManager->get_currentLevel()->get_music();
	if (music == nullptr) 
		return;
	play ?music->get_sound()->play()  : music->get_sound()->pause();
}
void State_Settings::Draw() {
	sf::RenderWindow* window = m_stateMgr->
		GetContext()->m_wind->GetRenderWindow();
	window->draw(m_backgroundSprite);
	for (int i = 0; i < m_amountButtons; ++i) {
		window->draw(m_rects[i]);
		window->draw(m_labels[i]);
	}
	window->draw(m_headline);
	window->draw(m_text);
}

void State_Settings::Continue() {
	if (ChangeTime >= ChangeTimeThreshold) {
		m_stateMgr->SwitchTo(StateType::MainMenu);
		ChangeTime = 0;
	}
}

void State_Settings::Update(const float l_time) {
	ChangeTime += l_time;
	float a = m_stateMgr->GetContext()->m_wind->GetViewSpace().width / m_backgroundSprite.getLocalBounds().width;
	float b = m_stateMgr->GetContext()->m_wind->GetViewSpace().height / m_backgroundSprite.getLocalBounds().height;
	m_backgroundSprite.setScale(a, b);
}
void State_Settings::Activate() {}
void State_Settings::Deactivate() {}