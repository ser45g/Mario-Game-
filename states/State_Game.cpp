#include "State_Game.h"
#include "StateManager.h"
#include<chrono>
#include<ctime>
#include<iomanip>
#include <SFML/Audio.hpp>
#include <thread>
#include <fstream>
#pragma warning(disable : 4996)

State_Game::State_Game(StateManager* l_stateManager):
	level(m_stateMgr->GetContext()->m_levelManager->get_currentLevel()),
	BaseState(l_stateManager) {
}

State_Game::~State_Game(){
	if(music != nullptr)
		music->get_sound()->stop();
	music_thread->detach();
	delete music_thread;
	music_thread = nullptr;

	for (auto pointer : enemy) {
		delete pointer;
	}
}

void State_Game::OnCreate(){

	map=(level->get_map());
	music = level->get_music();
	if (music == nullptr) {
		std::cout << "no State_GameBackground music\n";
	}
	
	music_thread=new std::thread([&]() {
		if (level->IsMusicOn())
			music->get_sound()->play();
		else
			music->get_sound()->pause();
		});
	music->get_sound()->setLoop(true);
	
	sf::Vector2u windowSize = m_stateMgr->GetContext()
		->m_wind->GetRenderWindow()->getSize();

	m_backgroundSprite= (level->get_sprite());

	m_backgroundSprite->setOrigin(level->get_texture()->getSize().x / 2.0f,
		level->get_texture()->getSize().y / 2.0f);
	
	heartTexture.loadFromFile(Utils::GetWorkingDirectory() + "Game\\Paint\\heart128.png");
	heart.setTexture(heartTexture);
	m_textbox.Setup(0, 17, 100, sf::Vector2f(windowSize.x -130, 8));
	
	sf::Vector2u size = m_stateMgr->GetContext()->m_wind->GetWindowSize();
	m_view.setSize(size.x,size.y);
	m_view.setCenter(size.x/2.0f,size.y/2.0f);
	m_view.zoom(1.5f);
	m_stateMgr->GetContext()->m_wind->GetRenderWindow()->setView(m_view);

	m_player.set(m_stateMgr->GetContext()->m_levelManager->get_textureManager(),
		level->get_map(),
		m_stateMgr->GetContext()->m_wind);
	
	for (int i = 0; i < map->get_H()-1; i++)
		for (int j = 0; j < map->get_W() - 1; j++) {
			char A = map->TileMap[i][j];
			if (map->TileMap[i][j] == 'Q') {

				enemy.push_back(new Enemy(m_stateMgr->GetContext()->
					m_levelManager->get_textureManager(),
					map, & m_player, i * 32, j * 32));
			}
			else if (map->TileMap[i][j] == 'W') {
				flag.set(&m_player, i * 32, j * 32-16);
			}
		}
		
}

void State_Game::OnDestroy(){ }

