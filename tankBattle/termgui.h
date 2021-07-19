/*给teminal类增加input等特性*/
//需要一个事件循环函数event loop处理输入event
#pragma once
#include "terminal.h"
#include <thread>
#include <set>
#include <map>
#include <memory>
#include "drawable.h"
using std::shared_ptr;
struct KeyEvent {
	// 参见 https://docs.microsoft.com/en-us/windows/console/key-event-record-str
	WORD key_code;

	BOOL key_down;//status:up/down
	WORD hold_time;//key is being held down.

	KeyEvent(INPUT_RECORD * input_record, WORD time);
	SHORT get_key_hold_time();
	void Debug();
};

/*该类是Drawable的友元*/
class TermioApp :
	public Terminal
{
public:
	TermioApp();
	~TermioApp();

	virtual void key_event(KeyEvent term_event);
	void renderDrawables();//负责将所有drawable object渲染出来

	bool addDrawable(shared_ptr<Drawable> in_obj, bool is_visuable = true);//加入Drawable object
	bool removeDrawable(shared_ptr<Drawable> in_obj);//将规定id的对象从列表中移除
	bool setVisuable(std::string id, bool visuable_value = true);//设置对象的可见性
	
private:
	HANDLE termapp_in;//输入标识符
	std::thread event_loop;
	bool loop_flag = true;//是否停止事件循环
	std::set<shared_ptr<Drawable>> obj_list;//app已经管理的Drawable object的列表

	COORD __coord_trans(COORD in_coord, Drawable::DrawDirect direct);

	struct counter_data {
		WORD counter;
		bool flag; //表示是否应当重新计时
	};
	std::map<WORD, counter_data> inner_meta; //键盘相关
	std::pair<WORD, counter_data> tmp_pair;

	void eventloop();//类的事件处理循环:处理输入(事件)

	void __get_key_hold_time(WORD key_code, bool key_down,WORD repeat);
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

