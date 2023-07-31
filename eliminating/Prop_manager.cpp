#include <SFML\Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include "Prop_manager.h"


Prop_Data::Prop_Data() {
	hammer_num = 0;
	hammer_img.loadFromFile("images/Prop/hammer_s.png");
	hammer.setTexture(hammer_img);

	swap_num = 0;
	swap_img.loadFromFile("images/Prop/swap_s.png");
	swap.setTexture(swap_img);

	refresh_num = 0;
	refresh_img.loadFromFile("images/Prop/refresh_s.png");
	refresh.setTexture(refresh_img);
}