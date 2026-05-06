#include "enemy.h"

Enemy::Enemy(TextureManager* txtman, Map* _map, Player* _player, int y, int x) :m_textureManager(txtman),
map(_map), player(_player), rect(x, y, 32, 32) {
	sprite.setTexture(*(m_textureManager->get_texture("State_GameEnemy")));
	sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

}

void Enemy::set(Map* _map, Player* _player, int x, int y) {
	map = _map;
	player = _player;
	sprite.setTexture(*(m_textureManager->get_texture("State_GameEnemy")));
	sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	rect = sf::FloatRect(x, y, 32, 32);

}

void Enemy::update(float time) {
	m_elapsed += time;
	if (m_elapsed > 4 and player->get_rect().left>(rect.left -800)and life) {
		dx = dx > 0 ? 150 : -150;
		
	}
	else {
		if (!life)
			sprite.setTextureRect(sf::IntRect(64, 0, 32, 32));
		sprite.setPosition(rect.left - map->get_offsetX(), rect.top - map->get_offsetY());
		return;
	}
	 
		rect.left += dx * time;
		Collision();
		currentFrame += time * 10;
		if (currentFrame > 2) currentFrame -= 2;

		sprite.setTextureRect(sf::IntRect(32 * int(currentFrame), 0, 32, 32));
		if (!life)
			sprite.setTextureRect(sf::IntRect(64, 0, 32, 32));

		if (player->get_rect().intersects(rect)) {
			if (touching == false) {
				if (life) {
					if (player->get_dy() > 0) {
						dx = 0;
						player->get_dy() = -40;
						life = false;
					}
					else {
						player->get_life()--;
						touching = true;
					}
				}
			}
		}
		else
			touching = false;
	
	sprite.setPosition(rect.left - map->get_offsetX(), rect.top - map->get_offsetY());
}

void Enemy::Collision() {
	if ((rect.left <= 0) || (rect.left + rect.width >= (map->get_ts() * (map->get_W() - 1)))) {
		dx *= -1;
		return;
	}
	for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
		for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++) {
			auto p = map->get_tiles().find(map->TileMap[i][j]);
			if (p == map->get_tiles().end())
				continue;
			if ((map->TileMap[i][j] == '1') || (((*p).second.solid))) {

				if (dx > 0) {
					rect.left = j * 32 - rect.width;
					dx *= -1;
				}
				else if (dx < 0) {
					rect.left = j * 32 + 32;
					dx *= -1;
				}
			}
		}
}

void Enemy::Render(sf::RenderWindow* wnd) {
	wnd->draw(sprite);
}