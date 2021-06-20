#include "Myapp.h"

void Myapp::key_event(KeyEvent  term_event)
{
	static WORD last_button;
	term_event.Debug();
	if (term_event.key_down)
	{
		// �ٶȷ�Ϊ����
		v = 1;
		last_button = term_event.key_code;
		switch (term_event.key_code)
		{
		case VK_UP:// �ϼ�ͷ����
			
			v_direct = Direct::Up;
			//std::cout << "count = " << term_event.hold_time;
			break;
		case VK_DOWN:
			v_direct = Direct::Down;
			//std::cout << "count = " << term_event.repeat_count << std::endl;
			break;
		case VK_LEFT:
			v_direct = Direct::Left;
			//std::cout << "count = " << term_event.repeat_count << std::endl;
			break;
		case VK_RIGHT:
			v_direct = Direct::Right;
			//std::cout << "count = " << term_event.repeat_count << std::endl;
			break;

		}
	}
	else {
		if(last_button == term_event.key_code) //���������Ϊ������������ͬʱ���µ�ʱ�򲻷�����ͻ
			v = 0;
	}
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
	auto tank_draw = get_drawable_from_file("tank.draw");
	addDrawable(tank_draw);
	auto tank = GameObj(tank_draw);
	tank.set_visualable();
	while (1)
	{
		render();
		switch (v_direct)
		{
		case Direct::Up:
			tank.turn_up();
			tank.move_up(v);
			break;
		case Direct::Down:
			tank.turn_down();
			tank.move_down(v);
			break;
		case Direct::Left:
			tank.turn_left();
			tank.move_left(v);
			break;
		case Direct::Right:
			tank.turn_right();
			tank.move_right(v);
			break;
		}
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
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	//cls();
}
