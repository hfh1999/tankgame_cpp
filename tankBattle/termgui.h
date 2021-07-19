/*��teminal������input������*/
//��Ҫһ���¼�ѭ������event loop��������event
#pragma once
#include "terminal.h"
#include <thread>
#include <set>
#include <map>
#include <memory>
#include "drawable.h"
using std::shared_ptr;
struct KeyEvent {
	// �μ� https://docs.microsoft.com/en-us/windows/console/key-event-record-str
	WORD key_code;

	BOOL key_down;//status:up/down
	WORD hold_time;//key is being held down.

	KeyEvent(INPUT_RECORD * input_record, WORD time);
	SHORT get_key_hold_time();
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
	bool removeDrawable(shared_ptr<Drawable> in_obj);//���涨id�Ķ�����б����Ƴ�
	bool setVisuable(std::string id, bool visuable_value = true);//���ö���Ŀɼ���
	
private:
	HANDLE termapp_in;//�����ʶ��
	std::thread event_loop;
	bool loop_flag = true;//�Ƿ�ֹͣ�¼�ѭ��
	std::set<shared_ptr<Drawable>> obj_list;//app�Ѿ������Drawable object���б�

	COORD __coord_trans(COORD in_coord, Drawable::DrawDirect direct);

	struct counter_data {
		WORD counter;
		bool flag; //��ʾ�Ƿ�Ӧ�����¼�ʱ
	};
	std::map<WORD, counter_data> inner_meta; //�������
	std::pair<WORD, counter_data> tmp_pair;

	void eventloop();//����¼�����ѭ��:��������(�¼�)

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

