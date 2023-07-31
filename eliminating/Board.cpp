#include <iostream>
#include "Board.h"

using namespace std;
string int_to_string(int n) {
	stringstream ss;
	ss << n;
	string str = ss.str();
	return str;
}

int Board::Generate_candy() { // ������ɷ������ͣ���6��
	return rand() % 6;
}

bool Board::valid_index_array(int r, int c) { // �ж������Ƿ�Ϸ� 5*8
	if (r >= 0 && r <= 7 && c >= 0 && c <= 4) return true;
	else return false;
}
void Board::Generate_explosion_at(int cnt, char type, int r, int c) { // ��������ı�ը��������֡��ʾ
																	  // cnt��ʾ�м�������Ҫ������type��ʾ�����ϵĻ������ϵģ��������������ϻ����ϣ�
	for (int i = 1; i <= 5; i++) { // i��ʾ���Ƶ�i֡�ı�ըЧ��
		int temp = 0; // ��ʾ�ڼ�������Ҫƫ�Ƶ�λ��
		window.clear();
		draw();
		for (int j = 0; j < cnt; j++) { // j��ʾ���Ƶ�j����
			switch (i) {
				case 1: {
					texture_data.explosion.loadFromFile("images/explosion/rsz_explosion01.png"); // ��������
					texture_data.exp1.setTexture(texture_data.explosion); // ��������
					if (type == 'r') texture_data.exp1.setPosition(c * 50 + temp + 255, r * 50 + 20); // ���ϵĵڼ���
					else texture_data.exp1.setPosition(c * 50 + 255, r * 50 + 20 + temp); // ���ϵĵڼ���
					window.draw(texture_data.exp1); // ���Ʊ�ըЧ��
					temp += 50; // λ�����ӣ�������һ����
				}
				break;
				case 2: { 
					texture_data.explosion.loadFromFile("images/explosion/rsz_explosion02.png");
					if (type == 'r') texture_data.exp1.setPosition(c * 50 + temp + 255, r * 50 + 20);
					else texture_data.exp1.setPosition(c * 50 + 255, r * 50 + 20 + temp);
					window.draw(texture_data.exp1);
					temp += 50;
				}
				break;
				case 3: { 
					texture_data.explosion.loadFromFile("images/explosion/rsz_explosion03.png");
					if (type == 'r') texture_data.exp1.setPosition(c * 50 + temp + 255, r * 50 + 20);
					else texture_data.exp1.setPosition(c * 50 + 255, r * 50 + 20 + temp);
					window.draw(texture_data.exp1);
					temp += 50;
				} 
				break;
				case 4: {
					texture_data.explosion.loadFromFile("images/explosion/rsz_explosion04.png");
					if (type == 'r') texture_data.exp1.setPosition(c * 50 + temp + 255, r * 50 + 20);
					else texture_data.exp1.setPosition(c * 50 + 255, r * 50 + 20 + temp);
					window.draw(texture_data.exp1);
					temp += 50;
				}
				break;
				case 5: {
					texture_data.explosion.loadFromFile("images/explosion/rsz_explosion05.png");
					if (type == 'r') texture_data.exp1.setPosition(c * 50 + temp + 255, r * 50 + 20);
					else texture_data.exp1.setPosition(c * 50 + 255, r * 50 + 20 + temp);
					window.draw(texture_data.exp1);
					temp += 50;
				}
				break;
			}
		}
		if (i < 5) { // ����֡����϶
			if (!Bonous_m.Get_curr_bonous()) Sleep(85);
			else Sleep(55);
			window.display();
		}
		if (i == 5 && Bonous_m.Get_curr_bonous() > 0) { // ���������Ķ���ӷ�
			window.clear();
			draw();
			Bonous_m.text_bonous.setPosition(c * 50 + 255, r * 50 + 20);
			Bonous_m.draw_bonous_at(window, int_to_string(Bonous_m.Get_curr_bonous() * 5)); // ÿ�����������5��
			window.display();
			Sleep(200);
			score_m.Increment_by(5 * Bonous_m.Get_curr_bonous());
		}
	}
}
bool Board::TL_eliminating(int x, int y, int c) { // cΪ��ͬ��״�ķ������
	Bonous_m.increment();
	window.clear();
	draw();
	window.display();
	swap_make_chain = true;
	S_M.remove_sound.play();
	switch (c % 3) { // TL����д���
		case 1:
			Generate_explosion_at(2, 'r', x, y + 1);
			while (x) {
				sprites[x][y + 1].t = sprites[x - 1][y + 1].t;
				sprites[x][y + 1].name = sprites[x - 1][y + 1].name;
				sprites[x][y + 2].t = sprites[x - 1][y + 2].t;
				sprites[x][y + 2].name = sprites[x - 1][y + 2].name;
				x--;
			}
			sprites[x][y + 1].name = files_name[Generate_candy()];
			sprites[x][y + 1].t.loadFromFile(sprites[x][y + 1].name);
			sprites[x][y + 2].name = files_name[Generate_candy()];
			sprites[x][y + 2].t.loadFromFile(sprites[x][y + 2].name);
			break;
		case 2:
			Generate_explosion_at(1, 'r', x, y - 1);
			Generate_explosion_at(1, 'r', x, y + 1);
			while (x) {
				sprites[x][y + 1].t = sprites[x - 1][y + 1].t;
				sprites[x][y + 1].name = sprites[x - 1][y + 1].name;
				sprites[x][y - 1].t = sprites[x - 1][y - 1].t;
				sprites[x][y - 1].name = sprites[x - 1][y - 1].name;
				x--;
			}
			sprites[x][y + 1].name = files_name[Generate_candy()];
			sprites[x][y + 1].t.loadFromFile(sprites[x][y + 1].name);
			sprites[x][y - 1].name = files_name[Generate_candy()];
			sprites[x][y - 1].t.loadFromFile(sprites[x][y - 1].name);
			break;
		case 0:
			Generate_explosion_at(2, 'r', x, y - 2);
			while (x) {
				sprites[x][y - 1].t = sprites[x - 1][y - 1].t;
				sprites[x][y - 1].name = sprites[x - 1][y - 1].name;
				sprites[x][y - 2].t = sprites[x - 1][y - 2].t;
				sprites[x][y - 2].name = sprites[x - 1][y - 2].name;
				x--;
			}
			sprites[x][y - 1].name = files_name[Generate_candy()];
			sprites[x][y - 1].t.loadFromFile(sprites[x][y - 1].name);
			sprites[x][y - 2].name = files_name[Generate_candy()];
			sprites[x][y - 2].t.loadFromFile(sprites[x][y - 2].name);
			break;
		default:
			break;
	}
	switch ((c - 1) / 3) { // TL�е��д���
		case 0:
			Generate_explosion_at(3, 'c', x - 1, y);
			for (int j = x + 1; j >= 0; j--)
				if (valid_index_array(j - 3, y)) {
					sprites[j][y].name = sprites[j - 3][y].name;
					sprites[j][y].t = sprites[j - 3][y].t;
				}
				else {
					sprites[j][y].name = files_name[Generate_candy()];
					sprites[j][y].t.loadFromFile(sprites[j][y].name);
				}
			break;
		case 1:
			Generate_explosion_at(3, 'c', x, y);
			for (int j = x + 2; j >= 0; j--)
				if (valid_index_array(j - 3, y)) {
					sprites[j][y].name = sprites[j - 3][y].name;
					sprites[j][y].t = sprites[j - 3][y].t;
				}
				else {
					sprites[j][y].name = files_name[Generate_candy()];
					sprites[j][y].t.loadFromFile(sprites[j][y].name);
				}
			break;
		case 2:
			Generate_explosion_at(3, 'c', x - 2, y);
			for (int j = x; j >= 0; j--)
				if (valid_index_array(j - 3, y)) {
					sprites[j][y].name = sprites[j - 3][y].name;
					sprites[j][y].t = sprites[j - 3][y].t;
				}
				else {
					sprites[j][y].name = files_name[Generate_candy()];
					sprites[j][y].t.loadFromFile(sprites[j][y].name);
				}
			break;
		default:
			return false;
	}
	score_m.Increment_by(50);
	Sleep(400);
	window.clear();
	draw();
	window.display();
	return true;
}

