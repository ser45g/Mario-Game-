#include <SFML/Graphics.hpp>
#include "Player.h"
class Flag {
private:
	float dy;
	sf::FloatRect rect;
	sf::Sprite sprite;
	sf::Texture texture;
	Player* m_player;
	int t;
	bool tim;
	int ts = 32;
public:
	Flag(){}
	Flag(Player* player, int y, int x);

	void set(Player* player, int y, int x);

	void update(float time);

	void Collision();
	void Render(sf::RenderWindow* window);
};