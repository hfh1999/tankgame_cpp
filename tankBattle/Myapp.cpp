#include "Myapp.h"

void Myapp::input_event(InputEvent  term_event)
{
	term_event.Debug();
	std::cout << "this is my input_event\n";
	//switch (ch)
	//{
	//	case 1: do something to the screen
	//	case 2: do anther thing to the screen
    //}
}

void Myapp::run()
{
	//游戏运行的主逻辑在这里
	while (1)
	{
		render();
		fresh();
	}
}

void Myapp::render()
{
	/*画图*/
	//std::cout << "[run:render] render here"<<std::endl;
	//example start;
	auto tankDrawable = getDrawable("tank");
	tankDrawable.moveDown();
	//example end;
	renderDrawables();//test draw "look"

}

void Myapp::fresh()
{
	/*更改与显示相关的数据结构*/
	/*input_event可更改这里面的更新逻辑*/
	//std::cout << "[run:fresh] fresh here"<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	std::cout << "here to change the data to control drawable obj.\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	//eraseDrawable(DrawableObj("look"));
	//clear需要刷新的物体
	cls();
}

inline GameObj::GameObj(string file_name)
{
	graph_ptr = std::make_shared<DrawMetaData>();//初始化图形对象
}

void GameObj::graph_move_left()
{
}

void GameObj::graph_move_right()
{
}

void GameObj::graph_move_up()
{
}

void GameObj::graph_move_down()
{
}

string GameObj::get_id()
{
	return string();
}

void GameObj::set_hp(int in_num)
{
}

void GameObj::set_hp_offset(int offset)
{
}

void GameObj::set_ac(int in_num)
{
}

void GameObj::set_ac_offset(int offset)
{
}

void GameObj::set_ap(int in_num)
{
}

void GameObj::set_ap_offset(int offset)
{
}

void GameObj::set_speed(int in_num)
{
}

void GameObj::set_hp_speed(int offset)
{
}