bool Board::Check_col_remove(int col) { // ���������û��������
	int cnt = 0; // ��������ĳ��ȣ�����3�ģ�
	bool again = false;
	for (int i = 2; i < 8; i++)
		if (sprites[i][col].name == sprites[i - 1][col].name && sprites[i][col].name == sprites[i - 2][col].name) {
			for (int j = i - 2; j < i + 1; j++) {//�ж��Ƿ�ΪTL�����Լ���״
				if (col + 2 < 5 && sprites[j][col].name == sprites[j][col + 1].name && sprites[j][col].name == sprites[j][col + 2].name) {
					if (j == i - 2) return TL_eliminating(j, col, 7);
					else if (j == i - 1) return TL_eliminating(j, col, 1);
					else if (j == i) return TL_eliminating(j, col, 4);
				}
				else if (col + 1 < 5 && col - 1 >= 0 && sprites[j][col].name == sprites[j][col + 1].name && sprites[j][col].name == sprites[j][col - 1].name) {
					if (j == i - 2) return TL_eliminating(j, col, 8);
					else if (j == i - 1) return TL_eliminating(j, col, 2);
					else if (j == i) return TL_eliminating(j, col, 5);
				}
				else if (col - 2 >= 0 && sprites[j][col].name == sprites[j][col - 1].name && sprites[j][col].name == sprites[j][col - 2].name) {
					if (j == i - 2) return TL_eliminating(j, col, 9);
					else if (j == i - 1) return TL_eliminating(j, col, 3);
					else if (j == i) return TL_eliminating(j, col, 6);
				}
			}
			again = true; // �Ƿ���������
			Bonous_m.increment();
			window.clear();
			draw();
			window.display();

			int tempI = i;
			while (tempI + 1 < 8 && sprites[tempI + 1][col].name == sprites[tempI][col].name) // ����������
				cnt++, tempI++;

			swap_make_chain = true;
			S_M.remove_sound.play(); // ������Ч
			Generate_explosion_at(cnt + 3, 'c', i - 2, col);
			i = tempI;
			for (int j = i; j >= 0; j--) // ����������µ���
				if (valid_index_array(j - 3 - cnt, col)) {
					sprites[j][col].name = sprites[j - 3 - cnt][col].name;
					sprites[j][col].t = sprites[j - 3 - cnt][col].t;
				}
				else {
					sprites[j][col].name = files_name[Generate_candy()]; // ������ɷ���
					sprites[j][col].t.loadFromFile(sprites[j][col].name);
				}
			score_m.Increment_by(30 + cnt * 10); // �����÷�30������ÿ��1��10��
			Sleep(400);
			window.clear();
			draw();
			window.display();
		}
	return again;
}

