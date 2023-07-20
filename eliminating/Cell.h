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
	Sprite s;
	string name;
	char type; // Activate or Deactivate
};