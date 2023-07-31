#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <string>
#include <time.h>     
#include <windows.h>
#include <sstream>

#include "Cell.h"
#include "Texture_Data.h"
#include "Sound_manager.h"
#include "Bonous_Manager.h"
#include "Score_manager.h"
#include "Prop_manager.h"

using namespace std;
using namespace sf;

class Board {
private:
	string files_name[6]; // 六种方块
	Sound_manager S_M; // 音效
	Cell sprites[8][5]; // 地图
	Texture_Data texture_data; // 方块材质
	Prop_Data prop_data; // 道具
	Bonous_manager Bonous_m; // 额外加分
	Score_manager score_m; // 得分
	bool swap_make_chain; // 是否发生消除
	
	Sprite mouse_hammer;
	Sprite mouse_swap;
	Sprite mouse_refresh;
	int prop_type = 0, prop_manu = 0; // 道具类型，是否进行操作
	int swap_num = 1, swap_first_x, swap_first_y; // 交换操作
	
public:
	RenderWindow window;
	bool mouse_draw_hammer = 0;
	bool mouse_draw_swap = 0;
	bool mouse_draw_refresh = 0;
	Board();
	void load();
	void draw();
	void Control_mouse_events(RenderWindow &window);
	void Check_board();
	bool Check_col_remove(int);
	bool Check_row_remove(int);
	bool TL_eliminating(int, int, int);
	int Generate_candy();
	bool valid_cell_window_domain(int x, int y);
	bool valid_index_array(int r, int c);
	void Generate_explosion_at(int cnt, char type, int r, int c);
	bool check_end();
	void exchange_check();
};