bool Board::Check_row_remove(int row) {
	int cnt = 0;
	bool again = false;
	for (int i = 2; i < 5; i++) {
		if (sprites[row][i].name == sprites[row][i - 1].name && sprites[row][i].name == sprites[row][i - 2].name) {
			for (int j = i; j > i - 3; j--) // �ж��Ƿ�ΪTL�����Լ���״
				if (row - 2 >= 0 && sprites[row][j].name == sprites[row - 1][j].name && sprites[row][j].name == sprites[row - 2][j].name) {
					if (j == i) return TL_eliminating(row, j, 6);
					else if (j == i - 1) return TL_eliminating(row, j, 5);
					else if (j == i - 2) return TL_eliminating(row, j, 4);
				}
				else if (row + 2 < 5 && sprites[row][j].name == sprites[row + 1][j].name && sprites[row][j].name == sprites[row + 2][j].name) {
					if (j == i) return TL_eliminating(row, j, 9);
					else if (j == i - 1) return TL_eliminating(row, j, 8);
					else if (j == i - 2) return TL_eliminating(row, j, 7);
				}
				else if (row + 1 < 5 && row - 1 >= 0 && sprites[row][j].name == sprites[row + 1][j].name && sprites[row][j].name == sprites[row - 1][j].name) {
					if (j == i) return TL_eliminating(row, j, 3);
					else if (j == i - 1) return TL_eliminating(row, j, 2);
					else if (j == i - 2) return TL_eliminating(row, j, 1);
				}
			again = true;
			Bonous_m.increment();
			window.clear();
			draw();
			window.display();

			int tempI = i;
			while (tempI + 1 < 5 && sprites[row][tempI].name == sprites[row][tempI + 1].name)
				cnt++, tempI++;

			swap_make_chain = true;
			S_M.remove_sound.play();
			Generate_explosion_at(cnt + 3, 'r', row, i - 2);
			while (row) { // �����������д���
				/****************�����ɵķ���****************/
				if (cnt > 0) { // 4��
					sprites[row][i + 1].t = sprites[row - 1][i + 1].t;
					sprites[row][i + 1].name = sprites[row - 1][i + 1].name;
					if (cnt > 1) { // 5��
						sprites[row][i + 2].t = sprites[row - 1][i + 2].t;
						sprites[row][i + 2].name = sprites[row - 1][i + 2].name;
					}
				}
				sprites[row][i].t = sprites[row - 1][i].t;
				sprites[row][i].name = sprites[row - 1][i].name;
				sprites[row][i - 1].t = sprites[row - 1][i - 1].t;
				sprites[row][i - 1].name = sprites[row - 1][i - 1].name;
				sprites[row][i - 2].t = sprites[row - 1][i - 2].t;
				sprites[row][i - 2].name = sprites[row - 1][i - 2].name;
				row--;
			}
			/****************�����µķ���****************/
			if (cnt > 0) {
				sprites[row][i + 1].name = files_name[Generate_candy()];
				sprites[row][i + 1].t.loadFromFile(sprites[row][i + 1].name);
				if (cnt > 1) {
					sprites[row][i + 2].name = files_name[Generate_candy()];
					sprites[row][i + 2].t.loadFromFile(sprites[row][i + 2].name);
				}
			}
			sprites[row][i].name = files_name[Generate_candy()];
			sprites[row][i].t.loadFromFile(sprites[row][i].name);
			sprites[row][i - 1].name = files_name[Generate_candy()];
			sprites[row][i - 1].t.loadFromFile(sprites[row][i - 1].name);
			sprites[row][i - 2].name = files_name[Generate_candy()];
			sprites[row][i - 2].t.loadFromFile(sprites[row][i - 2].name);

			score_m.Increment_by(30 + 10 * cnt);
			Sleep(400);
			window.clear();
			draw();
			window.display();
		}
	}
	return again;
}

