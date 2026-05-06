#include "State_Loading.h"
#include "StateManager.h"

State_Loading::State_Loading(StateManager* l_stateManager)
	: BaseState(l_stateManager) {}

State_Loading::~State_Loading() {
	

	delete music_manager_thread;
	delete texture_manager_thread;

	music_manager_thread = nullptr;
	texture_manager_thread = nullptr;
}

void State_Loading::OnCreate() {
	sf::Vector2u windowSize = m_stateMgr->GetContext()
		->m_wind->GetRenderWindow()->getSize();

	music_manager_thread = new std::thread([&]() {m_stateMgr->GetContext()->m_levelManager->get_musicManager()->Load(); });
	texture_manager_thread = new std::thread([&]() {m_stateMgr->GetContext()->m_levelManager->get_textureManager()->Load(); });
	
	m_backgroundTexture.loadFromFile(Utils::GetWorkingDirectory() + "Game\\Paint\\stars_sky.jpg");
	m_backgroundSprite.setTexture(m_backgroundTexture);
	m_backgroundSprite.setScale(0.7,0.5);

	m_backgroundSprite.setOrigin(m_backgroundTexture.getSize().x / 2.0f, m_backgroundTexture.getSize().y / 2.0f);
	m_backgroundSprite.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f); 
	m_backgroundSprite.setPosition(m_view.getCenter());


	m_introTexture.loadFromFile(Utils::GetWorkingDirectory() + "Game\\Paint\\mrbeast.png");
	m_introSprite.setTexture(m_introTexture);
	m_introSprite.setOrigin(m_introTexture.getSize().x / 2.0f, m_introTexture.getSize().y / 2.0f);
	m_introSprite.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

	m_font.loadFromFile(Utils::GetWorkingDirectory() + "Game\\Fonts\\arial.ttf");
	m_text.setFont(m_font);
	m_text.setString(sf::String("We're loading..."));
	m_text.setCharacterSize(20);
	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	
	m_text.setPosition(m_introSprite.getPosition().x,
		m_introSprite.getPosition().y + m_introTexture.getSize().y / 1.5f);

}

void State_Loading::OnDestroy() {
	music_manager_thread->join();
	texture_manager_thread->join();
	m_stateMgr->GetContext()->m_levelManager->Load();
}

void State_Loading::Draw() {
	sf::RenderWindow* window = m_stateMgr->
		GetContext()->m_wind->GetRenderWindow();

	window->draw(m_backgroundSprite);
	window->draw(m_introSprite);
	window->draw(m_text);
}

void State_Loading::Continue() {
	//m_stateMgr->SwitchTo(StateType::LevelsOrContinue);
	m_stateMgr->SwitchTo(StateType::Intro);
	m_stateMgr->Remove(StateType::Loading);
}

void State_Loading::Update(const float l_time) {
	m_elapsed += l_time;
	if (m_elapsed > threshold_sec) {
		Continue();
		m_elapsed = 0;
	}
	
	//Continue();

}
void State_Loading::Activate() {}
void State_Loading::Deactivate() {}