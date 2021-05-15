#include "egg.h"
#include "graphics.h"
#include "game.h"

void Egg::update()
{
	pos_x -= speed * graphics::getDeltaTime(); //xronos poy mesolabhse

	if (pos_x < -egg_size) {
		egg_active = false;
	}
}

void Egg::draw()
{
	egg_br.texture = std::string(ASSET_PATH) + "egg.png";
	egg_br.fill_opacity = 1.0f;
	egg_br.outline_opacity = 0.0f;
	graphics::drawRect(pos_x, pos_y, 25, 19, egg_br);

	if (game.getDebugMode()) {
		egg_br.outline_opacity = 1.0f;
		egg_br.texture = "";
		egg_br.fill_color[0] = 1.0f;
		egg_br.fill_color[1] = 0.3f;
		egg_br.fill_color[2] = 0.3f;
		egg_br.fill_opacity = 0.3f;
		egg_br.gradient = false;
		Disk hull = getCollisionHull();
		graphics::drawDisk(hull.cx, hull.cy, hull.radius, egg_br);
	}
}

void Egg::init()
{
	speed = 0.3f;
}

Egg::Egg(const Game& mygame)
	: GameObject(mygame)
{
	init();
}

Egg::~Egg()
{
}

Disk Egg::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = 10.0f;
	return disk;
}

void Egg::fireEgg(float pos_x, float pos_y)
{
		this->pos_x = pos_x - 50;
		this->pos_y = pos_y;
}
