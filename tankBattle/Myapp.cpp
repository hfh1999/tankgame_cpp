#include "Myapp.h"

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

		}
	}
	else {
		if(last_button == term_event.key_code) //这个处理是为了是两个按键同时按下的时候不发生冲突
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
	//游戏运行的主逻辑在这里
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
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	//cls();
}
