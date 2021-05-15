#include "game.h"
#include "graphics.h"
#include "config.h"
#include <list>
#include <iostream>

std::list<Invader> ve;
std::list <Bullet> bl;

int blcounter = 0;
int timesPlayed = 1;
int timesDied = 0;

void Game::spawnBullet()
{
	graphics::MouseState ms;
	graphics::getMouseState(ms);

	//graphics::getKeyState(graphics::SCANCODE_SPACE)
	if (ms.button_left_pressed) {
		bullet = new Bullet(*this);
		blcounter++;
		bullet->fire(player->getPosX(), player->getPosY());
		bl.push_back(*bullet);

		std::cout << "Bullet count " << blcounter;
		graphics::playSound(std::string(ASSET_PATH) + "pew.mp3", 0.01f, false);


	}

}

void Game::checkBullet()
{
	if (bullet && !bullet->isActive()) {
		delete bullet;
		bullet = nullptr; //shmantiko gt kapoios to elegxei kai prepei na kanei kati
	}
}

void Game::spawnEgg()
{
	//int i = 0;

	if (!egg && chicken) {
		egg = new Egg(*this);
		//bull.push_back(*enemyBullet);
		for (std::list<Invader>::iterator it = ve.begin(); it != ve.end(); it++) {
			//std::cout << i ;
			egg->fireEgg(it->getPosX(), it->getPosY());
		}
		//i++;
		graphics::playSound(std::string(ASSET_PATH) + "shoot.mp3", 0.1f, false);
	}
}

void Game::checkEgg()
{
	if (egg && !egg->isActive()) {
		delete egg;
		egg = nullptr; //shmantiko gt kapoios to elegxei kai prepei na kanei kati
	}
}

void Game::spawnChicken() {

	int numberOfenemies = 14;
	int numberOfcolumns = 2;
	float j = 0; // aksona x
	float x = 1; // aksonas y
	int i = 0;

	if (!chicken && timesPlayed%2 == 0) {
		timesPlayed++;
		for (int k = 0; k <= numberOfenemies; k++) {
			chicken = new Invader(*this);
			std::cout << "Chicken Created";
			ve.push_back(*chicken);
			std::cout << "Chicken pushed";
		}

		for (std::list<Invader>::iterator it = ve.begin(); it != ve.end(); it++) {
			std::cout << "\n List " << i; //debugging

			it->setPosX((CANVAS_WIDTH - (j * 150) - 100));
			it->setPosY((CANVAS_HEIGHT / (((numberOfenemies + 1) / 3) * 2) * x) + 10);

			//debugging
			std::cout << "\n x = " << x;
			std::cout << "\n pos_y = " << it->getPosY();

			x += 2;
			if (i == 4 || i == 9) {
				j++;
				x = 1;
			}
			i++;
		}
	}
	else
	{
		status = STATUS_PLAYING_B;
	}

}

void Game::checkChicken() {
	if (chicken && !chicken->isActive()) {
		delete chicken;
		chicken = nullptr; //shmantiko gt kapoios to elegxei kai prepei na kanei kati
	}
}

void Game::spawnMeteorite()
{
	if (!meteorite) {
		meteorite = new Enemy(*this);
	}
}

//elegxw an o meteorites yparxei mesa sthn othonh moy
void Game::checkMeteorite()
{
	if (meteorite && !meteorite->isActive()) {
		delete meteorite;
		meteorite = nullptr; //shmantiko gt kapoios to elegxei kai prepei na kanei kati
	}
}