void Board::Check_board() { // �ݹ�����Ƿ��п��������Ŀ�
	for (int i = 0; i < 5; i++) if (Check_col_remove(i)) Check_board();
	for (int i = 0; i < 8; i++) if (Check_row_remove(i)) Check_board();
}

Board::Board() {
	window.create(VideoMode(960, 437), "Game");
	window.setPosition(sf::Vector2i(500, 500)); // ��Ϸ���ڳ�������Ļ��λ��
	swap_make_chain = false;
	files_name[0] = "images/png/hat.png";
	files_name[1] = "images/png/clothes.png";
	files_name[2] = "images/png/latern.png";
	files_name[3] = "images/png/kit.png";
	files_name[4] = "images/png/pack.png";
	files_name[5] = "images/png/telescope.png";
}
void Board::load() {
    srand(time(NULL));
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 5; j++)
			sprites[i][j].name = files_name[Generate_candy()]; // ÿ��λ��������ɷ�������

	/******************************������һ��������ɷ���������3�������ͬʱ�����˸���������******************************/
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 3; j++) {
			if (sprites[i][j].name == "images/png/hat.png" && sprites[i][j + 1].name == "images/png/hat.png"&& sprites[i][j + 2].name == "images/png/hat.png") sprites[i][j].name = "images/png/clothes.png";
			else if (sprites[i][j].name == "images/png/clothes.png" && sprites[i][j + 1].name == "images/png/clothes.png" && sprites[i][j + 2].name == "images/png/clothes.png") sprites[i][j].name = "images/png/latern.png";
			else if (sprites[i][j].name == "images/png/latern.png" && sprites[i][j + 1].name == "images/png/latern.png" && sprites[i][j + 2].name == "images/png/latern.png") sprites[i][j].name = "images/png/kit.png";
			else if (sprites[i][j].name == "images/png/kit.png" && sprites[i][j + 1].name == "images/png/kit.png" && sprites[i][j + 2].name == "images/png/kit.png") sprites[i][j].name = "images/png/pack.png";
			else if (sprites[i][j].name == "images/png/pack.png" && sprites[i][j + 1].name == "images/png/pack.png" && sprites[i][j + 2].name == "images/png/pack.png") sprites[i][j].name = "images/png/telescope.png";
			else if (sprites[i][j].name == "images/png/telescope.png" && sprites[i][j + 1].name == "images/png/telescope.png" && sprites[i][j + 2].name == "images/png/telescope.png") sprites[i][j].name = "images/png/hat.png";
		}
	for (int j = 0; j < 5; j++)
		for (int i = 0; i < 6; i++) {
			if (sprites[i][j].name == "images/png/hat.png" && sprites[i+1][j].name == "images/png/hat.png"&& sprites[i+2][j].name == "images/png/hat.png") sprites[i][j].name = "images/png/clothes.png";
			else if (sprites[i][j].name == "images/png/clothes.png" && sprites[i+1][j].name == "images/png/clothes.png" && sprites[i+2][j].name == "images/png/clothes.png") sprites[i][j].name = "images/png/latern.png";
			else if (sprites[i][j].name == "images/png/latern.png" && sprites[i+1][j].name == "images/png/latern.png" && sprites[i+2][j].name == "images/png/latern.png") sprites[i][j].name = "images/png/kit.png";
			else if (sprites[i][j].name == "images/png/kit.png" && sprites[i+1][j].name == "images/png/kit.png" && sprites[i+2][j].name == "images/png/kit.png") sprites[i][j].name = "images/png/pack.png";
			else if (sprites[i][j].name == "images/png/pack.png" && sprites[i+1][j].name == "images/png/pack.png" && sprites[i + 2][j].name == "images/png/pack.png") sprites[i][j].name = "images/png/telescope.png";
			else if (sprites[i][j].name == "images/png/telescope.png" && sprites[i+1][j].name == "images/png/telescope.png" && sprites[i + 2][j].name == "images/png/telescope.png") sprites[i][j].name = "images/png/hat.png";
		}

	for (int i = 0; i < 8; i++) 
		for (int j = 0; j < 5; j++)
			sprites[i][j].t.loadFromFile(sprites[i][j].name); // ���ݸ��¹��ķ������ͼ���ͼƬ����ʱ�������3��
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 5; j++) {
			sprites[i][j].s.setTexture(sprites[i][j].t);
			sprites[i][j].type = 'D'; // Ĭ��Deactivate
			sprites[i][j].s.setPosition(j * 50 + 255, i * 50 + 20); // ����λ��
		}

	prop_data.hammer.setPosition(562, 40); // ����
	mouse_hammer = prop_data.hammer;
	prop_data.swap.setPosition(564, 103); // ����
	mouse_swap = prop_data.swap;
	prop_data.refresh.setPosition(563, 162); // ˢ������
	mouse_refresh = prop_data.refresh;
}

