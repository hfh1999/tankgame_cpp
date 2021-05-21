#pragma once
#include "TermioApp.h"
#include <memory>
using std::shared_ptr;
using std::string;
class GameObj {
public:
	GameObj(string file_name);//�������ļ�����һ��Gameobj.

	/*ͼ���ƶ�����*/
	void graph_move_left();
	void graph_move_right();
	void graph_move_up();
	void graph_move_down();
	string get_id();

	/*���ݲ���*/
	void set_hp(int in_num);
	void set_hp_offset(int offset);
	void set_ac(int in_num);
	void set_ac_offset(int offset);
	void set_ap(int in_num);
	void set_ap_offset(int offset);
	void set_speed(int in_num);
	void set_hp_speed(int offset);
private:
	shared_ptr<DrawableObj> graph_ptr;
	int hp;//heath points HP	
	int ac;//����
	int ap;//������
	int speed;//�ƶ��ٶ�
};
class Myapp :
	public TermioApp
{
public:
	void input_event(InputEvent  term_event)override;//�ı�һЩ�����Ĳ�����ʹ����Ϸ���в����任
	void run();
private:
	void render();//��Ⱦһ֡
	void fresh();//ˢ������״̬�ĺ���

};

