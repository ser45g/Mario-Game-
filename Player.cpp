#pragma once
#include "Player.h"
Player::Player(TextureManager* txtman,Map* map, Window* wnd) :m_textureManager(txtman),
	map(map), wnd(wnd), ts(map->get_ts()) {
	sprite.setTexture(*(m_textureManager->get_texture("State_GamePlayer")));;
	sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	rect = sf::FloatRect(7 * ts, 8 * ts, 32, 32);

	dx = dy = 0;
	curFrame = 2;
	rig = true;
	scal = true;
	life = 3;
	coins = 0;
}

void Player::set(TextureManager* txtman,Map* _map, Window* _wnd) {
	m_textureManager = txtman;
	map = _map;
	wnd = _wnd;
	ts = map->get_ts();
	sprite.setTexture(*(m_textureManager->get_texture("State_GamePlayer")));;
	sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	//sprite.setTexture(image);
	rect = sf::FloatRect(7 * ts, 8 * ts, 32, 32);
	
	dx = dy = 0;
	curFrame = 2;
	rig = true;
	scal = true;
	life = 3;
	coins = 0;

}
void Player::update(float time) {

	rect.left += dx * time;
	Collision(0);

	if (!onGround)
		dy += map->get_gravity() * time;

	rect.top += dy * time;
	onGround = false;
	Collision(1);

	
	if (rect.top >= (map->get_H() -2) * ts) {

		map->get_offsetX() = 0;
		map->get_offsetY() = 0;
		rect.top = 8*32;
		rect.left = 8*32;
		life = 3;
		scal = true;
	}
	if (rect.top - rect.height <= 0) {
		dy = 0;
	}

	if (rect.left <= 0)
		rect.left = 1;
	

	if (dx != 0 || life) {
		curFrame += 10 * time;
		if (curFrame > 5)
			curFrame -= 4;
	}

	if (life<1) {
		scal = false;
		sprite.setTextureRect(sf::IntRect(32 * 5, 0, 32, 32));
	}
	else if (dx > 0) {
		if (dy == 0)
			sprite.setTextureRect(sf::IntRect(32 * int(curFrame), 0, 32, 32));
		else
			sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

		rig = true;
	}
	else if (dx < 0) {
		if (dy == 0)
			sprite.setTextureRect(sf::IntRect(32 * int(curFrame) + 32, 0, -32, 32));
		else
			sprite.setTextureRect(sf::IntRect(32, 0, -32, 32));

		rig = false;
	}
	else if (dx == 0) {
		rig ? sprite.setTextureRect(sf::IntRect(0, 0, 32, 32)) :
			sprite.setTextureRect(sf::IntRect(32, 0, -32, 32));
	}
	

	sprite.setPosition(rect.left - map->get_offsetX(), rect.top - map->get_offsetY());
	dx = 0;
}

void Player::Collision(float dir) {
	if (rect.top - rect.height <= 0) {
		dy = 0;
		return;
	}
	if (rect.top >= 80 * 32) {
		return;
	}
	
	for (int i = rect.top / ts; i < (rect.top + rect.height) / ts; i++)
		for (int j = rect.left / ts; j < (rect.left + rect.width) / ts; j++) {

			auto p=map->get_tiles().find(map->TileMap[i][j]);
			if (p == map->get_tiles().end())
				continue;

			if ((((* p).second.solid) && scal)  ) {
				if (dx > 0 && dir == 0)
					rect.left = j * ts - rect.width;
				if (dx < 0 && dir == 0)
					rect.left = j * ts + ts;
				if (dy > 0 && dir == 1) {
					rect.top = i * ts - rect.height;
					dy = 0;
					onGround = true;
				}
				if (dy < 0 && dir == 1) {
					rect.top = i * ts + ts;
					dy = 0;
					if ((*p).first == 'C')
						map->TileMap[i][j] = '4';
					if (map->TileMap[i][j] == 'a')
						map->TileMap[i][j] = '5';

					if (map->TileMap[i - 1][j] == 'm') {
						map->TileMap[i - 1][j] = '6';
					}if (map->TileMap[i - 1][j] == 'P') {
						map->TileMap[i - 1][j] = '6';
					}

				}

				if (map->TileMap[i][j] == 'B' and ((i+rect.height)*ts-10)) {
					map->TileMap[i][j] = '3';

					int a = rand() % 60;
					if (a == 25)
						++life;
					else
						++coins;
				}
			}

			if (map->TileMap[i][j] == 'm') {
				map->TileMap[i][j] = '6';
				++coins;
			}
			if ((*p).second.deadly) {
				map->TileMap[i][j] = 'A';
				--life;
			}
		}
}

