#include <SFML\Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

class Texture_Data {
public:
	sf::Texture effectt; // ѡ�з����ľ۽�Ч������
	sf::Sprite effec;

	sf::Texture background; // ��Ϸ����
	sf::RectangleShape rectangle;

	sf::Texture explosion; // ������ı�ը����
	sf::Sprite exp1;

	sf::Font font;
	sf::Text text_score;
	Texture_Data();
};