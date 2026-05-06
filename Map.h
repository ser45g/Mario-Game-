#pragma once
#include <SFML/Graphics.hpp>
#include "Utility.cpp"
#include <fstream>
#include <unordered_map>

struct Tile {
	bool solid;
	bool deadly;
	sf::IntRect rect;
};

class Map {
private:
	sf::Sprite tile;
	sf::Texture tileSet;
	int W = 0;
	int H = 0;
	int gravity = 0;
	const int ts = 32;
	int offsetX = 0;
	int offsetY = 0;
	std::unordered_map<char, Tile> tiles;

public:
	std::vector<sf::String> TileMap;
	const int get_H()const { return H; }
	const int get_W()const { return W; }
	const int get_gravity()const { return gravity; }
	const int get_ts()const { return ts; }
	int& get_offsetX() { return offsetX; }
	int& get_offsetY() { return offsetY; }
	
	~Map() {}
	Map(const std::string& path);
	std::unordered_map<char, Tile>& get_tiles() { return tiles; }
	void Load(const std::string& path);
	
	void Render(sf::RenderWindow* wnd);
	
	void Update(float l_time) {}
};

/*if (TileMap[i][j] == 'A')
					tile.setTextureRect(sf::IntRect(0, 0, ts, ts));
				if (TileMap[i][j] == 'B')
					tile.setTextureRect(sf::IntRect(ts, 0, ts, ts));
				if (TileMap[i][j] == 'C')
					tile.setTextureRect(sf::IntRect(ts * 2, 0, ts, ts));
				if (TileMap[i][j] == 'D')
					tile.setTextureRect(sf::IntRect(ts * 3, 0, ts, ts));
				if (TileMap[i][j] == 'P')
					tile.setTextureRect(sf::IntRect(0, ts, ts * 2, ts * 4));
				if (TileMap[i][j] == 'W')
					tile.setTextureRect(sf::IntRect(ts * 2, ts, ts, ts * 8));
				if (TileMap[i][j] == 'F')
					tile.setTextureRect(sf::IntRect(ts * 7, ts, ts * 5, ts * 4));
				if (TileMap[i][j] == 'a')
					tile.setTextureRect(sf::IntRect(ts * 4, 0, ts, ts));
				if (TileMap[i][j] == 'b')
					tile.setTextureRect(sf::IntRect(ts * 6, 0, ts, ts));
				if (TileMap[i][j] == 'd')
					tile.setTextureRect(sf::IntRect(ts * 17, 0, ts, ts));
				if (TileMap[i][j] == 'm')
					tile.setTextureRect(sf::IntRect(ts * 5, 0, ts, ts));
				if (TileMap[i][j] == 'T')
					tile.setTextureRect(sf::IntRect(ts * 3, ts, ts * 4, ts * 10));
				if (TileMap[i][j] == 'E')
					tile.setTextureRect(sf::IntRect(ts * 7, 0, ts, ts));
				if (TileMap[i][j] == 'I')
					tile.setTextureRect(sf::IntRect(ts * 8, 0, ts, ts));
				if (TileMap[i][j] == 'H')
					tile.setTextureRect(sf::IntRect(ts * 9, 0, ts, ts));
				if (TileMap[i][j] == 'J')
					tile.setTextureRect(sf::IntRect(ts * 9, 0, -ts, ts));
				if (TileMap[i][j] == 't')
					tile.setTextureRect(sf::IntRect(ts * 7, ts * 5, ts * 4, ts * 3));
				if (TileMap[i][j] == 'f')
					tile.setTextureRect(sf::IntRect(ts * 12, ts, ts * 9, ts * 9));
				if (TileMap[i][j] == 'e')
					tile.setTextureRect(sf::IntRect(ts * 10, 0, ts, ts));
				if (TileMap[i][j] == 'k')
					tile.setTextureRect(sf::IntRect(ts * 11, 0, ts, ts));
				if (TileMap[i][j] == 'l')
					tile.setTextureRect(sf::IntRect(ts * 12, 0, ts, ts));
				if (TileMap[i][j] == 'M' || TileMap[i][j] == '3')
					tile.setTextureRect(sf::IntRect(ts * 13, 0, ts, ts));
				if (TileMap[i][j] == 'n')
					tile.setTextureRect(sf::IntRect(ts * 14, 0, ts, ts));
				if (TileMap[i][j] == 'o')
					tile.setTextureRect(sf::IntRect(ts * 15, 0, ts, ts));
				if (TileMap[i][j] == 'p')
					tile.setTextureRect(sf::IntRect(ts * 16, 0, ts, ts));
					if (TileMap[i][j] == ' ' || TileMap[i][j] == '0' ||
					 TileMap[i][j] == '1' ||TileMap[i][j] == '2' ||
					TileMap[i][j] == '4' || TileMap[i][j] == '5' ||
					TileMap[i][j] == '6' || TileMap[i][j] == '7' ||
					TileMap[i][j] == '8' || TileMap[i][j] == '9'||
					TileMap[i][j]=='Q')
					continue;*/
