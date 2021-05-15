#include "invader.h"
#include "graphics.h"
#include "config.h"
#include "util.h"
#include "game.h"
#include <iostream>

void Invader::update()
{	
	pos_y += velocity;

	if ((pos_y <= 35 && velocity < 0) || (pos_y >= 465 && velocity > 0)) {
		velocity = -velocity;
	}
}

void Invader::draw() {

	chicken_brush.texture = std::string(ASSET_PATH) + "chicken.png";
	chicken_brush.outline_opacity = 0.0f;
	graphics::drawRect(getPosX(), getPosY(), 60, 80, chicken_brush);

	if (game.getDebugMode()) {

		graphics::Brush br;
		br.outline_opacity = 1.0f;
		br.texture = "";
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 0.3f;
		br.fill_color[2] = 0.3f;
		br.fill_opacity = 0.3f;
		br.gradient = false;
		Disk hull = getCollisionHull();
		graphics::drawDisk(hull.cx, hull.cy, hull.radius, br);
	}
}

void Invader::positionChicken() {

}

void Invader::init()
{
	pos_x = CANVAS_WIDTH / 2;
	pos_y = CANVAS_HEIGHT / 2;

}

Invader::Invader(const Game& mygame)
	: GameObject(mygame)
{
	init();
}

Invader::~Invader()
{
}

Disk Invader::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = 32.0f;
	return disk;
}