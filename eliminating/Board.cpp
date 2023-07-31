#include <iostream>
#include "Board.h"

using namespace std;
string int_to_string(int n) {
	stringstream ss;
	ss << n;
	string str = ss.str();
	return str;
}

int Board::Generate_candy() { // 随机生成方格类型，共6种
	return rand() % 6;
}

bool Board::valid_index_array(int r, int c) { // 判断行列是否合法 5*8
	if (r >= 0 && r <= 7 && c >= 0 && c <= 4) return true;
	else return false;
}
void Board::Generate_explosion_at(int cnt, char type, int r, int c) { // 消除方格的爆炸动画，逐帧显示
																	  // cnt表示有几个块需要消除，type表示是行上的还是列上的（消除发生在行上或列上）
	for (int i = 1; i <= 5; i++) { // i表示绘制第i帧的爆炸效果
		int temp = 0; // 表示第几个块需要偏移的位置
		window.clear();
		draw();
		for (int j = 0; j < cnt; j++) { // j表示绘制第j个块
			switch (i) {
				case 1: {
					texture_data.explosion.loadFromFile("images/explosion/rsz_explosion01.png"); // 加载纹理
					texture_data.exp1.setTexture(texture_data.explosion); // 设置纹理
					if (type == 'r') texture_data.exp1.setPosition(c * 50 + temp + 255, r * 50 + 20); // 行上的第几个
					else texture_data.exp1.setPosition(c * 50 + 255, r * 50 + 20 + temp); // 列上的第几个
					window.draw(texture_data.exp1); // 绘制爆炸效果
					temp += 50; // 位置增加，绘制下一个块
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
		if (i < 5) { // 动画帧数间隙
			if (!Bonous_m.Get_curr_bonous()) Sleep(85);
			else Sleep(55);
			window.display();
		}
		if (i == 5 && Bonous_m.Get_curr_bonous() > 0) { // 绘制连击的额外加分
			window.clear();
			draw();
			Bonous_m.text_bonous.setPosition(c * 50 + 255, r * 50 + 20);
			Bonous_m.draw_bonous_at(window, int_to_string(Bonous_m.Get_curr_bonous() * 5)); // 每次连击额外加5分
			window.display();
			Sleep(200);
			score_m.Increment_by(5 * Bonous_m.Get_curr_bonous());
		}
	}
}
bool Board::TL_eliminating(int x, int y, int c) { // c为不同形状的分类参数
	Bonous_m.increment();
	window.clear();
	draw();
	window.display();
	swap_make_chain = true;
	S_M.remove_sound.play();
	switch (c % 3) { // TL里的行处理
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
	switch ((c - 1) / 3) { // TL中的列处理
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

bool Board::Check_col_remove(int col) { // 检查列上有没有消除链
	int cnt = 0; // 最长消除链的长度（超过3的）
	bool again = false;
	for (int i = 2; i < 8; i++)
		if (sprites[i][col].name == sprites[i - 1][col].name && sprites[i][col].name == sprites[i - 2][col].name) {
			for (int j = i - 2; j < i + 1; j++) {//判断是否为TL消除以及形状
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
			again = true; // 是否连续消除
			Bonous_m.increment();
			window.clear();
			draw();
			window.display();

			int tempI = i;
			while (tempI + 1 < 8 && sprites[tempI + 1][col].name == sprites[tempI][col].name) // 获得最长消除链
				cnt++, tempI++;

			swap_make_chain = true;
			S_M.remove_sound.play(); // 消除音效
			Generate_explosion_at(cnt + 3, 'c', i - 2, col);
			i = tempI;
			for (int j = i; j >= 0; j--) // 方块从上往下掉落
				if (valid_index_array(j - 3 - cnt, col)) {
					sprites[j][col].name = sprites[j - 3 - cnt][col].name;
					sprites[j][col].t = sprites[j - 3 - cnt][col].t;
				}
				else {
					sprites[j][col].name = files_name[Generate_candy()]; // 随机生成方块
					sprites[j][col].t.loadFromFile(sprites[j][col].name);
				}
			score_m.Increment_by(30 + cnt * 10); // 基础得分30，长度每加1得10分
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
			for (int j = i; j > i - 3; j--) // 判断是否为TL消除以及形状
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
			while (row) { // 从下往上逐行处理
				/****************消除旧的方块****************/
				if (cnt > 0) { // 4连
					sprites[row][i + 1].t = sprites[row - 1][i + 1].t;
					sprites[row][i + 1].name = sprites[row - 1][i + 1].name;
					if (cnt > 1) { // 5连
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
			/****************产生新的方块****************/
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

void Board::Check_board() { // 递归查找是否有可以消除的块
	for (int i = 0; i < 5; i++) if (Check_col_remove(i)) Check_board();
	for (int i = 0; i < 8; i++) if (Check_row_remove(i)) Check_board();
}

Board::Board() {
	window.create(VideoMode(960, 437), "Game");
	window.setPosition(sf::Vector2i(500, 500)); // 游戏窗口出现在屏幕的位置
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
			sprites[i][j].name = files_name[Generate_candy()]; // 每个位置随机生成方块类型

	/******************************消除第一次随机生成方块后产生的3连情况（同时消除了更多的情况）******************************/
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
			sprites[i][j].t.loadFromFile(sprites[i][j].name); // 根据更新过的方块类型加载图片，此时不会出现3连
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 5; j++) {
			sprites[i][j].s.setTexture(sprites[i][j].t);
			sprites[i][j].type = 'D'; // 默认Deactivate
			sprites[i][j].s.setPosition(j * 50 + 255, i * 50 + 20); // 矩阵位置
		}

	prop_data.hammer.setPosition(562, 40); // 锤子
	mouse_hammer = prop_data.hammer;
	prop_data.swap.setPosition(564, 103); // 交换
	mouse_swap = prop_data.swap;
	prop_data.refresh.setPosition(563, 162); // 刷新棋盘
	mouse_refresh = prop_data.refresh;
}

bool Board::valid_cell_window_domain(int x, int y) { // 判断鼠标指针是否在有效的位置
	if (x >= 255 && x <= 505 && y >= 20 && y <= 420 && x % 50 != 0 && y % 50 != 0) return true;
	else return false;
}

char valid_swap_cell(int x2cany, int y2canyd, int sourcX, int sourcY) { // y行 x列
	if (y2canyd - sourcY == 1 && x2cany == sourcX) return 'd'; // 下
	else if (sourcY - y2canyd == 1 && x2cany == sourcX) return 'u'; // 上
	else if (x2cany - sourcX == 1 && y2canyd == sourcY) return 'r'; // 右
	else if (sourcX - x2cany == 1 && y2canyd == sourcY) return 'l'; // 左
	else return 'n';
}
int valid_prop_domain(int x, int y) {
	if (x < 562 || y < 40) return 0;
	else if (x >= 562 && x <= 602 && y >= 40 && y <= 80) return 1; // 三种道具
	else if (x > 564 && x <= 604 && y >= 103 && y <= 143) return 2;
	else if (x > 563 && x <= 603 && y >= 162 && y <= 202) return 3;
	else return 0;
}

void Board::Control_mouse_events(RenderWindow &window) { // 鼠标事件
	sf::Event event;
	//int prop_type = 0, prop_manu = 0;
	static int xx_prev = -1, yy_prev = -1; // 交换操作需要点击两个块，prev记录第一个块
	while (window.pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed: // 关闭窗口
				window.close();
			break;
			case sf::Event::MouseButtonPressed: {// 鼠标按下
				int x, y;
				x = event.mouseButton.x; y = event.mouseButton.y;
				if (event.mouseButton.button == sf::Mouse::Left && valid_cell_window_domain(x, y) && !prop_type && !prop_manu) { // 交换操作
					if (xx_prev != -1 && yy_prev != -1) sprites[yy_prev][xx_prev].type = 'D';
					x -= 255; y -= 20;
					x /= 50; y /= 50;
					sprites[y][x].type = 'A'; // 坐标进行变换后对应到相应的块上，设置该块为Activate
					// x坐标能知道是第几列，y坐标能知道是第几行
					xx_prev = x; yy_prev = y;
				}
				else if (event.mouseButton.button == sf::Mouse::Left && valid_prop_domain(x, y) && !prop_type && !prop_manu) { // 在道具区点击道具
					prop_type = valid_prop_domain(x, y);
					prop_manu = 0;
				}
				else if (event.mouseButton.button == sf::Mouse::Left && valid_cell_window_domain(x, y) && prop_type && !prop_manu) { // 在游戏区点击道具
					prop_manu = prop_type;
				}
			}
			case sf::Event::MouseButtonReleased: { // 鼠标松开
				int x, y;
				x = event.mouseButton.x; y = event.mouseButton.y;
				//cout << x << " " << y << " " << valid_prop_domain(x, y) << " " << prop_type << " " << prop_manu << endl;
				if (valid_swap_cell((x - 255) / 50, (y - 20) / 50, xx_prev, yy_prev) != 'n' && valid_index_array((y - 20) / 50, (x - 255) / 50) && !prop_type && !prop_manu) { // 执行交换操作
					x -= 255; y -= 20;
					x /= 50; y /= 50;
					swap(sprites[y][x].t, sprites[yy_prev][xx_prev].t); // 交换方块材质
					swap(sprites[y][x].name, sprites[yy_prev][xx_prev].name); // 交换方块名称
					sprites[yy_prev][xx_prev].type = 'D';
					if (y == yy_prev) { // 水平位置上交换
						Check_col_remove(x);
						Check_col_remove(xx_prev);
						Check_row_remove(yy_prev);
					}
					else if (x == xx_prev) { // 垂直位置上交换
						Check_row_remove(y);
						Check_row_remove(yy_prev);
						Check_col_remove(x);
					}
					if (swap_make_chain) { // 发生了消除
						Check_board(); // 查找可消除块
						swap_make_chain = false;
						Bonous_m.start_again(); // 重置额外加分
					}
					else { // 选择的两个块交换后不能消除，则交换后再换回来
						S_M.swap_sound.play(); // 换的时候发第一声
						window.clear();
						draw();
						window.display();
						Sleep(500);
						swap(sprites[y][x].t, sprites[yy_prev][xx_prev].t);
						swap(sprites[y][x].name, sprites[yy_prev][xx_prev].name);
						sprites[y][x].s.setTexture(sprites[y][x].t);
						sprites[yy_prev][xx_prev].s.setTexture(sprites[yy_prev][xx_prev].t);
						sprites[yy_prev][xx_prev].type = 'D';
						S_M.swap_sound.play(); // 换回来再发一声
					}
				}
				else if (valid_prop_domain(x, y) && prop_type && !prop_manu) { // 道具区松开道具，绘制鼠标跟随
					if (prop_type == 1) {
						mouse_draw_hammer = 1;
					}
					else if (prop_type == 2) {
						mouse_draw_swap = 1;
					}
					else if (prop_type == 3) { // 重绘棋盘
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
				else if (valid_cell_window_domain(x, y) && prop_type && prop_manu) { // 游戏区松开道具，执行操作
					x -= 255; y -= 20;
					x /= 50; y /= 50;
					int i = y, col = x;
					if (prop_manu == 1) { // 任意消除某个方块
						mouse_draw_hammer = 0;
						S_M.hammer_sound.play();
						Generate_explosion_at(1, 'r', i, col);
						for (int j = i; j >= 0; j--) // 方块从上往下掉落
							if (valid_index_array(j - 1, col)) {
								sprites[j][col].name = sprites[j - 1][col].name;
								sprites[j][col].t = sprites[j - 1][col].t;
							}
							else {
								sprites[j][col].name = files_name[Generate_candy()]; // 随机生成方块
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
					else if (prop_manu == 2) { // 交换两个方块
						if (swap_num == 1) { // 选中第一个方块
							swap_num = 2;
							swap_first_x = y, swap_first_y = x;
							sprites[swap_first_x][swap_first_y].type = 'A';
						}
						else if (swap_num == 2) { // 第二个方块
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
							Check_board(); // 交换后检查有没有可消除的
							prop_type = 0;
							prop_manu = 0;
						}
					}
				}
			}
			break;
			case sf::Event::MouseMoved: { // 鼠标指到某方块时给予聚焦
				if (valid_cell_window_domain(event.mouseMove.x, event.mouseMove.y)) { // x代表列，y代表行
					int x, y;
					x = event.mouseMove.x; y = event.mouseMove.y;
					x -= 255; y -= 20;
					x /= 50; y /= 50;
					texture_data.effec.setPosition(x * 50 + 255, y * 50 + 20);
					window.draw(texture_data.effec);
				}
				if (mouse_draw_hammer) { // 道具跟随鼠标移动，在这里确定每帧的位置
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
	window.draw(texture_data.rectangle); // 绘制背景
	texture_data.text_score.setString(int_to_string(score_m.Get_curr_score())); // 类型转换
	window.draw(texture_data.text_score); // 绘制得分
	window.draw(prop_data.hammer); // 绘制三个道具
	window.draw(prop_data.swap);
	window.draw(prop_data.refresh);
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 5; j++) {
			if (sprites[i][j].type == 'A') { // 选中的块给予聚焦
				texture_data.effec.setPosition(j * 50 + 255, i * 50 + 20);
				window.draw(texture_data.effec);
			}
			window.draw(sprites[i][j].s); // 未选中就只绘制方块
		}
	if (mouse_draw_hammer) window.draw(mouse_hammer); // 道具跟随鼠标移动
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