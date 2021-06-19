#pragma once
#include <memory>
#include <vector>
#include "terminal.h"
class Drawable {//图形的基类
private:
	const enum DrawDirect{Left,Right,Up,Down}; // 图形朝向的定义

	bool is_managed;// 是否已经被显示接管
	friend class TermioApp;
	friend  std::shared_ptr<Drawable> get_drawable_from_file(std::string filename);

	/* 下面是内部的数据 */

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
	void set_visualable(); // 让图形可见
	void set_unvisualable();// 让图形不可见
	
};
std::shared_ptr<Drawable> get_drawable_from_file(std::string filename);
