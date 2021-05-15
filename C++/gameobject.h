#pragma once
#include "util.h"

//epeidh dn exoun ola ta GameObjects thn idia idiothta, ftiaxnoyme mia kainourgia gia to collide
class Collidable {
public:
	virtual Disk getCollisionHull() const = 0; //const kathws dn ephreazei kapws to antikeimeno moy, apla anaferei ena dedomeno
};

class GameObject
{
	//mas endiaferei otan dhmiourgoume gameObjects na kratame mia syndesh me to game. Auto ginetai h me reference h me pointer.
	//Edw epilegw reference gt thelw na eimai sigourh oti dn tha exw nullptr
	//protected gt prepei osoi klhronomoyn na mporoyn an to vlepoun
protected:
	const class Game& game;

public:
	GameObject(const class Game & mygame);
	virtual void update() = 0; // virtual shmainei oti to gameobject dn kanei kati apo mono toy, an thelw na kanei kati tha prepei na to ftiaksw
	virtual void draw() = 0;
	virtual void init() = 0;
};
