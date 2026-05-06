
#include "Flag.h"

void Flag::Collision() {
	for (int i = rect.top / ts; i < (rect.top + rect.height) / ts; i++)
		for (int j = rect.left / ts; j < (rect.left + rect.width) / ts; j++) {
			if ((m_player->get_map()->TileMap[i][j] == 'D' && m_player->get_win())) {
				m_player->set_finish(true);
				dy = 0;
			}
			if ((m_player->get_map()->TileMap[i][j] == 'W' && !m_player->get_win())) {
				dy = 0;

			}

		}
}

Flag::Flag(Player* player, int y, int x) :m_player(player) {
	texture.loadFromFile(Utils::GetWorkingDirectory() + "Game\\Paint\\flag.png");
	sprite.setTexture(texture);
	rect = sf::FloatRect(x, y, ts, ts);

	dy = 0;
	t = 0;
	tim = true;
}

void Flag::set(Player* player, int y, int x) {
	m_player = player;
	texture.loadFromFile(Utils::GetWorkingDirectory() + "Game\\Paint\\flag.png");
	sprite.setTexture(texture);
	rect = sf::FloatRect(x, y, ts, ts);

	dy = 0;
	t = 0;
	tim = true;
}

void Flag::update(float time) {

	rect.top += dy * time;
	Collision();

	if (m_player->get_rect().intersects(rect)) {
		m_player->set_win(true);
	}
	if (m_player->get_win() && tim) {
		dy = 60;
		tim = false;
	}
	sprite.setPosition(rect.left - m_player->get_map()->get_offsetX(),
		rect.top - m_player->get_map()->get_offsetY());
}

void Flag::Render(sf::RenderWindow* wnd) {
	wnd->draw(sprite);
}