#pragma once
#include <memory>
#include <vector>
#include "terminal.h"
#include "util.h"
class Drawable {//图形的基类
private:
	const enum DrawDirect{Up,Right,Down,Left}; // 图形朝向的定义

	friend class TermioApp;
	friend  std::shared_ptr<Drawable> get_drawable_from_file(const std::string & filename);

	/* 下面是内部的数据 */

	std::string guid;// 为了辨识drawable
	bool is_managed;// 是否已经被显示接管
	bool is_static;// 静态物体不需要重复渲染
	bool visualable;//可见性
	DrawDirect direct;//表示图形的朝向
	DrawDirect old_direct; //老朝向
	COORD origin_point;//原点坐标
	COORD old_point;
	std::vector<COORD> relative_pos;//以原点为相对位置作图
	std::vector<TermChar> content;//相应位置的符号

	const std::vector<COORD>& ReturnPos();
	const std::vector<TermChar>& Returncontent();

public:
	Drawable(std::string in_str = "");//默认创造一个空的,也可生成一个look标识(需要指定)
	Drawable(const Drawable & copy_src) :guid(generate_uuid()),is_managed(false),is_static(copy_src.is_static), visualable(copy_src.visualable),
		direct(copy_src.direct), old_direct(copy_src.old_direct), origin_point(copy_src.origin_point),
		old_point(copy_src.old_point),relative_pos(copy_src.relative_pos),content(copy_src.content)//copy structer
	{
	}
	Drawable& operator=(const Drawable &rhs) { //拷贝赋值函数
		guid = generate_uuid();
		is_managed = false;
		is_static = rhs.is_static;
		visualable = rhs.visualable;
		direct = rhs.direct;
		old_direct = rhs.old_direct;
		origin_point = rhs.origin_point;
		old_point = rhs.old_point;
		relative_pos = rhs.relative_pos;
		content = rhs.content;
	}
	//DrawableObj();//利用图形描述文件解析一个
	//void ReturnData();//一个通用的接口,返回内部数据以画图
	void turn_left();
	void turn_right();
	void turn_up();
	void turn_down();

	void move_left(SHORT step);
	void move_right(SHORT step);
	void move_up(SHORT step);
	void move_down(SHORT step);
	void move(COORD in_coord);//绝对移动
	void set_visualable(); // 让图形可见
	void set_unvisualable();// 让图形不可见
	COORD ret_coord() { return origin_point; }
	std::string ret_guid() { return guid; }
	
	void set_static(bool flag) { is_static = flag; }
};

std::shared_ptr<Drawable> get_drawable_from_file(const std::string & filename);
