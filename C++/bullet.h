#pragma once
#include "gameobject.h"
#include "graphics.h"

class Bullet : public GameObject, public Collidable {
	float pos_x, pos_y;
	bool type;
	float bullet_size = 10;
	float speed;
	bool bullet_active = true;
	graphics::Brush bullet_br;

public:
	void update() override;
	void draw() override;
	void init() override;
	bool isActive() {
		return bullet_active;
	}
	Bullet(const class Game& mygame);
	~Bullet();
	Disk getCollisionHull() const override;
	void fire(float pos_x, float pos_y);
};
