#pragma once
#include "TermioApp.h"
#include <memory>
using std::shared_ptr;
using std::string;
class GameObj {
public:
	GameObj(string file_name);//打开配置文件创建一个Gameobj.

	/*图形移动操作*/
	void graph_move_left();
	void graph_move_right();
	void graph_move_up();
	void graph_move_down();
	string get_id();

	/*数据操作*/
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
	int ac;//护甲
	int ap;//攻击力
	int speed;//移动速度
};
class Myapp :
	public TermioApp
{
public:
	void input_event(InputEvent  term_event)override;//改变一些这个类的参数来使得游戏运行参数变换
	void run();
private:
	void render();//渲染一帧
	void fresh();//刷新数据状态的函数

};

