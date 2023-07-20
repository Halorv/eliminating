#include "Score_manager.h"

Score_manager::Score_manager() { // 构造函数
	current_score = 0;
}

int Score_manager::Get_curr_score() { // 获取当前分数
	return current_score;
}

void Score_manager::Increment_by(int n) { // 加分
	current_score += n;
}