bool Board::valid_cell_window_domain(int x, int y) { // �ж����ָ���Ƿ�����Ч��λ��
	if (x >= 255 && x <= 505 && y >= 20 && y <= 420 && x % 50 != 0 && y % 50 != 0) return true;
	else return false;
}

char valid_swap_cell(int x2cany, int y2canyd, int sourcX, int sourcY) { // y�� x��
	if (y2canyd - sourcY == 1 && x2cany == sourcX) return 'd'; // ��
	else if (sourcY - y2canyd == 1 && x2cany == sourcX) return 'u'; // ��
	else if (x2cany - sourcX == 1 && y2canyd == sourcY) return 'r'; // ��
	else if (sourcX - x2cany == 1 && y2canyd == sourcY) return 'l'; // ��
	else return 'n';
}
int valid_prop_domain(int x, int y) {
	if (x < 562 || y < 40) return 0;
	else if (x >= 562 && x <= 602 && y >= 40 && y <= 80) return 1; // ���ֵ���
	else if (x > 564 && x <= 604 && y >= 103 && y <= 143) return 2;
	else if (x > 563 && x <= 603 && y >= 162 && y <= 202) return 3;
	else return 0;
}

void Board::Control_mouse_events(RenderWindow &window) { // ����¼�
	sf::Event event;
	//int prop_type = 0, prop_manu = 0;
	static int xx_prev = -1, yy_prev = -1; // ����������Ҫ��������飬prev��¼��һ����
	while (window.pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed: // �رմ���
				window.close();
			break;
			case sf::Event::MouseButtonPressed: {// ��갴��
				int x, y;
				x = event.mouseButton.x; y = event.mouseButton.y;
				if (event.mouseButton.button == sf::Mouse::Left && valid_cell_window_domain(x, y) && !prop_type && !prop_manu) { // ��������
					if (xx_prev != -1 && yy_prev != -1) sprites[yy_prev][xx_prev].type = 'D';
					x -= 255; y -= 20;
					x /= 50; y /= 50;
					sprites[y][x].type = 'A'; // ������б任���Ӧ����Ӧ�Ŀ��ϣ����øÿ�ΪActivate
					// x������֪���ǵڼ��У�y������֪���ǵڼ���
					xx_prev = x; yy_prev = y;
				}
				else if (event.mouseButton.button == sf::Mouse::Left && valid_prop_domain(x, y) && !prop_type && !prop_manu) { // �ڵ������������
					prop_type = valid_prop_domain(x, y);
					prop_manu = 0;
				}
				else if (event.mouseButton.button == sf::Mouse::Left && valid_cell_window_domain(x, y) && prop_type && !prop_manu) { // ����Ϸ���������
					prop_manu = prop_type;
				}
			}
			case sf::Event::MouseButtonReleased: { // ����ɿ�
				int x, y;
				x = event.mouseButton.x; y = event.mouseButton.y;
				//cout << x << " " << y << " " << valid_prop_domain(x, y) << " " << prop_type << " " << prop_manu << endl;
				if (valid_swap_cell((x - 255) / 50, (y - 20) / 50, xx_prev, yy_prev) != 'n' && valid_index_array((y - 20) / 50, (x - 255) / 50) && !prop_type && !prop_manu) { // ִ�н�������
					x -= 255; y -= 20;
					x /= 50; y /= 50;
					swap(sprites[y][x].t, sprites[yy_prev][xx_prev].t); // �����������
					swap(sprites[y][x].name, sprites[yy_prev][xx_prev].name); // ������������
					sprites[yy_prev][xx_prev].type = 'D';
					if (y == yy_prev) { // ˮƽλ���Ͻ���
						Check_col_remove(x);
						Check_col_remove(xx_prev);
						Check_row_remove(yy_prev);
					}
					else if (x == xx_prev) { // ��ֱλ���Ͻ���
						Check_row_remove(y);
						Check_row_remove(yy_prev);
						Check_col_remove(x);
					}
					if (swap_make_chain) { // ����������
						Check_board(); // ���ҿ�������
						swap_make_chain = false;
						Bonous_m.start_again(); // ���ö���ӷ�
					}
					else { // ѡ��������齻�������������򽻻����ٻ�����
						S_M.swap_sound.play(); // ����ʱ�򷢵�һ��
						window.clear();
						draw();
						window.display();
						Sleep(500);
						swap(sprites[y][x].t, sprites[yy_prev][xx_prev].t);
						swap(sprites[y][x].name, sprites[yy_prev][xx_prev].name);
						sprites[y][x].s.setTexture(sprites[y][x].t);
						sprites[yy_prev][xx_prev].s.setTexture(sprites[yy_prev][xx_prev].t);
						sprites[yy_prev][xx_prev].type = 'D';
						S_M.swap_sound.play(); // �������ٷ�һ��
					}
				}
				else if (valid_prop_domain(x, y) && prop_type && !prop_manu) { // �������ɿ����ߣ�����������
					if (prop_type == 1) {
						mouse_draw_hammer = 1;
					}
					else if (prop_type == 2) {
						mouse_draw_swap = 1;
					}
					else if (prop_type == 3) { // �ػ�����
						S_M.swap_sound.play();
						load();
						window.clear();
						draw();
						window.display();
						Check_board();
						prop_type = 0;
						prop_manu = 0;
					}
				}
				else if (valid_cell_window_domain(x, y) && prop_type && prop_manu) { // ��Ϸ���ɿ����ߣ�ִ�в���
					x -= 255; y -= 20;
					x /= 50; y /= 50;
					int i = y, col = x;
					if (prop_manu == 1) { // ��������ĳ������
						mouse_draw_hammer = 0;
						S_M.hammer_sound.play();
						Generate_explosion_at(1, 'r', i, col);
						for (int j = i; j >= 0; j--) // ����������µ���
							if (valid_index_array(j - 1, col)) {
								sprites[j][col].name = sprites[j - 1][col].name;
								sprites[j][col].t = sprites[j - 1][col].t;
							}
							else {
								sprites[j][col].name = files_name[Generate_candy()]; // ������ɷ���
								sprites[j][col].t.loadFromFile(sprites[j][col].name);
							}
						Sleep(400);
						Check_board();
						window.clear();
						draw();
						window.display();
						prop_type = 0;
						prop_manu = 0;
					}
					else if (prop_manu == 2) { // ������������
						if (swap_num == 1) { // ѡ�е�һ������
							swap_num = 2;
							swap_first_x = y, swap_first_y = x;
							sprites[swap_first_x][swap_first_y].type = 'A';
						}
						else if (swap_num == 2) { // �ڶ�������
							swap_num = 1;
							mouse_draw_swap = 0;
							S_M.swap_sound.play();
							int swap_second_x = y, swap_second_y = x;
							window.clear();
							draw();
							window.display();
							swap(sprites[swap_first_x][swap_first_y].t, sprites[swap_second_x][swap_second_y].t);
							swap(sprites[swap_first_x][swap_first_y].name, sprites[swap_second_x][swap_second_y].name);
							sprites[swap_first_x][swap_first_y].s.setTexture(sprites[swap_first_x][swap_first_y].t);
							sprites[swap_second_x][swap_second_y].s.setTexture(sprites[swap_second_x][swap_second_y].t);
							sprites[swap_first_x][swap_first_y].type = 'D';
							Check_board(); // ����������û�п�������
							prop_type = 0;
							prop_manu = 0;
						}
					}
				}
			}
			break;
			case sf::Event::MouseMoved: { // ���ָ��ĳ����ʱ����۽�
				if (valid_cell_window_domain(event.mouseMove.x, event.mouseMove.y)) { // x�����У�y������
					int x, y;
					x = event.mouseMove.x; y = event.mouseMove.y;
					x -= 255; y -= 20;
					x /= 50; y /= 50;
					texture_data.effec.setPosition(x * 50 + 255, y * 50 + 20);
					window.draw(texture_data.effec);
				}
				if (mouse_draw_hammer) { // ���߸�������ƶ���������ȷ��ÿ֡��λ��
					int x = event.mouseMove.x, y = event.mouseMove.y;
					mouse_hammer.setPosition(x, y);
					window.clear();
					draw();
					window.display();
				}
				if (mouse_draw_swap) {
					int x = event.mouseMove.x, y = event.mouseMove.y;
					mouse_swap.setPosition(x, y);
					window.clear();
					draw();
					window.display();
				}
			}
			break;
		}
	}
}
void Board::draw() {
	window.draw(texture_data.rectangle); // ���Ʊ���
	texture_data.text_score.setString(int_to_string(score_m.Get_curr_score())); // ����ת��
	window.draw(texture_data.text_score); // ���Ƶ÷�
	window.draw(prop_data.hammer); // ������������
	window.draw(prop_data.swap);
	window.draw(prop_data.refresh);
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 5; j++) {
			if (sprites[i][j].type == 'A') { // ѡ�еĿ����۽�
				texture_data.effec.setPosition(j * 50 + 255, i * 50 + 20);
				window.draw(texture_data.effec);
			}
			window.draw(sprites[i][j].s); // δѡ�о�ֻ���Ʒ���
		}
	if (mouse_draw_hammer) window.draw(mouse_hammer); // ���߸�������ƶ�
	if (mouse_draw_swap) window.draw(mouse_swap);
}

bool Board::check_end() {
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 5; j++) {
			if (i < 6 && sprites[i][j].name == sprites[i + 1][j].name && sprites[i + 1][j].name == sprites[i + 2][j].name) return false;
			if (j < 3 && sprites[i][j].name == sprites[i][j + 1].name && sprites[i][j + 1].name == sprites[i][j + 2].name) return false;
		}
	return true;
}

void Board::exchange_check() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 4; j++) {
			char temp = sprites[i][j].type;
			sprites[i][j].type = sprites[i][j + 1].type;
			sprites[i][j + 1].type = temp;

			bool end = check_end();
			if (!end) return;
			sprites[i][j + 1].type = sprites[i][j].type;
			sprites[i][j].type = temp;
		}
	}
	for (int k = 0; k < 7; k++) {
		for (int l = 0; l < 5; l++) {
			char temp2 = sprites[k][l].type;
			sprites[k][l].type = sprites[k + 1][l].type;
			sprites[k + 1][l].type = temp2;

			bool end2 = check_end();
			if (!end2) return;
			sprites[k + 1][l].type = sprites[k][l].type;
			sprites[k][l].type = temp2;
		}
	}
	load();
}