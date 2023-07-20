#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Audio.hpp>

#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

using namespace std;
using namespace sf;

class Cell {
public:
	Texture t;
	Sprite s; // Texture相当于Sprite的内部填充
	string name;
	char type; // 是否被选中（聚焦），Activate or Deactivate
};