#include "Board.h"

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
			Sleep(185);
			window.display();
		}
		if (i == 5 && Bonous_m.Get_curr_bonous() > 0) { // 绘制连击的额外加分
			window.clear();
			draw();
			Bonous_m.text_bonous.setPosition(c * 50 + 255, r * 50 + 20);
			Bonous_m.draw_bonous_at(window, int_to_string(Bonous_m.Get_curr_bonous() * 5)); // 每次连击额外加5分
			window.display();
			Sleep(650);
			score_m.Increment_by(5 * Bonous_m.Get_curr_bonous());
		}
	}
}

bool Board::Check_col_remove(int col) { // 检查列上有没有消除链
	int cnt = 0; // 最长消除链的长度（超过3的）
	bool again = false;
	for (int i = 2; i < 8; i++)
		
		if (sprites[i][col].name == sprites[i - 1][col].name && sprites[i][col].name == sprites[i - 2][col].name) {
			
			again = true; // 是否连续消除
			Bonous_m.increment();
			//Bonous_m.start_again();
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
			Sleep(800);
			window.clear();
			draw();
			window.display();
		//	Sleep(800);
		}
	return again;
}

bool Board::Check_row_remove(int row) {
	int keycol = -1;//发生特殊消除的列
	int cnt = 0;
	bool again = false;
	for (int i = 2; i < 5; i++) {
		if (sprites[row][i].name == sprites[row][i - 1].name && sprites[row][i].name == sprites[row][i - 2].name) {
			again = true;
			Bonous_m.increment();
			window.clear();       
			draw();
			window.display();
			int tempI = i;
			while (tempI + 1 < 5 && sprites[row][tempI].name == sprites[row][tempI + 1].name)
				cnt++, tempI++;

			for (int j = i; j < i + cnt + 3; j++) {
				if (sprites[row][j].name == sprites[row - 1][j].name && sprites[row][j].name == sprites[row + 1][j].name){
					keycol = j;
					Generate_explosion_at(3, 'c', row-1, j);
					for (int k = row+1; k >= 0; k--) // 方块从上往下掉落
						if (valid_index_array(k - 3, j)) {
							sprites[k][j].name = sprites[k - 3 ][j].name;
							sprites[k][j].t = sprites[k - 3 ][j].t;
						}
						else {
							sprites[k][j].name = files_name[Generate_candy()]; // 随机生成方块
							sprites[k][j].t.loadFromFile(sprites[k][j].name);
						}
					score_m.Increment_by(30);
				}
				else if (sprites[row][j].name == sprites[row - 1][j].name && sprites[row][j].name == sprites[row - 2][j].name) {
					keycol = j;
					Generate_explosion_at(3, 'c', row-2, j);
					for (int k = row; k >= 0; k--) // 方块从上往下掉落
						if (valid_index_array(k - 3, j)) {
							sprites[k][j].name = sprites[k - 3][j].name;
							sprites[k][j].t = sprites[k - 3][j].t;
						}
						else {
							sprites[k][j].name = files_name[Generate_candy()]; // 随机生成方块
							sprites[k][j].t.loadFromFile(sprites[k][j].name);
						}
					score_m.Increment_by(30);
				}
				else if (sprites[row][j].name == sprites[row + 1][j].name && sprites[row][j].name == sprites[row + 2][j].name) {
					keycol = j;
					Generate_explosion_at(3, 'c', row, j);
					for (int k = row + 2; k >= 0; k--) // 方块从上往下掉落
						if (valid_index_array(k - 3, j)) {
							sprites[k][j].name = sprites[k - 3][j].name;
							sprites[k][j].t = sprites[k - 3][j].t;
						}
						else {
							sprites[k][j].name = files_name[Generate_candy()]; // 随机生成方块
							sprites[k][j].t.loadFromFile(sprites[k][j].name);
						}
					score_m.Increment_by(30);
				}
			}

			swap_make_chain = true;
			S_M.remove_sound.play();

			Generate_explosion_at(cnt + 3, 'r', row, i - 2);

			if (keycol == -1) {
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
			}
			else {
				while (row) { // 从下往上逐行处理
					/****************消除旧的方块****************/
					if (i != keycol) {
						sprites[row][i].t = sprites[row - 1][i].t;
						sprites[row][i].name = sprites[row - 1][i].name;
					}
					if (i - 1 != keycol) {
						sprites[row][i - 1].t = sprites[row - 1][i - 1].t;
						sprites[row][i - 1].name = sprites[row - 1][i - 1].name;
					}
					if (i - 2 != keycol) {
						sprites[row][i - 2].t = sprites[row - 1][i - 2].t;
						sprites[row][i - 2].name = sprites[row - 1][i - 2].name;
						
					}
					row--;
				}
				/****************产生新的方块****************/
				if (i != keycol) {
					sprites[row][i].name = files_name[Generate_candy()];
					sprites[row][i].t.loadFromFile(sprites[row][i].name);
				}
				if (i - 1 != keycol) {
					sprites[row][i - 1].name = files_name[Generate_candy()];
					sprites[row][i - 1].t.loadFromFile(sprites[row][i - 1].name);
				}
				if (i - 2 != keycol) {
					sprites[row][i - 2].name = files_name[Generate_candy()];
					sprites[row][i - 2].t.loadFromFile(sprites[row][i - 2].name);
				}
				
				
			
			}
			score_m.Increment_by(30 + 10 * cnt);
			Sleep(800);
			window.clear();
			draw();
			window.display();
		//	Sleep(800);
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
	window.setPosition(sf::Vector2i(100, 50));
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
}

bool Board:: valid_cell_window_domain(int x, int y) { // 判断鼠标指针是否在有效的位置
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

void Board::Control_mouse_events(RenderWindow &window) { // 鼠标事件
	sf::Event event;
	static int xx_prev = -1, yy_prev = -1; // 交换操作需要点击两个块，prev记录第一个块
	while (window.pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed: // 关闭窗口
				window.close();
			break;
			case sf::Event::MouseButtonPressed: // 鼠标按下
				if (event.mouseButton.button == sf::Mouse::Left && valid_cell_window_domain(event.mouseButton.x, event.mouseButton.y)) {
					int x, y;
					x = event.mouseButton.x; y = event.mouseButton.y;
					if (xx_prev != -1 && yy_prev != -1) sprites[yy_prev][xx_prev].type = 'D';
					x -= 255; y -= 20;
					x /= 50; y /= 50;
					sprites[y][x].type = 'A'; // 坐标进行变换后对应到相应的块上，设置该块为Activate
											  // x坐标能知道是第几列，y坐标能知道是第几行
					xx_prev = x; yy_prev = y;
				}
			case sf::Event::MouseButtonReleased: { // 鼠标松开
				int x, y;
				x = event.mouseButton.x; y = event.mouseButton.y;
				x -= 255; y -= 20;
				x /= 50; y /= 50;
				if (valid_swap_cell(x, y, xx_prev, yy_prev) != 'n' && valid_index_array(y, x)) { // 检查是否是有效的交换here check vaild adjacent swap to the (prev selection)
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
						Sleep(600);
						swap(sprites[y][x].t, sprites[yy_prev][xx_prev].t);
						swap(sprites[y][x].name, sprites[yy_prev][xx_prev].name);
						sprites[y][x].s.setTexture(sprites[y][x].t);
						sprites[yy_prev][xx_prev].s.setTexture(sprites[yy_prev][xx_prev].t);
						sprites[yy_prev][xx_prev].type = 'D';
						S_M.swap_sound.play(); // 换回来再发一声
					}
				}
			}
			break;
			/*需修改*/
			case sf::Event::MouseMoved: // 鼠标指到某方块时给予聚焦
				if (valid_cell_window_domain(event.mouseMove.x, event.mouseMove.y)) { // x代表列，y代表行
					int x, y;
					x = event.mouseMove.x; y = event.mouseMove.y;
					x -= 255; y -= 20;
					x /= 50; y /= 50;
					texture_data.effec.setPosition(x * 50 + 255, y * 50 + 20);
					window.draw(texture_data.effec);
				}
			break;
		}
	}
}
void Board::draw() {
	window.draw(texture_data.rectangle); // 绘制背景
	texture_data.text_score.setString(int_to_string(score_m.Get_curr_score())); // 类型转换
	window.draw(texture_data.text_score); // 绘制得分
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 5; j++) {
			if (sprites[i][j].type == 'A') { // 选中的块给予聚焦
				texture_data.effec.setPosition(j * 50 + 255, i * 50 + 20);
				window.draw(texture_data.effec);
			}
			window.draw(sprites[i][j].s);
		}
}