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
	//��Ϸ���е����߼�������
//	auto look = std::make_shared<Drawable>("look");
//	addDrawable(look);
//	look->set_visualable();
	auto tank = get_drawable_from_file("tank.draw");
	addDrawable(tank);
	tank->set_visualable();
	while (1)
	{
		render();
		tank->move_right(1);
		fresh();
	}
}

void Myapp::render()
{
	/*��ͼ*/
	//std::cout << "[run:render] render here"<<std::endl;
	//example start;
	//example end;
	renderDrawables();//test draw "look"

}

void Myapp::fresh()
{
	/*��������ʾ��ص����ݽṹ*/
	/*input_event�ɸ���������ĸ����߼�*/
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	//cls();
}

inline GameObj::GameObj(string file_name)
{
	graph_ptr = std::make_shared<Drawable>();//��ʼ��ͼ�ζ���
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