void State_Game::Update(const float l_time) {
	Window* wnd = m_stateMgr->GetContext()->m_wind;
	sf::Vector2u size = wnd->GetWindowSize();

	flag.update(l_time);
	m_player.update(l_time);
	m_textbox.Clear();
	m_textbox.Add("Time: "+std::to_string(int(m_elapsed)));
	m_textbox.Add("Coins: "+std::to_string(m_player.get_coins()));
	
	for (int i = 0; i < enemy.size(); ++i) {
		enemy[i]->update(l_time);
	}
	map->Update(l_time);
	m_timePassedSinceLastPausePushed += l_time;
	m_elapsed += l_time;

	m_view.setCenter(m_player.GetPosition().x+size.x/4, m_player.GetPosition().y );
	
	wnd->GetRenderWindow()->setView(m_view);

	sf::FloatRect viewSpace = wnd->GetViewSpace();
	m_backgroundSprite->setPosition(m_view.getCenter());
	heart.setPosition(m_view.getCenter().x-m_view.getSize().x/2,
		m_view.getCenter().y - m_view.getSize().y / 2);
	//m_textbox.setPosition(m_view.getCenter());
	m_textbox.setPosition(sf::Vector2f{ m_view.getCenter().x + m_view.getSize().x / 2 
		-m_textbox.get_width(),//???
		m_view.getCenter().y - m_view.getSize().y / 2 });
	float a = m_stateMgr->GetContext()->m_wind->GetViewSpace().width / m_backgroundSprite->getLocalBounds().width;
	float b = m_stateMgr->GetContext()->m_wind->GetViewSpace().height / m_backgroundSprite->getLocalBounds().height;
	m_backgroundSprite->setScale(a, b);
	if (m_player.get_finish()) {
		if (m_stateMgr->GetContext()->m_levelManager->IsLastLevel()) {
			EndCredits();
		}else 
		GameOver();
	}
}
void State_Game::HandleInput(const sf::Event& event) {
	//Input handling.

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) and
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))) {
		if (m_player.Is_onGround()) {
			m_player.get_dy() = -m_player.get_startSpeed().y;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		m_player.get_dx() = -m_player.get_startSpeed().x;
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		m_player.get_dx() = m_player.get_startSpeed().x;
	} 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (m_player.Is_onGround()) {
			m_player.get_dy() = -m_player.get_startSpeed().y;
		}
		return;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
		MainMenu();
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
		Pause();
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		if (m_stateMgr->GetContext()->m_levelManager->IsLastLevel()) {
			level->IsDone() = true;
			SaveResults();
			EndCredits();
		}
		else
			GameOver();
		return;

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) and
		(event.type == sf::Event::MouseWheelScrolled)) {
		if (event.mouseWheelScroll.delta > 0)
			m_view.zoom(0.98);
		else
			m_view.zoom(1.02);
		return;
	}
}

void State_Game::Draw(){
	sf::RenderWindow* window = m_stateMgr->GetContext()->m_wind->GetRenderWindow();

	window->draw(*m_backgroundSprite);
	map->Render(window);
	for (int i = 0;i <enemy.size(); ++i)
		enemy[i]->Render(window);
	flag.Render(window);
	m_player.Render(window);
	m_textbox.Render(*window);
	sf::Vector2f hearts = heart.getPosition();
	for (int i = 0; i < m_player.get_life(); ++i) {
		heart.setPosition(hearts.x+i * 32, hearts.y+17);
		window->draw(heart);
	}
}

void State_Game::EndCredits(){
	m_stateMgr->SwitchTo(StateType::EndCredits);
	m_stateMgr->Remove(StateType::Game);
}

void State_Game::MainMenu(){
	//m_stateMgr->Remove(StateType::MainMenu);
	m_stateMgr->SwitchTo(StateType::MainMenu);
}
void State_Game::SaveResults() {
	std::ifstream f(Utils::GetWorkingDirectory() + "Game\\Log\\history.txt");
	if (!f.good()) {
		std::cout << "can't open"<< Utils::GetWorkingDirectory() + "Game\\Log\\history.txt";
	}

	std::list<std::string> vec;
	std::string temp;
	while (!f.eof()) {
		getline(f, temp);
		if (temp == "" or temp==" ")
			continue;
		vec.push_back(temp);
	}
	auto time = std::time(nullptr);
	std::time_t end_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	vec.push_front( " Level: "+std::to_string(m_stateMgr->GetContext()->m_levelManager->get_current_level()+1)
		+" Time: " + std::to_string(m_elapsed)//m_clockshow.getElapsedTime().asSeconds() 
		+" Coins: "+std::to_string(m_player.get_coins())+ 
		" Date: "+ std::ctime(&end_time));
	f.close();
	std::ofstream ofs(Utils::GetWorkingDirectory() + "Game\\Log\\history.txt", std::ios::out | std::ios::trunc); // clear contents
	
	for (auto& i : vec) {
		ofs << i << '\n';
	}
	ofs.close();
}

void State_Game::GameOver(){
	
	level->IsDone() = true;
	SaveResults();

	m_stateMgr->SwitchTo(StateType::GameOver);
	m_stateMgr->Remove(StateType::Game);
}

void State_Game::Pause(){
	if (m_timePassedSinceLastPausePushed >= 0.25) {

		m_stateMgr->SwitchTo(StateType::Paused);
		m_timePassedSinceLastPausePushed = 0;
	}
}

void State_Game::Activate() {  }
void State_Game::Deactivate(){ }
