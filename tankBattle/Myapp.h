#pragma once
#include "termgui.h"
#include "drawableobj.h"
#include <memory>
using std::shared_ptr;
using std::string;
class GameObj :public DrawableObj {
public:
	GameObj() = delete;
	GameObj(std::shared_ptr<Drawable> inDrawable)
		:DrawableObj(inDrawable),health_point(100),attack_point(100),shield_point(0){}


	void set_hp(SHORT in_hp) { health_point = in_hp; }
	void set_ap(SHORT in_ap) { attack_point = in_ap; }
	void set_sp(SHORT in_sp) { shield_point = in_sp; }
	void fresh(); //��һ֡�ж���Ϸ������ڲ����ݽ��и���
	void set_v_num(SHORT in_v_num) { v_num = in_v_num; }

	enum direct {up,down,left,right}; //����
	void set_v_direct(direct in_direct) {  v_direct = in_direct; }


private:
	SHORT health_point;//����ֵ
	SHORT attack_point;//������
	SHORT shield_point;//����ֵ
	SHORT v_num;   //�ٶ�ֵ
	direct v_direct;
};
class Myapp :
	public TermioApp
{
public:
	Myapp():TermioApp(),v_direct(Direct::Right){}
	void key_event(KeyEvent  term_event)override;//�ı�һЩ�����Ĳ�����ʹ����Ϸ���в����任
	std::shared_ptr<GameObj> add_gameobj_from_file(const std::string & filename);
	void run();
private:
	Direct v_direct; // �ٶȷ���
	SHORT v; //ÿ����ƶ��ٶ�
	SHORT v_p = 2;
	bool shoot_flag = false;
	std::vector<std::shared_ptr<GameObj>> things_list;

	void render();//��Ⱦһ֡
	void fresh();//ˢ������״̬�ĺ���

};

