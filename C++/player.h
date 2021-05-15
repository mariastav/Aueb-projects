#pragma once
#include "gameobject.h"
#include "config.h"

//pairnei klhronomikothta apo thn GameObject
class Player : public GameObject, public Collidable
{
	float speed = 2.0f; //taxuthta enallaghs theshs ana deuterolepto
	float pos_x = CANVAS_WIDTH / 10, pos_y = CANVAS_HEIGHT/2; //topothesia paikth
	float height = 1.0f;
	float life = 1.0f;
	float heart = 3.0f;

public:
	Player(const class Game& mygame);
	void update() override; //override to grafw gia na deiksw oti prohlthe apo polumorfikh antikatastash
	void draw() override;
	void init() override;
	float getPosY() {
		return pos_y;
	}
	float getPosX() {
		return pos_x;
	}
	Disk getCollisionHull() const override;
	float getRemainingLife()const {
		return life;
	}
	float getRemainingHeart()const {
		return heart;
	}
	void drainLife(float amount) {
		life = std::max<float>(0.0f, life - amount);
	}
	void drainHeart(float amount) {
		heart = std::max<float>(0.0f, heart - amount);
	}
	void resetLife(){
		life = 1.0f;
	}
};