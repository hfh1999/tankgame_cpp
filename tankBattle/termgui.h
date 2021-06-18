/*给teminal类增加input等特性*/
//需要一个事件循环函数event loop处理输入event
#pragma once
#include "terminal.h"
#include <thread>
#include <vector>
#include <memory>
#include "drawable.h"
using std::shared_ptr;
class InputEvent {
private:
	WORD key_code;
	BOOL key_down;//status:up/down
	WORD repeat_count;//key is being held down.
public:
	InputEvent(INPUT_RECORD * input_record);
	void Debug();
};
class TermioApp :
	public Terminal
{
public:
	TermioApp();
	~TermioApp();

	virtual void input_event(InputEvent term_event);
	void renderDrawables();//负责将所有drawable object渲染出来

	bool addDrawable(shared_ptr<Drawable> in_obj, bool is_visuable = true);//加入Drawable object
	bool removeDrawable(std::string id);//将规定id的对象从列表中移除
	bool setVisuable(std::string id, bool visuable_value = true);//设置对象的可见性
	
private:
	HANDLE termapp_in;//输入标识符
	std::thread event_loop;
	bool loop_flag = true;//是否停止事件循环
	std::vector<shared_ptr<Drawable>> obj_list;//app已经管理的Drawable object的列表

	void eventloop();//类的事件处理循环:处理输入(事件)

	//need event_call_back pointer here.

};
/*event loop*/
/*
	create global Event bind table:[events];
	loop{
	
	get a input data from console with "ReadConsoleInput()";
	look up the [events] to see if a events is happend;
	if happend{
		jump to the corresponding function;
	}else{
		continue;	
	}

	}


*/
/*event bind*/
/*
	insert a function pointer into the [events];

*/