bool Game::checkCollisionPlayer_Meteorite()
{
	if (!player || !meteorite) {
		return false;
	}
	Disk d1 = player->getCollisionHull();
	Disk d2 = meteorite->getCollisionHull();

	//Collision bullet - meteorite
	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		player->drainLife(0.1f);
		return true;
	}
	return false;
}
bool Game::checkCollisionPlayer_EnemyBullet() {

	if (!player || !egg) {
		return false;
	}

	Disk d1 = player->getCollisionHull();
	Disk d2 = egg->getCollisionHull();

	//Collision player - egg
	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		player->drainLife(0.1f);
		delete egg;
		egg = nullptr;
		return true;
	}
	return false;
}
// DEN XREIAZETAI
bool Game::checkCollisionPlayer_Chicken()
{
	if (!player || !chicken) {
		return false;
	}
	for (std::list<Invader>::iterator it = ve.begin(); it != ve.end(); it++) {
		Disk d1 = player->getCollisionHull();
		Disk d2 = it->getCollisionHull();

		float dx = d1.cx - d2.cx;
		float dy = d1.cy - d2.cy;

		if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
			player->drainLife(0.1f);
			return true;
		}
	}
	return false;
}

bool Game::checkCollisionBullet_Meteorite()
{
	if (!bullet || !meteorite) {
		return false;
	}

	for (std::list<Bullet>::iterator it_b = bl.begin(); it_b != bl.end(); it_b++) {

		Disk d1 = it_b->getCollisionHull();
		Disk d2 = meteorite->getCollisionHull();

		//Collision bullet - meteorite
		float dx = d1.cx - d2.cx;
		float dy = d1.cy - d2.cy;

		if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
			delete meteorite;
			meteorite = nullptr;
			bl.erase(it_b);
			/*delete bullet;
			bullet = nullptr;*/
			return true;
		}
	}
	return false;
}

bool Game::checkCollisionBullet_Chicken()
{
	int i = 0;
	int j = 0;

	if (!bullet || !chicken) {
		return false;
	}

	for (std::list<Invader>::iterator it = ve.begin(); it != ve.end(); it++) {
		for (std::list<Bullet>::iterator it_b = bl.begin(); it_b != bl.end(); it_b++) {
			Disk d1 = it_b->getCollisionHull();
			Disk d2 = it->getCollisionHull();

			float dx = d1.cx - d2.cx;
			float dy = d1.cy - d2.cy;

			if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
				std::cout << "I = " << i;
				std::cout << "J = " << j;
				ve.erase(it);
				bl.erase(it_b);
				/*delete bullet;
				bullet = nullptr;
				return true;*/
				return true;
			}
			i++;
		}
	}
	return false;
}

void Game::updateStartScreen()
{
	/*if (graphics::getKeyState(graphics::SCANCODE_RETURN)) {
		status = STATUS_PLAYING;
		graphics::stopMusic();
	}*/

	graphics::MouseState ms;
	graphics::getMouseState(ms);

	if (ms.button_left_pressed || graphics::getKeyState(graphics::SCANCODE_RETURN)) {
		status = STATUS_PLAYING_A;
		graphics::stopMusic();
		graphics::playMusic(std::string(ASSET_PATH) + "playing.mp3", 0.04f, false);
	}
}

