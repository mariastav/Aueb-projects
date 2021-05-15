#pragma once
#include "gameobject.h"
#include "graphics.h"

class Egg : public GameObject, public Collidable {
	float pos_x, pos_y;
	bool type;
	float egg_size = 10;
	float speed;
	bool egg_active = true;
	graphics::Brush egg_br;

public:
	void update() override;
	void draw() override;
	void init() override;
	bool isActive() {
		return egg_active;
	}
	Egg(const class Game& mygame);
	~Egg();
	Disk getCollisionHull() const override;
	void fireEgg(float pos_x, float pos_y);
};