//sf::String TileMap[81] = {
//" 000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
//"                                                                                                                                                                                                                   ",
//"                                                                                                                                                                                                                   ",
//"                                                                                                                                                                                            DD        W            ",
//"                                                                               1   Q    1 1 Q  1            1      Q        1  1  Q 1                                                      DDD                     ",
//"                1     B         mmm                                             CCCCCCCC   CCCB              BBBBBBBCBBBBCCC    CBBC                                                      DDDD                     ",
//"                                             1Q 1               B                                                                        k              k                                DDDDD                     ",
//"       kA          1  Q  1            mm      P0         P0                 1     Q   1            1 Q1                         1  1     D  D          DD QD                            DDDDDD            F        ",
//"      kAA       B   CBCBC  1 Q 1    1 P0      00         00                  CBCBBBBBB        B     CB    B  B  B     C          CC     DD  DD        DDD  DD           CCBC           DDDDDDD                     ",
//"     kAAA                   P0        00      00         00                                                                            DDD  DDD      DDDD  DDD     P0              P0 DDDDDDDD                     ",
//"    kAAAA  D  Q     Q       00     Q  00   Q  00   Q     00        m1 1               1 1        P0          Q              P0        DDDDkkDDDD    DDDDDkkDDDD    00              00DDDDDDDDD        D            ",
//"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA   AAAAAAAAAAAAAAA   AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
//"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA   AAAAAAAAAAAAAAA   AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
//"                                   mmmmmmm             aa              P             A   A                                                                                           0                             ",
//"                                                       aa  1   Q   1   0             A   A                                                                                           0                             ",
//"                               A                       aa   aaaaaBa    0             AA  A                                                                                           0                             ",
//"                                                       aa            B P             A   A                                                                                           0                             ",
//"                  mmmmmmmmmm          mmm         B    aa              0             A   A                                                                                           0        DDD                  ",
//"                        A                              aa   Bmmmmm     0             A  AA                                                                                           0       DDDD                  ",
//"                       A             m                 aa   mmmmmmm    0             A   A                                                                                           0      DDDDD                  ",
//"F                     A              b         m       aa   mmmmmmm    P             A   A                                                                                           0     DDDDDD             F    ",
//"                     A                         B       aa   aaaaaaa    0             AA  A                                                                                           0    DDDDDDD                  ",
//"                    A        mm  B                     aa   aaaaaaa    0             A   A                                                                                            P0 DDDDDDDD                  ",
//"                   A        m m                        aa   aaaaaaa    0             AQQ A                                                                                            00DDDDDDDDD        D         ",
//"AAAAAAAAAAAAAAAAAAA         mm                         bbbbbbbbbbbbbbbbbb            AAAAA                                                                                         ATAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
//"AAAAAAAAAAAAAAAAAAA                      B             bbbbbbbbbbbbbbbbbb                                                                                                          AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
//"                        mmmmm                          bb                         Q                                                                                           000000000000000                      ",
//"            a     aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaBaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa                        aaaaaaaa  aaaaa                      ",
//"            a                                                     aa  aaaaaa  aaaa      aaaa                                                                                            aaaaa                      ",
//"            a                                                     aa  aaaaaa  aaaa 1  1 aaaa                                                                                            aaaaa                      ",
//"            a                                        mmmm       aa        aa   a    aa          mmmmmm                                                                                  aaaaa                      ",
//"            a                                                   aa        aa   a    aa         1    Q 1                                                                                 aaaaa                      ",
//"            a                                      a aaaa B     aa    mmmmaa   amB  aa          aaaaaa                                                        aaaaaaa                   aaaaa                      ",
//"            a        1   Q 1       d d   B         ama  ama     aaaa  aaaaaa   aaa  aB 1    1   aaaaaa                   P0                         dd                                  aaaaa                      ",
//"            a         BBBBB      d d d d   d d     aaa  aaa       aa                aa  aaaa                       P0    00                        ddd                        aaaaaaaaaaaaaaa                      ",
//"            a                  d d d d d   d d                    aa                                               00    00    P0     aa          dddd                        aaaaaaaaaaaaaaa                      ",
//"            a       Q        d d d d d d Q d d      Q                                       1 1        Q           00   Q00  Q 00     aa 1       ddddd        1        1      aaaaaaaaaaaaaaa                      ",
//"            bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb   bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb  bb  bbbbbbbbbbbb         bbbbbbbb       bbbbbbbbbbbbbbb                      ",
//"            bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb   bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb  bb  bbbbbbbbbbbb         bbbbbbbb       bbbbbbbbbbbbbbb                      ",
//"                                                                                                                  a  aaaaaaaaaaaa                                                                                  ",
//"                                                                                                                  a  aaaaaaaaaaT                                                                                   ",
//"                                                                                                                  a  aaaaaaaaaaaa                                                                                  ",
//"                                                                                                                  a  aaaaaaaaaaaa                                                                                  ",
//"                                                                                                                  a            aa                                                                                  ",
//"                                                                                                                  a            aa                                                                                  ",
//"                                                                                                                  a   mmmmmmmm aa                                                                                  ",
//"                                                                                                                  a  aaaaaaaaBaaa                                                                                  ",
//"                                                                                                                  a            aa                                                                                  ",
//"                                                                                                                  a                                                                                                ",
//"                                                                                                                  a  mmmmmmmmm   0                                                                                 ",
//"                                                                                                                  bbbbbbbbbbbbbbbb                                                                                 ",
//"                                                                                                                  bbbbbbbbbbbbbbbb                                                                                 ",
//"                                      CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC",
//"                                                                                                                                                                                                                   ",
//"                                                              mm                                                                                                                                                   ",
//"                                                   1 mmmQ1       1    Q  1                                                                                                            f                            ",
//"                                                    IHHHJ         IHHHHHJ                           1      1   mm      mm mm                                           DD                                          ",
//"                                                     EEE           EEEEE    mm        mmmm           IHHHHJ                     1        1       mm                    DD                 mmmmmmmmmm               ",
//"                          0                          EEE    1   Q 1EEEEE              IHHJ            EEEE                       IHHHHHHJ                            DDDD                                          ",
//"                          0                          EEE     IHHHJ EEEEE               EE             EEEE                        EEEEEE                             DDDD                                          ",
//"                          0F             m        IHHHHHHJ    EEE  EEEEE               EE       IHJ   EEEE                        EEEEEE     IHHJ  IHHJ            DDDDDD      m            m                      ",
//"                          0                        EEEEEE     EEE  EEEEE               EE        E    EEEE                        EEEEEE      EE    EE             DDDDDD                            m             ",
//"                          0           m     1  Q 1 EEEEEE  m  EEE  EEEEE             B EE        E    EEEE                 IHHJ   EEEEEE      EE    EE             DDDDDD                       m                  ",
//"                          0                  IHHJ  EEEEEE IHJ EEE  EEEEE               EE        E    EEEE        IHHJ      EE    EEEEEE  mmm EE    EE   1         DDDDDD        D                                 ",
//"              m            AAAAAAAAAAAAAAAA   EE   EEEEEE  E  EEE  EEEEE    IHHJ     IHHHJ IHHHJ E    EEEE         EE       EE    EEEEEE  IHJ EE    EE    AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA                    ",
//"                           AAAAAAAAAAAAAAAAkkkEEkkkEEEEEEkkEkkEEEkkEEEEEkkkkkEEkkkkkkkEEEkkkEEEkkEkkkkEEEEkkkkkkkkkEEkkkkkkkEEkkkkEEEEEEkkkEkkEE    EE    AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA                    ",
//"                                                                                                                                                                                                                   ",
//"                                                                                                                                                                                                                   ",
//"                              eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee              ",
//"                              eeeeeeeeeeeeeeeeeeeeee             eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee        e        e     eeeeeee                   eeeee             eee                         0              ",
//"                              eeeeeeeeeeeeeeeeeeeeee             eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee        M        M     eeeeeee                   eeeee             eee                         0              ",
//"                             0                     e        1Q1     M        M          M      M                                      B  B  B                                                       0              ",
//"       BBBBB                  eee                     M      B                                                                                                          p                           0              ",
//"                              eeee                               1                                   1                                                    1      2     oeee                         0              ",
//"                              eeeee                1              eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee                       1        B  B  B   eeee   eeeeennnnnnnnnnnnneee                         0              ",
//"                              eeeeeeeeeeeee  eeeeeeeee   eMe   eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee   M       M       M   eeeeeee            eeee   eeeee             eee                         0              ",
//"                              eeeeeeeeeeeee  eeeeeeeee   eee   eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee            eeee   eeeee             eee                         0              ",
//"                              eeeeeeeeeeeeekkeeeeeeeeekkkeeekkkeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeekkkkkkkkkkkkkeeeeeeeeeeeeeeeeeeeeeeeeeeeee              ",
//"                              eeeeeeeeeeeeelleeeeeeeeellleeellleeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeellllllllllllleeeeeeeeeeeeeeeeeeeeeeeeeeeee              ",
//" 1         Q   Q Q  Q       1 eeeeeeeeeeeeelleeeeeeeeellleeellleeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeellllllllllllleeeeeeeeeeeeeeeeeeeeeeeeeeeee              ",
//"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
//};