void Game::updateLevelAScreen()
{
	//o paikths dhmiourgeite meta apo kapoio xroniko diasthma
	if (!player_initialized) {
		//&& graphics::getGlobalTime() > 1000
		player = new Player(*this);
		player_initialized = true;
	}

	//enhmerwnw thn katastash toy paikth
	if (player) {
		player->update();
	}

	spawnChicken();
	checkChicken();

	if (chicken) {
		for (std::list<Invader>::iterator it = ve.begin(); it != ve.end(); it++) {
			it->update();
		}
	}

	checkMeteorite();
	spawnMeteorite();

	if (meteorite) {
		meteorite->update();
	}

	checkBullet();
	spawnBullet();

	if (bullet) {
		for (std::list<Bullet>::iterator it = bl.begin(); it != bl.end(); it++) {
			it->update();
		}
		//bullet->update();
	}

	checkEgg();
	spawnEgg();

	if (egg) {
		egg->update();
	}


	//tha prepei na dhmiourghsw ena efe-gameObject, to opoio tha exei kapoia zwh(ksekinaei h ekrhksh kai teleiwnei)
	if (checkCollisionPlayer_Meteorite()) {
		delete meteorite;
		meteorite = nullptr; //DEN TO KSEXNAW
	}
	if (checkCollisionPlayer_Chicken()) {
		/*delete meteorite;
		meteorite = nullptr;*/ //DEN TO KSEXNAW
	}

	if (checkCollisionPlayer_EnemyBullet()) {
		delete egg;
		egg = nullptr;
		//delete player;
		//player = nullptr;
	}

	if (checkCollisionBullet_Meteorite()) {
		score += 10;
		delete meteorite;
		meteorite = nullptr;
		delete bullet;
		bullet = nullptr;
	}
	if (checkCollisionBullet_Chicken()) {
		score += 5;
		if (ve.empty()) {
			delete chicken;
			chicken = nullptr;
		}
		if (bl.empty()) {
			delete bullet;
			bullet = nullptr;
		}
		/*delete bullet;
		bullet = nullptr;*/
	}

	if (score >= highScore) {
		highScore = score;
	}

	//If player dead, GAME OVER
	if (player_initialized && player->getRemainingLife() == 0.0f)
	{ 
		if (timesDied == 4) {
			player->resetLife();
			status = STATUS_GAMEOVER;
			graphics::playMusic(std::string(ASSET_PATH) + "gameover.mp3", 0.1f, false);
		}
		else 
		{
			player->resetLife();
			status = STATUS_PLAYING_A;
		}
	}
}

void Game::updateLevelBScreen()
{

}

void Game::updateGameOverScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_RETURN)) {
		player_initialized = false;
		player = nullptr;
		delete player;
		graphics::stopMusic();
		status = STATUS_START;
	}
}

void Game::drawStartScreen()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "logo.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT, CANVAS_WIDTH, CANVAS_WIDTH, br);
	br.texture = "";

	char info[40];
	sprintf_s(info, "Press ENTER to start"); //h sprintf mporei na prosdiorisei akrivws tis times poy blepoun
	graphics::drawText(CANVAS_WIDTH / 2.5, CANVAS_HEIGHT - 70, 30, info, br);

	graphics::MouseState ms;
	graphics::getMouseState(ms);

	//allagh
	//graphics::playSound(std::string(ASSET_PATH) + "intro.mp3", 0.05f, true); //paizei to kommati poy thelw me entash, me looping kai fading 4sec

	//graphics::drawDisk(window2canvasX(ms.cur_pos_x), window2canvasY(ms.cur_pos_y), 10, br);

}

