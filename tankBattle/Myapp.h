#pragma once
#include "termgui.h"
#include "drawableobj.h"
#include <memory>
using std::shared_ptr;
using std::string;
class GameObj :public DrawableObj {
public:
	GameObj() = delete;
	GameObj(std::shared_ptr<Drawable> inDrawable):DrawableObj(inDrawable){}

private:
	int health_point;//����ֵ
	int attack_point;//������
	int shield_point;//����ֵ
};

class Myapp :
	public TermioApp
{
public:
	Myapp():TermioApp(),v_direct(Direct::Right){}
	void key_event(KeyEvent  term_event)override;//�ı�һЩ�����Ĳ�����ʹ����Ϸ���в����任
	void run();
private:
	Direct v_direct; // �ٶȷ���
	SHORT v; //ÿ����ƶ��ٶ�

	void render();//��Ⱦһ֡
	void fresh();//ˢ������״̬�ĺ���

};

