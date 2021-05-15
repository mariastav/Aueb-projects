#pragma once
#include "gameobject.h"
#include "graphics.h"
#include "config.h"
#include <string>

class Enemy : public GameObject, public Collidable
{
	float pos_x, pos_y;
	float speed;
	float size;
	float rotation;
	//string type;
	graphics::Brush brush;
	graphics::Brush chicken_brush;
	bool active = true;

public:
	void update() override;
	void draw() override;
	void init() override;
	bool isActive() {
		return active;
	}
	float getPosY() {
		return pos_y;
	}
	float getPosX() {
		return pos_x;
	}
	float setPosY(float y){
		pos_y = y;
	}
	float setPosX(float x) {
		pos_x = x;
	}
	Enemy(const class Game& mygame);
	~Enemy();
	Disk getCollisionHull() const override;
};