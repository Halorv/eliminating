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

using namespace std;
using namespace sf;

class Board {
private:
	string files_name[6]; // ���ַ���
	Sound_manager S_M; // ��Ч
	Cell sprites[8][5]; // ��ͼ
	Texture_Data texture_data; // �������
	Bonous_manager Bonous_m; // ����ӷ�
	Score_manager score_m; // �÷�
	bool swap_make_chain; // �Ƿ�������
	
public:
	RenderWindow window;
	Board();
	void load();
	void draw();
	void Control_mouse_events(RenderWindow &window);
	void Check_board();
	bool Check_col_remove(int);
	bool Check_row_remove(int);
	int Generate_candy();
	bool valid_cell_window_domain(int x, int y);
	bool valid_index_array(int r, int c);
	void Generate_explosion_at(int cnt, char type, int r, int c);
	bool check_end();
	void exchange_check();
};