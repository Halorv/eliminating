#include <SFML\Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

class Texture_Data {
public:
	sf::Texture effectt; // 选中方块后的聚焦效果纹理
	sf::Sprite effec;

	sf::Texture background; // 游戏背景
	sf::RectangleShape rectangle;

	sf::Texture explosion; // 消除后的爆炸动画
	sf::Sprite exp1;

	sf::Font font;
	sf::Text text_score;
	Texture_Data();
};