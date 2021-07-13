#include "termgui.h"
#include <map>

TermioApp::TermioApp():Terminal()
{
	termapp_in = GetStdHandle(STD_INPUT_HANDLE);
	event_loop = std::thread(&TermioApp::eventloop, this);
}

TermioApp::~TermioApp()
{
	loop_flag = false;//ֹͣevent loop flag
	event_loop.join();
	std::cout << "[TermioApp]event loop terminate";
}

void TermioApp::key_event(KeyEvent term_event)
{
	//do nothing
}

void TermioApp::renderDrawables()
{
	//print the renderDrawables.
//	std::cout << "renderDrawables... obj1,obj2,obj3\n";
	for (auto item : obj_list)
	{
		if (item->visualable)
		{
			auto len = (item->relative_pos).size();
			auto pos_array = item->relative_pos;
			auto char_array = item->content;
			auto origin_point_x = item->origin_point.X;
			auto origin_point_y = item->origin_point.Y;
			auto old_point_x = item->old_point.X;
			auto old_point_y = item->old_point.Y;
			auto direct = item->direct;
			auto direct_old = item->old_direct;

			if (!item->is_static)
			{

				for (int index = 0; index < len; index++)
				{

					auto relative_coord_to_erase = __coord_trans(COORD{ pos_array[index].X,pos_array[index].Y }, direct_old);
					erase(relative_coord_to_erase.X + old_point_x, old_point_y + relative_coord_to_erase.Y);
				}
			}
			for (int index = 0; index < len; index++)
			{
				auto relative_coord_to_draw = __coord_trans(COORD{ pos_array[index].X, pos_array[index].Y },direct );
				draw(relative_coord_to_draw.X + origin_point_x,relative_coord_to_draw.Y+origin_point_y,char_array[index]);
			}
		}
	}
}


bool TermioApp::addDrawable(shared_ptr<Drawable> in_obj, bool is_visuable)
{
	if (in_obj->is_managed)
		return false;  //已经加入过,加入失败
	else
	{
		obj_list.push_back(in_obj);
		in_obj->is_managed = true;
	}
}

bool TermioApp::removeDrawable(std::string id)
{
	return false;
}

bool TermioApp::setVisuable(std::string id, bool visuable_value)
{
	return false;
}


COORD TermioApp::__coord_trans(COORD in_coord, Drawable::DrawDirect direct)
{
	if (in_coord.X == 0 && in_coord.Y == 0)
		return COORD{ 0,0 };
	else
	{
		switch (direct - Drawable::DrawDirect::Up)
		{
		case 0: //坐标不变
			return in_coord;
			break;
		case 2://顺时针180度
			return COORD{ -in_coord.X,-in_coord.Y };
			break;
		case 3://逆时针90度
			return COORD{ in_coord.Y,-in_coord.X };
			break;
		case 1://顺时针90度
			return COORD{ -in_coord.Y,in_coord.X };
			break;

		}
	}
}

void TermioApp::__get_key_hold_time(WORD key_code,bool key_down,WORD repeat) {
//	static std::map<WORD, counter_data> inner_meta;
//	std::pair<WORD, counter_data> tmp_pair;
	static bool is_inited = false;

	if (!is_inited)
	{
		/* 这里可能要读取键盘定义表*/
		tmp_pair.first = VK_UP;
		inner_meta.insert(tmp_pair);
		tmp_pair.first = VK_RIGHT;
		inner_meta.insert(tmp_pair);
		tmp_pair.first = VK_DOWN;
		inner_meta.insert(tmp_pair);
		tmp_pair.first = VK_LEFT;
		inner_meta.insert(tmp_pair);

		for (auto item:inner_meta)
		{
			inner_meta[item.first] =  counter_data{0,false};
		}
		is_inited = true;
	}
	
	if (key_down)//按下的时候
	{
		auto find_result = inner_meta.at(key_code);
			//std::cout << "repeat>>>>" << repeat;
			//std::cout << "find>>>>" << find_result.counter;
		if (find_result.flag)//之前就已经被按下过了
		{
			// 注意类型相加可能会溢出,这里强行越过这一限制
			inner_meta[key_code] = counter_data{(WORD)(find_result.counter + repeat),find_result.flag };
		}
		else {

			inner_meta[key_code] = counter_data{(WORD)(find_result.counter + repeat),true };
			//std::cout << "";
		}
	}
	else
	{
		inner_meta[key_code] = counter_data{ 0,false };//这时计数已经无所谓了
		//std::cout << "release.";
	}

}
void TermioApp::eventloop()
{
	INPUT_RECORD irInBuf[128];
	DWORD cNumRead;//读取了多少记录
	DWORD queueLen;
	while(loop_flag)
	{
		/*	get some event */
		//get input and transmit it as io_event class
		//call input_event;
		GetNumberOfConsoleInputEvents(termapp_in, &queueLen);
		if (queueLen == 0)
		{
			//std::cout << "no input";
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
			continue;
		}
		ReadConsoleInput(termapp_in, irInBuf, 128, &cNumRead);
		for (DWORD counter = 0; counter < cNumRead; counter++)
		{
			auto tmp = irInBuf[counter];
			auto repeat_counter = inner_meta[tmp.Event.KeyEvent.wVirtualKeyCode].counter;
			switch (irInBuf[counter].EventType)
			{
			case FOCUS_EVENT:
				break;
			case KEY_EVENT:
				//std::cout << "[eventloop]key event\n";
				//执行一次按键测时函数
				__get_key_hold_time(tmp.Event.KeyEvent.wVirtualKeyCode, tmp.Event.KeyEvent.bKeyDown,tmp.Event.KeyEvent.wRepeatCount);
				//std::cout << "counter = " << repeat_counter;
			//	std::cout << "counter" << tmp.Event.KeyEvent.wRepeatCount;
				key_event(KeyEvent(&irInBuf[counter],repeat_counter));
				break;
			case MOUSE_EVENT:
				std::cout << "[eventloop]mouse event\n";
				break;
			case WINDOW_BUFFER_SIZE_EVENT:
				//std::cout << "[eventloop]window buffer size event.\n";
				break;
			//case MENU_EVENT: //内部使用,此处忽略
			default:
				break;
			}
		}
		//std::cout << cNumRead << "events readed" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}

KeyEvent::KeyEvent(INPUT_RECORD * input_record, WORD time)
{
	key_code = input_record->Event.KeyEvent.wVirtualKeyCode;
	key_down = input_record->Event.KeyEvent.bKeyDown;
	hold_time = time;
}

SHORT KeyEvent::get_key_hold_time()
{
	//return __get_key_hold_time(key_code,key_down);
	return hold_time;
}

void KeyEvent::Debug()
{
	//std::cout << "[InputEvent Debug]\n";
}

