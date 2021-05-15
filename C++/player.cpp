#include "player.h"
#include "graphics.h"
#include "game.h"

Player::Player(const Game& mygame)
	: GameObject(mygame)
{
}

void Player::update()
{
	//kinhsh paikth me WASD // dn vazw if-else kathws mporei na patountai tautoxrona kapoia pliktra kai gia ayto thelw na ta eleksw aneksarthta
	//A = kinhsh aristera
	if (graphics::getKeyState(graphics::SCANCODE_A)) {
		pos_x -= speed * graphics::getDeltaTime() / 10.0f;
	}
	//D = kinhsh deskia
	if (graphics::getKeyState(graphics::SCANCODE_D)) {
		pos_x += speed * graphics::getDeltaTime() / 10.0f;
	}
	//W = kinhsh panw ara meiwnw to upsos
	if (graphics::getKeyState(graphics::SCANCODE_W)) {
		pos_y -= speed * graphics::getDeltaTime() / 10.0f;
	}
	//S = kinhsh katw ara auksanw to upsos
	if (graphics::getKeyState(graphics::SCANCODE_S)) {
		pos_y += speed * graphics::getDeltaTime() / 10.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_DOWN)) {
		height -= 0.01f * graphics::getDeltaTime();
		//to vazw gia na mhn parei akraies times
		if (height < 0.1f) {
			height = 0.1f;
		}
	}
	if (graphics::getKeyState(graphics::SCANCODE_UP)) {
		height += 0.01f * graphics::getDeltaTime();
		//to vazw gia na mhn parei akraies times
		if (height > 3.0f) {
			height = 3.0f;
		}
	}

	//etsi dn afhnw ton paikth na bgei apeksw
	if (pos_x < 0) pos_x = 0;
	if (pos_x > CANVAS_WIDTH - 500) pos_x = CANVAS_WIDTH - 500;
	if (pos_y < 0) pos_y = 0;
	if (pos_y > CANVAS_HEIGHT) pos_y = CANVAS_HEIGHT;
}

void Player::draw()
{
	//etsi to kanw na anabosvinei
	float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime()/10);

	graphics::Brush br;
	br.outline_opacity = 0.0f;

	//ftiaknsw to orientantion toy spaceship
	graphics::setOrientation(-90.f);
	//graphics::setScale(height, height);
	//br.fill_opacity = 0.5f; //gia na misofainetai h skia
	//br.texture = std::string(ASSET_PATH) + "spaceship_shadow.png";
	//graphics::drawRect(pos_x-10*height, pos_y+30*3*height, 100, 100, br);

	br.fill_opacity = 1.0f; //to epanaferw
	br.texture = std::string(ASSET_PATH) + "spaceship.png";
	graphics::drawRect(pos_x, pos_y, 87, 90, br);

	graphics::resetPose(); //kanei reset kai to prosanatolismo kai to scaling

	//tha to ftiaksoyme na exei xrwmata eksw kai mesa
	br.texture = ""; //sbhnw to diasthmoploio apo to brush moy gia na epeksergastw to glow
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.5f + glow*0.5f;
	br.fill_color[2] = 0.0f;

	br.fill_secondary_color[0] = 0.3f;
	br.fill_secondary_color[1] = 0.1f;
	br.fill_secondary_color[2] = 0.0f;
	br.fill_opacity = 1.0f;
	br.fill_secondary_opacity = 0.0f;
	br.gradient = true;
	graphics::setScale(height, height);
	graphics::drawDisk(pos_x-50 * height, pos_y, 20, br);
	graphics::resetPose();

	if (game.getDebugMode()) {
		br.outline_opacity = 1.0f;
		br.texture = "";
		br.fill_color[0] = 0.3f;
		br.fill_color[1] = 1.0f;
		br.fill_color[2] = 0.3f;
		br.fill_opacity = 0.3f;
		br.gradient = false;
		Disk hull = getCollisionHull();
		graphics::drawDisk(hull.cx, hull.cy, hull.radius, br);
	}
}

void Player::init()
{
}

Disk Player::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = 45.0f;
	return disk;
}

