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
		case VK_SPACE:
			shoot_flag = true;//�����ڵ�
			break;

		}
	}
	else {
		if (term_event.key_code == VK_SPACE)
			shoot_flag = false;
			return;
		if(last_button == term_event.key_code) //���������Ϊ������������ͬʱ���µ�ʱ�򲻷�����ͻ
			v = 0;
	}
	//switch (ch)
	//{
	//	case 1: do something to the screen
	//	case 2: do anther thing to the screen
    //}
}

std::shared_ptr<GameObj> Myapp::add_gameobj_from_file(const std::string & filename)
{
	auto ptr_to_draw = get_drawable_from_file(filename);
	addDrawable(ptr_to_draw);
	auto ptr_to_gameobj = std::make_shared<GameObj>(ptr_to_draw);
	things_list.push_back(ptr_to_gameobj);
	return ptr_to_gameobj;
}

void Myapp::run()
{
	//��Ϸ���е����߼�������
//	auto look = std::make_shared<Drawable>("look");
//	addDrawable(look);
//	look->set_visualable();
	auto tank = add_gameobj_from_file("tank.draw");
	auto wall = add_gameobj_from_file("wall.draw");
	tank->set_static(false);
	wall->set_static(true);

	wall->move_right(20);
	wall->move_down(20);
	wall->set_v_num(0);
	wall->set_visualable();
	tank->set_visualable();
	tank->set_v_num(1);
	tank->set_v_direct(GameObj::direct::right);

	std::vector<GameObj> bullet_array;//�ڵ��ļ���

	while (1)
	{
		//render();
		//if (shoot_flag) { //����һ���ڵ�
		//	auto bumb_draw = get_drawable_from_file("bumb.draw");
		//	bumb_draw->set_static(false);
		//	addDrawable(bumb_draw);
		//	auto bumb = GameObj(bumb_draw);
		//	bumb.set_visualable();
		//	bumb_array.push_back(bumb);
		//	//auto pos_of_tank = bumb.ret_coord();

		//}
		if (v_direct == Direct::Down)
			tank->set_v_direct(GameObj::direct::down);
		if (v_direct == Direct::Up)
			tank->set_v_direct(GameObj::direct::up);
		if (v_direct == Direct::Left)
			tank->set_v_direct(GameObj::direct::left);
		if (v_direct == Direct::Right)
			tank->set_v_direct(GameObj::direct::right);
		if (shoot_flag) //�����ڵ�
		{
			std::cout << "out...";
		}
		tank->fresh();
		wall->fresh();
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
	render();
	//cls();
}

void GameObj::fresh()
{
	switch (v_direct)
	{
	case direct::up:
		turn_up();
		move_up(v_num);
		break;
	case direct::down:
		turn_down();
		move_down(v_num);
		break;
	case direct::right:
		turn_right();
		move_right(v_num);
		break;
	case direct::left:
		turn_left();
		move_left(v_num);
		break;
	}
}

