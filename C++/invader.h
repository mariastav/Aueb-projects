#pragma once
#include "gameobject.h"
#include "graphics.h"
#include "config.h"

class Invader : public GameObject, public Collidable {
	float pos_x, pos_y;
	float size;
	//float height = 1.0f;
	float rotation;
	bool up = false;
	bool down = false;
	graphics::Brush chicken_brush;
	bool active = true;
	int velocity = 1;
	//float speed = 0.5f;

public:
	void update() override;
	void draw() override;
	void positionChicken();
	//int get(std::list<Invader> _list, int _i);
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
	float setPosY(float y) {
		pos_y = y;
		return pos_y;
	}
	float setPosX(float x) {
		pos_x = x;
		return pos_x;
	}
	Invader(const class Game& mygame);
	~Invader();
	Disk getCollisionHull() const override;
};
