/*��teminal������input������*/
//��Ҫһ���¼�ѭ������event loop��������event
#pragma once
#include "terminal.h"
#include <thread>
#include <vector>
#include <memory>
#include "drawable.h"
using std::shared_ptr;
struct KeyEvent {
	// �μ� https://docs.microsoft.com/en-us/windows/console/key-event-record-str
	WORD key_code;

	BOOL key_down;//status:up/down
	WORD repeat_count;//key is being held down.

	KeyEvent(INPUT_RECORD * input_record);
	void Debug();
};

/*������Drawable����Ԫ*/
class TermioApp :
	public Terminal
{
public:
	TermioApp();
	~TermioApp();

	virtual void key_event(KeyEvent term_event);
	void renderDrawables();//��������drawable object��Ⱦ����

	bool addDrawable(shared_ptr<Drawable> in_obj, bool is_visuable = true);//����Drawable object
	bool removeDrawable(std::string id);//���涨id�Ķ�����б����Ƴ�
	bool setVisuable(std::string id, bool visuable_value = true);//���ö���Ŀɼ���
	
private:
	HANDLE termapp_in;//�����ʶ��
	std::thread event_loop;
	bool loop_flag = true;//�Ƿ�ֹͣ�¼�ѭ��
	std::vector<shared_ptr<Drawable>> obj_list;//app�Ѿ������Drawable object���б�

	COORD __coord_trans(COORD in_coord, Drawable::DrawDirect direct);
	void eventloop();//����¼�����ѭ��:��������(�¼�)

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

