#include "enemy.h"
#include "graphics.h"
#include "config.h"
#include "util.h"
#include "game.h"
#include <random>
#include <vector>

void Enemy::update()
{
	pos_x -= speed * graphics::getDeltaTime(); //xronos poy mesolabhse
	rotation += 0.05f * graphics::getDeltaTime();
	//epistrefei to ypoloipo mia float diaireshs
	rotation = fmodf(rotation, 360);

	if (pos_x < -size) {
		active = false;
	}
}

void Enemy::draw()
{
	graphics::setOrientation(rotation);
	brush.texture = std::string(ASSET_PATH) + "asteroid.png";
	brush.fill_opacity = 1.0f;
	graphics::drawRect(pos_x, pos_y, size, size, brush);
	graphics::resetPose(); //anairw ayto poy ekana prin

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

void Enemy::init()
{
	speed = 0.3f;
	//estw oti o meteoriths ksekinaei apo deskia kai erxetai pros to meros mas
	pos_x = CANVAS_WIDTH + 1.1f * size;
	//to diairw me thn RAND_MAX gia na mporesw na to kanw scale me to 0_CANVAS_HEIGHT
	pos_y = CANVAS_HEIGHT * rand0to1(); //h rand epistrefei enan arithmo metaksu to 0 kai toy max rand
	size = 50 + 100 * rand0to1();
	rotation = 360 * rand0to1();
	brush.outline_opacity = 0.0f;
}

Enemy::Enemy(const Game& mygame)
	: GameObject(mygame)
{
	/*float randNum = 10;
	for (float i = 0; i < randNum; i++) {
		Enemy* meteorite = new Enemy(*this);
	}*/
	init();
}

Enemy::~Enemy()
{
}

Disk Enemy::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = size*0.50f;
	return disk;
}