void Game::drawLevelAScreen()
{
	//to brush to xrhsimopoio gia na bapsw
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "stars.png";
	br.outline_opacity = 0.0f;

	//paragei ena imitono periodika os pros to xrono to opoio kineitai +- canvasheight/4, etsi mporoyme na killhsoyme to background panw-katw
	float offset = CANVAS_HEIGHT * sinf(graphics::getGlobalTime() / 2000.0f) / 4;

	//ftiaxnw ena rectangle gia na tou foresw thn eikona toy background
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + offset, CANVAS_WIDTH, CANVAS_WIDTH, br);

	//draw player
	if (player) {
		player->draw();
		//std::cout << "Player Drawed";
	}
	if (meteorite) {
		meteorite->draw(); //an exw mia sullogh apo meteorites kanoume mazika updates
	}
	if (bullet) {
		for (std::list<Bullet>::iterator it = bl.begin(); it != bl.end(); it++) {
			it->draw();
		}
	}
	if (chicken) {
		for (std::list<Invader>::iterator it = ve.begin(); it != ve.end(); it++) {
			it->draw();
		}
	}
	if (egg) {
		egg->draw();
	}

	//UI/info layer
	if (player && debug_mode)
	{
		char info[40];
		sprintf_s(info, "Player pos: (%5.1f, %5.1f)", player->getPosX(), player->getPosY()); //h sprintf mporei na prosdiorisei akrivws tis times poy blepoun
		graphics::drawText(20, 20, 15, info, br);
	}

	//einai zwntanos o player? an nai, pare thn remainingLife, alliws kane thn zwh = 0
	float player_life = player ? player->getRemainingLife() : 0.0F;

	//1o rectangle me thn mpara gemismatos
	br.outline_opacity = 0.0f; //NEWWWWWWWWWWW
	br.fill_color[1] = 0.2f;
	br.fill_color[2] = 0.2f;
	br.texture = "";
	//br.fill_secondary_color[0] = 1.0f * (1.0f - player_life) + player_life * 0.2f; //mple xrwma
	//br.fill_secondary_color[1] = 0.2f;
	//br.fill_secondary_color[2] = 0.2f * (1.0f - player_life) + player_life * 1.0f;
	br.gradient = true;
	br.gradient_dir_u = 1.0f;
	br.gradient_dir_v = 0.0f;
	graphics::drawRect(CANVAS_WIDTH - 900 - ((1.0f - player_life) * 120 / 2), 30, player_life * 120, 20, br);

	//2h mpara statherh
	br.outline_opacity = 1.0f;
	br.gradient = false;
	br.fill_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH - 900, 30, 120, 20, br);

	//score
	char info[40];
	sprintf_s(info, "Score: %5.0f", score); //h sprintf mporei na prosdiorisei akrivws tis times poy blepoun
	//graphics::drawText(CANVAS_WIDTH - 900, 70, 25, info, brH);
	graphics::drawText(CANVAS_WIDTH - 830, CANVAS_HEIGHT / 13, 25, info, br);

	//Draw Heart
	float player_heart = player ? player->getRemainingHeart() : 0.0F;

	br.texture = std::string(ASSET_PATH) + "heart.png";
	br.fill_opacity = 1.0f;
	br.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH - 980 - ((1.0f - player_heart) * 120 / 2), CANVAS_HEIGHT - 20, 25, 19, br);

	//br.outline_opacity = 1.0f;
	//br.gradient = false;
	//br.fill_opacity = 0.0f;
	//graphics::drawRect(CANVAS_WIDTH - 980, 30, 25, 19, br);
	

}

void Game::drawLevelBScreen()
{
}

void Game::drawGameOverScreen()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "stars.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_WIDTH, br);

	char info[40];
	sprintf_s(info, "GAME OVER"); //h sprintf mporei na prosdiorisei akrivws tis times poy blepoun
	graphics::drawText(CANVAS_WIDTH - 640, CANVAS_HEIGHT / 2, 80, info, br);
	sprintf_s(info, "Press ENTER to start over"); //h sprintf mporei na prosdiorisei akrivws tis times poy blepoun
	graphics::drawText(250, 330, 60, info, br);
}

void Game::update()
{
	if (status == STATUS_START) {
		updateStartScreen();
	}
	else if (status == STATUS_PLAYING_A) {
		updateLevelAScreen();
	}
	else if (status == STATUS_PLAYING_B) {
		updateLevelBScreen();
	}
	else {
		updateGameOverScreen();
	}

}

void Game::draw()
{
	if (status == STATUS_START) {
		drawStartScreen();
	}
	else if (status == STATUS_PLAYING_A) {
		drawLevelAScreen();
	}
	else if (status == STATUS_PLAYING_B) {
		drawLevelBScreen();
	}
	else {
		drawGameOverScreen();
	}
}

void Game::init()
{
	graphics::setFont(std::string(ASSET_PATH) + "text1.ttf");
	graphics::playMusic(std::string(ASSET_PATH) + "intro.mp3", 0.1f, true, 4000); //paizei to kommati poy thelw me entash, me looping kai fading 4sec
	//play sound thn vazw otan thelw na paiksw ena syntomo hxo
}

float Game::window2canvasX(float x)
{
	return x * CANVAS_WIDTH / (float)window_width;
}

float Game::window2canvasY(float y)
{
	return y * CANVAS_HEIGHT / (float)window_height;
}

Game::Game()
{
}

Game::~Game()
{
	if (player)
	{
		delete player;
	}
}
