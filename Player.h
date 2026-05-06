#pragma once
#include <SFML/Graphics.hpp>
#include "Utility.cpp"
#include "Map.h"
#include "Window.h"
#include "ResourceManagment/TextureManager.h"

class Player {
private:
	double dx, dy;
	sf::FloatRect rect;
	sf::Sprite sprite;

	bool onGround = false;
	bool rig;
	bool scal = true;
	bool win = false;
	bool finish = false;

	int life = 3;
	int coins = 0;
	
	float curFrame;
	sf::Vector2f startSpeed{ 200,600 };
	
	int ts;
	Map* map;
	TextureManager* m_textureManager;
	Window* wnd;
public:
	Player() {}
	bool get_win()const { return win; }
	bool get_finish()const { return finish; }
	void set_win(bool _win)  {  win=_win; }
	void set_finish(bool _finish)  {  finish=_finish; }
	Map* get_map() { return map; }
	const sf::FloatRect get_rect()const { return rect; }

	double& get_dx() { return dx; }

	double& get_dy() { return dy; }

	int& get_life() { return life; }

	int& get_coins() { return coins; }

	bool Is_onGround()const { return onGround; }

	sf::Vector2f& get_startSpeed() { return startSpeed; }

	const sf::Vector2f& GetPosition() { return sf::Vector2f{ rect.left,rect.top }; }

	void Render(sf::RenderWindow* wnd) {
		wnd->draw(sprite);
	}
	Player(TextureManager* txtman,Map* map, Window* wnd);
	
	void set(TextureManager* txtman, Map* _map, Window* _wnd);
	

	void update(float time);
	void Collision(float dir);
	

};
