#include "Map.h"
Map::Map(const std::string& path) {
	tileSet.loadFromFile(Utils::GetWorkingDirectory() + "Game\\Paint\\plat.png");
	tile.setTexture(tileSet);
	Load(path);
	tiles.emplace('0',Tile{1,0,sf::IntRect(0, ts*10, ts, ts)}) ;
	tiles.emplace('1',Tile{0,0,sf::IntRect(0, ts*10, ts, ts)}) ;
	tiles.emplace('A',Tile{1,0,sf::IntRect(0, 0, ts, ts)}) ;
	tiles.emplace('B',Tile{1,0,sf::IntRect(ts, 0, ts, ts) });
	tiles.emplace('C',Tile{1,0,sf::IntRect(ts * 2, 0, ts, ts)});
	tiles.emplace('D',Tile{1,0,sf::IntRect(ts * 3, 0, ts, ts)});
	tiles.emplace('P',Tile{1,0,sf::IntRect(0, ts, ts * 2, ts * 4)});
	tiles.emplace('W',Tile{0,0,sf::IntRect(ts * 2, ts, ts, ts * 8)});
	tiles.emplace('F',Tile{0,0,sf::IntRect(ts * 7, ts, ts * 5, ts * 4)});
	tiles.emplace('a',Tile{1,0,sf::IntRect(ts * 4, 0, ts, ts)});
	tiles.emplace('b',Tile{1,0,sf::IntRect(ts * 6, 0, ts, ts)});
	tiles.emplace('d',Tile{1,0,sf::IntRect(ts * 17, 0, ts, ts)});
	tiles.emplace('m',Tile{0,0,sf::IntRect(ts * 5, 0, ts, ts)});
	tiles.emplace('T',Tile{0,0,sf::IntRect(ts * 3, ts, ts * 4, ts * 10)});
	tiles.emplace('E',Tile{1,0,sf::IntRect(ts * 7, 0, ts, ts)});
	tiles.emplace('I',Tile{1,0,sf::IntRect(ts * 8, 0, ts, ts)});
	tiles.emplace('H',Tile{1,0,sf::IntRect(ts * 9, 0, ts, ts)});
	tiles.emplace('J',Tile{1,0,sf::IntRect(ts * 9, 0, -ts, ts)});
	tiles.emplace('t',Tile{0,0,sf::IntRect(ts * 7, ts * 5, ts * 4, ts * 3)});
	tiles.emplace('f',Tile{0,0,sf::IntRect(ts * 12, ts, ts * 9, ts * 9)});
	tiles.emplace('e',Tile{1,0,sf::IntRect(ts * 10, 0, ts, ts)});
	tiles.emplace('k',Tile{1,1,sf::IntRect(ts * 11, 0, ts, ts)});
	tiles.emplace('l',Tile{0,0,sf::IntRect(ts * 12, 0, ts, ts)});
	tiles.emplace('M',Tile{1,0,sf::IntRect(ts * 13, 0, ts, ts)});
	tiles.emplace('3',Tile{1,0,sf::IntRect(ts * 13, 0, ts, ts)});
	tiles.emplace('n',Tile{1,0,sf::IntRect(ts * 14, 0, ts, ts)});
	tiles.emplace('o',Tile{0,0,sf::IntRect(ts * 15, 0, ts, ts)});
	tiles.emplace('p', Tile{0,0,sf::IntRect(ts * 16, 0, ts, ts) });

}

void Map::Load(const std::string& path) {
	std::ifstream f(path);
	f >> W >> gravity;
	std::string s;

	while (!f.eof()) {
		getline(f, s);
		if (s.length() > W) {
			s.erase(W, std::string::npos);
		}
		if (s.length() < W) {
			s += s + std::string(W - s.length(), ' ');
		}
		TileMap.push_back(s);
	}
	H = TileMap.size();
	f.close();
}

void Map::Render(sf::RenderWindow* wnd) {
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++) {
			auto p = tiles.find(TileMap[i][j]) ;
			if (p== tiles.end())
				continue;
			tile.setTextureRect((*p).second.rect);
			tile.setPosition(j * ts - offsetX, i * ts - offsetY);
			wnd->draw(tile);
		}
}