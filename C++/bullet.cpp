#include "bullet.h"
#include "graphics.h"
#include "game.h"

void Bullet::update()
{
	pos_x += speed * graphics::getDeltaTime(); //xronos poy mesolabhse
	
	if (pos_x < +bullet_size) {
		bullet_active = false;
	}
}

void Bullet::draw()
{
	//bullet_br.outline_opacity = 0.0f;
	//bullet_br.fill_color[0] = 1.0f; //kokkino xrwma
	//bullet_br.fill_color[1] = 0.2f;
	//bullet_br.fill_color[2] = 0.2f;
	//graphics::drawRect(pos_x, pos_y, 10, 5, bullet_br);

	bullet_br.texture = std::string(ASSET_PATH) + "bullet.png";
	bullet_br.fill_opacity = 1.0f;
	bullet_br.outline_opacity = 0.0f;
	graphics::drawRect(pos_x, pos_y, 28, 12, bullet_br);

	if (game.getDebugMode()) {
		bullet_br.outline_opacity = 1.0f;
		bullet_br.texture = "";
		bullet_br.fill_color[0] = 0.3f;
		bullet_br.fill_color[1] = 1.0f;
		bullet_br.fill_color[2] = 0.3f;
		bullet_br.fill_opacity = 0.3f;
		bullet_br.gradient = false;
		Disk hull = getCollisionHull();
		graphics::drawDisk(hull.cx, hull.cy, hull.radius, bullet_br);
	}
}

void Bullet::init()
{
	speed = 0.3f;
}


Bullet::Bullet(const Game& mygame)
	: GameObject(mygame)
{
	init();
}

Bullet::~Bullet()
{
}

Disk Bullet::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = 10.0f;
	return disk;
}

void Bullet::fire(float pos_x, float pos_y)
{
	this->pos_x = pos_x + 60;
	this->pos_y = pos_y;
}
