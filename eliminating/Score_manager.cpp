#include "Score_manager.h"

Score_manager::Score_manager() { // ���캯��
	current_score = 0;
}

int Score_manager::Get_curr_score() { // ��ȡ��ǰ����
	return current_score;
}

void Score_manager::Increment_by(int n) { // �ӷ�
	current_score += n;
}