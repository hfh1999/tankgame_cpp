#include "Myapp.h"
#include <time.h>

void Myapp::key_event(KeyEvent  term_event)
{
	static WORD last_button;
	term_event.Debug();
	if (term_event.key_down)
	{
		// 速度分为三档
		v = 1;
		last_button = term_event.key_code;
		switch (term_event.key_code)
		{
		case VK_UP:// 上箭头按键
			
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
			shoot_flag = true;//发射炮弹
			break;

		}
	}
	else {
	//	if (term_event.key_code == VK_SPACE)
	//		shoot_flag = false;
	//		return;
		if(last_button == term_event.key_code) //这个处理是为了是两个按键同时按下的时候不发生冲突
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
	things_list.insert(ptr_to_gameobj);
	return ptr_to_gameobj;
}

bool Myapp::add_gameobj(shared_ptr<GameObj> in_ptr)
{
	addDrawable(in_ptr->ret_draw_ptr());
	things_list.insert(in_ptr);
	return true;
}

bool Myapp::rm_gameobj(const std::shared_ptr<GameObj> in_ptr)
{
	bool flag = false;
	for (auto it = things_list.begin(); it != things_list.end();)
	{
		if ((*in_ptr).ret_guid() == (*it)->ret_guid())
		{
			it = things_list.erase(it);
			flag = true;
			break;
		}
		else {
			it++;
		}
	}
	if (!flag)
	{
		std::cerr << "failed to find.";
		return false;
	}
	return  this->removeDrawable(in_ptr->ret_ptr_of_Drawable());
}

void Myapp::run()
{
	//游戏运行的主逻辑在这里
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

	auto bullet_test = add_gameobj_from_file("bullet.draw");
	bullet_test->set_static(false);

	std::set<std::shared_ptr<GameObj>> bullet_array;//炮弹的集合

	while (1)
	{
		//render();
		//if (shoot_flag) { //产生一个炮弹
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

		if (shoot_flag)
		{
			//std::cout << "shoot!!!";
			auto tmp_bullet = bullet_test->copy();
			add_gameobj(tmp_bullet);
			bullet_array.insert(tmp_bullet);
			tmp_bullet->set_visualable();
			tmp_bullet->set_v_num(2);
			tmp_bullet->set_v_direct(tank->ret_v_direct());
			tmp_bullet->move(tank->ret_coord());
			tank->fresh();
			wall->fresh();
			fresh();
			shoot_flag = false;
			continue;
		}
		tank->fresh();
		wall->fresh();

		//炮弹出界,应该删除
		std::vector <std::shared_ptr<GameObj>> items_to_del;
		for (auto item : bullet_array)
		{
			auto tmp_pos = item->ret_coord();
			auto x = tmp_pos.X;
			auto y = tmp_pos.Y;
			if (x < display_size.Left || y < display_size.Top || x > display_size.Right || y > display_size.Bottom)
			{
				items_to_del.push_back(item);
			}
			item->fresh();
		}
		//std::cout << "bullet size = " << bullet_array.size();
		for (auto ptr : items_to_del)
		{
			rm_gameobj(ptr);
			for (auto it = bullet_array.begin(); it != bullet_array.end();)
			{
				if ((*it)->ret_guid() == ptr->ret_guid())
				{
					it = bullet_array.erase(it);
				}
				else {
					it++;
				}
			}
		}
		fresh();
	}
}

void Myapp::render()
{
	/*画图*/
	//std::cout << "[run:render] render here"<<std::endl;
	//example start;
	//example end;
	renderDrawables();//test draw "look"

}

void Myapp::fresh()
{
	/*更改与显示相关的数据结构*/
	/*input_event可更改这里面的更新逻辑*/

	/*这里的目标是尽量确保每次的帧的时间固定*/
	const long fix_dur = 50; //固定间隔为50ms
	static clock_t last_time = 0;
	auto time = clock();
	auto dur = time - last_time;
	last_time = time;
	if (dur < fix_dur)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(fix_dur - dur));
	}
	else {
		//否则尽量不耽误.
	}
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

