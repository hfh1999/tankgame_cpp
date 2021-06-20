#pragma once
#include "termgui.h"
#include "drawableobj.h"
#include <memory>
using std::shared_ptr;
using std::string;
class GameObj :public DrawableObj {
public:
	GameObj() = delete;
	GameObj(std::shared_ptr<Drawable> inDrawable):DrawableObj(inDrawable){}

private:
	int health_point;//生命值
	int attack_point;//攻击力
	int shield_point;//护甲值
};

class Myapp :
	public TermioApp
{
public:
	Myapp():TermioApp(),v_direct(Direct::Right){}
	void key_event(KeyEvent  term_event)override;//改变一些这个类的参数来使得游戏运行参数变换
	void run();
private:
	Direct v_direct; // 速度方向
	SHORT v; //每秒的移动速度

	void render();//渲染一帧
	void fresh();//刷新数据状态的函数

};

