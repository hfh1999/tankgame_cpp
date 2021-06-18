#include "termgui.h"

TermioApp::TermioApp()
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

void TermioApp::input_event(InputEvent term_event)
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

			for (int index = 0; index < len; index++)
				erase(old_point_x + pos_array[index].X,old_point_y + pos_array[index].Y);
			for (int index = 0; index < len; index++)
				draw(pos_array[index].X + origin_point_x, pos_array[index].Y + origin_point_y, char_array[index]);
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

void TermioApp::eventloop()
{
	INPUT_RECORD irInBuf[128];
	DWORD cNumRead;//读取了多少记录
	while(loop_flag)
	{
		/*	get some event */
		//get input and transmit it as io_event class
		//call input_event;
		ReadConsoleInput(termapp_in, irInBuf, 128, &cNumRead);
		for (DWORD counter = 0; counter < cNumRead; counter++)
		{
			switch (irInBuf[counter].EventType)
			{
			case FOCUS_EVENT:
				break;
			case KEY_EVENT:
				//std::cout << "[eventloop]key event\n";
				input_event(InputEvent(&irInBuf[counter]));
				break;
			case MOUSE_EVENT:
				//std::cout << "[eventloop]mouse event\n";
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
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	}
}

InputEvent::InputEvent(INPUT_RECORD * input_record)
{
	key_code = input_record->Event.KeyEvent.wVirtualKeyCode;
	key_down = input_record->Event.KeyEvent.bKeyDown;
	repeat_count = input_record->Event.KeyEvent.wRepeatCount;
}

void InputEvent::Debug()
{
	//std::cout << "[InputEvent Debug]\n";
}

