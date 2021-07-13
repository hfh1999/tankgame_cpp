#pragma once
#include "termgui.h"
#include "drawableobj.h"
#include <memory>
using std::shared_ptr;
using std::string;
class GameObj :public DrawableObj {
public:
	GameObj() = delete;
	GameObj(std::shared_ptr<Drawable> inDrawable)
		:DrawableObj(inDrawable),health_point(100),attack_point(100),shield_point(0){}


	void set_hp(SHORT in_hp) { health_point = in_hp; }
	void set_ap(SHORT in_ap) { attack_point = in_ap; }
	void set_sp(SHORT in_sp) { shield_point = in_sp; }
	void fresh(); //在一帧中对游戏对象的内部数据进行更新
	void set_v_num(SHORT in_v_num) { v_num = in_v_num; }

	enum direct {up,down,left,right}; //方向
	void set_v_direct(direct in_direct) {  v_direct = in_direct; }


private:
	SHORT health_point;//生命值
	SHORT attack_point;//攻击力
	SHORT shield_point;//护甲值
	SHORT v_num;   //速度值
	direct v_direct;
};
class Myapp :
	public TermioApp
{
public:
	Myapp():TermioApp(),v_direct(Direct::Right){}
	void key_event(KeyEvent  term_event)override;//改变一些这个类的参数来使得游戏运行参数变换
	std::shared_ptr<GameObj> add_gameobj_from_file(const std::string & filename);
	void run();
private:
	Direct v_direct; // 速度方向
	SHORT v; //每秒的移动速度
	SHORT v_p = 2;
	bool shoot_flag = false;
	std::vector<std::shared_ptr<GameObj>> things_list;

	void render();//渲染一帧
	void fresh();//刷新数据状态的函数

};

