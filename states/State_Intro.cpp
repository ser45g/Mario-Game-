#include "State_Intro.h"
#include "StateManager.h"

State_Intro::State_Intro(StateManager* l_stateManager)
	: BaseState(l_stateManager) {}

State_Intro::~State_Intro() { }

void State_Intro::OnCreate() {
	sf::Vector2u windowSize = m_stateMgr->GetContext()
		->m_wind->GetRenderWindow()->getSize();


	backgroundTexture = m_stateMgr->GetContext()->m_levelManager->get_textureManager()->
		get_texture("Intro");
	m_backgroundSprite.setTexture(*(backgroundTexture));
	float a = float(windowSize.x) / m_backgroundSprite.getGlobalBounds().width;
	float b = float(windowSize.y) / m_backgroundSprite.getGlobalBounds().height;
	m_backgroundSprite.setScale(a,
		b);

	m_backgroundSprite.setOrigin(backgroundTexture->getSize().x / 2.0f, backgroundTexture->getSize().y / 2.0f);
	m_backgroundSprite.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);


	sf::Texture* m_introTexture= m_stateMgr->GetContext()->m_levelManager->get_textureManager()->
		get_texture("IntroLogo");
	m_introSprite.setTexture(*m_introTexture);
	m_introSprite.setOrigin(m_introTexture->getSize().x / 2.0f, m_introTexture->getSize().y / 2.0f);
	m_introSprite.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);
	
	m_font.loadFromFile(Utils::GetWorkingDirectory() + "Game\\Fonts\\arial.ttf");
	m_text.setFont(m_font);
	m_text.setString(sf::String("Press SPACE to continue"));
	m_text.setCharacterSize(15);
	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);

	m_text.setPosition(m_introSprite.getPosition().x, 
		m_introSprite.getPosition().y + m_introTexture->getSize().y / 1.5f);

}

void State_Intro::OnDestroy() { }

void State_Intro::Draw() {
	sf::RenderWindow* window = m_stateMgr->
		GetContext()->m_wind->GetRenderWindow();

	window->draw(m_backgroundSprite);
	window->draw(m_introSprite);
	window->draw(m_text);
}

void State_Intro::Continue( ) {
	m_stateMgr->SwitchTo(StateType::MainMenu);
	m_stateMgr->Remove(StateType::Intro);
}

void State_Intro::Update(const float l_time) {
	
}

void State_Intro::HandleInput(const sf::Event& event)  {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
		Continue();
	}
	if (event.type == sf::Event::Resized) {
		sf::Vector2u windowSize = m_stateMgr->GetContext()
			->m_wind->GetRenderWindow()->getSize();
		m_backgroundSprite.setPosition(m_view.getCenter());


		float a = float(windowSize.x) / m_backgroundSprite.getGlobalBounds().width;
		float b = float(windowSize.y) / m_backgroundSprite.getGlobalBounds().height;
		//m_backgroundSprite.setScale(a, b);
		//m_backgroundSprite.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);
	}
}

void State_Intro::Activate() {}
void State_Intro::Deactivate() {}