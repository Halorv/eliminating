#include <SFML\Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

class Prop_Data {
public:
	Texture hammer_img;
	Sprite hammer;
	int hammer_num;

	Texture swap_img;
	Sprite swap;
	int swap_num;

	Texture refresh_img;
	Sprite refresh;
	int refresh_num;

	Prop_Data();
};