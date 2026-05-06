#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Player.h"
#include "ResourceManagment/TextureManager.h"

class Enemy {
private:
	float dx = 0, dy = 0;
	sf::FloatRect rect;
	sf::Sprite sprite;
	float currentFrame = 0;
	int life = 1;
	bool touching = false;
	bool onGround = false;
	float m_elapsed = 0;
	bool ok = false;
	Player* player = nullptr;
	Map* map = nullptr;
	TextureManager* m_textureManager = nullptr;
public:

	Enemy() {}
	Enemy(TextureManager* txtman, Map* _map, Player* _player, int y, int x);

	void set(Map* _map, Player* _player, int x, int y);

	void update(float time);

	void Collision();

	void Render(sf::RenderWindow* wnd);
};



